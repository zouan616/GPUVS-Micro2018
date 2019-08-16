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

#ifndef POWER_STAT_H
#define POWER_STAT_H

#include <stdio.h>
#include <zlib.h>
#include "mem_latency_stat.h"
#include "shader.h"
#include "gpu-sim.h"

struct shader_core_power_stats_pod {
	// [0] = Current stat, [1] = last reading
	float *m_pipeline_duty_cycle[2];
    unsigned *m_num_decoded_insn[2]; // number of instructions committed by this shader core
    unsigned *m_num_FPdecoded_insn[2]; // number of instructions committed by this shader core
    unsigned *m_num_INTdecoded_insn[2]; // number of instructions committed by this shader core
    unsigned *m_num_storequeued_insn[2];
    unsigned *m_num_loadqueued_insn[2];
    unsigned *m_num_ialu_acesses[2];
    unsigned *m_num_fp_acesses[2];
    unsigned *m_num_tex_inst[2];
    unsigned *m_num_imul_acesses[2];
    unsigned *m_num_imul32_acesses[2];
    unsigned *m_num_imul24_acesses[2];
    unsigned *m_num_fpmul_acesses[2];
    unsigned *m_num_idiv_acesses[2];
    unsigned *m_num_fpdiv_acesses[2];
    unsigned *m_num_sp_acesses[2];
    unsigned *m_num_sfu_acesses[2];
    unsigned *m_num_trans_acesses[2];
    unsigned *m_num_mem_acesses[2];
    unsigned *m_num_sp_committed[2];
    unsigned *m_num_sfu_committed[2];
    unsigned *m_num_mem_committed[2];
    unsigned *m_active_sp_lanes[2];
    unsigned *m_active_sfu_lanes[2];
    unsigned *m_read_regfile_acesses[2];
    unsigned *m_write_regfile_acesses[2];
    unsigned *m_non_rf_operands[2];
};

class power_core_stat_t : public shader_core_power_stats_pod {
public:
   power_core_stat_t(const struct shader_core_config *shader_config, shader_core_stats *core_stats);
   void visualizer_print( gzFile visualizer_file );
   void print (FILE *fout);
   void init();
   void save_stats();
   shader_core_stats * m_core_stats;

private:
   const shader_core_config *m_config;
   float average_duty_cycle;


};

struct mem_power_stats_pod{
	// [0] = Current stat, [1] = last reading
	unsigned *inst_c_read_access[2];	// Instruction cache read access
	unsigned *inst_c_read_miss[2];		// Instruction cache read miss
	unsigned *const_c_read_access[2];	// Constant cache read access
	unsigned *const_c_read_miss[2];		// Constant cache read miss
	unsigned *text_c_read_access[2];	// Texture cache read access
	unsigned *text_c_read_miss[2];		// Texture cache read miss
	unsigned *l1d_read_access[2];		// L1 Data cache read access
	unsigned *l1d_read_miss[2];			// L1 Data cache read miss
	unsigned *l1d_write_access[2];		// L1 Data cache write access
	unsigned *l1d_write_miss[2];		// L1 Data cache write miss
	unsigned *shmem_read_access[2]; 	// Shared memory access

	// Low level L2 stats
	unsigned *n_l2_read_access[2];
	unsigned *n_l2_read_miss[2];
	unsigned *n_l2_write_access[2];
	unsigned *n_l2_write_miss[2];

	// Low level DRAM stats
    unsigned *n_cmd[2];
    unsigned *n_activity[2];
    unsigned *n_nop[2];
    unsigned *n_act[2];
    unsigned *n_pre[2];
    unsigned *n_rd[2];
    unsigned *n_wr[2];
    unsigned *n_req[2];

    // Interconnect stats
    unsigned *n_simt_to_mem[2];
    unsigned *n_mem_to_simt[2];
};



class power_mem_stat_t : public mem_power_stats_pod{
public:
   power_mem_stat_t(const struct memory_config *mem_config, const struct shader_core_config *shdr_config, memory_stats_t *mem_stats, shader_core_stats *shdr_stats);
   void visualizer_print( gzFile visualizer_file );
   void print (FILE *fout) const;
   void init();
   void save_stats();
private:
   memory_stats_t *m_mem_stats;
   shader_core_stats * m_core_stats;
   const memory_config *m_config;
   const shader_core_config *m_core_config;
};


