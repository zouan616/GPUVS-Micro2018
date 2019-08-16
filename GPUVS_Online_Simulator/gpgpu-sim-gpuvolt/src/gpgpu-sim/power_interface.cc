// Copyright (c) 2009-2011, Tor M. Aamodt, Ahmed El-Shafiey, Tayler Hetherington
// The University of British Columbia
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, this
// list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
// Neither the name of The University of British Columbia nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "power_interface.h"
#include <vector>

#undef DEBUG_DEC_5
//#define DEBUG_DEC_5

// Jingwen: record the miss address
new_addr_type g_per_core_dcache_r_miss_addr[100];  
new_addr_type g_per_core_dcache_w_miss_addr[100];  
extern double g_local_predict_input[30][10];
extern double g_per_core_fpu_next_cycle_decrement[100];
extern double g_per_core_alu_next_cycle_decrement[100];
extern double g_per_core_sfu_next_cycle_decrement[100];
extern double g_per_core_ldst_next_cycle_increment[100];

extern unsigned g_per_core_memsubsys_response[100][2];
extern unsigned g_per_core_dram2core_buffer[100];

#ifndef GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE 
#define GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE 50 
#define GLOBAL_AGGREGATE_WINDOW_SIZE 50
#endif
extern double 	g_global_detection_metrics[GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE];
extern double 	g_global_per_core_waiting_warps_history[30][GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE];
extern double 	g_this_interval_per_core_warp_waiting[30];
extern unsigned	g_this_interval_per_core_warp_ready[30];
extern unsigned	g_global_per_core_ready_warps_history[30][GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE];

template<typename T>
class CircularBuffer {
	public:
		void clear() { m_buffer.clear(); m_tail=0; m_size=0; }
		void resize(unsigned size) { m_buffer.resize(size); m_tail=size-1; m_size=size;}
		unsigned size() { return m_size; }
		void enqueue( T val ) { m_tail++; if(m_tail >= m_size) m_tail=0; m_buffer[m_tail]=val; }
		const T operator[](const unsigned idx) const { return m_buffer[(idx+m_tail+1)%m_size];};
		T head() {return (*this)[0];}
		T tail() {return (*this)[m_size-1];}
	private:
		unsigned m_size, m_tail;
		std::vector<T> m_buffer;
};

// Jingwen: added variables
extern float avg_pipe_duty;
extern float per_core_pipe_duty[100];
unsigned long long mcpat_cycle_count = 0;
extern unsigned core_idle[100];
FILE * per_core_power_file = NULL;
FILE * total_power_file = NULL;

extern FILE * scheduler_stall_file[100];
extern FILE * dispatch_unit_file[100];
extern FILE * issued_exe_units_file[100];
extern FILE * warp_count_file[100];
extern FILE * warp_statu_file[100];
extern FILE * cta_activity_file[100];
extern FILE * dcache_miss_file[100];
extern FILE * ldst_dump_file[100];

extern FILE * hier_local_prediction_file[100];
extern FILE * mem_subsystem_dump_file[100];
extern FILE * mem_subsystem_buffer_count_dump_file[100];
std::vector<FILE**> dump_file_container;

std::vector<CircularBuffer<double>> throttle_synced_behavior_interval_power_history;
std::vector<double> throttle_synced_behavior_this_interval_power;


void init_mcpat(const gpgpu_sim_config &config, class gpgpu_sim_wrapper *wrapper, unsigned stat_sample_freq, unsigned tot_inst, unsigned inst){
// Jingwen: cycle by cyle power calculation
	stat_sample_freq = 1;
	wrapper->init_mcpat(config.g_power_config_name, config.g_power_filename, config.g_power_trace_filename,
	    			config.g_metric_trace_filename,config.g_steady_state_tracking_filename,config.g_power_simulation_enabled,
	    			config.g_power_trace_enabled,config.g_steady_power_levels_enabled,config.g_power_per_cycle_dump,
	    			config.gpu_steady_power_deviation,config.gpu_steady_min_period,config.g_power_trace_zlevel,
	    			tot_inst+inst,stat_sample_freq
	    			);
	wrapper->g_per_core_metric_dump = config.g_per_core_metric_dump;

}

