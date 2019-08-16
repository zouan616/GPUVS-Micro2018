// Copyright (c) 2009-2011, Tor M. Aamodt, Wilson W.L. Fung, Andrew Turner,
// Ali Bakhoda 
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

#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <list>
#include <bitset>
#include <utility>
#include <algorithm>
#include <deque>
#include <queue>

//#include "../cuda-sim/ptx.tab.h"

#include "delayqueue.h"
#include "stack.h"
#include "dram.h"
#include "../abstract_hardware_model.h"
#include "scoreboard.h"
#include "mem_fetch.h"
#include "stats.h"
#include "gpu-cache.h"



#define NO_OP_FLAG            0xFF

/* READ_PACKET_SIZE:
   bytes: 6 address (flit can specify chanel so this gives up to ~2GB/channel, so good for now),
          2 bytes   [shaderid + mshrid](14 bits) + req_size(0-2 bits if req_size variable) - so up to 2^14 = 16384 mshr total 
 */

#define READ_PACKET_SIZE 8

//WRITE_PACKET_SIZE: bytes: 6 address, 2 miscelaneous. 
#define WRITE_PACKET_SIZE 8

#define WRITE_MASK_SIZE 8

//Set a hard limit of 32 CTAs per shader [cuda only has 8]
#define MAX_CTA_PER_SHADER 32

class CircularStats: public std::vector<float> {
public:
	bool  circular_stats_initialized;
	std::vector<float> remaining_cycles;
	float operation_latency; // in terms of cycles

	void  reduce_by(float elapsed_cycles) {
	}

/*************************************************/
	void  push(unsigned counts) {
		assert((this->size() < 5000) && 
			"Only allow 1000 maxim in the Circular Stats Bufferi!\n");
		assert(circular_stats_initialized);
		//float tmp = (float) counts * operation_latency;
		push_back(counts);
		remaining_cycles.push_back( operation_latency);
	}

/*************************************************/
	float get_tot_counts( float elapsed_cycles ) {

		iterator iter, iter2;
		iterator b    = begin();
		iterator b2   = remaining_cycles.begin();
		iterator e    = end();
		iterator e2   = remaining_cycles.end();
		float tot_counts = 0;
		
		assert( size() == remaining_cycles.size());
		//std::cout << "size = " << size() << " " << remaining_cycles.size() << "\n";

		for ( iter = b, iter2 = b2; iter != e && iter2 != e2; iter ++ , iter2 ++) {
			// if remaining impact less than the elapsed cycles, then 
			// add the remaining cycles to the total counts and 
			// erase the element
			if ( *iter2 <= elapsed_cycles ) {
				tot_counts += (*iter) * (*iter2);
				*iter  = 0;
				*iter2 = 0;
			} else {
				tot_counts += (*iter) * elapsed_cycles;
				(*iter2) -= elapsed_cycles;
			}
		}
		erase(std::remove(begin(), end(), 0), end());
		remaining_cycles.erase(std::remove(remaining_cycles.begin(), remaining_cycles.end(), 0), remaining_cycles.end()); 

		return tot_counts;
	
	}

/*************************************************/
	float get_tot_counts_next_cycle_delta (float elapsed_cycles) {

		iterator iter, iter2;
		iterator b    = begin();
		iterator b2   = remaining_cycles.begin();
		iterator e    = end();
		iterator e2   = remaining_cycles.end();
		float tot_counts = 0;
		
		assert( size() == remaining_cycles.size());
		//std::cout << "size = " << size() << " " << remaining_cycles.size() << "\n";

		for ( iter = b, iter2 = b2; iter != e && iter2 != e2; iter ++ , iter2 ++) {
			// if remaining impact less than the elapsed cycles + 1, then 
			// there will be a decrement next cycle
			if ( *iter2 < (elapsed_cycles + 1) && *iter2 >=  elapsed_cycles) {
				tot_counts += (*iter) * ((elapsed_cycles + 1) - (*iter2));
			} else if ( *iter2 < elapsed_cycles ) {
				tot_counts += (*iter) *  (*iter2);
			} 
		}
		return tot_counts;
	}

/*************************************************/
	CircularStats() {
		circular_stats_initialized = false;
	}
};

class thread_ctx_t {
public:
   unsigned m_cta_id; // hardware CTA this thread belongs

   // per thread stats (ac stands for accumulative).
   unsigned n_insn;
   unsigned n_insn_ac;
   unsigned n_l1_mis_ac;
   unsigned n_l1_mrghit_ac;
   unsigned n_l1_access_ac; 

   bool m_active; 
};

class shd_warp_t {
public:
    shd_warp_t( class shader_core_ctx *shader, unsigned warp_size) 
        : m_shader(shader), m_warp_size(warp_size)
    {
        m_stores_outstanding=0;
        m_inst_in_pipeline=0;
        reset(); 
    }
    void reset()
    {
        assert( m_stores_outstanding==0);
        assert( m_inst_in_pipeline==0);
        m_imiss_pending=false;
        m_warp_id=(unsigned)-1;
        m_dynamic_warp_id = (unsigned)-1;
        n_completed = m_warp_size; 
        m_n_atomic=0;
        m_membar=false;
        m_done_exit=true;
        m_last_fetch=0;
        m_next=0;
    }
    void init( address_type start_pc,
               unsigned cta_id,
               unsigned wid,
               const std::bitset<MAX_WARP_SIZE> &active,
               unsigned dynamic_warp_id )
    {
        m_cta_id=cta_id;
        m_warp_id=wid;
        m_dynamic_warp_id=dynamic_warp_id;
        m_next_pc=start_pc;
        assert( n_completed >= active.count() );
        assert( n_completed <= m_warp_size);
        n_completed   -= active.count(); // active threads are not yet completed
        m_active_threads = active;
        m_done_exit=false;
    }

    bool functional_done() const;
    bool waiting(); // not const due to membar
    bool hardware_done() const;

    bool done_exit() const { return m_done_exit; }
    void set_done_exit() { m_done_exit=true; }

    void print( FILE *fout ) const;
    void print_ibuffer( FILE *fout ) const;

    unsigned get_n_completed() const { return n_completed; }
    void set_completed( unsigned lane ) 
    { 
        assert( m_active_threads.test(lane) );
        m_active_threads.reset(lane);
        n_completed++; 
    }

    void set_last_fetch( unsigned long long sim_cycle ) { m_last_fetch=sim_cycle; }

    unsigned get_n_atomic() const { return m_n_atomic; }
    void inc_n_atomic() { m_n_atomic++; }
    void dec_n_atomic(unsigned n) { m_n_atomic-=n; }

    void set_membar() { m_membar=true; }
    void clear_membar() { m_membar=false; }
    bool get_membar() const { return m_membar; }
    address_type get_pc() const { return m_next_pc; }
    void set_next_pc( address_type pc ) { m_next_pc = pc; }

    void ibuffer_fill( unsigned slot, const warp_inst_t *pI )
    {
       assert(slot < IBUFFER_SIZE );
       m_ibuffer[slot].m_inst=pI;
       m_ibuffer[slot].m_valid=true;
       m_next=0; 
    }
    bool ibuffer_empty() const
    {
        for( unsigned i=0; i < IBUFFER_SIZE; i++) 
            if(m_ibuffer[i].m_valid) 
                return false;
        return true;
    }
    void ibuffer_flush()
    {
        for(unsigned i=0;i<IBUFFER_SIZE;i++) {
            if( m_ibuffer[i].m_valid )
                dec_inst_in_pipeline();
            m_ibuffer[i].m_inst=NULL; 
            m_ibuffer[i].m_valid=false; 
        }
    }
    const warp_inst_t *ibuffer_next_inst() { return m_ibuffer[m_next].m_inst; }
    bool ibuffer_next_valid() { return m_ibuffer[m_next].m_valid; }
    void ibuffer_free()
    {
        m_ibuffer[m_next].m_inst = NULL;
        m_ibuffer[m_next].m_valid = false;
    }
    void ibuffer_step() { m_next = (m_next+1)%IBUFFER_SIZE; }

    bool imiss_pending() const { return m_imiss_pending; }
    void set_imiss_pending() { m_imiss_pending=true; }
    void clear_imiss_pending() { m_imiss_pending=false; }

    bool stores_done() const { return m_stores_outstanding == 0; }
    void inc_store_req() { m_stores_outstanding++; }
    void dec_store_req() 
    {
        assert( m_stores_outstanding > 0 );
        m_stores_outstanding--;
    }

    bool inst_in_pipeline() const { return m_inst_in_pipeline > 0; }
    void inc_inst_in_pipeline() { m_inst_in_pipeline++; }
    void dec_inst_in_pipeline() 
    {
        assert( m_inst_in_pipeline > 0 );
        m_inst_in_pipeline--;
    }

    unsigned get_cta_id() const { return m_cta_id; }

    unsigned get_dynamic_warp_id() const { return m_dynamic_warp_id; }
    unsigned get_warp_id() const { return m_warp_id; }

private:
    static const unsigned IBUFFER_SIZE=2;
    class shader_core_ctx *m_shader;
    unsigned m_cta_id;
    unsigned m_warp_id;
    unsigned m_warp_size;
    unsigned m_dynamic_warp_id;

    address_type m_next_pc;
    unsigned n_completed;          // number of threads in warp completed
    std::bitset<MAX_WARP_SIZE> m_active_threads;

    bool m_imiss_pending;
    
    struct ibuffer_entry {
       ibuffer_entry() { m_valid = false; m_inst = NULL; }
       const warp_inst_t *m_inst;
       bool m_valid;
    };
    ibuffer_entry m_ibuffer[IBUFFER_SIZE]; 
    unsigned m_next;
                                   
    unsigned m_n_atomic;           // number of outstanding atomic operations 
    bool     m_membar;             // if true, warp is waiting at memory barrier

    bool m_done_exit; // true once thread exit has been registered for threads in this warp

    unsigned long long m_last_fetch;

    unsigned m_stores_outstanding; // number of store requests sent but not yet acknowledged
    unsigned m_inst_in_pipeline;
};