class power_stat_t {
public:
   power_stat_t( const struct shader_core_config *shader_config,float * average_pipeline_duty_cycle,float * active_sms,shader_core_stats * shader_stats, const struct memory_config *mem_config,memory_stats_t * memory_stats);
   void visualizer_print( gzFile visualizer_file );
   void print (FILE *fout) const;
   void save_stats(){
	   pwr_core_stat->save_stats();
	   pwr_mem_stat->save_stats();
	   *m_average_pipeline_duty_cycle=0;
	   *m_active_sms=0;
   }


   float get_total_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_decoded_insn[0][i]) - (pwr_core_stat->m_num_decoded_insn[1][i]);
	   }
	   return total_inst;
   }
   float get_total_int_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_INTdecoded_insn[0][i]) - (pwr_core_stat->m_num_INTdecoded_insn[1][i]);
	   }
	   return total_inst;
   }
   float get_total_fp_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_FPdecoded_insn[0][i]) - (pwr_core_stat->m_num_FPdecoded_insn[1][i]);
	   }
	   return total_inst;
   }
   float get_total_load_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_loadqueued_insn[0][i]) - (pwr_core_stat->m_num_loadqueued_insn[1][i]);
	   }
	   return total_inst;
   }
   float get_total_store_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_storequeued_insn[0][i]) - (pwr_core_stat->m_num_storequeued_insn[1][i]);
	   }
	   return total_inst;
   }
   float get_sp_committed_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_sp_committed[0][i]) - (pwr_core_stat->m_num_sp_committed[1][i]);
	   }
	   return total_inst;
   }
   float get_sfu_committed_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_sfu_committed[0][i]) - (pwr_core_stat->m_num_sfu_committed[1][i]);
	   }
	   return total_inst;
   }
   float get_mem_committed_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_mem_committed[0][i]) - (pwr_core_stat->m_num_mem_committed[1][i]);
	   }
	   return total_inst;
   }
   float get_committed_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_mem_committed[0][i]) - (pwr_core_stat->m_num_mem_committed[1][i])
				       +(pwr_core_stat->m_num_sfu_committed[0][i]) - (pwr_core_stat->m_num_sfu_committed[1][i])
				       +(pwr_core_stat->m_num_sp_committed[0][i]) - (pwr_core_stat->m_num_sp_committed[1][i]);
	   }
	   return total_inst;
   }
   float get_regfile_reads(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_read_regfile_acesses[0][i]) - (pwr_core_stat->m_read_regfile_acesses[1][i]);
	   }
	   return total_inst;
   }
   float get_regfile_writes(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_write_regfile_acesses[0][i]) - (pwr_core_stat->m_write_regfile_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_pipeline_duty(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_pipeline_duty_cycle[0][i]) - (pwr_core_stat->m_pipeline_duty_cycle[1][i]);
	   }
	   return total_inst;
   }

   float get_non_regfile_operands(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_non_rf_operands[0][i]) - (pwr_core_stat->m_non_rf_operands[1][i]);
	   }
	   return total_inst;
   }

   float get_sp_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_sp_acesses[0][i]) - (pwr_core_stat->m_num_sp_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_sfu_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_sfu_acesses[0][i]) - (pwr_core_stat->m_num_sfu_acesses[1][i]);
	   }
	   return total_inst;
   }
   float get_trans_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_trans_acesses[0][i]) - (pwr_core_stat->m_num_trans_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_mem_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_mem_acesses[0][i]) - (pwr_core_stat->m_num_mem_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_intdiv_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_idiv_acesses[0][i]) - (pwr_core_stat->m_num_idiv_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_fpdiv_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_fpdiv_acesses[0][i]) - (pwr_core_stat->m_num_fpdiv_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_intmul32_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_imul32_acesses[0][i]) - (pwr_core_stat->m_num_imul32_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_intmul24_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_imul24_acesses[0][i]) - (pwr_core_stat->m_num_imul24_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_intmul_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_imul_acesses[0][i]) - (pwr_core_stat->m_num_imul_acesses[1][i])+
				   	   (pwr_core_stat->m_num_imul24_acesses[0][i]) - (pwr_core_stat->m_num_imul24_acesses[1][i])+
				   	   (pwr_core_stat->m_num_imul32_acesses[0][i]) - (pwr_core_stat->m_num_imul32_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_fpmul_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_fp_acesses[0][i]) - (pwr_core_stat->m_num_fp_acesses[1][i]);
	   }
	   return total_inst;
   }

   float get_sp_active_lanes(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_active_sp_lanes[0][i]) - (pwr_core_stat->m_active_sp_lanes[1][i]);
	   }
	   return (total_inst/m_config->num_shader())/m_config->gpgpu_num_sp_units;
   }

   float get_sfu_active_lanes(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_active_sfu_lanes[0][i]) - (pwr_core_stat->m_active_sfu_lanes[1][i]);	   }

	   return (total_inst/m_config->num_shader())/m_config->gpgpu_num_sfu_units;
   }