void mcpat_cycle(const gpgpu_sim_config &config, const struct shader_core_config *shdr_config, class gpgpu_sim_wrapper *wrapper, class power_stat_t *power_stats, unsigned stat_sample_freq, unsigned tot_cycle, unsigned cycle, unsigned tot_inst, unsigned inst, kernel_info_t * kinfo){

	static bool mcpat_init=true;
	mcpat_cycle_count  += 1;



	if (cycle == 1) { // a new  kernel launch

		for(unsigned core_id = 0 ; core_id <= power_stats->m_config->num_shader(); core_id++) {
			g_per_core_fpu_next_cycle_decrement[core_id] = 0;
			g_per_core_alu_next_cycle_decrement[core_id] = 0;
			g_per_core_sfu_next_cycle_decrement[core_id] = 0;
			g_per_core_ldst_next_cycle_increment[core_id] = 0;
			g_per_core_memsubsys_response[core_id][0] = 0;
			g_per_core_memsubsys_response[core_id][1] = 0;
			g_per_core_dram2core_buffer[core_id] = 0;
			g_this_interval_per_core_warp_waiting[core_id] = 0;
			g_this_interval_per_core_warp_ready[core_id] = 0;
		}

		for ( unsigned i =0; i < GLOBAL_AGGREGATE_WINDOW_SIZE; i++ ) {
			g_global_detection_metrics[i] = 0;
			for(unsigned core_id = 0 ; core_id <= power_stats->m_config->num_shader(); core_id++) {
				g_global_per_core_waiting_warps_history[core_id][i] = 0;
				g_global_per_core_ready_warps_history[core_id][i] = 0;
			}
		}

		dump_file_container.clear();
		dump_file_container.push_back(&scheduler_stall_file[0]);
		dump_file_container.push_back(&dispatch_unit_file[0]);
		dump_file_container.push_back(&issued_exe_units_file[0]);
		dump_file_container.push_back(&warp_count_file[0]);
		dump_file_container.push_back(&warp_statu_file[0]);
		dump_file_container.push_back(&cta_activity_file[0]);
		dump_file_container.push_back(&dcache_miss_file[0]);
		dump_file_container.push_back(&hier_local_prediction_file[0]);
		dump_file_container.push_back(&mem_subsystem_dump_file[0]);
		dump_file_container.push_back(&mem_subsystem_buffer_count_dump_file[0]);

		wrapper->set_num_core(power_stats->m_config->num_shader());
		wrapper->kernel_count++;


		if ( config.enable_throttle_synced_behavior ) {
			throttle_synced_behavior_interval_power_history.resize(power_stats->m_config->num_shader());
			throttle_synced_behavior_this_interval_power.resize(power_stats->m_config->num_shader());
			for(unsigned core_id = 0 ; core_id < power_stats->m_config->num_shader(); core_id++) {
				throttle_synced_behavior_interval_power_history[core_id].clear();
				throttle_synced_behavior_interval_power_history[core_id].resize(50);
				throttle_synced_behavior_this_interval_power[core_id] = 0.0f;
			}
		}

		printf("g_per_core_metric_dump=%d\n", config.g_per_core_metric_dump);
		if (wrapper->per_kernel_per_core_power_file_opened) {

			wrapper->per_kernel_per_core_power_file_opened = 0;

  			if (wrapper->per_kernel_per_core_power_file) {
  				fclose(wrapper->per_kernel_per_core_power_file);
  				wrapper->per_kernel_per_core_power_file = NULL;
			}
  			if (wrapper->non_core_metric_file) {
  				fclose(wrapper->non_core_metric_file);
  				wrapper->non_core_metric_file = NULL;
			}
			for ( unsigned i = 0; i < power_stats->m_config->num_shader(); i++) {
  				if (wrapper->per_kernel_per_core_metric_file[i]) {
  					fclose(wrapper->per_kernel_per_core_metric_file[i]);
  					wrapper->per_kernel_per_core_metric_file[i] = NULL;
				}
			}
		}
		// print out kernel ptx to the file
		char kernel_ptx_file_name[512];
		sprintf(kernel_ptx_file_name, "kernel.%d.ptx", wrapper->kernel_count);
		FILE * kernel_ptx_file = fopen(kernel_ptx_file_name, "w");
		kinfo->print_kernel_ptx_to_file(kernel_ptx_file);
		fflush(kernel_ptx_file);
		fclose(kernel_ptx_file);

		for(unsigned core_id = 0 ; core_id <= power_stats->m_config->num_shader(); core_id++) {
			// first close all dump file if not NULL
			for  ( unsigned file_id = 0; file_id < dump_file_container.size(); file_id ++ ){
				FILE ** file_p = dump_file_container[file_id];
				if (file_p[core_id] != NULL) {
					fclose(file_p[core_id]);
					file_p[core_id] = NULL;
				}	
			}


			char scheduler_stall_file_name[512];
			sprintf(scheduler_stall_file_name, "scheduler_stall.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", scheduler_stall_file_name);
			if ( config.g_per_core_scheduler_dump ) {
				scheduler_stall_file[core_id] = fopen(scheduler_stall_file_name, "w");
				assert( scheduler_stall_file[core_id] != NULL);
			}

			char warp_count_file_name[512];
			sprintf(warp_count_file_name, "warp_count.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", warp_count_file_name);
			if ( config.g_per_core_warp_type_count_dump ) {
				warp_count_file[core_id] = fopen(warp_count_file_name, "w");
				assert( warp_count_file[core_id] != NULL);
			}

			char warp_status_file_name[512];
			sprintf(warp_status_file_name, "warp_status.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", warp_status_file_name);
			if ( config.g_per_core_warp_type_count_dump ) {
				warp_statu_file[core_id] = fopen(warp_status_file_name, "w");
				assert( warp_statu_file[core_id] != NULL);
			}

			// dispatch unit
			char dispatch_unit_file_name[512];
			sprintf(dispatch_unit_file_name, "dispatch_unit.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", dispatch_unit_file_name);
			if ( config.g_per_core_dispatch_unit_dump ) {
				dispatch_unit_file[core_id] = fopen(dispatch_unit_file_name, "w");
				assert( dispatch_unit_file[core_id] != NULL);
			}

			// issued_exe name 
			char tmp_file_name[512];
			sprintf(tmp_file_name, "issued_exe_units_ops.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", tmp_file_name);
			if ( config.g_per_core_issued_exe_units_ops_dump ) {
				issued_exe_units_file[core_id] = fopen(tmp_file_name, "w");
				assert( issued_exe_units_file[core_id] != NULL);
			}
			
			// cta activity
			sprintf(tmp_file_name, "cta_activity.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", tmp_file_name);
			if ( config.g_per_core_cta_activity) {
				cta_activity_file[core_id] = fopen(tmp_file_name, "w");
				assert( cta_activity_file[core_id] != NULL);
			}

			// dcache miss addr
			sprintf(tmp_file_name, "dcache_miss_addr.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", tmp_file_name);
			if ( config.g_per_core_cache_miss_addr_dump) {
				dcache_miss_file[core_id] = fopen(tmp_file_name, "w");
				assert( dcache_miss_file[core_id] != NULL);
			}

			// ldst unit activity
			sprintf(tmp_file_name, "ldst_unit.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", tmp_file_name);
			if ( config.g_per_core_ldst_unit_activity_dump) {
				ldst_dump_file[core_id] = fopen(tmp_file_name, "w");
				assert( ldst_dump_file[core_id] != NULL);
			}


			// local prediction
			sprintf(tmp_file_name, "hie_local_prediction.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", tmp_file_name);
			if ( config.g_dev_hier_local_prediction ) {
				hier_local_prediction_file[core_id] = fopen(tmp_file_name, "w");
				assert( hier_local_prediction_file[core_id] != NULL);
			}


			// memory subsystem
			sprintf(tmp_file_name, "mem_subsystem.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", tmp_file_name);
			if ( config.g_per_core_mem_sub_activity_dump ) {
				mem_subsystem_dump_file[core_id] = fopen(tmp_file_name, "w");
				assert( mem_subsystem_dump_file[core_id] != NULL);
			}

			// memory subsystem
			sprintf(tmp_file_name, "mem_dram2sm_buffer_count.kernel.%d.core.%d.txt", wrapper->kernel_count, core_id+1); // 0 - 14 -> 1 - 15
			printf("%s\n", tmp_file_name);
			if ( config.g_per_core_mem_sub_buffer_count_dump ) {
				mem_subsystem_buffer_count_dump_file[core_id] = fopen(tmp_file_name, "w");
				assert( mem_subsystem_buffer_count_dump_file[core_id] != NULL);
			}
		}
	}

	if(mcpat_init){ // If first cycle, don't have any power numbers yet
		mcpat_init=false;
		return;
	}

	stat_sample_freq = 1;
	float elapsed_cycles = 1;
	if ((tot_cycle+cycle) % stat_sample_freq == 0) {

		wrapper->set_inst_power(shdr_config->gpgpu_clock_gated_lanes,
				stat_sample_freq, stat_sample_freq,
				power_stats->get_total_inst(), power_stats->get_total_int_inst(),
				power_stats->get_total_fp_inst(), power_stats->get_l1d_read_accesses(),
				power_stats->get_l1d_write_accesses(), power_stats->get_committed_inst());

		// Single RF for both int and fp ops
		wrapper->set_regfile_power(power_stats->get_regfile_reads(), power_stats->get_regfile_writes(), power_stats->get_non_regfile_operands());

		//Instruction cache stats
		wrapper->set_icache_power(power_stats->get_inst_c_hits(), power_stats->get_inst_c_misses());

		//Constant Cache, shared memory, texture cache
		wrapper->set_ccache_power(power_stats->get_constant_c_hits(), power_stats->get_constant_c_misses());
		wrapper->set_tcache_power(power_stats->get_texture_c_hits(), power_stats->get_texture_c_misses());
		wrapper->set_shrd_mem_power(power_stats->get_shmem_read_access());

		wrapper->set_l1cache_power(power_stats->get_l1d_read_hits(), power_stats->get_l1d_read_misses(),
				power_stats->get_l1d_write_hits(), power_stats->get_l1d_write_misses());


		wrapper->set_l2cache_power(power_stats->get_l2_read_hits(), power_stats->get_l2_read_misses(),
				power_stats->get_l2_write_hits(), power_stats->get_l2_write_misses());


		float active_sms=(*power_stats->m_active_sms)/stat_sample_freq;
		float num_cores = shdr_config->num_shader();
		float num_idle_core = num_cores - active_sms;
		wrapper->set_idle_core_power(num_idle_core);

		//pipeline power - pipeline_duty_cycle *= percent_active_sms;
		float pipeline_duty_cycle=((*power_stats->m_average_pipeline_duty_cycle/( stat_sample_freq)) < 0.8)?((*power_stats->m_average_pipeline_duty_cycle)/stat_sample_freq):0.8;
		wrapper->set_duty_cycle_power(avg_pipe_duty);
		//fprintf(stderr, "old pipe duty = %f, new = %f\n", pipeline_duty_cycle, avg_pipe_duty);

		//Memory Controller
		wrapper->set_mem_ctrl_power(power_stats->get_dram_rd(), power_stats->get_dram_wr(), power_stats->get_dram_pre());

		// Jingwen: before calling the get_tot_FUNCTIONALUNITS_accesses, estimate the writeback of next cycle
		//Execution pipeline accesses
		//FPU (SP) accesses, Integer ALU (not present in Tesla), Sfu accesses
		power_stats->get_tot_fpu_next_cycle_decrement(elapsed_cycles);
		power_stats->get_tot_alu_next_cycle_decrement(elapsed_cycles);
		power_stats->get_tot_sfu_next_cycle_decrement(elapsed_cycles);

		for(unsigned core_id = 0 ; core_id <= power_stats->m_config->num_shader(); core_id++) {
			g_per_core_fpu_next_cycle_decrement[core_id] = power_stats->per_core_fpu_next_cycle_decrement[core_id];
			g_per_core_alu_next_cycle_decrement[core_id] = power_stats->per_core_alu_next_cycle_decrement[core_id];
			g_per_core_sfu_next_cycle_decrement[core_id] = power_stats->per_core_sfu_next_cycle_decrement[core_id];
		}
		double fpu_acc = power_stats->get_tot_fpu_accessess(elapsed_cycles);
		double ialu_acc = power_stats->get_ialu_accessess(elapsed_cycles);
		double sfu_acc = power_stats->get_tot_sfu_accessess(elapsed_cycles);
		wrapper->set_exec_unit_power(fpu_acc, ialu_acc, sfu_acc);

		//Average active lanes for sp and sfu pipelines
		float avg_sp_active_lanes=(power_stats->get_sp_active_lanes())/stat_sample_freq;
		float avg_sfu_active_lanes=(power_stats->get_sfu_active_lanes())/stat_sample_freq;
		assert(avg_sp_active_lanes<=32);
		assert(avg_sfu_active_lanes<=32);
		wrapper->set_active_lanes_power((power_stats->get_sp_active_lanes())/stat_sample_freq, (power_stats->get_sfu_active_lanes())/stat_sample_freq);


		//NoC stats (32/4)--> Number of 32 bit words in 32B block
		//unsigned l2cache_tot_access = power_stats->get_l2_read_accesses() +  power_stats->get_l2_write_accesses();
		unsigned n_icnt_simt_to_mem = power_stats->get_icnt_simt_to_mem(); // # flits from SIMT clusters to memory partitions
		unsigned n_icnt_mem_to_simt = power_stats->get_icnt_mem_to_simt(); // # flits from memory partitions to SIMT clusters
		//wrapper->set_NoC_power((double)(n_icnt_mem_to_simt + n_icnt_simt_to_mem)); // Number of flits traversing the interconnect
		wrapper->set_NoC_power(n_icnt_mem_to_simt, n_icnt_simt_to_mem); // Number of flits traversing the interconnect

		wrapper->compute();


		wrapper->update_components_power();

		float core_power=0;
		wrapper->clear_per_core_stats();
		float num_core=(float) power_stats->m_config->num_shader();
		if (1) {
		for (unsigned core_id = 0; core_id < power_stats->m_config->num_shader(); core_id++) {

			wrapper->set_core_inst_power(shdr_config->gpgpu_clock_gated_lanes,
					stat_sample_freq, stat_sample_freq,
											power_stats->get_core_inst(core_id), 
											power_stats->get_core_int_inst(core_id),
											power_stats->get_core_fp_inst(core_id), 
											power_stats->get_core_l1d_read_accesses(core_id),
											power_stats->get_core_l1d_write_accesses(core_id), 
											power_stats->get_core_committed_inst(core_id));
			wrapper->set_core_regfile_power(power_stats->get_core_regfile_reads(core_id), 
											power_stats->get_core_regfile_writes(core_id), 
											power_stats->get_core_non_regfile_operands(core_id));
			wrapper->set_core_icache_power(power_stats->get_core_inst_c_hits(core_id), 
											power_stats->get_core_inst_c_misses(core_id));
			wrapper->set_core_ccache_power(power_stats->get_core_constant_c_hits(core_id), 
											power_stats->get_core_constant_c_misses(core_id));
			wrapper->set_core_tcache_power(power_stats->get_core_texture_c_hits(core_id), 
											power_stats->get_core_texture_c_misses(core_id));
			wrapper->set_core_shrd_mem_power(power_stats->get_core_shmem_read_access(core_id));
			
			unsigned l1_r_miss=power_stats->get_core_l1d_read_misses(core_id);
			unsigned l1_w_miss=power_stats->get_core_l1d_write_misses(core_id);
			FILE * cache_miss_addr_dump_file = dcache_miss_file[core_id];
			if ( cache_miss_addr_dump_file != NULL ) {
				if ( l1_r_miss == 1 ) {
					//printf("  core %d read miss, addr %X\n", core_id, g_per_core_dcache_r_miss_addr[core_id]);
					fprintf(cache_miss_addr_dump_file, "%X ", g_per_core_dcache_r_miss_addr[core_id]);
				} else {
					fprintf(cache_miss_addr_dump_file, "0 ");
				}

				if ( l1_w_miss == 1 ) {
					fprintf(cache_miss_addr_dump_file, "%X\n", g_per_core_dcache_w_miss_addr[core_id]);
					//printf("  core %d write miss, addr %X\n", core_id, g_per_core_dcache_w_miss_addr[core_id]);
					//printf("core %d l1 write miss\n", core_id);
				} else {
					fprintf(cache_miss_addr_dump_file, "0\n");
				}
			}

			wrapper->set_core_l1cache_power(power_stats->get_core_l1d_read_hits(core_id), 
											power_stats->get_core_l1d_read_misses(core_id),
											power_stats->get_core_l1d_write_hits(core_id), 
											power_stats->get_core_l1d_write_misses(core_id));
			wrapper->set_core_l2cache_power(power_stats->get_l2_read_hits()/num_core, 
											power_stats->get_l2_read_misses()/num_core,
											power_stats->get_l2_write_hits()/num_core, 
											power_stats->get_l2_write_misses()/num_core);
			wrapper->set_core_idle_core_power(core_idle[core_id]);
			wrapper->set_core_duty_cycle_power(per_core_pipe_duty[core_id]);
			//wrapper->set_core_duty_cycle_power(pipeline_duty_cycle/num_core);
			wrapper->set_core_mem_ctrl_power(power_stats->get_dram_rd()/num_core, 
											power_stats->get_dram_wr()/num_core, 
											power_stats->get_dram_pre()/num_core);

			
			double fpu_acc = power_stats->get_core_fpu_accessess(core_id, elapsed_cycles);
			double ialu_acc = power_stats->get_core_ialu_accessess(core_id, elapsed_cycles);
			double sfu_acc = power_stats->get_core_sfu_accessess(core_id, elapsed_cycles);
			g_local_predict_input[core_id][1] += ialu_acc;
			g_local_predict_input[core_id][2] += fpu_acc;
			g_local_predict_input[core_id][3] += sfu_acc;
			wrapper->set_core_exec_unit_power(fpu_acc, ialu_acc, sfu_acc);
											
			float avg_sp_active_lanes=(power_stats->get_sp_active_lanes())/stat_sample_freq;
			float avg_sfu_active_lanes=(power_stats->get_sfu_active_lanes())/stat_sample_freq;
			assert(avg_sp_active_lanes<=32);
			assert(avg_sfu_active_lanes<=32);
			wrapper->set_core_active_lanes_power((power_stats->get_sp_active_lanes())/stat_sample_freq,
											(power_stats->get_sfu_active_lanes())/stat_sample_freq);
			unsigned n_icnt_simt_to_mem = power_stats->get_icnt_simt_to_mem(); // # flits from SIMT clusters to memory partitions
			unsigned n_icnt_mem_to_simt = power_stats->get_icnt_mem_to_simt(); // # flits from memory partitions to SIMT clusters
			wrapper->set_core_NoC_power(n_icnt_mem_to_simt/num_core, 
										n_icnt_simt_to_mem/num_core); // Number of flits traversing the interconnect
			wrapper->core_compute(core_id);
			//core_power+=wrapper->core_proc->core.rt_power.readOp.dynamic;
			core_power+=wrapper->per_core_power_record[core_id];
			//wrapper->record_core_power(core_id);
		
			if ( config.enable_throttle_synced_behavior ) {
				if ( cycle % config.throttle_synced_behavior_averaging_power_window == 0) {
					throttle_synced_behavior_interval_power_history[core_id].enqueue(throttle_synced_behavior_this_interval_power[core_id]/config.throttle_synced_behavior_averaging_power_window);
#ifdef DEBUG_DEC_5
					if ( core_id == 0 ) {
						printf("%d-cycle avg power core (%d): %.4f - %.4f\n",  config.throttle_synced_behavior_averaging_power_window, core_id,  throttle_synced_behavior_interval_power_history[core_id].tail(), throttle_synced_behavior_this_interval_power[core_id]/config.throttle_synced_behavior_averaging_power_window);
					}
#endif
					throttle_synced_behavior_this_interval_power[core_id] = 0;
				} 

				throttle_synced_behavior_this_interval_power[core_id] += wrapper->per_core_power_record[core_id];
#ifdef DEBUG_DEC_5
				if ( core_id == 0 ) {
					printf("cycle by cycle @ %d power: core (%d): %.4f\n", cycle, core_id, wrapper->per_core_power_record[core_id]);
				}
#endif
			}
		}
		}
		wrapper->check_per_core_stats();

		// Jingwen: check each core's averaging power 
		if ( config.enable_throttle_synced_behavior ) {
			double power_delta_threshold = 3.0f; // Watt
			if ( cycle % config.throttle_synced_behavior_averaging_power_window == 0 && cycle > 3000) {
				unsigned num_core_power_increasing = 0;
				unsigned num_core_power_decreasing = 0;
				for (unsigned core_id = 0; core_id < power_stats->m_config->num_shader(); core_id++) {
					unsigned buffer_size=throttle_synced_behavior_interval_power_history[core_id].size();
					if( throttle_synced_behavior_interval_power_history[core_id][buffer_size-2] < 
						(throttle_synced_behavior_interval_power_history[core_id][buffer_size-1] - power_delta_threshold ) ) {
						num_core_power_increasing ++;	
					}
					if( throttle_synced_behavior_interval_power_history[core_id][buffer_size-2] > 
						(throttle_synced_behavior_interval_power_history[core_id][buffer_size-1]+ power_delta_threshold ) ) {
						num_core_power_decreasing ++;	
					}
				}
				if ( num_core_power_increasing  > 0  || num_core_power_decreasing ) {
					printf("@ cycle %d, cores # increasing vs decreasing: %d - %d\n", cycle, num_core_power_increasing, num_core_power_decreasing);
				}
			}
		}
                //An Zou: close power mismatch check
		//assert("Per core power doesn't match!" && wrapper->sanity_check(wrapper->proc->core.rt_power.readOp.dynamic, core_power));
		double orginal_processor_core_power = wrapper->proc->core.rt_power.readOp.dynamic;
 		orginal_processor_core_power += ( wrapper->proc->mc->frontend->PRT->power_t.readOp.dynamic + wrapper->proc->mc->frontend->threadMasks->power_t.readOp.dynamic+ wrapper->proc->mc->frontend->PRC->power_t.readOp.dynamic)/(wrapper->proc->cores[0]->executionTime); // mcl
		//if ( !wrapper->sanity_check(orginal_processor_core_power, core_power)) {
			//fprintf(stderr, "ERROR, Per core power doesn't match!\n");
			//fprintf(stderr, "processor core power %f, sum of other cores %f\n", orginal_processor_core_power, core_power);
			//for(unsigned i = 0; i<num_core; i++) {
			//	fprintf(stderr, "%.2f ", wrapper->per_core_power_record[i]);
			//}
			//fprintf(stderr, "\n");
		//}

		// dump per core power file
		if (per_core_power_file  == NULL) 
			per_core_power_file  = fopen("per_core_power_record.txt", "w"); 
		assert(per_core_power_file  != NULL);
		//Modified by An Zou
                wrapper->print_per_core_power(per_core_power_file);
                fflush(per_core_power_file);
		//wrapper->print_per_core_power();

		// dumpe total power number
		Processor * proc = wrapper->proc;
		double static_pwr_t=(proc->XML->sys.longer_channel_device? proc->power.readOp.longer_channel_leakage:proc->power.readOp.leakage)+proc->power.readOp.gate_leakage;
		double tot_pwr_t = static_pwr_t + proc->rt_power.readOp.dynamic;
		if (total_power_file  == NULL) 
			total_power_file  = fopen("processor_power_record.txt", "w"); 
		assert(total_power_file  != NULL);
		fprintf(total_power_file, "%5.3f\n", tot_pwr_t);
		static unsigned print_count = 0; 
		print_count ++;

		// flush
		if ( print_count % 1 == 0 ) {
			fflush(total_power_file);
			print_count = 0;
			for(unsigned core_id = 0 ; core_id <= power_stats->m_config->num_shader(); core_id++) {
				for  ( unsigned file_id = 0; file_id < dump_file_container.size(); file_id ++ ){
					FILE ** file_p = dump_file_container[file_id];
					if (file_p[core_id] != NULL) {
						fflush(file_p[core_id]);
					}	
				}

			}

		}

		wrapper->print_trace_files();
		power_stats->save_stats();

		wrapper->detect_print_steady_state(0,tot_inst+inst);

		wrapper->power_metrics_calculations();


		wrapper->dump();
	}
	//wrapper->close_files();
}

void mcpat_reset_perf_count(class gpgpu_sim_wrapper *wrapper, bool do_print){
	wrapper->reset_counters(do_print);
}