inline unsigned hw_tid_from_wid(unsigned wid, unsigned warp_size, unsigned i){return wid * warp_size + i;};
inline unsigned wid_from_hw_tid(unsigned tid, unsigned warp_size){return tid/warp_size;};

const unsigned WARP_PER_CTA_MAX = 48;
typedef std::bitset<WARP_PER_CTA_MAX> warp_set_t;

int register_bank(int regnum, int wid, unsigned num_banks, unsigned bank_warp_shift);

class shader_core_ctx;
class shader_core_config;
class shader_core_stats;

enum scheduler_prioritization_type
{
    SCHEDULER_PRIORITIZATION_LRR = 0, // Loose Round Robin
    SCHEDULER_PRIORITIZATION_SRR, // Strict Round Robin
    SCHEDULER_PRIORITIZATION_GTO, // Greedy Then Oldest
    SCHEDULER_PRIORITIZATION_GTLRR, // Greedy Then Loose Round Robin
    SCHEDULER_PRIORITIZATION_GTY, // Greedy Then Youngest
    SCHEDULER_PRIORITIZATION_OLDEST, // Oldest First
    SCHEDULER_PRIORITIZATION_YOUNGEST, // Youngest First
};

// Each of these corresponds to a string value in the gpgpsim.config file
// For example - to specify the LRR scheudler the config must contain lrr
enum concrete_scheduler
{
    CONCRETE_SCHEDULER_LRR = 0,
    CONCRETE_SCHEDULER_GTO,
    CONCRETE_SCHEDULER_TWO_LEVEL_ACTIVE,
    NUM_CONCRETE_SCHEDULERS
};

class scheduler_unit { //this can be copied freely, so can be used in std containers.
public:
    scheduler_unit(shader_core_stats* stats, shader_core_ctx* shader, 
                   Scoreboard* scoreboard, simt_stack** simt, 
                   std::vector<shd_warp_t>* warp, 
                   register_set* sp_out,
                   register_set* sfu_out,
                   register_set* mem_out,
                   int id) 
        : m_supervised_warps(), m_stats(stats), m_shader(shader),
        m_scoreboard(scoreboard), m_simt_stack(simt), /*m_pipeline_reg(pipe_regs),*/ m_warp(warp),
        m_sp_out(sp_out),m_sfu_out(sfu_out),m_mem_out(mem_out), m_id(id){}
    virtual ~scheduler_unit(){}
    virtual void add_supervised_warp_id(int i) {
        m_supervised_warps.push_back(&warp(i));
    }
    virtual void done_adding_supervised_warps() {
        m_last_supervised_issued = m_supervised_warps.end();
    }


    // The core scheduler cycle method is meant to be common between
    // all the derived schedulers.  The scheduler's behaviour can be
    // modified by changing the contents of the m_next_cycle_prioritized_warps list.
    void cycle();

    // These are some common ordering fucntions that the
    // higher order schedulers can take advantage of
    template < typename T >
    void order_lrr( typename std::vector< T >& result_list,
                    const typename std::vector< T >& input_list,
                    const typename std::vector< T >::const_iterator& last_issued_from_input,
                    unsigned num_warps_to_add );
    
    enum OrderingType 
    {
        // The item that issued last is prioritized first then the sorted result
        // of the priority_function
        ORDERING_GREEDY_THEN_PRIORITY_FUNC = 0,
        // No greedy scheduling based on last to issue. Only the priority function determines
        // priority
        ORDERED_PRIORITY_FUNC_ONLY,
        NUM_ORDERING,
    };
    template < typename U >
    void order_by_priority( std::vector< U >& result_list,
                            const typename std::vector< U >& input_list,
                            const typename std::vector< U >::const_iterator& last_issued_from_input,
                            unsigned num_warps_to_add,
                            OrderingType age_ordering,
                            bool (*priority_func)(U lhs, U rhs) );
    static bool sort_warps_by_oldest_dynamic_id(shd_warp_t* lhs, shd_warp_t* rhs);

    // Derived classes can override this function to populate
    // m_supervised_warps with their scheduling policies
    virtual void order_warps() = 0;

protected:
    virtual void do_on_warp_issued( unsigned warp_id,
                                    unsigned num_issued,
                                    const std::vector< shd_warp_t* >::const_iterator& prioritized_iter );
    inline int get_sid() const;
protected:
    shd_warp_t& warp(int i);

    // This is the prioritized warp list that is looped over each cycle to determine
    // which warp gets to issue.
    std::vector< shd_warp_t* > m_next_cycle_prioritized_warps;
    // The m_supervised_warps list is all the warps this scheduler is supposed to
    // arbitrate between.  This is useful in systems where there is more than
    // one warp scheduler. In a single scheduler system, this is simply all
    // the warps assigned to this core.
    std::vector< shd_warp_t* > m_supervised_warps;
    // This is the iterator pointer to the last supervised warp you issued
    std::vector< shd_warp_t* >::const_iterator m_last_supervised_issued;
    shader_core_stats *m_stats;
    shader_core_ctx* m_shader;
    // these things should become accessors: but would need a bigger rearchitect of how shader_core_ctx interacts with its parts.
    Scoreboard* m_scoreboard; 
    simt_stack** m_simt_stack;
    //warp_inst_t** m_pipeline_reg;
    std::vector<shd_warp_t>* m_warp;
    register_set* m_sp_out;
    register_set* m_sfu_out;
    register_set* m_mem_out;

    int m_id;
};

class lrr_scheduler : public scheduler_unit {
public:
	lrr_scheduler ( shader_core_stats* stats, shader_core_ctx* shader,
                    Scoreboard* scoreboard, simt_stack** simt,
                    std::vector<shd_warp_t>* warp,
                    register_set* sp_out,
                    register_set* sfu_out,
                    register_set* mem_out,
                    int id )
	: scheduler_unit ( stats, shader, scoreboard, simt, warp, sp_out, sfu_out, mem_out, id ){}
	virtual ~lrr_scheduler () {}
	virtual void order_warps ();
    virtual void done_adding_supervised_warps() {
        m_last_supervised_issued = m_supervised_warps.end();
    }
};

class gto_scheduler : public scheduler_unit {
public:
	gto_scheduler ( shader_core_stats* stats, shader_core_ctx* shader,
                    Scoreboard* scoreboard, simt_stack** simt,
                    std::vector<shd_warp_t>* warp,
                    register_set* sp_out,
                    register_set* sfu_out,
                    register_set* mem_out,
                    int id )
	: scheduler_unit ( stats, shader, scoreboard, simt, warp, sp_out, sfu_out, mem_out, id ){}
	virtual ~gto_scheduler () {}
	virtual void order_warps ();
    virtual void done_adding_supervised_warps() {
        m_last_supervised_issued = m_supervised_warps.begin();
    }

};


class two_level_active_scheduler : public scheduler_unit {
public:
	two_level_active_scheduler ( shader_core_stats* stats, shader_core_ctx* shader,
                          Scoreboard* scoreboard, simt_stack** simt,
                          std::vector<shd_warp_t>* warp,
                          register_set* sp_out,
                          register_set* sfu_out,
                          register_set* mem_out,
                          int id,
                          char* config_str )
	: scheduler_unit ( stats, shader, scoreboard, simt, warp, sp_out, sfu_out, mem_out, id ),
	  m_pending_warps()
    {
        int ret = sscanf( config_str,
                          "two_level_active:%d:%d:%d",
                          &m_max_active_warps,
                          (int*)&m_inner_level_prioritization,
                          (int*)&m_outer_level_prioritization );
        assert( 3 == ret );
    }
	virtual ~two_level_active_scheduler () {}
    virtual void order_warps();
	void add_supervised_warp_id(int i) {
        if ( m_next_cycle_prioritized_warps.size() < m_max_active_warps ) {
            m_next_cycle_prioritized_warps.push_back( &warp(i) );
        } else {
		    m_pending_warps.push_back(&warp(i));
        }
	}
    virtual void done_adding_supervised_warps() {
        m_last_supervised_issued = m_supervised_warps.begin();
    }

protected:
    virtual void do_on_warp_issued( unsigned warp_id,
                                    unsigned num_issued,
                                    const std::vector< shd_warp_t* >::const_iterator& prioritized_iter );

private:
	std::deque< shd_warp_t* > m_pending_warps; 
    scheduler_prioritization_type m_inner_level_prioritization;
    scheduler_prioritization_type m_outer_level_prioritization;
	unsigned m_max_active_warps;
};


#define MAX_DISPATCH_MONITOR_HISTORY_SIZE 1000

class opndcoll_rfu_t { // operand collector based register file unit
public:
   // constructors
   opndcoll_rfu_t()
   {
      m_num_banks=0;
      m_shader=NULL;
      m_initialized=false;
	  m_dispatched_warp_history.resize(MAX_DISPATCH_MONITOR_HISTORY_SIZE);
	  m_dispatched_warp_history_head=0;
   }
   void add_cu_set(unsigned cu_set, unsigned num_cu, unsigned num_dispatch);
   typedef std::vector<register_set*> port_vector_t;
   typedef std::vector<unsigned int> uint_vector_t;
   void add_port( port_vector_t & input, port_vector_t & ouput, uint_vector_t cu_sets);
   void init( unsigned num_banks, shader_core_ctx *shader );

   // modifiers
   bool writeback( const warp_inst_t &warp ); // might cause stall 

   void step()
   {
        dispatch_ready_cu();   
        allocate_reads();
        for( unsigned p = 0 ; p < m_in_ports.size(); p++ ) 
            allocate_cu( p );
        process_banks();
   }

   void dump( FILE *fp ) const
   {
      fprintf(fp,"\n");
      fprintf(fp,"Operand Collector State:\n");
      for( unsigned n=0; n < m_cu.size(); n++ ) {
         fprintf(fp,"   CU-%2u: ", n);
         m_cu[n]->dump(fp,m_shader);
      }
      m_arbiter.dump(fp);
   }

   shader_core_ctx *shader_core() { return m_shader; }


   // recording dispatched warp in last cycle
   unsigned m_last_cycle_dispatched_warp;
   std::vector<unsigned> m_dispatched_warp_history;
   unsigned m_dispatched_warp_history_head; 

private:

   void process_banks()
   {
      m_arbiter.reset_alloction();
   }

   void dispatch_ready_cu();
   void allocate_cu( unsigned port );
   void allocate_reads();

   // types

   class collector_unit_t;

   class op_t {
   public:

      op_t() { m_valid = false; }
      op_t( collector_unit_t *cu, unsigned op, unsigned reg, unsigned num_banks, unsigned bank_warp_shift )
      {
         m_valid = true;
         m_warp=NULL;
         m_cu = cu;
         m_operand = op;
         m_register = reg;
         m_bank = register_bank(reg,cu->get_warp_id(),num_banks,bank_warp_shift);
      }
      op_t( const warp_inst_t *warp, unsigned reg, unsigned num_banks, unsigned bank_warp_shift )
      {
         m_valid=true;
         m_warp=warp;
         m_register=reg;
         m_cu=NULL;
         m_operand = -1;
         m_bank = register_bank(reg,warp->warp_id(),num_banks,bank_warp_shift);
      }

      // accessors
      bool valid() const { return m_valid; }
      unsigned get_reg() const
      {
         assert( m_valid );
         return m_register;
      }
      unsigned get_wid() const
      {
          if( m_warp ) return m_warp->warp_id();
          else if( m_cu ) return m_cu->get_warp_id();
          else abort();
      }
      unsigned get_active_count() const
      {
          if( m_warp ) return m_warp->active_count();
          else if( m_cu ) return m_cu->get_active_count();
          else abort();
      }
      const active_mask_t & get_active_mask()
      {
          if( m_warp ) return m_warp->get_active_mask();
          else if( m_cu ) return m_cu->get_active_mask();
          else abort();
      }
      unsigned get_op3() const
      {
          if( m_warp ) return m_warp->op3;
          else if( m_cu ) return m_cu->get_op3();
          else abort();
      }
      unsigned get_oc_id() const { return m_cu->get_id(); }
      unsigned get_bank() const { return m_bank; }
      unsigned get_operand() const { return m_operand; }
      void dump(FILE *fp) const 
      {
         if(m_cu) 
            fprintf(fp," <R%u, CU:%u, w:%02u> ", m_register,m_cu->get_id(),m_cu->get_warp_id());
         else if( !m_warp->empty() )
            fprintf(fp," <R%u, wid:%02u> ", m_register,m_warp->warp_id() );
      }
      std::string get_reg_string() const
      {
         char buffer[64];
         snprintf(buffer,64,"R%u", m_register);
         return std::string(buffer);
      }

      // modifiers
      void reset() { m_valid = false; }
   private:
      bool m_valid;
      collector_unit_t  *m_cu; 
      const warp_inst_t *m_warp;
      unsigned  m_operand; // operand offset in instruction. e.g., add r1,r2,r3; r2 is oprd 0, r3 is 1 (r1 is dst)
      unsigned  m_register;
      unsigned  m_bank;
   };

   enum alloc_t {
      NO_ALLOC,
      READ_ALLOC,
      WRITE_ALLOC,
   };

   class allocation_t {
   public:
      allocation_t() { m_allocation = NO_ALLOC; }
      bool is_read() const { return m_allocation==READ_ALLOC; }
      bool is_write() const {return m_allocation==WRITE_ALLOC; }
      bool is_free() const {return m_allocation==NO_ALLOC; }
      void dump(FILE *fp) const {
         if( m_allocation == NO_ALLOC ) { fprintf(fp,"<free>"); }
         else if( m_allocation == READ_ALLOC ) { fprintf(fp,"rd: "); m_op.dump(fp); }
         else if( m_allocation == WRITE_ALLOC ) { fprintf(fp,"wr: "); m_op.dump(fp); }
         fprintf(fp,"\n");
      }
      void alloc_read( const op_t &op )  { assert(is_free()); m_allocation=READ_ALLOC; m_op=op; }
      void alloc_write( const op_t &op ) { assert(is_free()); m_allocation=WRITE_ALLOC; m_op=op; }
      void reset() { m_allocation = NO_ALLOC; }
   private:
      enum alloc_t m_allocation;
      op_t m_op;
   };

   class arbiter_t {
   public:
      // constructors
      arbiter_t()
      {
         m_queue=NULL;
         m_allocated_bank=NULL;
         m_allocator_rr_head=NULL;
         _inmatch=NULL;
         _outmatch=NULL;
         _request=NULL;
         m_last_cu=0;
      }
      void init( unsigned num_cu, unsigned num_banks ) 
      { 
         assert(num_cu > 0);
         assert(num_banks > 0);
         m_num_collectors = num_cu;
         m_num_banks = num_banks;
         _inmatch = new int[ m_num_banks ];
         _outmatch = new int[ m_num_collectors ];
         _request = new int*[ m_num_banks ];
         for(unsigned i=0; i<m_num_banks;i++) 
             _request[i] = new int[m_num_collectors];
         m_queue = new std::list<op_t>[num_banks];
         m_allocated_bank = new allocation_t[num_banks];
         m_allocator_rr_head = new unsigned[num_cu];
         for( unsigned n=0; n<num_cu;n++ ) 
            m_allocator_rr_head[n] = n%num_banks;
         reset_alloction();
      }

      // accessors
      void dump(FILE *fp) const
      {
         fprintf(fp,"\n");
         fprintf(fp,"  Arbiter State:\n");
         fprintf(fp,"  requests:\n");
         for( unsigned b=0; b<m_num_banks; b++ ) {
            fprintf(fp,"    bank %u : ", b );
            std::list<op_t>::const_iterator o = m_queue[b].begin();
            for(; o != m_queue[b].end(); o++ ) {
               o->dump(fp);
            }
            fprintf(fp,"\n");
         }
         fprintf(fp,"  grants:\n");
         for(unsigned b=0;b<m_num_banks;b++) {
            fprintf(fp,"    bank %u : ", b );
            m_allocated_bank[b].dump(fp);
         }
         fprintf(fp,"\n");
      }

      // modifiers
      std::list<op_t> allocate_reads(); 

      void add_read_requests( collector_unit_t *cu ) 
      {
         const op_t *src = cu->get_operands();
         for( unsigned i=0; i<MAX_REG_OPERANDS*2; i++) {
            const op_t &op = src[i];
            if( op.valid() ) {
               unsigned bank = op.get_bank();
               m_queue[bank].push_back(op);
            }
         }
      }
      bool bank_idle( unsigned bank ) const
      {
          return m_allocated_bank[bank].is_free();
      }
      void allocate_bank_for_write( unsigned bank, const op_t &op )
      {
         assert( bank < m_num_banks );
         m_allocated_bank[bank].alloc_write(op);
      }
      void allocate_for_read( unsigned bank, const op_t &op )
      {
         assert( bank < m_num_banks );
         m_allocated_bank[bank].alloc_read(op);
      }
      void reset_alloction()
      {
         for( unsigned b=0; b < m_num_banks; b++ ) 
            m_allocated_bank[b].reset();
      }

   private:
      unsigned m_num_banks;
      unsigned m_num_collectors;

      allocation_t *m_allocated_bank; // bank # -> register that wins
      std::list<op_t> *m_queue;

      unsigned *m_allocator_rr_head; // cu # -> next bank to check for request (rr-arb)
      unsigned  m_last_cu; // first cu to check while arb-ing banks (rr)

      int *_inmatch;
      int *_outmatch;
      int **_request;
   };

   class input_port_t {
   public:
       input_port_t(port_vector_t & input, port_vector_t & output, uint_vector_t cu_sets)
       : m_in(input),m_out(output), m_cu_sets(cu_sets)
       {
           assert(input.size() == output.size());
           assert(not m_cu_sets.empty());
       }
   //private:
       port_vector_t m_in,m_out;
       uint_vector_t m_cu_sets;
   };

   class collector_unit_t {
   public:
      // constructors
      collector_unit_t()
      { 
         m_free = true;
         m_warp = NULL;
         m_output_register = NULL;
         m_src_op = new op_t[MAX_REG_OPERANDS*2];
         m_not_ready.reset();
         m_warp_id = -1;
         m_num_banks = 0;
         m_bank_warp_shift = 0;
      }
      // accessors
      bool ready() const;
      const op_t *get_operands() const { return m_src_op; }
      void dump(FILE *fp, const shader_core_ctx *shader ) const;

      unsigned get_warp_id() const { return m_warp_id; }
      warp_inst_t * get_warp() const { return m_warp; }
      unsigned get_active_count() const { return m_warp->active_count(); }
      const active_mask_t & get_active_mask() const { return m_warp->get_active_mask(); }
      unsigned get_op3() const { return m_warp->op3; }
      unsigned get_id() const { return m_cuid; } // returns CU hw id

      // modifiers
      void init(unsigned n, 
                unsigned num_banks, 
                unsigned log2_warp_size,
                const core_config *config,
                opndcoll_rfu_t *rfu ); 
      bool allocate( register_set* pipeline_reg, register_set* output_reg );

      void collect_operand( unsigned op )
      {
         m_not_ready.reset(op);
      }
      unsigned get_num_operands() const{
    	  return m_warp->get_num_operands();
      }
      unsigned get_num_regs() const{
    	  return m_warp->get_num_regs();
      }
      void dispatch();
      bool is_free(){return m_free;}

   private:
      bool m_free;
      unsigned m_cuid; // collector unit hw id
      unsigned m_warp_id;
      warp_inst_t  *m_warp;
      register_set* m_output_register; // pipeline register to issue to when ready
      op_t *m_src_op;
      std::bitset<MAX_REG_OPERANDS*2> m_not_ready;
      unsigned m_num_banks;
      unsigned m_bank_warp_shift;
      opndcoll_rfu_t *m_rfu;

   };

   class dispatch_unit_t {
   public:
      dispatch_unit_t(std::vector<collector_unit_t>* cus) 
      { 
         m_last_cu=0;
         m_collector_units=cus;
         m_num_collectors = (*cus).size();
         m_next_cu=0;
      }

