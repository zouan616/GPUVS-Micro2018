// Copyright (c) 2009-2011, Tor M. Aamodt, Wilson W.L. Fung, George L. Yuan,
// Ali Bakhoda, Andrew Turner, Ivan Sham
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


#include "gpu-sim.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include "zlib.h"


#include "shader.h"
#include "dram.h"
#include "mem_fetch.h"

#include <time.h>
#include "gpu-cache.h"
#include "gpu-misc.h"
#include "delayqueue.h"
#include "shader.h"
#include "icnt_wrapper.h"
#include "dram.h"
#include "addrdec.h"
#include "stat-tool.h"
#include "l2cache.h"

#include "../cuda-sim/ptx-stats.h"
#include "../cuda-sim/ptx_ir.h"
#include "../intersim/statwraper.h"
#include "../intersim/interconnect_interface.h"
#include "../abstract_hardware_model.h"
#include "../debug.h"
#include "../gpgpusim_entrypoint.h"
#include "../cuda-sim/cuda-sim.h"
#include "../trace.h"
#include "mem_latency_stat.h"
#include "power_stat.h"
#include "visualizer.h"
#include "stats.h"


#include <assert.h>
#include <string.h>
#include <signal.h>
#include "sharedspice.h"
#include <dlfcn.h> /* to load libraries*/
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <fstream>



#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <my_shared_mem.h>

//defined by An Zou

using namespace std;

typedef void *  funptr_t;
funptr_t dlsym (void *, const char *);

#define true 1
#define false 0
//#define RTLD_LAZY	1	/* lazy function call binding */
//#define RTLD_NOW	2	/* immediate function call binding */
//#define RTLD_GLOBAL	4	/* symbols in this dlopen'ed obj are visible to other dlopen'ed objs */


funptr_t ngSpice_Init_handle = NULL;
funptr_t ngSpice_Command_handle = NULL;
funptr_t ngSpice_Circ_handle = NULL;
funptr_t ngSpice_CurPlot_handle = NULL;
funptr_t ngSpice_AllVecs_handle = NULL;
funptr_t ngSpice_GVI_handle = NULL;


/* callback functions used by ngspice */
int ng_getchar(char* outputreturn, int ident, void* userdata);

int ng_getstat(char* outputreturn, int ident, void* userdata);

int ng_thread_runs(bool noruns, int ident, void* userdata);

bool no_bg = true;
bool not_yet = true;
bool will_unload = false;
int cieq(const char *p, const char *s);
int vecgetnumber = 0;
double v2dat;
static bool has_break = false;

int i;
char ** circarray;
char **vecarray;

ControlledExit ng_exit;
SendData ng_data;
SendInitData ng_initdata;








#ifdef GPGPUSIM_POWER_MODEL
#include "power_interface.h"
extern float avg_pipe_duty;
extern float per_core_pipe_duty[100];
unsigned core_idle[100];
#else
class  gpgpu_sim_wrapper {};
#endif

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>

#define MAX(a,b) (((a)>(b))?(a):(b))


//AnZou:
extern int core_num;
extern int issue_request[2][15];
extern int power_mode;
extern float power_width_10cycle[16];
int last_0_cycle;
int zero_request_counter;