/**********************************************/
/*******
 Jingwen : per core stats
** ***/
   float get_core_inst(unsigned i){ // core id = i
	   	float total_inst=0;
		total_inst+=(pwr_core_stat->m_num_decoded_insn[0][i]) - (pwr_core_stat->m_num_decoded_insn[1][i]);
	   	return total_inst;
   }
   float get_core_int_inst(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_INTdecoded_insn[0][i]) - (pwr_core_stat->m_num_INTdecoded_insn[1][i]);
	   return total_inst;
   }
   float get_core_fp_inst(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_FPdecoded_insn[0][i]) - (pwr_core_stat->m_num_FPdecoded_insn[1][i]);
	   return total_inst;
   }
   float get_core_load_inst(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_loadqueued_insn[0][i]) - (pwr_core_stat->m_num_loadqueued_insn[1][i]);
	   return total_inst;
   }
   float get_core_store_inst(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_storequeued_insn[0][i]) - (pwr_core_stat->m_num_storequeued_insn[1][i]);
	   return total_inst;
   }
   float get_core_sp_committed_inst(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_sp_committed[0][i]) - (pwr_core_stat->m_num_sp_committed[1][i]);
	   return total_inst;
   }
   float get_core_sfu_committed_inst(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_sfu_committed[0][i]) - (pwr_core_stat->m_num_sfu_committed[1][i]);
	   return total_inst;
   }
   float get_core_mem_committed_inst(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_mem_committed[0][i]) - (pwr_core_stat->m_num_mem_committed[1][i]);
	   return total_inst;
   }
   float get_core_committed_inst(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_mem_committed[0][i]) - (pwr_core_stat->m_num_mem_committed[1][i])
				 +(pwr_core_stat->m_num_sfu_committed[0][i]) - (pwr_core_stat->m_num_sfu_committed[1][i])
				 +(pwr_core_stat->m_num_sp_committed[0][i]) - (pwr_core_stat->m_num_sp_committed[1][i]);
	   return total_inst;
   }
   float get_core_regfile_reads(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_read_regfile_acesses[0][i]) - (pwr_core_stat->m_read_regfile_acesses[1][i]);
	   return total_inst;
   }
   float get_core_regfile_writes(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_write_regfile_acesses[0][i]) - (pwr_core_stat->m_write_regfile_acesses[1][i]);
	   return total_inst;
   }

   float get_core_pipeline_duty(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_pipeline_duty_cycle[0][i]) - (pwr_core_stat->m_pipeline_duty_cycle[1][i]);
	   return total_inst;
   }

   float get_core_non_regfile_operands(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_non_rf_operands[0][i]) - (pwr_core_stat->m_non_rf_operands[1][i]);
	   return total_inst;
   }

   float get_core_sp_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_sp_acesses[0][i]) - (pwr_core_stat->m_num_sp_acesses[1][i]);
	   return total_inst;
   }

   float get_core_sfu_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_sfu_acesses[0][i]) - (pwr_core_stat->m_num_sfu_acesses[1][i]);
	   return total_inst;
   }
   float get_core_trans_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_trans_acesses[0][i]) - (pwr_core_stat->m_num_trans_acesses[1][i]);
	   return total_inst;
   }
   float get_core_mem_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_mem_acesses[0][i]) - (pwr_core_stat->m_num_mem_acesses[1][i]);
	   return total_inst;
   }

   float get_core_intdiv_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_idiv_acesses[0][i]) - (pwr_core_stat->m_num_idiv_acesses[1][i]);
	   return total_inst;
   }

   float get_core_fpdiv_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_fpdiv_acesses[0][i]) - (pwr_core_stat->m_num_fpdiv_acesses[1][i]);
	   return total_inst;
   }

   float get_core_intmul32_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_imul32_acesses[0][i]) - (pwr_core_stat->m_num_imul32_acesses[1][i]);
	   return total_inst;
   }

   float get_core_intmul24_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_imul24_acesses[0][i]) - (pwr_core_stat->m_num_imul24_acesses[1][i]);
	   return total_inst;
   }

   float get_core_intmul_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_imul_acesses[0][i]) - (pwr_core_stat->m_num_imul_acesses[1][i])+
			   	   (pwr_core_stat->m_num_imul24_acesses[0][i]) - (pwr_core_stat->m_num_imul24_acesses[1][i])+
			   	   (pwr_core_stat->m_num_imul32_acesses[0][i]) - (pwr_core_stat->m_num_imul32_acesses[1][i]);
	   return total_inst;
   }

   float get_core_fpmul_accessess(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_num_fp_acesses[0][i]) - (pwr_core_stat->m_num_fp_acesses[1][i]);
	   return total_inst;
   }

   float get_core_sp_active_lanes(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_active_sp_lanes[0][i]) - (pwr_core_stat->m_active_sp_lanes[1][i]);
	   return (total_inst/m_config->num_shader())/m_config->gpgpu_num_sp_units;
   }

   float get_core_sfu_active_lanes(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_core_stat->m_active_sfu_lanes[0][i]) - (pwr_core_stat->m_active_sfu_lanes[1][i]);
	   return (total_inst/m_config->num_shader())/m_config->gpgpu_num_sfu_units;
   }