      collector_unit_t *find_ready()
      {
         for( unsigned n=0; n < m_num_collectors; n++ ) {
            unsigned c=(m_last_cu+n+1)%m_num_collectors;
            if( (*m_collector_units)[c].ready() ) {
               m_last_cu=c;
               return &((*m_collector_units)[c]);
            }
         }
         return NULL;
      }

   private:
      unsigned m_num_collectors;
      std::vector<collector_unit_t>* m_collector_units;
      unsigned m_last_cu; // dispatch ready cu's rr
      unsigned m_next_cu;  // for initialization
   };

   // opndcoll_rfu_t data members
   bool m_initialized;

   unsigned m_num_collector_sets;
   //unsigned m_num_collectors;
   unsigned m_num_banks;
   unsigned m_bank_warp_shift;
   unsigned m_warp_size;
   std::vector<collector_unit_t *> m_cu;
   arbiter_t m_arbiter;

   //unsigned m_num_ports;
   //std::vector<warp_inst_t**> m_input;
   //std::vector<warp_inst_t**> m_output;
   //std::vector<unsigned> m_num_collector_units;
   //warp_inst_t **m_alu_port;

   std::vector<input_port_t> m_in_ports;
   typedef std::map<unsigned /* collector set */, std::vector<collector_unit_t> /*collector sets*/ > cu_sets_t;
   cu_sets_t m_cus;
   std::vector<dispatch_unit_t> m_dispatch_units;

   //typedef std::map<warp_inst_t**/*port*/,dispatch_unit_t> port_to_du_t;
   //port_to_du_t                     m_dispatch_units;
   //std::map<warp_inst_t**,std::list<collector_unit_t*> > m_free_cu;
   shader_core_ctx                 *m_shader;
};

class barrier_set_t {
public:
   barrier_set_t( unsigned max_warps_per_core, unsigned max_cta_per_core );

   // during cta allocation
   void allocate_barrier( unsigned cta_id, warp_set_t warps );

   // during cta deallocation
   void deallocate_barrier( unsigned cta_id );

   typedef std::map<unsigned, warp_set_t >  cta_to_warp_t;

   // individual warp hits barrier
   void warp_reaches_barrier( unsigned cta_id, unsigned warp_id );

   // fetching a warp
   bool available_for_fetch( unsigned warp_id ) const;

   // warp reaches exit 
   void warp_exit( unsigned warp_id );

   // assertions
   bool warp_waiting_at_barrier( unsigned warp_id ) const;

   // debug
   void dump() const;

private:
   unsigned m_max_cta_per_core;
   unsigned m_max_warps_per_core;

   cta_to_warp_t m_cta_to_warps; 
   warp_set_t m_warp_active;
   warp_set_t m_warp_at_barrier;
};

struct insn_latency_info {
   unsigned pc;
   unsigned long latency;
};

struct ifetch_buffer_t {
    ifetch_buffer_t() { m_valid=false; }

    ifetch_buffer_t( address_type pc, unsigned nbytes, unsigned warp_id ) 
    { 
        m_valid=true; 
        m_pc=pc; 
        m_nbytes=nbytes; 
        m_warp_id=warp_id;
    }

    bool m_valid;
    address_type m_pc;
    unsigned m_nbytes;
    unsigned m_warp_id;
};

class shader_core_config;

class simd_function_unit {
public:
    simd_function_unit( const shader_core_config *config );
    ~simd_function_unit() { delete m_dispatch_reg; }

    // modifiers
    virtual void issue( register_set& source_reg ) { source_reg.move_out_to(m_dispatch_reg); occupied.set(m_dispatch_reg->latency);}
    virtual void cycle() = 0;
    virtual void active_lanes_in_pipeline() = 0;

    // accessors
    virtual unsigned clock_multiplier() const { return 1; }
    virtual bool can_issue( const warp_inst_t &inst ) const { return m_dispatch_reg->empty() && !occupied.test(inst.latency); }
    virtual bool stallable() const = 0;
    virtual void print( FILE *fp ) const
    {
        fprintf(fp,"%s dispatch= ", m_name.c_str() );
        m_dispatch_reg->print(fp);
    }
protected:
    std::string m_name;
    const shader_core_config *m_config;
    warp_inst_t *m_dispatch_reg;
    static const unsigned MAX_ALU_LATENCY = 512;
    std::bitset<MAX_ALU_LATENCY> occupied;
};

class pipelined_simd_unit : public simd_function_unit {
public:
    pipelined_simd_unit( register_set* result_port, const shader_core_config *config, unsigned max_latency, shader_core_ctx *core );

    //modifiers
    virtual void cycle() 
    {
        if( !m_pipeline_reg[0]->empty() ){
            m_result_port->move_in(m_pipeline_reg[0]);
        }
        for( unsigned stage=0; (stage+1)<m_pipeline_depth; stage++ ) 
            move_warp(m_pipeline_reg[stage], m_pipeline_reg[stage+1]);
        if( !m_dispatch_reg->empty() ) {
            if( !m_dispatch_reg->dispatch_delay()) {
                int start_stage = m_dispatch_reg->latency - m_dispatch_reg->initiation_interval;
                move_warp(m_pipeline_reg[start_stage],m_dispatch_reg);
            }
        }
        occupied >>=1;
    }
    virtual void issue( register_set& source_reg );
    virtual unsigned get_active_lanes_in_pipeline()
    {
    	active_mask_t active_lanes;
    	active_lanes.reset();
        for( unsigned stage=0; (stage+1)<m_pipeline_depth; stage++ ){
        	if( !m_pipeline_reg[stage]->empty() )
        		active_lanes|=m_pipeline_reg[stage]->get_active_mask();
        }
        return active_lanes.count();
    }
    virtual void active_lanes_in_pipeline() = 0;
/*
    virtual void issue( register_set& source_reg )
    {
        //move_warp(m_dispatch_reg,source_reg);
        //source_reg.move_out_to(m_dispatch_reg);
        simd_function_unit::issue(source_reg);
    }
*/
    // accessors
    virtual bool stallable() const { return false; }
    virtual bool can_issue( const warp_inst_t &inst ) const
    {
        return simd_function_unit::can_issue(inst);
    }
    virtual void print(FILE *fp) const
    {
        simd_function_unit::print(fp);
        for( int s=m_pipeline_depth-1; s>=0; s-- ) {
            if( !m_pipeline_reg[s]->empty() ) { 
                fprintf(fp,"      %s[%2d] ", m_name.c_str(), s );
                m_pipeline_reg[s]->print(fp);
            }
        }
    }
protected:
    unsigned m_pipeline_depth;
    warp_inst_t **m_pipeline_reg;
    register_set *m_result_port;
    class shader_core_ctx *m_core;
};

class sfu : public pipelined_simd_unit
{
public:
    sfu( register_set* result_port, const shader_core_config *config, shader_core_ctx *core );
    virtual bool can_issue( const warp_inst_t &inst ) const
    {
        switch(inst.op) {
        case SFU_OP: break;
        case ALU_SFU_OP: break;
        default: return false;
        }
        return pipelined_simd_unit::can_issue(inst);
    }
    virtual void active_lanes_in_pipeline();
    virtual void issue(  register_set& source_reg );
};

class sp_unit : public pipelined_simd_unit
{
public:
    sp_unit( register_set* result_port, const shader_core_config *config, shader_core_ctx *core );
    virtual bool can_issue( const warp_inst_t &inst ) const
    {
        switch(inst.op) {
        case SFU_OP: return false; 
        case LOAD_OP: return false;
        case STORE_OP: return false;
        case MEMORY_BARRIER_OP: return false;
        default: break;
        }
        return pipelined_simd_unit::can_issue(inst);
    }
    virtual void active_lanes_in_pipeline();
    virtual void issue( register_set& source_reg );
};

class simt_core_cluster;
class shader_memory_interface;
class shader_core_mem_fetch_allocator;
class cache_t;

class ldst_unit: public pipelined_simd_unit {
public:
    ldst_unit( mem_fetch_interface *icnt,
               shader_core_mem_fetch_allocator *mf_allocator,
               shader_core_ctx *core, 
               opndcoll_rfu_t *operand_collector,
               Scoreboard *scoreboard,
               const shader_core_config *config, 
               const memory_config *mem_config,  
               class shader_core_stats *stats, 
               unsigned sid, unsigned tpc );

    // modifiers
    virtual void issue( register_set &inst );
    virtual void cycle();
     
    void fill( mem_fetch *mf );
    void flush();
    void writeback();

    // accessors
    virtual unsigned clock_multiplier() const;

    virtual bool can_issue( const warp_inst_t &inst ) const
    {
        switch(inst.op) {
        case LOAD_OP: break;
        case STORE_OP: break;
        case MEMORY_BARRIER_OP: break;
        default: return false;
        }
        return m_dispatch_reg->empty();
    }

    virtual void active_lanes_in_pipeline();
    virtual bool stallable() const { return true; }
    bool response_buffer_full() const;
    void print(FILE *fout) const;
    void print_cache_stats( FILE *fp, unsigned& dl1_accesses, unsigned& dl1_misses );
    void get_cache_stats(unsigned &read_accesses, unsigned &write_accesses, unsigned &read_misses, unsigned &write_misses, unsigned cache_type);
    void set_stats();

    void set_icnt_power_stats(unsigned &simt_to_mem) const;

protected:
    ldst_unit( mem_fetch_interface *icnt,
               shader_core_mem_fetch_allocator *mf_allocator,
               shader_core_ctx *core, 
               opndcoll_rfu_t *operand_collector,
               Scoreboard *scoreboard,
               const shader_core_config *config,
               const memory_config *mem_config,  
               shader_core_stats *stats,
               unsigned sid,
               unsigned tpc,
               l1_cache* new_l1d_cache );
    void init( mem_fetch_interface *icnt,
               shader_core_mem_fetch_allocator *mf_allocator,
               shader_core_ctx *core, 
               opndcoll_rfu_t *operand_collector,
               Scoreboard *scoreboard,
               const shader_core_config *config,
               const memory_config *mem_config,  
               shader_core_stats *stats,
               unsigned sid,
               unsigned tpc );

protected:
   bool shared_cycle( warp_inst_t &inst, mem_stage_stall_type &rc_fail, mem_stage_access_type &fail_type);
   bool constant_cycle( warp_inst_t &inst, mem_stage_stall_type &rc_fail, mem_stage_access_type &fail_type);
   bool texture_cycle( warp_inst_t &inst, mem_stage_stall_type &rc_fail, mem_stage_access_type &fail_type);
   bool memory_cycle( warp_inst_t &inst, mem_stage_stall_type &rc_fail, mem_stage_access_type &fail_type);