//An Zou: DVFS
extern double SM_issued_last_cycle[16];
extern double SM_freq[16];
extern double total_has_issued;
extern double SM_remaining[16];
double total_inst =  67500;
double total_cycle = 50000;
int DVFS_freq = 150;
extern double accumulate[16];
extern double DVFS_mask[16];
double issue_accumulate[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int fd;
struct my_shared_memory *ptr;
int date_update_frequency = 1;



extern FILE * cta_activity_file[100];
extern addr_t g_kernel_start_pc;


bool g_interactive_debugger_enabled=false;

extern gpgpu_sim_config g_the_gpu_config;

unsigned long long  gpu_sim_cycle = 0;
unsigned long long  gpu_tot_sim_cycle = 0;
unsigned long long  cycles_since_last_issued_thread_block=999999;
unsigned long long  g_last_issued_sm_id=0;


// performance counter for stalls due to congestion.
unsigned int gpu_stall_dramfull = 0;
unsigned int gpu_stall_icnt2sh = 0;

// Jingwen: memeory subsystem dump file and counter
extern FILE * mem_subsystem_dump_file[100];
extern FILE * mem_subsystem_buffer_count_dump_file[100];
extern unsigned g_per_core_memsubsys_response[100][2];
extern unsigned g_per_core_dram2core_buffer[100];

// Jingwen: local prediction input
extern FILE * hier_local_prediction_file[100];

extern double g_local_predict_input[30][10];
extern double g_local_throttle_net_budget[100];
extern double g_local_throttle_increment_budget[100];

extern double g_per_core_alu_next_cycle_decrement[100];
extern double g_per_core_alu_this_cycle_increment[100];
extern double g_per_core_alu_this_cycle_decrement[100];

extern double g_per_core_fpu_next_cycle_decrement[100];
extern double g_per_core_fpu_this_cycle_increment[100];
extern double g_per_core_fpu_this_cycle_decrement[100];

extern double g_per_core_sfu_next_cycle_decrement[100];
extern double g_per_core_sfu_this_cycle_increment[100];
extern double g_per_core_sfu_this_cycle_decrement[100];

extern double g_per_core_ldst_this_cycle_increment[100];
extern double g_per_core_ldst_next_cycle_increment[100];

extern double g_per_core_local_increment[100];

double g_tmp_history_val[10];
#define LOCAL_THROTTLE_HISTORY_WINDOW_SIZE 10
double g_local_predict_weighted_input_per_core[30][LOCAL_THROTTLE_HISTORY_WINDOW_SIZE];
// Moved following two defines to power_interface.h
//#define GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE 50
//#define GLOBAL_AGGREGATE_WINDOW_SIZE 50
#define GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE 50
#define GLOBAL_AGGREGATE_WINDOW_SIZE 50
double 		g_global_detection_metrics[GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE];
double 		g_this_interval_per_core_warp_waiting[30];
double 		g_global_per_core_waiting_warps_history[30][GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE];

unsigned 	g_this_interval_per_core_warp_ready[30];
unsigned 	g_global_per_core_ready_warps_history[30][GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE];

bool 		g_global_throttle_flag;
unsigned 	g_global_throttle_duration;

bool 		g_global_throttle_issue_warp_flag;
unsigned 	g_global_throttle_issue_warp_duration;

/* -------------------------------------------- */
// Jingwen: types of global states
typedef enum GlobalDetectionState {
  GlobalDetectionState_NONE = 0,
  GlobalDetectionState_PRE,
  GlobalDetectionState_ACTION,
  GlobalDetectionState_COUNT,
} GlobalDetectionState;
GlobalDetectionState g_global_detection_state;
GlobalDetectionState g_global_detection_state_ready_warp;


/* Clock Domains */

#define  CORE  0x01
#define  L2    0x02
#define  DRAM  0x04
#define  ICNT  0x08


#define MEM_LATENCY_STAT_IMPL




#include "mem_latency_stat.h"

void power_config::reg_options(class OptionParser * opp)
{


	  option_parser_register(opp, "-gpuwattch_xml_file", OPT_CSTR,
			  	  	  	  	 &g_power_config_name,"GPUWattch XML file",
	                   "gpuwattch.xml");

	   option_parser_register(opp, "-power_simulation_enabled", OPT_BOOL,
	                          &g_power_simulation_enabled, "Turn on power simulator (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-power_per_cycle_dump", OPT_BOOL,
	                          &g_power_per_cycle_dump, "Dump detailed power output each cycle",
	                          "0");

	   // Output Data Formats
	   option_parser_register(opp, "-power_trace_enabled", OPT_BOOL,
	                          &g_power_trace_enabled, "produce a file for the power trace (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-power_trace_zlevel", OPT_INT32,
	                          &g_power_trace_zlevel, "Compression level of the power trace output log (0=no comp, 9=highest)",
	                          "6");

	   option_parser_register(opp, "-steady_power_levels_enabled", OPT_BOOL,
	                          &g_steady_power_levels_enabled, "produce a file for the steady power levels (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-steady_state_definition", OPT_CSTR,
			   	  &gpu_steady_state_definition, "allowed deviation:number of samples",
	                 	  "8:4");

	   option_parser_register(opp, "-per_core_metric_dump", OPT_BOOL,
	                          &g_per_core_metric_dump, "Turn on power simulator (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-per_core_scheduler_dump", OPT_BOOL,
	                          &g_per_core_scheduler_dump, "Turn on scheduler activity dump (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-per_core_warp_type_count_dump", OPT_BOOL,
	                          &g_per_core_warp_type_count_dump, "Turn on warp type count dump (1=On, 0=Off)",
	                          "0");
	   option_parser_register(opp, "-per_core_dispatch_unit_dump", OPT_BOOL,
	                          &g_per_core_dispatch_unit_dump, "Turn on dispatch unit activity dump (1=On, 0=Off)",
	                          "0");
	   option_parser_register(opp, "-per_core_issued_exe_units_ops_dump", OPT_BOOL,
	                          &g_per_core_issued_exe_units_ops_dump, "Turn on issued ops activity dump (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-per_core_cta_activity", OPT_BOOL,
	                          &g_per_core_cta_activity, "Turn on/off per core cta activity dump (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-per_core_cache_miss_addr_dump", OPT_BOOL,
	                          &g_per_core_cache_miss_addr_dump, "Turn on/off per core cache miss addr dump (1=On, 0=Off)",
	                          "0");
	   option_parser_register(opp, "-per_core_ldst_unit_activity_dump", OPT_BOOL,
	                          &g_per_core_ldst_unit_activity_dump, "Turn on/off per core ldst unit activity dump (1=On, 0=Off)",
	                          "0");
	   option_parser_register(opp, "-per_core_mem_sub_activity_dump", OPT_BOOL,
	                          &g_per_core_mem_sub_activity_dump, "Turn on/off per core memory subsystem dump (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-per_core_mem_sub_buffer_count_dump", OPT_BOOL,
	                          &g_per_core_mem_sub_buffer_count_dump, "Turn on/off per core memory subsystem buffer counts dump (1=On, 0=Off)",
	                          "0");

	   // for throttling register file
	   option_parser_register(opp, "-throttle_regs_enabled", OPT_BOOL,
	                          &g_throttle_regs_enabled, "Turn of register file throttling (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-throttle_reg_interval_size", OPT_INT32,
	                          &g_throttle_reg_interval_size, "throttlin reg file interval",
	                          "0");

	   option_parser_register(opp, "-throttle_regs_ratio", OPT_CSTR,
			   	  &g_throttle_regs_ratio_str, "throttle reg ratio",
	                 	  "1");

	   // for throttling the FPU
	   option_parser_register(opp, "-g_throttle_fpu_enable", OPT_BOOL,
	                          &g_throttle_fpu_enable, "Turn of FPU throttling (1=On, 0=Off)",
	                          "0");
	   option_parser_register(opp, "-g_throttle_fpu_delta", OPT_INT32,
	                          &g_throttle_fpu_delta, "throttlin FPU detla",
	                          "0");
	   option_parser_register(opp, "-g_throttle_fpu_interval_size", OPT_INT32,
	                          &g_throttle_fpu_interval_size, "throttlin FPU interval size",
	                          "0");
	   option_parser_register(opp, "-g_throttle_fpu_averaging_interval_size", OPT_INT32,
	                          &g_throttle_fpu_averaging_interval_size, "throttlin FPU averaging interval size",
	                          "0");


	   option_parser_register(opp, "-throttle_thread_block_issue", OPT_BOOL,
	                          &throttle_thread_block_issue, "Turn off thread block (CTA) throttling (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-throttle_thread_block_issue_interval", OPT_INT32,
	                          &throttle_thread_block_issue_interval, "CTA issuing interval",
	                          "0");

	   option_parser_register(opp, "-enable_throttle_synced_behavior", OPT_BOOL,
	                          &enable_throttle_synced_behavior, "Turn off syned behavior detection and throttling (1=On, 0=Off)",
	                          "0");

	   option_parser_register(opp, "-throttle_synced_behavior_averaging_power_window", OPT_INT32,
	                          &throttle_synced_behavior_averaging_power_window, "synced behavior detection window",
	                          "0");

	   option_parser_register(opp, "-throttle_synced_behavior_delay_window", OPT_INT32,
	                          &throttle_synced_behavior_delay_window, "synced behavior delay window",
	                          "0");

		// for developing hierarchical thorrottling
	   option_parser_register(opp, "-dev_hier_local_prediction", OPT_BOOL,
	                          &g_dev_hier_local_prediction, "Turn on/off local droop prediction (1=On, 0=Off)",
	                          "0");
	   // for enableing hierarchical local thorrottling
	   option_parser_register(opp, "-dev_hier_local_throttle", OPT_BOOL,
	                          &g_dev_hier_local_throttle, "Turn on/off local droop throttling (1=On, 0=Off)",
	                          "0");
	   option_parser_register(opp, "-dev_hier_local_throttle_threshold_str", OPT_CSTR,
			   	  &g_dev_hier_local_throttle_threshold_str, "local throttle threshold",
	                 	  "1");
	   option_parser_register(opp, "-dev_hier_global_throttle", OPT_BOOL,
	                          &g_dev_hier_global_throttle, "Turn on/off global droop throttling (1=On, 0=Off)",
	                          "0");
	   option_parser_register(opp, "-dev_hier_global_throttle_per_core_quantum", OPT_INT32,
	                          &g_dev_hier_global_throttle_per_core_quantum, "per core quantum if global throttle is active",
	                          "0");
	   option_parser_register(opp, "-dev_hier_global_throttle_per_core_issue_quantum", OPT_INT32,
	                          &g_dev_hier_global_throttle_per_core_issue_quantum, "per core quantum for warp issuing if global throttle is active",
	                          "0");
}

void memory_config::reg_options(class OptionParser * opp)
{
    option_parser_register(opp, "-gpgpu_dram_scheduler", OPT_INT32, &scheduler_type,
                                "0 = fifo, 1 = FR-FCFS (defaul)", "1");
    option_parser_register(opp, "-gpgpu_dram_partition_queues", OPT_CSTR, &gpgpu_L2_queue_config,
                           "i2$:$2d:d2$:$2i",
                           "8:8:8:8");

    option_parser_register(opp, "-l2_ideal", OPT_BOOL, &l2_ideal,
                           "Use a ideal L2 cache that always hit",
                           "0");
    option_parser_register(opp, "-gpgpu_cache:dl2", OPT_CSTR, &m_L2_config.m_config_string,
                   "unified banked L2 data cache config "
                   " {<nsets>:<bsize>:<assoc>,<rep>:<wr>:<alloc>:<wr_alloc>,<mshr>:<N>:<merge>,<mq>}",
                   "64:128:8,L:B:m:N,A:16:4,4");
    option_parser_register(opp, "-gpgpu_cache:dl2_texture_only", OPT_BOOL, &m_L2_texure_only,
                           "L2 cache used for texture only",
                           "1");
    option_parser_register(opp, "-gpgpu_n_mem", OPT_UINT32, &m_n_mem,
                 "number of memory modules (e.g. memory controllers) in gpu",
                 "8");
    option_parser_register(opp, "-gpgpu_n_mem_per_ctrlr", OPT_UINT32, &gpu_n_mem_per_ctrlr,
                 "number of memory chips per memory controller",
                 "1");
    option_parser_register(opp, "-gpgpu_memlatency_stat", OPT_INT32, &gpgpu_memlatency_stat,
                "track and display latency statistics 0x2 enables MC, 0x4 enables queue logs",
                "0");
    option_parser_register(opp, "-gpgpu_frfcfs_dram_sched_queue_size", OPT_INT32, &gpgpu_frfcfs_dram_sched_queue_size,
                "0 = unlimited (default); # entries per chip",
                "0");
    option_parser_register(opp, "-gpgpu_dram_return_queue_size", OPT_INT32, &gpgpu_dram_return_queue_size,
                "0 = unlimited (default); # entries per chip",
                "0");
    option_parser_register(opp, "-gpgpu_dram_buswidth", OPT_UINT32, &busW,
                 "default = 4 bytes (8 bytes per cycle at DDR)",
                 "4");
    option_parser_register(opp, "-gpgpu_dram_burst_length", OPT_UINT32, &BL,
                 "Burst length of each DRAM request (default = 4 data bus cycle)",
                 "4");
    option_parser_register(opp, "-dram_data_command_freq_ratio", OPT_UINT32, &data_command_freq_ratio,
                 "Frequency ratio between DRAM data bus and command bus (default = 2 times, i.e. DDR)",
                 "2");
    option_parser_register(opp, "-gpgpu_dram_timing_opt", OPT_CSTR, &gpgpu_dram_timing_opt,
                "DRAM timing parameters = {nbk:tCCD:tRRD:tRCD:tRAS:tRP:tRC:CL:WL:tCDLR:tWR:nbkgrp:tCCDL:tRTPL}",
                "4:2:8:12:21:13:34:9:4:5:13:1:0:0");
    option_parser_register(opp, "-rop_latency", OPT_UINT32, &rop_latency,
                     "ROP queue latency (default 85)",
                     "85");
    option_parser_register(opp, "-dram_latency", OPT_UINT32, &dram_latency,
                     "DRAM latency (default 30)",
                     "30");

    m_address_mapping.addrdec_setoption(opp);
}

void shader_core_config::reg_options(class OptionParser * opp)
{
    option_parser_register(opp, "-gpgpu_simd_model", OPT_INT32, &model,
                   "1 = post-dominator", "1");
    option_parser_register(opp, "-gpgpu_shader_core_pipeline", OPT_CSTR, &gpgpu_shader_core_pipeline_opt,
                   "shader core pipeline config, i.e., {<nthread>:<warpsize>}",
                   "1024:32");
    option_parser_register(opp, "-gpgpu_tex_cache:l1", OPT_CSTR, &m_L1T_config.m_config_string,
                   "per-shader L1 texture cache  (READ-ONLY) config "
                   " {<nsets>:<bsize>:<assoc>,<rep>:<wr>:<alloc>:<wr_alloc>,<mshr>:<N>:<merge>,<mq>:<rf>}",
                   "8:128:5,L:R:m:N,F:128:4,128:2");
    option_parser_register(opp, "-gpgpu_const_cache:l1", OPT_CSTR, &m_L1C_config.m_config_string,
                   "per-shader L1 constant memory cache  (READ-ONLY) config "
                   " {<nsets>:<bsize>:<assoc>,<rep>:<wr>:<alloc>:<wr_alloc>,<mshr>:<N>:<merge>,<mq>} ",
                   "64:64:2,L:R:f:N,A:2:32,4" );
    option_parser_register(opp, "-gpgpu_cache:il1", OPT_CSTR, &m_L1I_config.m_config_string,
                   "shader L1 instruction cache config "
                   " {<nsets>:<bsize>:<assoc>,<rep>:<wr>:<alloc>:<wr_alloc>,<mshr>:<N>:<merge>,<mq>} ",
                   "4:256:4,L:R:f:N,A:2:32,4" );
    option_parser_register(opp, "-gpgpu_cache:dl1", OPT_CSTR, &m_L1D_config.m_config_string,
                   "per-shader L1 data cache config "
                   " {<nsets>:<bsize>:<assoc>,<rep>:<wr>:<alloc>:<wr_alloc>,<mshr>:<N>:<merge>,<mq> | none}",
                   "none" );
    option_parser_register(opp, "-gpgpu_perfect_mem", OPT_BOOL, &gpgpu_perfect_mem,
                 "enable perfect memory mode (no cache miss)",
                 "0");
    option_parser_register(opp, "-n_regfile_gating_group", OPT_UINT32, &n_regfile_gating_group,
                 "group of lanes that should be read/written together)",
                 "4");
    option_parser_register(opp, "-gpgpu_clock_gated_reg_file", OPT_BOOL, &gpgpu_clock_gated_reg_file,
                 "enable clock gated reg file for power calculations",
                 "0");
    option_parser_register(opp, "-gpgpu_clock_gated_lanes", OPT_BOOL, &gpgpu_clock_gated_lanes,
                 "enable clock gated lanes for power calculations",
                 "0");
    option_parser_register(opp, "-gpgpu_shader_registers", OPT_UINT32, &gpgpu_shader_registers,
                 "Number of registers per shader core. Limits number of concurrent CTAs. (default 8192)",
                 "8192");
    option_parser_register(opp, "-gpgpu_shader_cta", OPT_UINT32, &max_cta_per_core,
                 "Maximum number of concurrent CTAs in shader (default 8)",
                 "8");
    option_parser_register(opp, "-gpgpu_n_clusters", OPT_UINT32, &n_simt_clusters,
                 "number of processing clusters",
                 "10");
    option_parser_register(opp, "-gpgpu_n_cores_per_cluster", OPT_UINT32, &n_simt_cores_per_cluster,
                 "number of simd cores per cluster",
                 "3");
    option_parser_register(opp, "-gpgpu_n_cluster_ejection_buffer_size", OPT_UINT32, &n_simt_ejection_buffer_size,
                 "number of packets in ejection buffer",
                 "8");
    option_parser_register(opp, "-gpgpu_n_ldst_response_buffer_size", OPT_UINT32, &ldst_unit_response_queue_size,
                 "number of response packets in ld/st unit ejection buffer",
                 "2");
    option_parser_register(opp, "-gpgpu_shmem_size", OPT_UINT32, &gpgpu_shmem_size,
                 "Size of shared memory per shader core (default 16kB)",
                 "16384");
    option_parser_register(opp, "-gpgpu_shmem_num_banks", OPT_UINT32, &num_shmem_bank,
                 "Number of banks in the shared memory in each shader core (default 16)",
                 "16");
    option_parser_register(opp, "-gpgpu_shmem_limited_broadcast", OPT_BOOL, &shmem_limited_broadcast,
                 "Limit shared memory to do one broadcast per cycle (default on)",
                 "1");
    option_parser_register(opp, "-gpgpu_shmem_warp_parts", OPT_INT32, &mem_warp_parts,
                 "Number of portions a warp is divided into for shared memory bank conflict check ",
                 "2");
    option_parser_register(opp, "-gpgpu_warpdistro_shader", OPT_INT32, &gpgpu_warpdistro_shader,
                "Specify which shader core to collect the warp size distribution from",
                "-1");
    option_parser_register(opp, "-gpgpu_warp_issue_shader", OPT_INT32, &gpgpu_warp_issue_shader,
                "Specify which shader core to collect the warp issue distribution from",
                "0");
    option_parser_register(opp, "-gpgpu_local_mem_map", OPT_BOOL, &gpgpu_local_mem_map,
                "Mapping from local memory space address to simulated GPU physical address space (default = enabled)",
                "1");
    option_parser_register(opp, "-gpgpu_num_reg_banks", OPT_INT32, &gpgpu_num_reg_banks,
                "Number of register banks (default = 8)",
                "8");
    option_parser_register(opp, "-gpgpu_reg_bank_use_warp_id", OPT_BOOL, &gpgpu_reg_bank_use_warp_id,
             "Use warp ID in mapping registers to banks (default = off)",
             "0");
    option_parser_register(opp, "-gpgpu_operand_collector_num_units_sp", OPT_INT32, &gpgpu_operand_collector_num_units_sp,
                "number of collector units (default = 4)",
                "4");
    option_parser_register(opp, "-gpgpu_operand_collector_num_units_sfu", OPT_INT32, &gpgpu_operand_collector_num_units_sfu,
                "number of collector units (default = 4)",
                "4");
    option_parser_register(opp, "-gpgpu_operand_collector_num_units_mem", OPT_INT32, &gpgpu_operand_collector_num_units_mem,
                "number of collector units (default = 2)",
                "2");
    option_parser_register(opp, "-gpgpu_operand_collector_num_units_gen", OPT_INT32, &gpgpu_operand_collector_num_units_gen,
                "number of collector units (default = 0)",
                "0");
    option_parser_register(opp, "-gpgpu_operand_collector_num_in_ports_sp", OPT_INT32, &gpgpu_operand_collector_num_in_ports_sp,
                           "number of collector unit in ports (default = 1)",
                           "1");
    option_parser_register(opp, "-gpgpu_operand_collector_num_in_ports_sfu", OPT_INT32, &gpgpu_operand_collector_num_in_ports_sfu,
                           "number of collector unit in ports (default = 1)",
                           "1");
    option_parser_register(opp, "-gpgpu_operand_collector_num_in_ports_mem", OPT_INT32, &gpgpu_operand_collector_num_in_ports_mem,
                           "number of collector unit in ports (default = 1)",
                           "1");
    option_parser_register(opp, "-gpgpu_operand_collector_num_in_ports_gen", OPT_INT32, &gpgpu_operand_collector_num_in_ports_gen,
                           "number of collector unit in ports (default = 0)",
                           "0");
    option_parser_register(opp, "-gpgpu_operand_collector_num_out_ports_sp", OPT_INT32, &gpgpu_operand_collector_num_out_ports_sp,
                           "number of collector unit in ports (default = 1)",
                           "1");
    option_parser_register(opp, "-gpgpu_operand_collector_num_out_ports_sfu", OPT_INT32, &gpgpu_operand_collector_num_out_ports_sfu,
                           "number of collector unit in ports (default = 1)",
                           "1");
    option_parser_register(opp, "-gpgpu_operand_collector_num_out_ports_mem", OPT_INT32, &gpgpu_operand_collector_num_out_ports_mem,
                           "number of collector unit in ports (default = 1)",
                           "1");
    option_parser_register(opp, "-gpgpu_operand_collector_num_out_ports_gen", OPT_INT32, &gpgpu_operand_collector_num_out_ports_gen,
                           "number of collector unit in ports (default = 0)",
                           "0");
    option_parser_register(opp, "-gpgpu_coalesce_arch", OPT_INT32, &gpgpu_coalesce_arch,
                            "Coalescing arch (default = 13, anything else is off for now)",
                            "13");
    option_parser_register(opp, "-gpgpu_num_sched_per_core", OPT_INT32, &gpgpu_num_sched_per_core,
                            "Number of warp schedulers per core",
                            "1");
    option_parser_register(opp, "-gpgpu_max_insn_issue_per_warp", OPT_INT32, &gpgpu_max_insn_issue_per_warp,
                            "Max number of instructions that can be issued per warp in one cycle by scheduler",
                            "2");
    option_parser_register(opp, "-gpgpu_simt_core_sim_order", OPT_INT32, &simt_core_sim_order,
                            "Select the simulation order of cores in a cluster (0=Fix, 1=Round-Robin)",
                            "1");
    option_parser_register(opp, "-gpgpu_pipeline_widths", OPT_CSTR, &pipeline_widths_string,
                            "Pipeline widths "
                            "ID_OC_SP,ID_OC_SFU,ID_OC_MEM,OC_EX_SP,OC_EX_SFU,OC_EX_MEM,EX_WB",
                            "1,1,1,1,1,1,1" );
    option_parser_register(opp, "-gpgpu_num_sp_units", OPT_INT32, &gpgpu_num_sp_units,
                            "Number of SP units (default=1)",
                            "1");
    option_parser_register(opp, "-gpgpu_num_sfu_units", OPT_INT32, &gpgpu_num_sfu_units,
                            "Number of SF units (default=1)",
                            "1");
    option_parser_register(opp, "-gpgpu_num_mem_units", OPT_INT32, &gpgpu_num_mem_units,
                            "Number if ldst units (default=1) WARNING: not hooked up to anything",
                             "1");
    option_parser_register(opp, "-gpgpu_scheduler", OPT_CSTR, &gpgpu_scheduler_string,
                                "Scheduler configuration: < lrr | gto | two_level_active > "
                                "If two_level_active:<num_active_warps>:<inner_prioritization>:<outer_prioritization>"
                                "For complete list of prioritization values see shader.h enum scheduler_prioritization_type"
                                "Default: gto",
                                 "gto");
}

void gpgpu_sim_config::reg_options(option_parser_t opp)
{
    gpgpu_functional_sim_config::reg_options(opp);
    m_shader_config.reg_options(opp);
    m_memory_config.reg_options(opp);
    power_config::reg_options(opp);
   option_parser_register(opp, "-gpgpu_max_cycle", OPT_INT32, &gpu_max_cycle_opt,
               "terminates gpu simulation early (0 = no limit)",
               "0");
   option_parser_register(opp, "-gpgpu_max_insn", OPT_INT32, &gpu_max_insn_opt,
               "terminates gpu simulation early (0 = no limit)",
               "0");
   option_parser_register(opp, "-gpgpu_max_cta", OPT_INT32, &gpu_max_cta_opt,
               "terminates gpu simulation early (0 = no limit)",
               "0");
   option_parser_register(opp, "-gpgpu_runtime_stat", OPT_CSTR, &gpgpu_runtime_stat,
                  "display runtime statistics such as dram utilization {<freq>:<flag>}",
                  "10000:0");
   option_parser_register(opp, "-gpgpu_flush_l1_cache", OPT_BOOL, &gpgpu_flush_l1_cache,
                "Flush L1 cache at the end of each kernel call",
                "0");
   option_parser_register(opp, "-gpgpu_flush_l2_cache", OPT_BOOL, &gpgpu_flush_l2_cache,
                   "Flush L2 cache at the end of each kernel call",
                   "0");

   option_parser_register(opp, "-gpgpu_deadlock_detect", OPT_BOOL, &gpu_deadlock_detect,
                "Stop the simulation at deadlock (1=on (default), 0=off)",
                "1");
   option_parser_register(opp, "-gpgpu_ptx_instruction_classification", OPT_INT32,
               &gpgpu_ptx_instruction_classification,
               "if enabled will classify ptx instruction types per kernel (Max 255 kernels now)",
               "0");
   option_parser_register(opp, "-gpgpu_ptx_sim_mode", OPT_INT32, &g_ptx_sim_mode,
               "Select between Performance (default) or Functional simulation (1)",
               "0");
   option_parser_register(opp, "-gpgpu_clock_domains", OPT_CSTR, &gpgpu_clock_domains,
                  "Clock Domain Frequencies in MhZ {<Core Clock>:<ICNT Clock>:<L2 Clock>:<DRAM Clock>}",
                  "500.0:2000.0:2000.0:2000.0");
   option_parser_register(opp, "-gpgpu_max_concurrent_kernel", OPT_INT32, &max_concurrent_kernel,
                          "maximum kernels that can run concurrently on GPU", "8" );
   option_parser_register(opp, "-gpgpu_cflog_interval", OPT_INT32, &gpgpu_cflog_interval,
               "Interval between each snapshot in control flow logger",
               "0");
   option_parser_register(opp, "-visualizer_enabled", OPT_BOOL,
                          &g_visualizer_enabled, "Turn on visualizer output (1=On, 0=Off)",
                          "1");
   option_parser_register(opp, "-visualizer_outputfile", OPT_CSTR,
                          &g_visualizer_filename, "Specifies the output log file for visualizer",
                          NULL);
   option_parser_register(opp, "-visualizer_zlevel", OPT_INT32,
                          &g_visualizer_zlevel, "Compression level of the visualizer output log (0=no comp, 9=highest)",
                          "6");
    option_parser_register(opp, "-trace_enabled", OPT_BOOL,
                          &Trace::enabled, "Turn on traces",
                          "0");
    option_parser_register(opp, "-trace_components", OPT_CSTR,
                          &Trace::config_str, "comma seperated list of traces to enable. "
                          "Complete list found in trace_streams.tup. "
                          "Default none",
                          "none");
    option_parser_register(opp, "-trace_sampling_core", OPT_INT32,
                          &Trace::sampling_core, "The core which is printed using CORE_DPRINTF. Default 0",
                          "0");
   ptx_file_line_stats_options(opp);
}

/////////////////////////////////////////////////////////////////////////////

void increment_x_then_y_then_z( dim3 &i, const dim3 &bound)
{
   i.x++;
   if ( i.x >= bound.x ) {
      i.x = 0;
      i.y++;
      if ( i.y >= bound.y ) {
         i.y = 0;
         if( i.z < bound.z )
            i.z++;
      }
   }
}

void gpgpu_sim::launch( kernel_info_t *kinfo )
{
   unsigned cta_size = kinfo->threads_per_cta();
   if ( cta_size > m_shader_config->n_thread_per_shader ) {
      printf("Execution error: Shader kernel CTA (block) size is too large for microarch config.\n");
      printf("                 CTA size (x*y*z) = %u, max supported = %u\n", cta_size,
             m_shader_config->n_thread_per_shader );
      printf("                 => either change -gpgpu_shader argument in gpgpusim.config file or\n");
      printf("                 modify the CUDA source to decrease the kernel block size.\n");
      abort();
   }
   unsigned n=0;
   for(n=0; n < m_running_kernels.size(); n++ ) {
       if( (NULL==m_running_kernels[n]) || m_running_kernels[n]->done() ) {
           m_running_kernels[n] = kinfo;
           break;
       }
   }
   assert(n < m_running_kernels.size());
}

bool gpgpu_sim::can_start_kernel()
{
   for(unsigned n=0; n < m_running_kernels.size(); n++ ) {
       if( (NULL==m_running_kernels[n]) || m_running_kernels[n]->done() )
           return true;
   }
   return false;
}

bool gpgpu_sim::get_more_cta_left() const
{
   if (m_config.gpu_max_cta_opt != 0) {
      if( m_total_cta_launched >= m_config.gpu_max_cta_opt )
          return false;
   }
   for(unsigned n=0; n < m_running_kernels.size(); n++ ) {
       if( m_running_kernels[n] && !m_running_kernels[n]->no_more_ctas_to_run() )
           return true;
   }
   return false;
}

kernel_info_t *gpgpu_sim::select_kernel()
{
    for(unsigned n=0; n < m_running_kernels.size(); n++ ) {
        unsigned idx = (n+m_last_issued_kernel+1)%m_config.max_concurrent_kernel;
        if( m_running_kernels[idx] && !m_running_kernels[idx]->no_more_ctas_to_run() ) {
            m_last_issued_kernel=idx;

            // record this kernel for stat print if it is the first time this kernel is selected for execution
            unsigned launch_uid = m_running_kernels[idx]->get_uid();
            if (std::find(m_executed_kernel_uids.begin(), m_executed_kernel_uids.end(), launch_uid) == m_executed_kernel_uids.end()) {
               m_executed_kernel_uids.push_back(launch_uid);
               m_executed_kernel_names.push_back(m_running_kernels[idx]->name());
            }

            return m_running_kernels[idx];
        }
    }
    return NULL;
}

unsigned gpgpu_sim::finished_kernel()
{
    if( m_finished_kernel.empty() )
        return 0;
    unsigned result = m_finished_kernel.front();
    m_finished_kernel.pop_front();
    return result;
}

void gpgpu_sim::set_kernel_done( kernel_info_t *kernel )
{
    unsigned uid = kernel->get_uid();
    m_finished_kernel.push_back(uid);
    std::vector<kernel_info_t*>::iterator k;
    for( k=m_running_kernels.begin(); k!=m_running_kernels.end(); k++ ) {
        if( *k == kernel ) {
            *k = NULL;
            break;
        }
    }
    assert( k != m_running_kernels.end() );
}

void set_ptx_warp_size(const struct core_config * warp_size);

gpgpu_sim::gpgpu_sim( const gpgpu_sim_config &config )
    : gpgpu_t(config), m_config(config)
{
    m_shader_config = &m_config.m_shader_config;
    m_memory_config = &m_config.m_memory_config;
    set_ptx_warp_size(m_shader_config);
    ptx_file_line_stats_create_exposed_latency_tracker(m_config.num_shader());

#ifdef GPGPUSIM_POWER_MODEL
        m_gpgpusim_wrapper = new gpgpu_sim_wrapper(config.g_power_simulation_enabled,config.g_power_config_name);
#endif

    m_shader_stats = new shader_core_stats(m_shader_config);
    m_memory_stats = new memory_stats_t(m_config.num_shader(),m_shader_config,m_memory_config);
    average_pipeline_duty_cycle = (float *)malloc(sizeof(float));
    active_sms=(float *)malloc(sizeof(float));
    m_power_stats = new power_stat_t(m_shader_config,average_pipeline_duty_cycle,active_sms,m_shader_stats,m_memory_config,m_memory_stats);

    gpu_sim_insn = 0;
    gpu_tot_sim_insn = 0;
    gpu_tot_issued_cta = 0;
    gpu_deadlock = false;


    m_cluster = new simt_core_cluster*[m_shader_config->n_simt_clusters];
    for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++)
        m_cluster[i] = new simt_core_cluster(this,i,m_shader_config,m_memory_config,m_shader_stats,m_memory_stats);

    m_memory_partition_unit = new memory_partition_unit*[m_memory_config->m_n_mem];
    for (unsigned i=0;i<m_memory_config->m_n_mem;i++)
        m_memory_partition_unit[i] = new memory_partition_unit(i, m_memory_config, m_memory_stats);

    icnt_init(m_shader_config->n_simt_clusters,m_memory_config->m_n_mem);

    time_vector_create(NUM_MEM_REQ_STAT);
    fprintf(stdout, "GPGPU-Sim uArch: performance model initialization complete.\n");

    m_running_kernels.resize( config.max_concurrent_kernel, NULL );
    m_last_issued_kernel = 0;
    m_last_cluster_issue = 0;
    *average_pipeline_duty_cycle=0;
    *active_sms=0;
}