/***
 * Jingwen: decide next cycle's decrement
 * get_tot_counts_next_cycle_delta
 */
 double per_core_fpu_next_cycle_decrement[100];
   void get_tot_fpu_next_cycle_decrement (float elapsed_cycles){

	   for(unsigned i=0; i<m_config->num_shader();i++){
   		   per_core_fpu_next_cycle_decrement[i]=0;
		   per_core_fpu_next_cycle_decrement[i]+=pwr_core_stat->m_core_stats->circular_stats_fpalu[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
		   per_core_fpu_next_cycle_decrement[i]+=pwr_core_stat->m_core_stats->circular_stats_fpdiv[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
		   per_core_fpu_next_cycle_decrement[i]+=pwr_core_stat->m_core_stats->circular_stats_fpmul[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
		   per_core_fpu_next_cycle_decrement[i]+=pwr_core_stat->m_core_stats->circular_stats_imul24[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
		   per_core_fpu_next_cycle_decrement[i]+=pwr_core_stat->m_core_stats->circular_stats_imul[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
		   per_core_fpu_next_cycle_decrement[i]+= (get_core_load_inst(i) + get_core_store_inst(i));
	       per_core_fpu_next_cycle_decrement[i]+= pwr_core_stat->m_core_stats->circular_stats_tex[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
	   }
   }

/*******
 Jingwen : use fuction that average the muticycle operations
** ***/

   float per_core_fpu_accesses[100];
   float get_tot_fpu_accessess(float elapsed_cycles){

	   float total_inst=0;
	   get_tex_inst(elapsed_cycles);

	   for(unsigned i=0; i<m_config->num_shader();i++){
   		   per_core_fpu_accesses[i]=0;
		   per_core_fpu_accesses[i]+=pwr_core_stat->m_core_stats->circular_stats_fpalu[i].get_tot_counts(elapsed_cycles);
		   //if ( i == 0 && per_core_fpu_accesses[i] > 0) {
		    //printf("get_tot_fpu_accessess 1 - %f\n",per_core_fpu_accesses[i]);
		   //}
		   per_core_fpu_accesses[i]+=pwr_core_stat->m_core_stats->circular_stats_fpdiv[i].get_tot_counts(elapsed_cycles);
		   //if ( i == 0 && per_core_fpu_accesses[i] > 0) {
		    //printf("get_tot_fpu_accessess 2 - %f\n",per_core_fpu_accesses[i]);
		   //}
		   per_core_fpu_accesses[i]+=pwr_core_stat->m_core_stats->circular_stats_fpmul[i].get_tot_counts(elapsed_cycles);
		   //if ( i == 0 && per_core_fpu_accesses[i] > 0) {
		    //printf("get_tot_fpu_accessess 3 - %f\n",per_core_fpu_accesses[i]);
		   //}
		   per_core_fpu_accesses[i]+=pwr_core_stat->m_core_stats->circular_stats_imul24[i].get_tot_counts(elapsed_cycles);
		   //if ( i == 0 && per_core_fpu_accesses[i] > 0) {
		    //printf("get_tot_fpu_accessess 4 - %f\n",per_core_fpu_accesses[i]);
		   //}
		   per_core_fpu_accesses[i]+=pwr_core_stat->m_core_stats->circular_stats_imul[i].get_tot_counts(elapsed_cycles);
		   //if ( i == 0 && per_core_fpu_accesses[i] > 0) {
		   // printf("get_tot_fpu_accessess 5 - %f\n",per_core_fpu_accesses[i]);
		   //}
		   per_core_fpu_accesses[i]+= (get_core_load_inst(i) + get_core_store_inst(i));
		   //if ( i == 0 && per_core_fpu_accesses[i] > 0) {
		   // printf("get_tot_fpu_accessess 6 - %f\n",per_core_fpu_accesses[i]);
		   //}
	       per_core_fpu_accesses[i]+= get_core_tex_inst(i,elapsed_cycles);
		   //if ( i == 0 && per_core_fpu_accesses[i] > 0) {
		   // printf("get_tot_fpu_accessess 7 - %f\n",per_core_fpu_accesses[i]);
		   //}
		   total_inst+=per_core_fpu_accesses[i];
	   }
   
	   return total_inst;
   }

   float get_core_fpu_accessess(unsigned i, float elapsed_cycles){

	   float total_inst=0;

	   total_inst+=per_core_fpu_accesses[i];
	   return total_inst;
   }

/**********************************************/
   float get_tot_fpu_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_fp_acesses[0][i]) - (pwr_core_stat->m_num_fp_acesses[1][i])+
			   (pwr_core_stat->m_num_fpdiv_acesses[0][i]) - (pwr_core_stat->m_num_fpdiv_acesses[1][i])+
				       (pwr_core_stat->m_num_fpmul_acesses[0][i]) - (pwr_core_stat->m_num_fpmul_acesses[1][i])+
				       (pwr_core_stat->m_num_imul24_acesses[0][i]) - (pwr_core_stat->m_num_imul24_acesses[1][i])+
					(pwr_core_stat->m_num_imul_acesses[0][i]) - (pwr_core_stat->m_num_imul_acesses[1][i])       ;
		   //printf("imul_accesses0: %d imul_acccesses1: %d imul0 - imul1: %d\n",(pwr_core_stat->m_num_imul_acesses[0][i]),(pwr_core_stat->m_num_imul_acesses[1][i]),(pwr_core_stat->m_num_imul_acesses[0][i]-pwr_core_stat->m_num_imul_acesses[1][i]));
		   //printf("imul24_accesses0: %d imul24_acccesses1: %d imu24l0 - imul241: %d\n",(pwr_core_stat->m_num_imul24_acesses[0][i]),(pwr_core_stat->m_num_imul24_acesses[1][i]),(pwr_core_stat->m_num_imul24_acesses[0][i]-pwr_core_stat->m_num_imul24_acesses[1][i]));
		   //printf("total_insn:%d\n",total_inst);


	   }
	   total_inst += get_total_load_inst()+get_total_store_inst()+get_tex_inst();
	   return total_inst;
   }


/**********************************************/
//Jingwen
   float per_core_sfu_next_cycle_decrement[100];
   void get_tot_sfu_next_cycle_decrement ( float elapsed_cycles ) {


	   for(unsigned i=0; i<m_config->num_shader();i++){
		   per_core_sfu_next_cycle_decrement[i]=pwr_core_stat->m_core_stats->circular_stats_idiv[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
		   per_core_sfu_next_cycle_decrement[i]+=pwr_core_stat->m_core_stats->circular_stats_imul32[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
		   per_core_sfu_next_cycle_decrement[i]+=pwr_core_stat->m_core_stats->circular_stats_trans[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
	   }
   }
   
   
   float per_core_sfu_accesses[100];
   // this function has to be called after the get_tot_sfu_accesss()
   float get_core_sfu_accessess( unsigned i, float elapsed_cycles ) {
   		float total_inst = per_core_sfu_accesses[i];
		return total_inst;
   }

   float get_tot_sfu_accessess( float elapsed_cycles ) {

	   float total_inst=0;

	   for(unsigned i=0; i<m_config->num_shader();i++){
		   per_core_sfu_accesses[i]=pwr_core_stat->m_core_stats->circular_stats_idiv[i].get_tot_counts(elapsed_cycles);
		   per_core_sfu_accesses[i]+=pwr_core_stat->m_core_stats->circular_stats_imul32[i].get_tot_counts(elapsed_cycles);
		   per_core_sfu_accesses[i]+=pwr_core_stat->m_core_stats->circular_stats_trans[i].get_tot_counts(elapsed_cycles);
		   total_inst+=per_core_sfu_accesses[i];
	   }
	   return total_inst;
   }


/**********************************************/
   float get_tot_sfu_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+= 
				        (pwr_core_stat->m_num_idiv_acesses[0][i]) - (pwr_core_stat->m_num_idiv_acesses[1][i])+
				        (pwr_core_stat->m_num_imul32_acesses[0][i]) - (pwr_core_stat->m_num_imul32_acesses[1][i])+
						(pwr_core_stat->m_num_trans_acesses[0][i]) - (pwr_core_stat->m_num_trans_acesses[1][i]);
	   }
	   return total_inst;
   }


/**********************************************/
//Jingwen
   float per_core_alu_next_cycle_decrement[100];
   void get_tot_alu_next_cycle_decrement(float elapsed_cycles){
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   per_core_alu_next_cycle_decrement[i]=pwr_core_stat->m_core_stats->circular_stats_ialu[i].get_tot_counts_next_cycle_delta(elapsed_cycles);
	   }
   }

   float per_core_ialue_accesses[100];
   float get_core_ialu_accessess(unsigned i, float elapsed_cycles){
		   float total_inst=per_core_ialue_accesses[i];
		   return total_inst;
   }
   float get_ialu_accessess(float elapsed_cycles){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   per_core_ialue_accesses[i]=pwr_core_stat->m_core_stats->circular_stats_ialu[i].get_tot_counts(elapsed_cycles);
		   total_inst+=per_core_ialue_accesses[i];
	   }
	   return total_inst;
   }


/**********************************************/
   float get_ialu_accessess(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_ialu_acesses[0][i]) - (pwr_core_stat->m_num_ialu_acesses[1][i]);
	   }
	   return total_inst;
   }