   virtual mem_stage_stall_type process_cache_access( cache_t* cache,
                                                      new_addr_type address,
                                                      warp_inst_t &inst,
                                                      std::list<cache_event>& events,
                                                      mem_fetch *mf,
                                                      enum cache_request_status status );
   mem_stage_stall_type process_memory_access_queue( cache_t *cache, warp_inst_t &inst );

   const memory_config *m_memory_config;
   class mem_fetch_interface *m_icnt;
   shader_core_mem_fetch_allocator *m_mf_allocator;
   class shader_core_ctx *m_core;
   unsigned m_sid;
   unsigned m_tpc;

   tex_cache *m_L1T; // texture cache
   read_only_cache *m_L1C; // constant cache
   l1_cache *m_L1D; // data cache
   std::map<unsigned/*warp_id*/, std::map<unsigned/*regnum*/,unsigned/*count*/> > m_pending_writes;
   std::list<mem_fetch*> m_response_fifo;
   opndcoll_rfu_t *m_operand_collector;
   Scoreboard *m_scoreboard;

   mem_fetch *m_next_global;
   warp_inst_t m_next_wb;
   unsigned m_writeback_arb; // round-robin arbiter for writeback contention between L1T, L1C, shared
   unsigned m_num_writeback_clients;

   enum mem_stage_stall_type m_mem_rc;

   shader_core_stats *m_stats; 

   // for debugging
   unsigned long long m_last_inst_gpu_sim_cycle;
   unsigned long long m_last_inst_gpu_tot_sim_cycle;

   // Interconnect power stats
   unsigned n_simt_to_mem;

   // Jingwen: cache access recorders
   int tex_cache_access_count; 
   int const_cache_access_count; 
   int data_cache_access_count; 
};

enum pipeline_stage_name_t {
    ID_OC_SP=0,
    ID_OC_SFU,  
    ID_OC_MEM,  
    OC_EX_SP,
    OC_EX_SFU,
    OC_EX_MEM,
    EX_WB,
    N_PIPELINE_STAGES 
};

const char* const pipeline_stage_name_decode[] = {
    "ID_OC_SP",
    "ID_OC_SFU",  
    "ID_OC_MEM",  
    "OC_EX_SP",
    "OC_EX_SFU",
    "OC_EX_MEM",
    "EX_WB",
    "N_PIPELINE_STAGES" 
};

struct shader_core_config : public core_config
{
    shader_core_config(){
	pipeline_widths_string = NULL;
    }

    void init()
    {
        int ntok = sscanf(gpgpu_shader_core_pipeline_opt,"%d:%d", 
                          &n_thread_per_shader,
                          &warp_size);
        if(ntok != 2) {
           printf("GPGPU-Sim uArch: error while parsing configuration string gpgpu_shader_core_pipeline_opt\n");
           abort();
	}

	char* toks = new char[100];
	char* tokd = toks;
	strcpy(toks,pipeline_widths_string);

	toks = strtok(toks,",");
	for (unsigned i = 0; i < N_PIPELINE_STAGES; i++) { 
	    assert(toks);
	    ntok = sscanf(toks,"%d", &pipe_widths[i]);
	    assert(ntok == 1); 
	    toks = strtok(NULL,",");
	}
	delete[] tokd;

        if (n_thread_per_shader > MAX_THREAD_PER_SM) {
           printf("GPGPU-Sim uArch: Error ** increase MAX_THREAD_PER_SM in abstract_hardware_model.h from %u to %u\n", 
                  MAX_THREAD_PER_SM, n_thread_per_shader);
           abort();
        }
        max_warps_per_shader =  n_thread_per_shader/warp_size;
        assert( !(n_thread_per_shader % warp_size) );
        max_sfu_latency = 512;
        max_sp_latency = 32;
        m_L1I_config.init();
        m_L1T_config.init();
        m_L1C_config.init();
        m_L1D_config.init();
        gpgpu_cache_texl1_linesize = m_L1T_config.get_line_sz();
        gpgpu_cache_constl1_linesize = m_L1C_config.get_line_sz();
        m_valid = true;
    }
    void reg_options(class OptionParser * opp );
    unsigned max_cta( const kernel_info_t &k ) const;
    unsigned num_shader() const { return n_simt_clusters*n_simt_cores_per_cluster; }
    unsigned sid_to_cluster( unsigned sid ) const { return sid / n_simt_cores_per_cluster; }
    unsigned sid_to_cid( unsigned sid )     const { return sid % n_simt_cores_per_cluster; }
    unsigned cid_to_sid( unsigned cid, unsigned cluster_id ) const { return cluster_id*n_simt_cores_per_cluster + cid; }

// data
    char *gpgpu_shader_core_pipeline_opt;
    bool gpgpu_perfect_mem;
    bool gpgpu_clock_gated_reg_file;
    bool gpgpu_clock_gated_lanes;
    enum divergence_support_t model;
    unsigned n_thread_per_shader;
    unsigned n_regfile_gating_group;
    unsigned max_warps_per_shader; 
    unsigned max_cta_per_core; //Limit on number of concurrent CTAs in shader core

    char * gpgpu_scheduler_string;

    char* pipeline_widths_string;
    int pipe_widths[N_PIPELINE_STAGES];

    cache_config m_L1I_config;
    cache_config m_L1T_config;
    cache_config m_L1C_config;
    cache_config m_L1D_config;

    bool gpgpu_dwf_reg_bankconflict;

    int gpgpu_num_sched_per_core;
    int gpgpu_max_insn_issue_per_warp;

    //op collector
    int gpgpu_operand_collector_num_units_sp;
    int gpgpu_operand_collector_num_units_sfu;
    int gpgpu_operand_collector_num_units_mem;
    int gpgpu_operand_collector_num_units_gen;

    unsigned int gpgpu_operand_collector_num_in_ports_sp;
    unsigned int gpgpu_operand_collector_num_in_ports_sfu;
    unsigned int gpgpu_operand_collector_num_in_ports_mem;
    unsigned int gpgpu_operand_collector_num_in_ports_gen;

    unsigned int gpgpu_operand_collector_num_out_ports_sp;
    unsigned int gpgpu_operand_collector_num_out_ports_sfu;
    unsigned int gpgpu_operand_collector_num_out_ports_mem;
    unsigned int gpgpu_operand_collector_num_out_ports_gen;

    int gpgpu_num_sp_units;
    int gpgpu_num_sfu_units;
    int gpgpu_num_mem_units;

    //Shader core resources
    unsigned gpgpu_shader_registers;
    int gpgpu_warpdistro_shader;
    int gpgpu_warp_issue_shader;
    unsigned gpgpu_num_reg_banks;
    bool gpgpu_reg_bank_use_warp_id;
    bool gpgpu_local_mem_map;
    
    unsigned max_sp_latency;
    unsigned max_sfu_latency;
    
    unsigned n_simt_cores_per_cluster;
    unsigned n_simt_clusters;
    unsigned n_simt_ejection_buffer_size;
    unsigned ldst_unit_response_queue_size;

    int simt_core_sim_order; 
    
    unsigned mem2device(unsigned memid) const { return memid + n_simt_clusters; }
};

struct shader_core_stats_pod {

	void* shader_core_stats_pod_start[]; // DO NOT MOVE FROM THE TOP - spaceless pointer to the start of this structure
	unsigned long long *shader_cycles;
    unsigned *m_num_sim_insn; // number of scalar thread instructions committed by this shader core
    unsigned *m_num_sim_winsn; // number of warp instructions committed by this shader core
	unsigned *m_last_num_sim_insn;
	unsigned *m_last_num_sim_winsn;
    unsigned *m_num_decoded_insn; // number of instructions decoded by this shader core
    float *m_pipeline_duty_cycle;
    unsigned *m_num_FPdecoded_insn;
    unsigned *m_num_INTdecoded_insn;
    unsigned *m_num_storequeued_insn;
    unsigned *m_num_loadqueued_insn;
    unsigned *m_num_ialu_acesses;
    unsigned *m_num_fp_acesses;
    unsigned *m_num_imul_acesses;
    unsigned *m_num_tex_inst;
    unsigned *m_num_fpmul_acesses;
    unsigned *m_num_idiv_acesses;
    unsigned *m_num_fpdiv_acesses;
    unsigned *m_num_sp_acesses;
    unsigned *m_num_sfu_acesses;
    unsigned *m_num_trans_acesses;
    unsigned *m_num_mem_acesses;
    unsigned *m_num_sp_committed;
    unsigned *m_num_tlb_hits;
    unsigned *m_num_tlb_accesses;
    unsigned *m_num_sfu_committed;
    unsigned *m_num_mem_committed;
    unsigned *m_read_regfile_acesses;
    unsigned *m_write_regfile_acesses;
    unsigned *m_non_rf_operands;
    unsigned *m_num_imul24_acesses;
    unsigned *m_num_imul32_acesses;
    unsigned *m_active_sp_lanes;
    unsigned *m_active_sfu_lanes;
    unsigned *m_active_fu_lanes;
    unsigned *m_active_fu_mem_lanes;
    unsigned *m_n_diverge;    // number of divergence occurring in this shader
    unsigned gpgpu_n_load_insn;
    unsigned gpgpu_n_store_insn;
    unsigned gpgpu_n_shmem_insn;
    unsigned gpgpu_n_tex_insn;
    unsigned gpgpu_n_const_insn;
    unsigned gpgpu_n_param_insn;
    unsigned gpgpu_n_shmem_bkconflict;
    unsigned gpgpu_n_cache_bkconflict;
    int      gpgpu_n_intrawarp_mshr_merge;
    unsigned gpgpu_n_cmem_portconflict;
    unsigned gpu_stall_shd_mem_breakdown[N_MEM_STAGE_ACCESS_TYPE][N_MEM_STAGE_STALL_TYPE];
    unsigned gpu_reg_bank_conflict_stalls;
    unsigned *shader_cycle_distro;
    unsigned *last_shader_cycle_distro;
    unsigned *num_warps_issuable;
    unsigned gpgpu_n_stall_shd_mem;