int gpgpu_sim::shared_mem_size() const
{
   return m_shader_config->gpgpu_shmem_size;
}

int gpgpu_sim::num_registers_per_core() const
{
   return m_shader_config->gpgpu_shader_registers;
}

int gpgpu_sim::wrp_size() const
{
   return m_shader_config->warp_size;
}

int gpgpu_sim::shader_clock() const
{
   return m_config.core_freq/1000;
}

void gpgpu_sim::set_prop( cudaDeviceProp *prop )
{
   m_cuda_properties = prop;
}

const struct cudaDeviceProp *gpgpu_sim::get_prop() const
{
   return m_cuda_properties;
}

enum divergence_support_t gpgpu_sim::simd_model() const
{
   return m_shader_config->model;
}

void gpgpu_sim_config::init_clock_domains(void )
{
   sscanf(gpgpu_clock_domains,"%lf:%lf:%lf:%lf",
          &core_freq, &icnt_freq, &l2_freq, &dram_freq);
   core_freq = core_freq MhZ;
   icnt_freq = icnt_freq MhZ;
   l2_freq = l2_freq MhZ;
   dram_freq = dram_freq MhZ;
   core_period = 1/core_freq;
   icnt_period = 1/icnt_freq;
   dram_period = 1/dram_freq;
   l2_period = 1/l2_freq;
   printf("GPGPU-Sim uArch: clock freqs: %lf:%lf:%lf:%lf\n",core_freq,icnt_freq,l2_freq,dram_freq);
   printf("GPGPU-Sim uArch: clock periods: %.20lf:%.20lf:%.20lf:%.20lf\n",core_period,icnt_period,l2_period,dram_period);
}