/**********************************************/
// Jingwen
   float per_core_tex_inst[100];
   float get_core_tex_inst( unsigned i,  float elapsed_cycles ){
		   float total_inst=per_core_tex_inst[i];
		   return total_inst;
   }

   float get_tex_inst( float elapsed_cycles ){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   per_core_tex_inst[i]=pwr_core_stat->m_core_stats->circular_stats_tex[i].get_tot_counts(elapsed_cycles);
		   total_inst+=per_core_tex_inst[i];
	   }
	   return total_inst;
   }

   float get_tex_inst(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_core_stat->m_num_tex_inst[0][i]) - (pwr_core_stat->m_num_tex_inst[1][i]);
	   }
	   return total_inst;
   }

   float get_core_constant_c_accesses(unsigned i){
	   float total_inst=0;
	   total_inst = (pwr_mem_stat->const_c_read_access[0][i]) - (pwr_mem_stat->const_c_read_access[1][i]);
	   return total_inst;
   }

   float get_constant_c_accesses(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   unsigned core_inst = (pwr_mem_stat->const_c_read_access[0][i]) - (pwr_mem_stat->const_c_read_access[1][i]);
		   total_inst+=core_inst;
		   //fprintf(stderr, "c$_access: core:%d, access:%d\n", i, core_inst);
	   }
	   return total_inst;
   }


   float get_core_constant_c_misses(unsigned i){
	   float total_inst=0;
	   unsigned core_inst = (pwr_mem_stat->const_c_read_miss[0][i]) - (pwr_mem_stat->const_c_read_miss[1][i]);
	   total_inst+=core_inst;
	   return total_inst;
   }
   float get_constant_c_misses(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   unsigned core_inst = (pwr_mem_stat->const_c_read_miss[0][i]) - (pwr_mem_stat->const_c_read_miss[1][i]);
		   total_inst+=core_inst;
		   //fprintf(stderr, "c$_misses: core:%d, access:%d\n", i, core_inst);
	   }
	   return total_inst;
   }

   float get_core_constant_c_hits(unsigned i){
	   return (get_core_constant_c_accesses(i)-get_core_constant_c_misses(i));
   }
   float get_constant_c_hits(){
	   return (get_constant_c_accesses()-get_constant_c_misses());
   }


   float get_core_texture_c_accesses(unsigned i){
	   float total_inst=0;
	   unsigned core_inst = (pwr_mem_stat->text_c_read_access[0][i]) - (pwr_mem_stat->text_c_read_access[1][i]);
	   total_inst+=core_inst;
	   return total_inst;
   }
   float get_texture_c_accesses(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   unsigned core_inst = (pwr_mem_stat->text_c_read_access[0][i]) - (pwr_mem_stat->text_c_read_access[1][i]);
		   total_inst+=core_inst;
		   //fprintf(stderr, "t$_accesses: core:%d, access:%d\n", i, core_inst);
	   }
	   return total_inst;
   }
   float get_core_texture_c_misses(unsigned i){
	   float total_inst=0;
	   unsigned core_inst = (pwr_mem_stat->text_c_read_miss[0][i]) - (pwr_mem_stat->text_c_read_miss[1][i]);
	   total_inst+=core_inst;
	   return total_inst;
   }
   float get_texture_c_misses(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   unsigned core_inst = (pwr_mem_stat->text_c_read_miss[0][i]) - (pwr_mem_stat->text_c_read_miss[1][i]);
		   total_inst+=core_inst;
		   //fprintf(stderr, "t$_misses : core:%d, access:%d\n", i, core_inst);
	   }
	   return total_inst;
   }
   float get_core_texture_c_hits(unsigned i){
	   return ( get_core_texture_c_accesses(i)- get_core_texture_c_misses(i));
   }
   float get_texture_c_hits(){
	   return ( get_texture_c_accesses()- get_texture_c_misses());
   }


   float get_core_inst_c_accesses(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_mem_stat->inst_c_read_access[0][i]) - (pwr_mem_stat->inst_c_read_access[1][i]);
	   return total_inst;
   }
   float get_inst_c_accesses(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_mem_stat->inst_c_read_access[0][i]) - (pwr_mem_stat->inst_c_read_access[1][i]);
	   }
	   return total_inst;
   }
   float get_core_inst_c_misses(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_mem_stat->inst_c_read_miss[0][i]) - (pwr_mem_stat->inst_c_read_miss[1][i]);
	   return total_inst;
   }
   float get_inst_c_misses(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_mem_stat->inst_c_read_miss[0][i]) - (pwr_mem_stat->inst_c_read_miss[1][i]);
	   }
	   return total_inst;
   }
   float get_core_inst_c_hits(unsigned i){
	   return (get_core_inst_c_accesses(i)-get_core_inst_c_misses(i));
   }
   float get_inst_c_hits(){
	   return (get_inst_c_accesses()-get_inst_c_misses());
   }

   float get_core_l1d_read_accesses(unsigned i){
	   float total_inst=0;
	   unsigned core_inst = (pwr_mem_stat->l1d_read_access[0][i]) - (pwr_mem_stat->l1d_read_access[1][i]);
	   total_inst+=core_inst;
	   return total_inst;
   }
   float get_l1d_read_accesses(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   unsigned core_inst = (pwr_mem_stat->l1d_read_access[0][i]) - (pwr_mem_stat->l1d_read_access[1][i]);
		   total_inst+=core_inst;
		   //fprintf(stderr, "l1d$_r_accesses : core:%d, access:%d\n", i, core_inst);
	   }
	   return total_inst;
   }
   float get_core_l1d_read_misses(unsigned i){
	   float total_inst=0;
	   unsigned core_inst = (pwr_mem_stat->l1d_read_miss[0][i]) - (pwr_mem_stat->l1d_read_miss[1][i]);
	   total_inst+=core_inst;
	   return total_inst;
   }
   float get_l1d_read_misses(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   unsigned core_inst = (pwr_mem_stat->l1d_read_miss[0][i]) - (pwr_mem_stat->l1d_read_miss[1][i]);
		   total_inst+=core_inst;
		   if ( core_inst > 10 ) {
		   		fprintf(stderr, "core %d l1d_read_misses bigger than 10 (%d)!\n", i, core_inst);
		   }
		   //fprintf(stderr, "l1d$_r_misses : core:%d, access:%d\n", i, core_inst);
	   }
	   return total_inst;
   }
   float get_core_l1d_read_hits(unsigned i){
	   return (get_core_l1d_read_accesses(i)-get_core_l1d_read_misses(i));
   }
   float get_l1d_read_hits(){
	   return (get_l1d_read_accesses()-get_l1d_read_misses());
   }
   float get_core_l1d_write_accesses(unsigned i){
 	   float total_inst=0;
	   unsigned core_inst = (pwr_mem_stat->l1d_write_access[0][i]) - (pwr_mem_stat->l1d_write_access[1][i]);
	   total_inst+=core_inst;
 	   return total_inst;
    }
   float get_l1d_write_accesses(){
 	   float total_inst=0;
 	   for(unsigned i=0; i<m_config->num_shader();i++){
		   unsigned core_inst = (pwr_mem_stat->l1d_write_access[0][i]) - (pwr_mem_stat->l1d_write_access[1][i]);
		   total_inst+=core_inst;
		   //fprintf(stderr, "l1d$_w_accesses : core:%d, access:%d\n", i, core_inst);
 	   }
 	   return total_inst;
    }
   float get_core_l1d_write_misses(unsigned i){
	   float total_inst=0;
	   unsigned core_inst = (pwr_mem_stat->l1d_write_miss[0][i]) - (pwr_mem_stat->l1d_write_miss[1][i]);
	   total_inst+=core_inst;
	   return total_inst;
   }
   float get_l1d_write_misses(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   unsigned core_inst = (pwr_mem_stat->l1d_write_miss[0][i]) - (pwr_mem_stat->l1d_write_miss[1][i]);
		   total_inst+=core_inst;
		   //fprintf(stderr, "l1d$_w_misses : core:%d, access:%d\n", i, core_inst);
	   }
	   return total_inst;
   }
   float get_core_l1d_write_hits(unsigned i){
	   return (get_core_l1d_write_accesses(i)-get_core_l1d_write_misses(i));
   }
   float get_l1d_write_hits(){
	   return (get_l1d_write_accesses()-get_l1d_write_misses());
   }
	float get_cache_misses(){
     return get_l1d_read_misses()+get_constant_c_misses()+get_l1d_write_misses()+
		      get_texture_c_misses();
	}
	
	float get_cache_read_misses(){
     return get_l1d_read_misses()+get_constant_c_misses()+
		      get_texture_c_misses();
	}

	float get_cache_write_misses(){
     return get_l1d_write_misses();
	}

   float get_core_shmem_read_access(unsigned i){
	   float total_inst=0;
	   total_inst+=(pwr_mem_stat->shmem_read_access[0][i]) - (pwr_mem_stat->shmem_read_access[1][i]);
	   return total_inst;
   }
   float get_shmem_read_access(){
	   float total_inst=0;
	   for(unsigned i=0; i<m_config->num_shader();i++){
		   total_inst+=(pwr_mem_stat->shmem_read_access[0][i]) - (pwr_mem_stat->shmem_read_access[1][i]);
	   }
	   return total_inst;
   }

   float get_l2_read_accesses(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_l2_read_access[0][i] - pwr_mem_stat->n_l2_read_access[1][i]);
	   }
	   return total;
   }

   float get_l2_read_misses(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_l2_read_miss[0][i] - pwr_mem_stat->n_l2_read_miss[1][i]);
	   }
	   return total;
   }

   float get_l2_read_hits(){
	   return (get_l2_read_accesses()-get_l2_read_misses());
   }

   float get_l2_write_accesses(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_l2_write_access[0][i] - pwr_mem_stat->n_l2_write_access[1][i]);
	   }
	   return total;
   }

   float get_l2_write_misses(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_l2_write_miss[0][i] - pwr_mem_stat->n_l2_write_miss[1][i]);
	   }
	   return total;
   }
   float get_l2_write_hits(){
	   return (get_l2_write_accesses()-get_l2_write_misses());
   }
   float get_dram_cmd(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_cmd[0][i] - pwr_mem_stat->n_cmd[1][i]);
	   }
	   return total;
   }
   float get_dram_activity(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_activity[0][i] - pwr_mem_stat->n_activity[1][i]);
	   }
	   return total;
   }
   float get_dram_nop(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_nop[0][i] - pwr_mem_stat->n_nop[1][i]);
	   }
	   return total;
   }
   float get_dram_act(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_act[0][i] - pwr_mem_stat->n_act[1][i]);
	   }
	   return total;
   }
   float get_dram_pre(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_pre[0][i] - pwr_mem_stat->n_pre[1][i]);
	   }
	   return total;
   }
   float get_dram_rd(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_rd[0][i] - pwr_mem_stat->n_rd[1][i]);
	   }
	   return total;
   }
   float get_dram_wr(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_wr[0][i] - pwr_mem_stat->n_wr[1][i]);
	   }
	   return total;
   }
   float get_dram_req(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_req[0][i] - pwr_mem_stat->n_req[1][i]);
	   }
	   return total;
   }

   float get_icnt_simt_to_mem(){
	   float total=0;
	   for(unsigned i=0; i<m_config->num_shader(); ++i){
		   total += (pwr_mem_stat->n_simt_to_mem[0][i] - pwr_mem_stat->n_simt_to_mem[1][i]);
	   }
	   return total;
   }

   float get_icnt_mem_to_simt(){
	   float total=0;
	   for(unsigned i=0; i<m_mem_config->m_n_mem; ++i){
		   total += (pwr_mem_stat->n_mem_to_simt[0][i] - pwr_mem_stat->n_mem_to_simt[1][i]);
	   }
	   return total;
   }

   power_core_stat_t * pwr_core_stat;
   power_mem_stat_t * pwr_mem_stat;
   float * m_average_pipeline_duty_cycle;
   float * m_active_sms;
   const shader_core_config *m_config;
   const struct memory_config *m_mem_config;
};


#endif /*POWER_LATENCY_STAT_H*/