    //memory access classification
    int gpgpu_n_mem_read_local;
    int gpgpu_n_mem_write_local;
    int gpgpu_n_mem_texture;
    int gpgpu_n_mem_const;
    int gpgpu_n_mem_read_global;
    int gpgpu_n_mem_write_global;
    int gpgpu_n_mem_read_inst;
    
    int gpgpu_n_mem_l2_writeback;
    int gpgpu_n_mem_l2_write_allocate;

    unsigned made_write_mfs;
    unsigned made_read_mfs;

    // Power stats
    unsigned *gpgpu_n_shmem_bank_access;
    unsigned *inst_c_read_access;	// Instruction cache read access
    unsigned *inst_c_read_miss;		// Instruction cache read miss
    unsigned *const_c_read_access;	// Constant cache read access
    unsigned *const_c_read_miss;		// Constant cache read miss
    unsigned *text_c_read_access;	// Texture cache read access
    unsigned *text_c_read_miss;		// Texture cache read miss
    unsigned *l1d_read_access;		// L1 Data cache read access
    unsigned *l1d_read_miss;			// L1 Data cache read miss
    unsigned *l1d_write_access;		// L1 Data cache write access
    unsigned *l1d_write_miss;		// L1 Data cache write miss

};

class shader_core_stats : public shader_core_stats_pod {
public:
    shader_core_stats( const shader_core_config *config )
    {
        m_config = config;
        shader_core_stats_pod *pod = reinterpret_cast< shader_core_stats_pod * > ( this->shader_core_stats_pod_start );
        memset(pod,0,sizeof(shader_core_stats_pod));
        shader_cycles=(unsigned long long *) calloc(config->num_shader(),sizeof(unsigned long long ));
        m_num_sim_insn = (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
/******************************
 * Jingwen: For multi-cyle operations, use the circular buffer to generate stats
******************************/
		unsigned shader_counts = config->num_shader();
	 	circular_stats_ialu.resize(shader_counts);
		circular_stats_tex.resize(shader_counts);
		circular_stats_imul.resize(shader_counts);
		circular_stats_imul24.resize(shader_counts);
		circular_stats_imul32.resize(shader_counts);
		circular_stats_idiv.resize(shader_counts);
		circular_stats_fpalu.resize(shader_counts);
		circular_stats_fpmul.resize(shader_counts);
		circular_stats_fpdiv.resize(shader_counts);
		circular_stats_trans.resize(shader_counts);
		circular_stats_sfu.resize(shader_counts);
		circular_stats_sp.resize(shader_counts);
		circular_stats_mem.resize(shader_counts);
/******************************/

        m_num_sim_winsn = (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_last_num_sim_winsn = (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_last_num_sim_insn = (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_pipeline_duty_cycle=(float*) calloc(config->num_shader(),sizeof(float));
        m_num_decoded_insn = (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_FPdecoded_insn = (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_storequeued_insn=(unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_loadqueued_insn=(unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_INTdecoded_insn = (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_ialu_acesses = (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_fp_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_tex_inst= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_imul_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_imul24_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_imul32_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_fpmul_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_idiv_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_fpdiv_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_sp_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_sfu_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_trans_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_mem_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_sp_committed= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_tlb_hits=(unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_tlb_accesses=(unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_active_sp_lanes= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_active_sfu_lanes= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_active_fu_lanes= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_active_fu_mem_lanes= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_sfu_committed= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_num_mem_committed= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_read_regfile_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_write_regfile_acesses= (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_non_rf_operands=(unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        m_n_diverge = (unsigned*) calloc(config->num_shader(),sizeof(unsigned));
        shader_cycle_distro = (unsigned*) calloc(config->warp_size+3, sizeof(unsigned));
        last_shader_cycle_distro = (unsigned*) calloc(m_config->warp_size+3, sizeof(unsigned));

        // Power stats
        inst_c_read_access = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));
        inst_c_read_miss = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));
        const_c_read_access = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));
        const_c_read_miss = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));
        text_c_read_access = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));
        text_c_read_miss = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));
        l1d_read_access = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));
        l1d_read_miss = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));
        l1d_write_access = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));
        l1d_write_miss = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));

        gpgpu_n_shmem_bank_access = (unsigned *)calloc(config->num_shader(), sizeof(unsigned));

        m_shader_dynamic_warp_issue_distro.resize( config->num_shader() );
        m_shader_warp_slot_issue_distro.resize( config->num_shader() );
    }

    void new_grid()
    {
    }

    void event_warp_issued( unsigned s_id, unsigned warp_id, unsigned num_issued, unsigned dynamic_warp_id );

    void visualizer_print( gzFile visualizer_file );

    void print( FILE *fout ) const;

/******************************
 * Jingwen: For multi-cyle operations, use the circular buffer to generate stats
******************************/
	std::vector<CircularStats> 	circular_stats_ialu,
								circular_stats_tex,
								circular_stats_imul,
								circular_stats_imul24,
								circular_stats_imul32,
								circular_stats_idiv,
								circular_stats_fpalu,
								circular_stats_fpmul,
								circular_stats_fpdiv,
								circular_stats_trans,
								circular_stats_sfu,
								circular_stats_sp,
								circular_stats_mem;
/******************************/
    const std::vector< std::vector<unsigned> >& get_dynamic_warp_issue() const
    {
        return m_shader_dynamic_warp_issue_distro;
    }

    const std::vector< std::vector<unsigned> >& get_warp_slot_issue() const
    {
        return m_shader_warp_slot_issue_distro;
    }

private:
    const shader_core_config *m_config;
    // Counts the instructions issued for each dynamic warp.
    std::vector< std::vector<unsigned> > m_shader_dynamic_warp_issue_distro;
    std::vector<unsigned> m_last_shader_dynamic_warp_issue_distro;
    std::vector< std::vector<unsigned> > m_shader_warp_slot_issue_distro;
    std::vector<unsigned> m_last_shader_warp_slot_issue_distro;

    friend class power_stat_t;
    friend class shader_core_ctx;
    friend class ldst_unit;
    friend class simt_core_cluster;
    friend class scheduler_unit;
    friend class TwoLevelScheduler;
    friend class LooseRoundRobbinScheduler;
};

class shader_core_mem_fetch_allocator : public mem_fetch_allocator {
public:
    shader_core_mem_fetch_allocator( unsigned core_id, unsigned cluster_id, const memory_config *config )
    {
    	m_core_id = core_id;
    	m_cluster_id = cluster_id;
    	m_memory_config = config;
    }
    mem_fetch *alloc( new_addr_type addr, mem_access_type type, unsigned size, bool wr ) const 
    {
    	mem_access_t access( type, addr, size, wr );
    	mem_fetch *mf = new mem_fetch( access, 
    				       NULL,
    				       wr?WRITE_PACKET_SIZE:READ_PACKET_SIZE, 
    				       -1, 
    				       m_core_id, 
    				       m_cluster_id,
    				       m_memory_config );
    	return mf;
    }
    
    mem_fetch *alloc( const warp_inst_t &inst, const mem_access_t &access ) const
    {
        warp_inst_t inst_copy = inst;
        mem_fetch *mf = new mem_fetch(access, 
                                      &inst_copy, 
                                      access.is_write()?WRITE_PACKET_SIZE:READ_PACKET_SIZE,
                                      inst.warp_id(),
                                      m_core_id, 
                                      m_cluster_id, 
                                      m_memory_config);
        return mf;
    }

private:
    unsigned m_core_id;
    unsigned m_cluster_id;
    const memory_config *m_memory_config;
};

class shader_core_ctx : public core_t {
public:
    // creator:
    shader_core_ctx( class gpgpu_sim *gpu,
                     class simt_core_cluster *cluster,
                     unsigned shader_id,
                     unsigned tpc_id,
                     const struct shader_core_config *config,
                     const struct memory_config *mem_config,
                     shader_core_stats *stats );

// used by simt_core_cluster:
    // modifiers
    void cycle();
    void reinit(unsigned start_thread, unsigned end_thread, bool reset_not_completed );
    void issue_block2core( class kernel_info_t &kernel );
    void cache_flush();
    void accept_fetch_response( mem_fetch *mf );
    void accept_ldst_unit_response( class mem_fetch * mf );
    void set_kernel( kernel_info_t *k ) 
    {
        assert(k);
        m_kernel=k; 
        k->inc_running(); 
        printf("GPGPU-Sim uArch: Shader %d bind to kernel %u \'%s\'\n", m_sid, m_kernel->get_uid(),
                 m_kernel->name().c_str() );
    }
   
    // accessors
    bool fetch_unit_response_buffer_full() const;
    bool ldst_unit_response_buffer_full() const;
    unsigned get_not_completed() const { return m_not_completed; }
    unsigned get_n_active_cta() const { return m_n_active_cta; }
    unsigned isactive() const {if(m_n_active_cta>0) return 1; else return 0;}
    kernel_info_t *get_kernel() { return m_kernel; }
    unsigned get_sid() const {return m_sid;}

// used by functional simulation:
    // modifiers
    virtual void warp_exit( unsigned warp_id );
    
    // accessors
    virtual bool warp_waiting_at_barrier( unsigned warp_id ) const;
    void get_pdom_stack_top_info( unsigned tid, unsigned *pc, unsigned *rpc ) const;

// used by pipeline timing model components:
    // modifiers
    void mem_instruction_stats(const warp_inst_t &inst);
    void decrement_atomic_count( unsigned wid, unsigned n );
    void inc_store_req( unsigned warp_id) { m_warp[warp_id].inc_store_req(); }
    void dec_inst_in_pipeline( unsigned warp_id ) { m_warp[warp_id].dec_inst_in_pipeline(); } // also used in writeback()
    void store_ack( class mem_fetch *mf );
    bool warp_waiting_at_mem_barrier( unsigned warp_id );
    void set_max_cta( const kernel_info_t &kernel );
    void warp_inst_complete(const warp_inst_t &inst);
    