void gpgpu_sim::reinit_clock_domains(void)
{
   core_time = 0;
   dram_time = 0;
   icnt_time = 0;
   l2_time = 0;
}

bool gpgpu_sim::active()
{
    if (m_config.gpu_max_cycle_opt && (gpu_tot_sim_cycle + gpu_sim_cycle) >= m_config.gpu_max_cycle_opt)
       return false;
    if (m_config.gpu_max_insn_opt && (gpu_tot_sim_insn + gpu_sim_insn) >= m_config.gpu_max_insn_opt)
       return false;
    if (m_config.gpu_max_cta_opt && (gpu_tot_issued_cta >= m_config.gpu_max_cta_opt) )
       return false;
    if (m_config.gpu_deadlock_detect && gpu_deadlock)
       return false;
    for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++)
       if( m_cluster[i]->get_not_completed()>0 )
           return true;;
    for (unsigned i=0;i<m_memory_config->m_n_mem;i++)
       if( m_memory_partition_unit[i]->busy()>0 )
           return true;;
    if( icnt_busy() )
        return true;
    if( get_more_cta_left() )
        return true;
    return false;
}

void gpgpu_sim::init()
{
    //An: init power mode
    extern int power_mode;
    extern float power_width_10cycle[16];
    power_mode = 2;
    extern int issue_request[2][15];



    // run a CUDA grid on the GPU microarchitecture simulator
    gpu_sim_cycle = 0;
    gpu_sim_insn = 0;
    last_gpu_sim_insn = 0;
    m_total_cta_launched=0;
    reinit_clock_domains();
    set_param_gpgpu_num_shaders(m_config.num_shader());
    for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++)
       m_cluster[i]->reinit();
    m_shader_stats->new_grid();
    // initialize the control-flow, memory access, memory latency logger
    if (m_config.g_visualizer_enabled) {
        create_thread_CFlogger( m_config.num_shader(), m_shader_config->n_thread_per_shader, 0, m_config.gpgpu_cflog_interval );
    }
    shader_CTA_count_create( m_config.num_shader(), m_config.gpgpu_cflog_interval);
    if (m_config.gpgpu_cflog_interval != 0) {
       insn_warp_occ_create( m_config.num_shader(), m_shader_config->warp_size );
       shader_warp_occ_create( m_config.num_shader(), m_shader_config->warp_size, m_config.gpgpu_cflog_interval);
       shader_mem_acc_create( m_config.num_shader(), m_memory_config->m_n_mem, 4, m_config.gpgpu_cflog_interval);
       shader_mem_lat_create( m_config.num_shader(), m_config.gpgpu_cflog_interval);
       shader_cache_access_create( m_config.num_shader(), 3, m_config.gpgpu_cflog_interval);
       set_spill_interval (m_config.gpgpu_cflog_interval * 40);
    }

    if (g_network_mode)
       icnt_init_grid();

    // McPAT initialization function. Called on first launch of GPU
#ifdef GPGPUSIM_POWER_MODEL
    if(m_config.g_power_simulation_enabled){
        init_mcpat(m_config, m_gpgpusim_wrapper, m_config.gpu_stat_sample_freq,  gpu_tot_sim_insn, gpu_sim_insn);
    }
#endif
}

void gpgpu_sim::update_stats() {
    m_memory_stats->memlatstat_lat_pw();
    gpu_tot_sim_cycle += gpu_sim_cycle;
    gpu_tot_sim_insn += gpu_sim_insn;
}

void gpgpu_sim::print_stats()
{

    ptx_file_line_stats_write_file();
    gpu_print_stat();

    if (g_network_mode) {
       interconnect_stats();
       printf("----------------------------Interconnect-DETAILS---------------------------------" );
       icnt_overal_stat();
       printf("----------------------------END-of-Interconnect-DETAILS-------------------------" );
    }
}

void gpgpu_sim::deadlock_check()
{
   if (m_config.gpu_deadlock_detect && gpu_deadlock) {
      fflush(stdout);
      printf("\n\nGPGPU-Sim uArch: ERROR ** deadlock detected: last writeback core %u @ gpu_sim_cycle %u (+ gpu_tot_sim_cycle %u) (%u cycles ago)\n",
             gpu_sim_insn_last_update_sid,
             (unsigned) gpu_sim_insn_last_update, (unsigned) (gpu_tot_sim_cycle-gpu_sim_cycle),
             (unsigned) (gpu_sim_cycle - gpu_sim_insn_last_update ));
      unsigned num_cores=0;
      for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++) {
         unsigned not_completed = m_cluster[i]->get_not_completed();
         if( not_completed ) {
             if ( !num_cores )  {
                 printf("GPGPU-Sim uArch: DEADLOCK  shader cores no longer committing instructions [core(# threads)]:\n" );
                 printf("GPGPU-Sim uArch: DEADLOCK  ");
                 m_cluster[i]->print_not_completed(stdout);
             } else if (num_cores < 8 ) {
                 m_cluster[i]->print_not_completed(stdout);
             } else if (num_cores >= 8 ) {
                 printf(" + others ... ");
             }
             num_cores+=m_shader_config->n_simt_cores_per_cluster;
         }
      }
      printf("\n");
      for (unsigned i=0;i<m_memory_config->m_n_mem;i++) {
         bool busy = m_memory_partition_unit[i]->busy();
         if( busy )
             printf("GPGPU-Sim uArch DEADLOCK:  memory partition %u busy\n", i );
      }
      if( icnt_busy() ) {
         printf("GPGPU-Sim uArch DEADLOCK:  iterconnect contains traffic\n");
         display_icnt_state( stdout );
      }
      printf("\nRe-run the simulator in gdb and use debug routines in .gdbinit to debug this\n");
      fflush(stdout);
      abort();
   }
}

/// printing the names and uids of a set of executed kernels (usually there is only one)
std::string gpgpu_sim::executed_kernel_info_string()
{
   std::stringstream statout;

   statout << "kernel_name = ";
   for (unsigned int k = 0; k < m_executed_kernel_names.size(); k++) {
      statout << m_executed_kernel_names[k] << " ";
   }
   statout << std::endl;
   statout << "kernel_launch_uid = ";
   for (unsigned int k = 0; k < m_executed_kernel_uids.size(); k++) {
      statout << m_executed_kernel_uids[k] << " ";
   }
   statout << std::endl;

   return statout.str();
}

void gpgpu_sim::clear_executed_kernel_info()
{
   m_executed_kernel_names.clear();
   m_executed_kernel_uids.clear();
}

void gpgpu_sim::gpu_print_stat()
{
   FILE *statfout = stdout;

   std::string kernel_info_str = executed_kernel_info_string();
   fprintf(statfout, "%s", kernel_info_str.c_str());

   printf("gpu_sim_cycle = %lld\n", gpu_sim_cycle);
   printf("gpu_sim_insn = %lld\n", gpu_sim_insn);
   printf("gpu_ipc = %12.4f\n", (float)gpu_sim_insn / gpu_sim_cycle);
   printf("gpu_tot_sim_cycle = %lld\n", gpu_tot_sim_cycle+gpu_sim_cycle);
   printf("gpu_tot_sim_insn = %lld\n", gpu_tot_sim_insn+gpu_sim_insn);
   printf("gpu_tot_ipc = %12.4f\n", (float)(gpu_tot_sim_insn+gpu_sim_insn) / (gpu_tot_sim_cycle+gpu_sim_cycle));
   printf("gpu_tot_issued_cta = %lld\n", gpu_tot_issued_cta);



   // performance counter for stalls due to congestion.
   printf("gpu_stall_dramfull = %d\n", gpu_stall_dramfull);
   printf("gpu_stall_icnt2sh    = %d\n", gpu_stall_icnt2sh );

   time_t curr_time;
   time(&curr_time);
   unsigned long long elapsed_time = MAX( curr_time - g_simulation_starttime, 1 );
   printf( "gpu_total_sim_rate=%u\n", (unsigned)( ( gpu_tot_sim_insn + gpu_sim_insn ) / elapsed_time ) );

   shader_print_l1_miss_stat( stdout );
   shader_print_scheduler_stat( stdout, true );

   m_shader_stats->print(stdout);
#ifdef GPGPUSIM_POWER_MODEL
   if(m_config.g_power_simulation_enabled){
	   m_gpgpusim_wrapper->print_power_kernel_stats(gpu_sim_cycle, gpu_tot_sim_cycle, gpu_tot_sim_insn + gpu_sim_insn, kernel_info_str );
	   mcpat_reset_perf_count(m_gpgpusim_wrapper, true);
   }
#endif

   // performance counter that are not local to one shader
   m_memory_stats->memlatstat_print(m_memory_config->m_n_mem,m_memory_config->nbk);
   m_memory_stats->print(stdout);
   for (unsigned i=0;i<m_memory_config->m_n_mem;i++)
      m_memory_partition_unit[i]->print(stdout);
   if (!m_memory_config->m_L2_config.disabled() && m_memory_config->m_L2_config.get_num_lines())
      L2c_print_cache_stat();
   if (m_config.gpgpu_cflog_interval != 0) {
      spill_log_to_file (stdout, 1, gpu_sim_cycle);
      insn_warp_occ_print(stdout);
   }
   if ( gpgpu_ptx_instruction_classification ) {
      StatDisp( g_inst_classification_stat[g_ptx_kernel_count]);
      StatDisp( g_inst_op_classification_stat[g_ptx_kernel_count]);
   }

#ifdef GPGPUSIM_POWER_MODEL
   if(m_config.g_power_simulation_enabled){
       m_gpgpusim_wrapper->detect_print_steady_state(1,gpu_tot_sim_insn+gpu_sim_insn);
   }
#endif


   // Interconnect power stat print
   unsigned total_mem_to_simt=0;
   unsigned total_simt_to_mem=0;
   for (unsigned i=0;i<m_memory_config->m_n_mem;i++){
      unsigned temp=0;
      m_memory_partition_unit[i]->set_icnt_power_stats(temp);
      total_mem_to_simt += temp;
   }
   for(unsigned i=0; i<m_config.num_cluster(); i++){
	   unsigned temp=0;
	   m_cluster[i]->set_icnt_stats(temp);
	   total_simt_to_mem += temp;
   }
   printf("\nicnt_total_pkts_mem_to_simt=%u\n", total_mem_to_simt);
   printf("icnt_total_pkts_simt_to_mem=%u\n\n", total_simt_to_mem);

   time_vector_print();
   fflush(stdout);

   clear_executed_kernel_info();
}


// performance counter that are not local to one shader
unsigned gpgpu_sim::threads_per_core() const
{
   return m_shader_config->n_thread_per_shader;
}