    // accessors
    std::list<unsigned> get_regs_written( const inst_t &fvt ) const;
    const shader_core_config *get_config() const { return m_config; }
    void print_cache_stats( FILE *fp, unsigned& dl1_accesses, unsigned& dl1_misses );
    void get_cache_stats(unsigned &read_accesses, unsigned &write_accesses, unsigned &read_misses, unsigned &write_misses, unsigned cache_type);

    void set_icnt_power_stats(unsigned &n_simt_to_mem) const;

// debug:
    void display_simt_state(FILE *fout, int mask ) const;
    void display_pipeline( FILE *fout, int print_mem, int mask3bit ) const;

    void incload_stat() {m_stats->m_num_loadqueued_insn[m_sid]++;}
    void incstore_stat() {m_stats->m_num_storequeued_insn[m_sid]++;}

/* Jingwen: GPUVolt */
	// recording the issued instructions in past 20 cycles
	double  issued_alu_ops_count;
	double  issued_fpu_ops_count;
	double  issued_sfu_ops_count;

	int issued_ops_cycle_count;

	// Jingwen: add vector to record warp status
	std::vector<int>  m_warp_status_vector;


	// throttling fpu
   std::vector<double> m_issued_fpu_history;
   unsigned m_issued_fpu_history_head; 
   double m_allowed_fpu_issue_count; 