void shader_core_ctx::mem_instruction_stats(const warp_inst_t &inst)
{
    unsigned active_count = inst.active_count();
    //this breaks some encapsulation: the is_[space] functions, if you change those, change this.
    switch (inst.space.get_type()) {
    case undefined_space:
    case reg_space:
        break;
    case shared_space:
        m_stats->gpgpu_n_shmem_insn += active_count;
        break;
    case const_space:
        m_stats->gpgpu_n_const_insn += active_count;
        break;
    case param_space_kernel:
    case param_space_local:
        m_stats->gpgpu_n_param_insn += active_count;
        break;
    case tex_space:
        m_stats->gpgpu_n_tex_insn += active_count;
        break;
    case global_space:
    case local_space:
        if( inst.is_store() )
            m_stats->gpgpu_n_store_insn += active_count;
        else
            m_stats->gpgpu_n_load_insn += active_count;
        break;
    default:
        abort();
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Launches a cooperative thread array (CTA).
 *
 * @param kernel
 *    object that tells us which kernel to ask for a CTA from
 */

void shader_core_ctx::issue_block2core( kernel_info_t &kernel )
{
	if ( g_the_gpu_config.throttle_thread_block_issue ) {
		if ( cycles_since_last_issued_thread_block < (unsigned)g_the_gpu_config.throttle_thread_block_issue_interval )
		//if ( cycles_since_last_issued_thread_block < (unsigned)g_the_gpu_config.throttle_thread_block_issue_interval && m_sid != g_last_issued_sm_id)
			return;
	}
    set_max_cta(kernel);

    // find a free CTA context
    unsigned free_cta_hw_id=(unsigned)-1;
    for (unsigned i=0;i<kernel_max_cta_per_shader;i++ ) {
      if( m_cta_status[i]==0 ) {
         free_cta_hw_id=i;
         break;
      }
    }
    assert( free_cta_hw_id!=(unsigned)-1 );

    // determine hardware threads and warps that will be used for this CTA
    int cta_size = kernel.threads_per_cta();

    // hw warp id = hw thread id mod warp size, so we need to find a range
    // of hardware thread ids corresponding to an integral number of hardware
    // thread ids
    int padded_cta_size = cta_size;
    if (cta_size%m_config->warp_size)
      padded_cta_size = ((cta_size/m_config->warp_size)+1)*(m_config->warp_size);
    unsigned start_thread = free_cta_hw_id * padded_cta_size;
    unsigned end_thread  = start_thread +  cta_size;

    // reset the microarchitecture state of the selected hardware thread and warp contexts
    reinit(start_thread, end_thread,false);

    // initalize scalar threads and determine which hardware warps they are allocated to
    // bind functional simulation state of threads to hardware resources (simulation)
    warp_set_t warps;
    unsigned nthreads_in_block= 0;
    for (unsigned i = start_thread; i<end_thread; i++) {
        m_threadState[i].m_cta_id = free_cta_hw_id;
        unsigned warp_id = i/m_config->warp_size;
        nthreads_in_block += ptx_sim_init_thread(kernel,&m_thread[i],m_sid,i,cta_size-(i-start_thread),m_config->n_thread_per_shader,this,free_cta_hw_id,warp_id,m_cluster->get_gpu());
        m_threadState[i].m_active = true;
        warps.set( warp_id );
    }
    assert( nthreads_in_block > 0 && nthreads_in_block <= m_config->n_thread_per_shader); // should be at least one, but less than max
    m_cta_status[free_cta_hw_id]=nthreads_in_block;

    // now that we know which warps are used in this CTA, we can allocate
    // resources for use in CTA-wide barrier operations
    m_barriers.allocate_barrier(free_cta_hw_id,warps);

    // initialize the SIMT stacks and fetch hardware
    init_warps( free_cta_hw_id, start_thread, end_thread);
    m_n_active_cta++;

    shader_CTA_count_log(m_sid, 1);
	cycles_since_last_issued_thread_block=0;
	g_last_issued_sm_id=m_sid;
    printf("GPGPU-Sim uArch: core:%3d, cta:%2u initialized @(%lld,%lld)\n", m_sid, free_cta_hw_id, gpu_sim_cycle, gpu_tot_sim_cycle );

	if ( cta_activity_file[m_sid] != NULL ) {
   		const class function_info *k_info = kernel.entry();
		g_kernel_start_pc = k_info->get_start_PC();
		fprintf(cta_activity_file[m_sid], "cta,%lu,start,%d, dim<%d-%d-%d>, pc=%d\n", gpu_sim_cycle, free_cta_hw_id,
			 			   kernel.get_cta_dim().x, kernel.get_cta_dim().y, kernel.get_cta_dim().z, g_kernel_start_pc);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////

void dram_t::dram_log( int task )
{
   if (task == SAMPLELOG) {
      StatAddSample(mrqq_Dist, que_length());
   } else if (task == DUMPLOG) {
      printf ("Queue Length DRAM[%d] ",id);StatDisp(mrqq_Dist);
   }
}

//Find next clock domain and increment its time
int gpgpu_sim::next_clock_domain(void)
{
   double smallest = min3(core_time,icnt_time,dram_time);
   int mask = 0x00;
   if ( l2_time <= smallest ) {
      smallest = l2_time;
      mask |= L2 ;
      l2_time += m_config.l2_period;
   }
   if ( icnt_time <= smallest ) {
      mask |= ICNT;
      icnt_time += m_config.icnt_period;
   }
   if ( dram_time <= smallest ) {
      mask |= DRAM;
      dram_time += m_config.dram_period;
   }
   if ( core_time <= smallest ) {
      mask |= CORE;
      core_time += m_config.core_period;
   }
   return mask;
}

void gpgpu_sim::issue_block2core()
{
    unsigned last_issued = m_last_cluster_issue;
    for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++) {
        unsigned idx = (i + last_issued + 1) % m_shader_config->n_simt_clusters;
        unsigned num = m_cluster[idx]->issue_block2core();
        if( num ) {
            m_last_cluster_issue=idx;
            m_total_cta_launched += num;
        }
    }
}

unsigned long long g_single_step; // set this in gdb to single step the pipeline

//This simulates a cycle of 16 cores
void gpgpu_sim::cycle()
{
   int clock_mask = next_clock_domain();

   if (clock_mask & CORE ) {
       // shader core loading (pop from ICNT into core) follows CORE clock
      for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++)
		 {
         m_cluster[i]->icnt_cycle();
		 //cout << "higher level core num: " <<  core_num << endl;
		 }
   }
    if (clock_mask & ICNT) {
        // pop from memory controller to interconnect
        for (unsigned i=0;i<m_memory_config->m_n_mem;i++) {
            mem_fetch* mf = m_memory_partition_unit[i]->top();
            if (mf) {
                unsigned response_size = mf->get_is_write()?mf->get_ctrl_size():mf->size();
                if ( ::icnt_has_buffer( m_shader_config->mem2device(i), response_size ) ) {
                    if (!mf->get_is_write())
                       mf->set_return_timestamp(gpu_sim_cycle+gpu_tot_sim_cycle);
                    mf->set_status(IN_ICNT_TO_SHADER,gpu_sim_cycle+gpu_tot_sim_cycle);
                    ::icnt_push( m_shader_config->mem2device(i), mf->get_tpc(), mf, response_size );
                    m_memory_partition_unit[i]->pop();
                } else {
                    gpu_stall_icnt2sh++;
                }
            } else {
               m_memory_partition_unit[i]->pop();
            }
        }
    }

   if (clock_mask & DRAM) {
      for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++) {
	      g_per_core_dram2core_buffer[i]=0; // clear the buffer to record the number of elements for each core
	  }
      for (unsigned i=0;i<m_memory_config->m_n_mem;i++){
         m_memory_partition_unit[i]->dram_cycle(); // Issue the dram command (scheduler + delay model)
         // Update performance counters for DRAM
         m_memory_partition_unit[i]->set_dram_power_stats(m_power_stats->pwr_mem_stat->n_cmd[0][i], m_power_stats->pwr_mem_stat->n_activity[0][i],
                        m_power_stats->pwr_mem_stat->n_nop[0][i], m_power_stats->pwr_mem_stat->n_act[0][i], m_power_stats->pwr_mem_stat->n_pre[0][i],
                        m_power_stats->pwr_mem_stat->n_rd[0][i], m_power_stats->pwr_mem_stat->n_wr[0][i], m_power_stats->pwr_mem_stat->n_req[0][i]);
      }
   }

   // L2 operations follow L2 clock domain
   if (clock_mask & L2) {
      for (unsigned i=0;i<m_memory_config->m_n_mem;i++) {
          //move memory request from interconnect into memory partition (if not backed up)
          //Note:This needs to be called in DRAM clock domain if there is no L2 cache in the system
          if ( m_memory_partition_unit[i]->full() ) {
             gpu_stall_dramfull++;
          } else {
              mem_fetch* mf = (mem_fetch*) icnt_pop( m_shader_config->mem2device(i) );
              m_memory_partition_unit[i]->push( mf, gpu_sim_cycle + gpu_tot_sim_cycle );
          }
          m_memory_partition_unit[i]->cache_cycle(gpu_sim_cycle+gpu_tot_sim_cycle);
          m_memory_partition_unit[i]->set_L2cache_power_stats(m_power_stats->pwr_mem_stat->n_l2_read_access[0][i], m_power_stats->pwr_mem_stat->n_l2_read_miss[0][i],
          m_power_stats->pwr_mem_stat->n_l2_write_access[0][i], m_power_stats->pwr_mem_stat->n_l2_write_miss[0][i]);

          m_memory_partition_unit[i]->set_icnt_power_stats(m_power_stats->pwr_mem_stat->n_mem_to_simt[0][i]);
       }
   }

   if (clock_mask & ICNT) {
      icnt_transfer();
   }

   if (clock_mask & CORE) {
      // L1 cache + shader core pipeline stages
	  avg_pipe_duty = 0;
      for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++) {
	    core_idle[i] = 1;
		g_local_throttle_net_budget[i] = std::numeric_limits<double>::max();
		g_local_throttle_increment_budget[i] = std::numeric_limits<double>::max();
		g_per_core_fpu_this_cycle_increment[i] = 0;
		g_per_core_fpu_this_cycle_decrement[i] = g_per_core_fpu_next_cycle_decrement[i]; // previous cycle's next cycle decrment is this cycle

		g_per_core_alu_this_cycle_increment[i] = 0;
		g_per_core_alu_this_cycle_decrement[i] = g_per_core_alu_next_cycle_decrement[i]; // previous cycle's next cycle decrment is this cycle

		g_per_core_sfu_this_cycle_increment[i] = 0;
		g_per_core_sfu_this_cycle_decrement[i] = g_per_core_sfu_next_cycle_decrement[i]; // previous cycle's next cycle decrment is this cycle

		g_per_core_ldst_this_cycle_increment[i] = g_per_core_ldst_next_cycle_increment[i];
		g_per_core_ldst_next_cycle_increment[i] = 0;

		g_per_core_local_increment[i] = 0;

		if ( g_the_gpu_config.g_dev_hier_local_throttle && gpu_sim_cycle > LOCAL_THROTTLE_HISTORY_WINDOW_SIZE ) {
			double possible_increment_delta = std::numeric_limits<double>::max();
			for (unsigned history_idx = 0; history_idx < 4; history_idx ++ ) {
				double tmp_delta = g_local_predict_weighted_input_per_core[i][(gpu_sim_cycle-history_idx)%LOCAL_THROTTLE_HISTORY_WINDOW_SIZE] + g_the_gpu_config.g_dev_hier_local_throttle_threshold[history_idx];
				if ( tmp_delta < possible_increment_delta )
					possible_increment_delta = tmp_delta;
			}
			g_local_throttle_net_budget[i] = possible_increment_delta;

			double this_cycle_local_weighted_input_decrement = 0;
			double this_cycle_local_weighted_input_decrement_fus = (g_per_core_alu_this_cycle_decrement[i]*0.2f + g_per_core_fpu_this_cycle_decrement[i] + g_per_core_sfu_this_cycle_decrement[i] )/32.0f;
			this_cycle_local_weighted_input_decrement += this_cycle_local_weighted_input_decrement_fus;
			this_cycle_local_weighted_input_decrement += g_local_predict_input[i][0] + g_local_predict_input[i][4];
			g_local_throttle_increment_budget[i] = (g_local_throttle_net_budget[i] + this_cycle_local_weighted_input_decrement - g_per_core_ldst_this_cycle_increment[i]) - g_local_predict_weighted_input_per_core[i][(gpu_sim_cycle)%LOCAL_THROTTLE_HISTORY_WINDOW_SIZE]; // considering the ops that will write back this cycle
			//if ( i == 0 )
				//printf("[DEV] @ cycle %lu SM %d g_local_throttle_increment_budget %.2f compose %.2f %.2f (fus %.2f ldst %.2f regs %.2f) %.2f %.2f\n", gpu_sim_cycle+1, i, g_local_throttle_increment_budget[i], g_local_throttle_net_budget[i], this_cycle_local_weighted_input_decrement, this_cycle_local_weighted_input_decrement_fus, g_local_predict_input[i][0], g_local_predict_input[i][4], -g_per_core_ldst_this_cycle_increment[i], -g_local_predict_weighted_input_per_core[i][(gpu_sim_cycle)%LOCAL_THROTTLE_HISTORY_WINDOW_SIZE]);
		}


		// 0: ldst, 1: sp int, 2: sp fp, 3: sfu, 4: reg
		for( int j = 0; j < 5; j++) {
			g_local_predict_input[i][j] = 0;
		}

         if (m_cluster[i]->get_not_completed() || get_more_cta_left() ) {


// Below is modified by An Zou


    //i is the core number and gpu_sim_cycle is the cycle number
    if((i == 0)&&(gpu_sim_cycle==0))
    {
    cout << "Initialize Circuit Simulation" << endl;

    fd = shm_open(shared_memory_name, O_CREAT | O_RDWR, S_IRWXU);
    if (fd<0) {
    printf("error open shared memory\n");
    exit(0);
    }

    ftruncate(fd, sizeof(my_shared_memory1));


    ptr = (struct my_shared_memory *)mmap(NULL, sizeof(my_shared_memory1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr  == MAP_FAILED) {
    printf("error map\n");
    exit(0);
    }
    ptr->spice_finish = 0;
    ptr->gpusim_finish = 1;


    cout << "Finish Circuit Simulation Initialization" << endl;
    }

  //Initialization power mode
  if(gpu_sim_cycle <= 1)
  {
    ptr->power_mode[i] = 2;
  }



  //GPGPUsim is 20 + 20 cycle fast than circuit simulator
  if(gpu_sim_cycle > 10040)
  {
    if((i == 0)&&((gpu_sim_cycle%date_update_frequency==0)))
    {
    cout <<"------------GPU simulator cycle:" << gpu_sim_cycle << endl;
    ptr->spice_finish = 0;
    ptr->gpusim_finish = 1;
    while(ptr->spice_finish == 0)
      {
      //wait for the spice simulator
      }
    }

  }

//worst case analysis
/*
  if(gpu_sim_cycle < 19000)
  {
    for(int l=0; l<16; l++)
    {
    issue_accumulate[l] = 0;
    }
  }
*/


//An Zou: DVFS
//Initialization DVFS
if((gpu_sim_cycle == 0)&&(i == 0))
{
  total_has_issued = 0;
  for(int l=0; l<16; l++)
  {
  SM_issued_last_cycle[l] = 0;
  SM_freq[l] = 700;
  SM_remaining[l] = total_inst;
  }
}

//Adjust DVFS
if((gpu_sim_cycle > 0)&&(gpu_sim_cycle % DVFS_freq == 0)&&(i == 0))
{

  
for(int l=0; l<16; l++)
{

  SM_remaining[l] = SM_remaining[l] - SM_issued_last_cycle[l];  
  SM_freq[l] = SM_freq[l]*(SM_remaining[l]/((total_cycle - gpu_sim_cycle)/DVFS_freq))/SM_issued_last_cycle[l];
  SM_issued_last_cycle[l] = 0;
  
  SM_freq[l] = 50*ceil(SM_freq[l]/50);

  if(SM_freq[l] >= 700)
  {
  SM_freq[l] = 700;
  }

  if(SM_remaining[l] <= 0)
  {
  SM_freq[l] = 0;
  }

}




cout << "~~~~~~~~~~~~~~~~Before hypervisor layer~~~~~~~~~~~~~~~~" << endl;
for(int l=0; l<16; l++)
{
  cout << "SM_remaining[l]" << SM_remaining[l] << endl;
  cout << "SM_freq[l]: " << SM_freq[l] << endl;
  cout << "issue_accumulate[l]" << l << ": " << issue_accumulate[l] << endl;
}


///*
//Hypervisor layer
for(int l=0; l<11; l++)
{
  if(abs(SM_freq[l+4] - SM_freq[l]) > 100)
  {
    if(SM_freq[l+4] > SM_freq[l])
    {
    SM_freq[l+4] = SM_freq[l] + 100;
    }
    else
    {
    SM_freq[l] = SM_freq[l+4] + 100;
    }
  }
}



cout << "~~~~~~~~~~~~~~~~After hypervisor layer~~~~~~~~~~~~~~~~" << endl;
for(int l=0; l<16; l++)
{
  cout << "SM_remaining[l]" << SM_remaining[l] << endl;
  cout << "SM_freq[l]: " << SM_freq[l] << endl;
  cout << "issue_accumulate[l]" << l << ": " << issue_accumulate[l] << endl;
}
//*/






}

//DVFS frequency scaling
accumulate[core_num] = accumulate[core_num] + SM_freq[core_num]/700;
if(accumulate[core_num] >= 1)
{
accumulate[core_num] = accumulate[core_num] - 1;
DVFS_mask[core_num] = 0;
}
else
{
DVFS_mask[core_num] = 1;
}
//DVFS finish





  //Update the 5cycle issue width of each core

  if(gpu_sim_cycle % 5 == 0)
  {
  power_width_10cycle[i] = ptr->power_mode[i] * 5;
  if(power_width_10cycle[i] > 10)
  {
  power_width_10cycle[i] = 10;
  }
  if(power_width_10cycle[i] < 0)
  {
  power_width_10cycle[i] = 0;
  }
  issue_accumulate[i] = issue_accumulate[i] + power_width_10cycle[i];
  }
 
  core_num = i;




  //cout << "check core_num: "<< core_num << endl;
  //cout << "check power_width_10cycle: " << power_width_10cycle[core_num] << endl;




		if(24000 == gpu_sim_cycle)
		{
                cout << "total_has_issued: " << total_has_issued << endl;
                printf("Simulation finish!!!!!!!!!\n");
                for(int l = 0; l < 16; l++)
                {
                cout << "issue_accumulate[l]" << l << ": " << issue_accumulate[l] << endl;
                }
		exit(0);
		}



               m_cluster[i]->core_cycle();
               *active_sms+=m_cluster[i]->get_n_active_sms();
			   core_idle[i] = ( 1 - m_cluster[i]->get_n_active_sms());

               // Interconnect power stats: SIMT->MEM
               m_cluster[i]->set_icnt_stats(m_power_stats->pwr_mem_stat->n_simt_to_mem[0][i]);

			   per_core_pipe_duty[i] /= (float)(m_shader_config->num_shader());
         }
      }

      avg_pipe_duty /= (float)(m_shader_config->num_shader());
      float temp=0;
      for (unsigned i=0;i<m_shader_config->num_shader();i++){
        temp+=m_shader_stats->m_pipeline_duty_cycle[i];
      }
      temp=temp/m_shader_config->num_shader();
      *average_pipeline_duty_cycle=((*average_pipeline_duty_cycle)+temp);
      //cout<<"Average pipeline duty cycle: "<<*average_pipeline_duty_cycle<<endl;


      if( g_single_step && ((gpu_sim_cycle+gpu_tot_sim_cycle) >= g_single_step) ) {
          asm("int $03");
      }
      gpu_sim_cycle++;
	  cycles_since_last_issued_thread_block++;

	  if ( g_the_gpu_config.g_dev_hier_global_throttle ) {
	  	if ( g_global_throttle_duration > 0 && !g_global_throttle_flag ) {
			g_global_throttle_duration--;
		}
	  	if ( g_global_throttle_issue_warp_duration > 0 && !g_global_throttle_issue_warp_flag ) {
			g_global_throttle_issue_warp_duration--;
		}
	  }
      if( g_interactive_debugger_enabled )
         gpgpu_debug();

	  	// record the per core ready warps
	  	{
			unsigned this_interval_history_idx = gpu_sim_cycle  % GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE;
			unsigned core_sum_id = m_shader_config->n_simt_clusters;
			g_global_per_core_ready_warps_history[core_sum_id][this_interval_history_idx] = 0;
			for (unsigned core_id=0;core_id<m_shader_config->n_simt_clusters;core_id++) {
				g_global_per_core_ready_warps_history[core_id][this_interval_history_idx] = g_this_interval_per_core_warp_ready[core_id];
				g_global_per_core_ready_warps_history[core_sum_id][this_interval_history_idx] += g_this_interval_per_core_warp_ready[core_id];
				g_this_interval_per_core_warp_ready[core_id] = 0;
			}
			//printf("[READY WARP] %lu,%d\n", gpu_sim_cycle, g_global_per_core_ready_warps_history[core_sum_id][this_interval_history_idx]);

			if ( gpu_sim_cycle > 4000 ) {
				bool is_in_pre_trigger = true;
				#define GLOBAL_THROTTLE_PRE_TRIGGER_READY_WARP_THRESHOLD 15.0f
				for ( unsigned i = 0; i < 10; i ++ ) {
					unsigned history_idx = (gpu_sim_cycle - i) % GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE;
					if ( g_global_per_core_ready_warps_history[core_sum_id][history_idx] > GLOBAL_THROTTLE_PRE_TRIGGER_READY_WARP_THRESHOLD )
						is_in_pre_trigger = false;

				}
				#undef GLOBAL_THROTTLE_PRE_TRIGGER_READY_WARP_THRESHOLD

				if (is_in_pre_trigger) {
					g_global_detection_state_ready_warp = GlobalDetectionState_PRE;
				} else {
					if ( g_global_detection_state_ready_warp == GlobalDetectionState_PRE && g_global_throttle_issue_warp_duration== 0 ) { // ignore this if already throttling
						printf("[GLOBAL THROTTLE WAPR ISSUE]: cycle %lu transition to ACT state!\n", gpu_sim_cycle);
						g_global_throttle_issue_warp_flag = true;
						g_global_throttle_issue_warp_duration = g_the_gpu_config.g_dev_hier_global_throttle_per_core_issue_quantum*m_shader_config->n_simt_clusters;
					}
					g_global_detection_state_ready_warp = GlobalDetectionState_NONE;
				}
			} else {
				g_global_detection_state_ready_warp 	= GlobalDetectionState_NONE;
				g_global_throttle_issue_warp_flag 		= false;
				g_global_throttle_issue_warp_duration 	= 0;
			}
			//printf("[GLOBAL THROTTLE METRIC]: %lu,%f\n", gpu_sim_cycle,g_global_detection_metrics[this_cycle_idx]);

	  	}

		if ( gpu_sim_cycle % GLOBAL_AGGREGATE_WINDOW_SIZE == 0 ) {

			unsigned this_interval_history_idx = (gpu_sim_cycle / GLOBAL_AGGREGATE_WINDOW_SIZE) % GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE;

			g_global_detection_metrics[this_interval_history_idx] = 0;

			for (unsigned core_id=0;core_id<m_shader_config->n_simt_clusters;core_id++) {

				g_global_per_core_waiting_warps_history[core_id][this_interval_history_idx] = g_this_interval_per_core_warp_waiting[core_id] / double(GLOBAL_AGGREGATE_WINDOW_SIZE);
				g_this_interval_per_core_warp_waiting[core_id] = 0;
				if ( g_the_gpu_config.g_per_core_mem_sub_activity_dump ) {
					FILE * output_file = mem_subsystem_dump_file[core_id];
					if ( output_file ) {
						fprintf(output_file, "%d,%d,%.2f\n", g_per_core_memsubsys_response[core_id][0], g_per_core_memsubsys_response[core_id][1], g_global_per_core_waiting_warps_history[core_id][this_interval_history_idx]);
					}
				}
				g_global_detection_metrics[this_interval_history_idx] += g_per_core_memsubsys_response[core_id][1];

				g_per_core_memsubsys_response[core_id][0] = 0;
				g_per_core_memsubsys_response[core_id][1] = 0;

			}

			if ( g_the_gpu_config.g_dev_hier_global_throttle ) {
				if ( gpu_sim_cycle > 4000 ) {
					bool is_in_pre_trigger = true;
					#define GLOBAL_THROTTLE_PRE_TRIGGER_THRESHOLD 5.0f
					for ( unsigned i = 0; i < 2; i ++ ) {
						unsigned history_idx = (gpu_sim_cycle/GLOBAL_AGGREGATE_WINDOW_SIZE - i) % GLOBAL_THROTTLE_HISTORY_WINDOW_SIZE;
						if ( g_global_detection_metrics[history_idx] > GLOBAL_THROTTLE_PRE_TRIGGER_THRESHOLD)
							is_in_pre_trigger = false;

					}
					#undef GLOBAL_THROTTLE_PRE_TRIGGER_THRESHOLD

					if (is_in_pre_trigger) {
						g_global_detection_state = GlobalDetectionState_PRE;
					} else {
						if ( g_global_detection_state == GlobalDetectionState_PRE && g_global_throttle_duration == 0 ) { // ignore this if already throttling
							printf("[GLOBAL THROTTLE]: cycle %lu transition to ACT state!\n", gpu_sim_cycle);
							g_global_throttle_flag = true;
							g_global_throttle_duration = g_the_gpu_config.g_dev_hier_global_throttle_per_core_quantum*m_shader_config->n_simt_clusters;
						}
						g_global_detection_state = GlobalDetectionState_NONE;
					}
				} else {
					g_global_detection_state = GlobalDetectionState_NONE;
					g_global_throttle_flag = false;
					g_global_throttle_duration = 0;
				}
				//printf("[GLOBAL THROTTLE METRIC]: %lu,%f\n", gpu_sim_cycle,g_global_detection_metrics[this_cycle_idx]);
			}
		}



      // McPAT main cycle (interface with McPAT)
#ifdef GPGPUSIM_POWER_MODEL
      if(m_config.g_power_simulation_enabled){
          mcpat_cycle(m_config, getShaderCoreConfig(), m_gpgpusim_wrapper, m_power_stats, m_config.gpu_stat_sample_freq, gpu_tot_sim_cycle, gpu_sim_cycle, gpu_tot_sim_insn, gpu_sim_insn, m_running_kernels[m_last_issued_kernel]);
      }


		for (unsigned core_id=0;core_id<m_shader_config->n_simt_clusters;core_id++) {

			if ( g_the_gpu_config.g_dev_hier_local_prediction ) {
				if ( core_id == 0 ) {
					double predicted_increment;
					double actual_increment;

					predicted_increment = g_per_core_alu_this_cycle_increment[core_id] - g_per_core_alu_this_cycle_decrement[core_id];
					actual_increment = g_local_predict_input[core_id][1] - g_tmp_history_val[1];
					if ( abs( predicted_increment - actual_increment ) > 0.01 )
						printf("[DEV] @ cycle %lu, alu increment predicted %f, actual %f\n", gpu_sim_cycle, predicted_increment, actual_increment);

					predicted_increment = g_per_core_fpu_this_cycle_increment[core_id] - g_per_core_fpu_this_cycle_decrement[core_id];
					actual_increment = g_local_predict_input[core_id][2] - g_tmp_history_val[2];
					if ( abs( predicted_increment - actual_increment ) > 0.01 )
						printf("[DEV] @ cycle %lu, fpu increment predicted %f, actual %f, delta %f\n", gpu_sim_cycle, predicted_increment, actual_increment, abs( predicted_increment - actual_increment ));

					predicted_increment = g_per_core_sfu_this_cycle_increment[core_id] - g_per_core_sfu_this_cycle_decrement[core_id];
					actual_increment = g_local_predict_input[core_id][3] - g_tmp_history_val[3];
					if ( abs( predicted_increment - actual_increment ) > 0.01 )
						printf("[DEV] @ cycle %lu, sfu increment predicted %f, actual %f\n", gpu_sim_cycle, predicted_increment, actual_increment);

					g_tmp_history_val[1] = g_local_predict_input[core_id][1];
					g_tmp_history_val[2] = g_local_predict_input[core_id][2];
					g_tmp_history_val[3] = g_local_predict_input[core_id][3];
				}
			}

			FILE * output_file = hier_local_prediction_file[core_id];
			if ( output_file ) {
				double tmp_sum = g_local_predict_input[core_id][0] + g_local_predict_input[core_id][1]*0.2f/32.0f + g_local_predict_input[core_id][2]/32.0f + g_local_predict_input[core_id][3]/32.0f + g_local_predict_input[core_id][4];
				double tmp_power = m_gpgpusim_wrapper->per_core_power_record[core_id];
				for(int i = 0; i < 5;i++) {
					if ( i==4)
						fprintf(output_file,"%.1f", g_local_predict_input[core_id][i]);
						//fprintf(output_file,"%.1f,%.1f,%.1f\n", g_local_predict_input[core_id][i], tmp_sum, tmp_power);
					else
						fprintf(output_file,"%.1f,", g_local_predict_input[core_id][i]);
				}
			}

			if ( g_the_gpu_config.g_dev_hier_local_throttle ) {
				double this_cycle_weighted_input = g_local_predict_input[core_id][0] + g_local_predict_input[core_id][1]*0.2f/32.0f + g_local_predict_input[core_id][2]/32.0f + g_local_predict_input[core_id][3]/32.0f + g_local_predict_input[core_id][4];
				//double actual_increment = this_cycle_weighted_input - g_local_predict_weighted_input_per_core[core_id][(gpu_sim_cycle-1) % LOCAL_THROTTLE_HISTORY_WINDOW_SIZE];
				if (g_local_throttle_net_budget[core_id] < (this_cycle_weighted_input-1) ) {
					printf("[DEV] @ SM %d cycle %lu, local increment exceeds budget (%f), actual %f\n", core_id, gpu_sim_cycle, g_local_throttle_net_budget[core_id], this_cycle_weighted_input);
				}

				unsigned history_idx = gpu_sim_cycle % LOCAL_THROTTLE_HISTORY_WINDOW_SIZE;
				g_local_predict_weighted_input_per_core[core_id][history_idx] = this_cycle_weighted_input;
				if ( output_file )
					fprintf(output_file,",%.1f,%.1f,%.1f", this_cycle_weighted_input, g_local_throttle_net_budget[core_id], g_local_throttle_increment_budget[core_id]);
			}
			if ( output_file )
				fprintf(output_file,"\n");

			// Jingwen: print the mem dram2sm buffer count
			output_file = mem_subsystem_buffer_count_dump_file[core_id];
			if ( output_file )
				fprintf(output_file, "%d\n", g_per_core_dram2core_buffer[core_id]);

		}

#endif

      issue_block2core();

      // Depending on configuration, flush the caches once all of threads are completed.
      int all_threads_complete = 1;
      if (m_config.gpgpu_flush_l1_cache) {
         for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++) {
            if (m_cluster[i]->get_not_completed() == 0)
                m_cluster[i]->cache_flush();
            else
               all_threads_complete = 0 ;
         }
      }

      if(m_config.gpgpu_flush_l2_cache){
          if(!m_config.gpgpu_flush_l1_cache){
              for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++) {
                  if (m_cluster[i]->get_not_completed() != 0){
                      all_threads_complete = 0 ;
                      break;
                  }
              }
          }

         if (all_threads_complete && !m_memory_config->m_L2_config.disabled() ) {
            printf("Flushed L2 caches...\n");
            if (m_memory_config->m_L2_config.get_num_lines()) {
               int dlc = 0;
               for (unsigned i=0;i<m_memory_config->m_n_mem;i++) {
                  dlc = m_memory_partition_unit[i]->flushL2();
                  assert (dlc == 0); // need to model actual writes to DRAM here
                  printf("Dirty lines flushed from L2 %d is %d\n", i, dlc  );
               }
            }
         }
      }

      if (!(gpu_sim_cycle % m_config.gpu_stat_sample_freq)) {
         time_t days, hrs, minutes, sec;
         time_t curr_time;
         time(&curr_time);
         unsigned long long  elapsed_time = MAX(curr_time - g_simulation_starttime, 1);
         days    = elapsed_time/(3600*24);
         hrs     = elapsed_time/3600 - 24*days;
         minutes = elapsed_time/60 - 60*(hrs + 24*days);
         sec = elapsed_time - 60*(minutes + 60*(hrs + 24*days));
         printf("GPGPU-Sim uArch: cycles simulated: %lld  inst.: %lld (ipc=%4.1f) sim_rate=%u (inst/sec) elapsed = %u:%u:%02u:%02u / %s",
                gpu_tot_sim_cycle + gpu_sim_cycle, gpu_tot_sim_insn + gpu_sim_insn,
                (double)gpu_sim_insn/(double)gpu_sim_cycle,
                (unsigned)((gpu_tot_sim_insn+gpu_sim_insn) / elapsed_time),
                (unsigned)days,(unsigned)hrs,(unsigned)minutes,(unsigned)sec,
                ctime(&curr_time));
         fflush(stdout);
         visualizer_printstat();
         m_memory_stats->memlatstat_lat_pw();
         if (m_config.gpgpu_runtime_stat && (m_config.gpu_runtime_stat_flag != 0) ) {
            if (m_config.gpu_runtime_stat_flag & GPU_RSTAT_BW_STAT) {
               for (unsigned i=0;i<m_memory_config->m_n_mem;i++)
                  m_memory_partition_unit[i]->print_stat(stdout);
               printf("maxmrqlatency = %d \n", m_memory_stats->max_mrq_latency);
               printf("maxmflatency = %d \n", m_memory_stats->max_mf_latency);
            }
            if (m_config.gpu_runtime_stat_flag & GPU_RSTAT_SHD_INFO)
               shader_print_runtime_stat( stdout );
            if (m_config.gpu_runtime_stat_flag & GPU_RSTAT_L1MISS)
               shader_print_l1_miss_stat( stdout );
            if (m_config.gpu_runtime_stat_flag & GPU_RSTAT_SCHED)
               shader_print_scheduler_stat( stdout, false );
         }
      }

      if (!(gpu_sim_cycle % 20000)) {
         // deadlock detection
         if (m_config.gpu_deadlock_detect && gpu_sim_insn == last_gpu_sim_insn) {
            gpu_deadlock = true;
         } else {
            last_gpu_sim_insn = gpu_sim_insn;
         }
      }
      try_snap_shot(gpu_sim_cycle);
      spill_log_to_file (stdout, 0, gpu_sim_cycle);
   }
}


void shader_core_ctx::dump_warp_state( FILE *fout ) const
{
   fprintf(fout, "\n");
   fprintf(fout, "per warp functional simulation status:\n");
   for (unsigned w=0; w < m_config->max_warps_per_shader; w++ )
       m_warp[w].print(fout);
}

void gpgpu_sim::dump_pipeline( int mask, int s, int m ) const
{
/*
   You may want to use this function while running GPGPU-Sim in gdb.
   One way to do that is add the following to your .gdbinit file:

      define dp
         call g_the_gpu.dump_pipeline_impl((0x40|0x4|0x1),$arg0,0)
      end

   Then, typing "dp 3" will show the contents of the pipeline for shader core 3.
*/

   printf("Dumping pipeline state...\n");
   if(!mask) mask = 0xFFFFFFFF;
   for (unsigned i=0;i<m_shader_config->n_simt_clusters;i++) {
      if(s != -1) {
         i = s;
      }
      if(mask&1) m_cluster[m_shader_config->sid_to_cluster(i)]->display_pipeline(i,stdout,1,mask & 0x2E);
      if(s != -1) {
         break;
      }
   }
   if(mask&0x10000) {
      for (unsigned i=0;i<m_memory_config->m_n_mem;i++) {
         if(m != -1) {
            i=m;
         }
         printf("DRAM / memory controller %u:\n", i);
         if(mask&0x100000) m_memory_partition_unit[i]->print_stat(stdout);
         if(mask&0x1000000)   m_memory_partition_unit[i]->visualize();
         if(mask&0x10000000)   m_memory_partition_unit[i]->print(stdout);
         if(m != -1) {
            break;
         }
      }
   }
   fflush(stdout);
}

const struct shader_core_config * gpgpu_sim::getShaderCoreConfig()
{
   return m_shader_config;
}

const struct memory_config * gpgpu_sim::getMemoryConfig()
{
   return m_memory_config;
}

simt_core_cluster * gpgpu_sim::getSIMTCluster()
{
   return *m_cluster;
}

void memory_partition_unit::visualizer_print( gzFile visualizer_file )
{
   m_dram->visualizer_print(visualizer_file);
}