   // recording fus weighted input increment
   double m_local_weighted_increment_from_fus;

/***************************************************************/
    void incialu_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_ialu[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_ialu[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_ialu[sid].operation_latency = latency;
		}

		if(m_config->gpgpu_clock_gated_lanes==false){
			m_stats->m_num_ialu_acesses[sid]=m_stats->m_num_ialu_acesses[sid]+active_count*latency
		    	+ inactive_lanes_accesses_nonsfu(active_count, latency);
			m_stats->circular_stats_ialu[sid].push(active_count+inactive_lanes_accesses_nonsfu(active_count, 1));
		}else {
        	m_stats->m_num_ialu_acesses[sid]=m_stats->m_num_ialu_acesses[sid]+active_count*latency;
			m_stats->circular_stats_ialu[sid].push(active_count);
		}

	 }
/***************************************************************/
    void inctex_stat(unsigned active_count,double latency){
		unsigned sid = m_sid;

		if (m_stats->circular_stats_tex[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_tex[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_tex[sid].operation_latency = latency;
		}

    	m_stats->m_num_tex_inst[sid]=m_stats->m_num_tex_inst[sid]+active_count*latency;
		m_stats->circular_stats_tex[sid].push(active_count);

    }

/***************************************************************/
    void incimul_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_imul[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_imul[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_imul[sid].operation_latency = latency;
		}

		if(m_config->gpgpu_clock_gated_lanes==false){
			m_stats->m_num_imul_acesses[sid]=m_stats->m_num_imul_acesses[sid]+active_count*latency
		    	+ inactive_lanes_accesses_nonsfu(active_count, latency);
			m_stats->circular_stats_imul[sid].push(active_count+inactive_lanes_accesses_nonsfu(active_count, 1));
		}else {
        	m_stats->m_num_imul_acesses[sid]=m_stats->m_num_imul_acesses[sid]+active_count*latency;
			m_stats->circular_stats_imul[sid].push(active_count);
		}
	 }

/***************************************************************/
    void incimul24_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_imul24[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_imul24[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_imul24[sid].operation_latency = latency;
		}

      	if(m_config->gpgpu_clock_gated_lanes==false){
   			m_stats->m_num_imul24_acesses[sid]=m_stats->m_num_imul24_acesses[sid]+active_count*latency
		    	+ inactive_lanes_accesses_nonsfu(active_count, latency);
			m_stats->circular_stats_imul24[sid].push(active_count+inactive_lanes_accesses_nonsfu(active_count, 1));
		}else {
			m_stats->m_num_imul24_acesses[sid]=m_stats->m_num_imul24_acesses[sid]+active_count*latency;
			m_stats->circular_stats_imul24[sid].push(active_count);
		}
	 }

/***************************************************************/
	 void incimul32_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_imul32[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_imul32[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_imul32[sid].operation_latency = latency;
		}

		if(m_config->gpgpu_clock_gated_lanes==false){
			m_stats->m_num_imul32_acesses[sid]=m_stats->m_num_imul32_acesses[sid]+active_count*latency
				+ inactive_lanes_accesses_sfu(active_count, latency);			
			m_stats->circular_stats_imul32[sid].push(active_count+inactive_lanes_accesses_sfu(active_count, 1));
		}else{
			m_stats->m_num_imul32_acesses[sid]=m_stats->m_num_imul32_acesses[sid]+active_count*latency;
			m_stats->circular_stats_imul32[sid].push(active_count);
		}
		//printf("Int_Mul -- Active_count: %d\n",active_count);
	 }

/***************************************************************/
	 void incidiv_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_idiv[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_idiv[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_idiv[sid].operation_latency = latency;
		}

		if(m_config->gpgpu_clock_gated_lanes==false){
			m_stats->m_num_idiv_acesses[sid]=m_stats->m_num_idiv_acesses[sid]+active_count*latency
				+ inactive_lanes_accesses_sfu(active_count, latency); 
			m_stats->circular_stats_idiv[sid].push(active_count+inactive_lanes_accesses_sfu(active_count, 1));
		} else {
			m_stats->m_num_idiv_acesses[sid]=m_stats->m_num_idiv_acesses[sid]+active_count*latency;
			m_stats->circular_stats_idiv[sid].push(active_count);
		}
	 }

/***************************************************************/
	 void incfpalu_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_fpalu[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_fpalu[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_fpalu[sid].operation_latency = latency;
		}

		if(m_config->gpgpu_clock_gated_lanes==false){
			m_stats->m_num_fp_acesses[sid]=m_stats->m_num_fp_acesses[sid]+active_count*latency
				+ inactive_lanes_accesses_nonsfu(active_count, latency);
			m_stats->circular_stats_fpalu[sid].push(active_count+inactive_lanes_accesses_nonsfu(active_count, 1));
		}else {
        	m_stats->m_num_fp_acesses[sid]=m_stats->m_num_fp_acesses[sid]+active_count*latency;
			m_stats->circular_stats_fpalu[sid].push(active_count);
		} 
	 }

/***************************************************************/
	 void incfpmul_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_fpmul[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_fpmul[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_fpmul[sid].operation_latency = latency;
		}
		 		// printf("FP MUL stat increament\n");
      	if(m_config->gpgpu_clock_gated_lanes==false){
			m_stats->m_num_fpmul_acesses[sid]=m_stats->m_num_fpmul_acesses[sid]+active_count*latency
		    	+ inactive_lanes_accesses_nonsfu(active_count, latency);
			m_stats->circular_stats_fpmul[sid].push(active_count+inactive_lanes_accesses_nonsfu(active_count, 1));
		}else {
        	m_stats->m_num_fpmul_acesses[sid]=m_stats->m_num_fpmul_acesses[sid]+active_count*latency;
			m_stats->circular_stats_fpmul[sid].push(active_count);
		}
	 }

/***************************************************************/
	 void incfpdiv_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_fpdiv[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_fpdiv[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_fpdiv[sid].operation_latency = latency;
		}

		if(m_config->gpgpu_clock_gated_lanes==false){
			m_stats->m_num_fpdiv_acesses[sid]=m_stats->m_num_fpdiv_acesses[sid]+active_count*latency
				+ inactive_lanes_accesses_sfu(active_count, latency); 
			m_stats->circular_stats_fpdiv[sid].push(active_count+inactive_lanes_accesses_sfu(active_count, 1));
		}else {
		  	m_stats->m_num_fpdiv_acesses[sid]=m_stats->m_num_fpdiv_acesses[sid]+active_count*latency;		
			m_stats->circular_stats_fpdiv[sid].push(active_count);
		}
	 }

/***************************************************************/
	 void inctrans_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_trans[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_trans[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_trans[sid].operation_latency = latency;
		}

		if(m_config->gpgpu_clock_gated_lanes==false){
			m_stats->m_num_trans_acesses[sid]=m_stats->m_num_trans_acesses[sid]+active_count*latency
				+ inactive_lanes_accesses_sfu(active_count, latency); 
			m_stats->circular_stats_trans[sid].push(active_count+inactive_lanes_accesses_sfu(active_count, 1));
		}else{
		  	m_stats->m_num_trans_acesses[sid]=m_stats->m_num_trans_acesses[sid]+active_count*latency;
			m_stats->circular_stats_trans[sid].push(active_count);
		}
	 }

/***************************************************************/
	 void incsfu_stat(unsigned active_count,double latency) { 
		unsigned sid = m_sid;

		if (m_stats->circular_stats_sfu[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_sfu[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_sfu[sid].operation_latency = latency;
		}

	 	m_stats->m_num_sfu_acesses[sid]=m_stats->m_num_sfu_acesses[sid]+active_count*latency; 
		// Jingwen: found this counters is not used by mcpat currently
		//m_stats->circular_stats_sfu[sid].push(active_count);
	 }

/***************************************************************/
	 void incsp_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;
		if (m_stats->circular_stats_sp[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_sp[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_sp[sid].operation_latency = latency;
		}
	 	
		m_stats->m_num_sp_acesses[sid]=m_stats->m_num_sp_acesses[sid]+active_count*latency;
		// Jingwen: found this counters is not used by mcpat currently
		//m_stats->circular_stats_sp[sid].push(active_count);
		
	 }

/***************************************************************/
	 void incmem_stat(unsigned active_count,double latency) {
		unsigned sid = m_sid;

		if (m_stats->circular_stats_mem[sid].circular_stats_initialized  == false ) {
			m_stats->circular_stats_mem[sid].circular_stats_initialized  = true;
			m_stats->circular_stats_mem[sid].operation_latency = latency;
		}

		if(m_config->gpgpu_clock_gated_lanes==false){
			m_stats->m_num_mem_acesses[sid]=m_stats->m_num_mem_acesses[sid]+active_count*latency
		    	+ inactive_lanes_accesses_nonsfu(active_count, latency);
			// Jingwen: found this counters is not used by mcpat currently
			//m_stats->circular_stats_mem[sid].push(active_count + inactive_lanes_accesses_nonsfu(active_count, 1));
		}else {
		  	m_stats->m_num_mem_acesses[sid]=m_stats->m_num_mem_acesses[sid]+active_count*latency;
			// Jingwen: found this counters is not used by mcpat currently
			//m_stats->circular_stats_mem[sid].push(active_count);
		}
	 }
/***************************************************************/
	 void incexecstat(warp_inst_t *&inst);

	 void incregfile_reads(unsigned active_count) {m_stats->m_read_regfile_acesses[m_sid]=m_stats->m_read_regfile_acesses[m_sid]+active_count;}
	 void incregfile_writes(unsigned active_count){m_stats->m_write_regfile_acesses[m_sid]=m_stats->m_write_regfile_acesses[m_sid]+active_count;}
	 void incnon_rf_operands(unsigned active_count){m_stats->m_non_rf_operands[m_sid]=m_stats->m_non_rf_operands[m_sid]+active_count;}

	 void incspactivelanes_stat(unsigned active_count) {m_stats->m_active_sp_lanes[m_sid]=m_stats->m_active_sp_lanes[m_sid]+active_count;}
	 void incsfuactivelanes_stat(unsigned active_count) {m_stats->m_active_sfu_lanes[m_sid]=m_stats->m_active_sfu_lanes[m_sid]+active_count;}
	 void incfuactivelanes_stat(unsigned active_count) {m_stats->m_active_fu_lanes[m_sid]=m_stats->m_active_fu_lanes[m_sid]+active_count;}
	 void incfumemactivelanes_stat(unsigned active_count) {m_stats->m_active_fu_mem_lanes[m_sid]=m_stats->m_active_fu_mem_lanes[m_sid]+active_count;}
private:
	 unsigned inactive_lanes_accesses_sfu(unsigned active_count,double latency){
      return  ( ((32-active_count)>>1)*latency) + ( ((32-active_count)>>3)*latency) + ( ((32-active_count)>>3)*latency);
	 }
	 unsigned inactive_lanes_accesses_nonsfu(unsigned active_count,double latency){
      return  ( ((32-active_count)>>1)*latency);
	 }

    int test_res_bus(int latency);
    void init_warps(unsigned cta_id, unsigned start_thread, unsigned end_thread);
    virtual void checkExecutionStatusAndUpdate(warp_inst_t &inst, unsigned t, unsigned tid);
    address_type next_pc( int tid ) const;
    void fetch();
    void register_cta_thread_exit( unsigned cta_num );

    void decode();
    
    void issue();
    friend class scheduler_unit; //this is needed to use private issue warp.
    friend class TwoLevelScheduler;
    friend class LooseRoundRobbinScheduler;
    void issue_warp( register_set& warp, const warp_inst_t *pI, const active_mask_t &active_mask, unsigned warp_id );
    void func_exec_inst( warp_inst_t &inst );

     // Returns numbers of addresses in translated_addrs
    unsigned translate_local_memaddr( address_type localaddr, unsigned tid, unsigned num_shader, unsigned datasize, new_addr_type* translated_addrs );

    void read_operands();
    
    void execute();
    
    void writeback();
    
    // used in display_pipeline():
    void dump_warp_state( FILE *fout ) const;
    void print_stage(unsigned int stage, FILE *fout) const;
    unsigned long long m_last_inst_gpu_sim_cycle;
    unsigned long long m_last_inst_gpu_tot_sim_cycle;

    // general information
    unsigned m_sid; // shader id
    unsigned m_tpc; // texture processor cluster id (aka, node id when using interconnect concentration)
    const shader_core_config *m_config;
    const memory_config *m_memory_config;
    class simt_core_cluster *m_cluster;

    // statistics 
    shader_core_stats *m_stats;

    // CTA scheduling / hardware thread allocation
    unsigned m_n_active_cta; // number of Cooperative Thread Arrays (blocks) currently running on this shader.
    unsigned m_cta_status[MAX_CTA_PER_SHADER]; // CTAs status 
    unsigned m_not_completed; // number of threads to be completed (==0 when all thread on this core completed) 
    std::bitset<MAX_THREAD_PER_SM> m_active_threads;
    
    // thread contexts 
    thread_ctx_t             *m_threadState;
    
    // interconnect interface
    mem_fetch_interface *m_icnt;
    shader_core_mem_fetch_allocator *m_mem_fetch_allocator;
    
    // fetch
    read_only_cache *m_L1I; // instruction cache
    int  m_last_warp_fetched;

    // decode/dispatch
    std::vector<shd_warp_t>   m_warp;   // per warp information array
    barrier_set_t             m_barriers;
    ifetch_buffer_t           m_inst_fetch_buffer;
    std::vector<register_set> m_pipeline_reg;
    std::vector<register_set> m_pipeline_reg_old;
    std::vector<std::vector<bool>> pipe_reg_empty;
    std::vector<std::vector<bool>> pipe_reg_empty_old;
    std::vector<std::vector<unsigned long>> pipe_reg_pc;
    std::vector<std::vector<unsigned long>> pipe_reg_pc_old;
    std::vector<std::vector<unsigned long>> pipe_reg_warpid;
    std::vector<std::vector<unsigned long>> pipe_reg_warpid_old;
	bool old_assigned;
    Scoreboard               *m_scoreboard;
    opndcoll_rfu_t            m_operand_collector;

    //schedule
    std::vector<scheduler_unit*>  schedulers;

    // execute
    unsigned m_num_function_units;
    std::vector<pipeline_stage_name_t> m_dispatch_port;
    std::vector<pipeline_stage_name_t> m_issue_port;
    std::vector<simd_function_unit*> m_fu; // stallable pipelines should be last in this array
    ldst_unit *m_ldst_unit;
    static const unsigned MAX_ALU_LATENCY = 512;
    unsigned num_result_bus;
    std::vector< std::bitset<MAX_ALU_LATENCY>* > m_result_bus;

    // used for local address mapping with single kernel launch
    unsigned kernel_max_cta_per_shader;
    unsigned kernel_padded_threads_per_cta;
    // Used for handing out dynamic warp_ids to new warps.
    // the differnece between a warp_id and a dynamic_warp_id
    // is that the dynamic_warp_id is a running number unique to every warp
    // run on this shader, where the warp_id is the static warp slot.
    unsigned m_dynamic_warp_id;
};

class simt_core_cluster {
public:
    simt_core_cluster( class gpgpu_sim *gpu, 
                       unsigned cluster_id, 
                       const struct shader_core_config *config, 
                       const struct memory_config *mem_config,
                       shader_core_stats *stats,
                       memory_stats_t *mstats );

    void core_cycle();
    void icnt_cycle();

    void reinit();
    unsigned issue_block2core();
    void cache_flush();
    bool icnt_injection_buffer_full(unsigned size, bool write);
    void icnt_inject_request_packet(class mem_fetch *mf);

    // for perfect memory interface
    bool response_queue_full() {
        return ( m_response_fifo.size() >= m_config->n_simt_ejection_buffer_size );
    }
    void push_response_fifo(class mem_fetch *mf) {
        m_response_fifo.push_back(mf);
    }

    void get_pdom_stack_top_info( unsigned sid, unsigned tid, unsigned *pc, unsigned *rpc ) const;
    unsigned max_cta( const kernel_info_t &kernel );
    unsigned get_not_completed() const;
    void print_not_completed( FILE *fp ) const;
    unsigned get_n_active_cta() const;
    unsigned get_n_active_sms() const;
    gpgpu_sim *get_gpu() { return m_gpu; }

    void display_pipeline( unsigned sid, FILE *fout, int print_mem, int mask );
    void print_cache_stats( FILE *fp, unsigned& dl1_accesses, unsigned& dl1_misses ) const;
    void get_cache_stats(unsigned &read_accesses, unsigned &write_accesses, unsigned &read_misses, unsigned &write_misses, unsigned cache_type) const;

    void set_icnt_stats(unsigned &n_simt_to_mem) const;

private:
    unsigned m_cluster_id;
    gpgpu_sim *m_gpu;
    const shader_core_config *m_config;
    shader_core_stats *m_stats;
    memory_stats_t *m_memory_stats;
    shader_core_ctx **m_core;

    unsigned m_cta_issue_next_core;
    std::list<unsigned> m_core_sim_order;
    std::list<mem_fetch*> m_response_fifo;
};

class shader_memory_interface : public mem_fetch_interface {
public:
    shader_memory_interface( shader_core_ctx *core, simt_core_cluster *cluster ) { m_core=core; m_cluster=cluster; }
    virtual bool full( unsigned size, bool write ) const 
    {
        return m_cluster->icnt_injection_buffer_full(size,write);
    }
    virtual void push(mem_fetch *mf) 
    {
        m_cluster->icnt_inject_request_packet(mf);
    }
private:
    shader_core_ctx *m_core;
    simt_core_cluster *m_cluster;
};

class perfect_memory_interface : public mem_fetch_interface {
public:
    perfect_memory_interface( shader_core_ctx *core, simt_core_cluster *cluster ) { m_core=core; m_cluster=cluster; }
    virtual bool full( unsigned size, bool write) const
    {
        return m_cluster->response_queue_full();
    }
    virtual void push(mem_fetch *mf)
    {
        if( !mf->get_inst().empty() )
            m_core->mem_instruction_stats(mf->get_inst()); // not I$-fetch
        if ( mf && mf->isatomic() )
            mf->do_atomic(); // execute atomic inside the "memory subsystem"
        m_cluster->push_response_fifo(mf);
    }
private:
    shader_core_ctx *m_core;
    simt_core_cluster *m_cluster;
};


inline int scheduler_unit::get_sid() const { return m_shader->get_sid(); }

#endif /* SHADER_H */