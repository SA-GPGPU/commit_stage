#include <stdio.h>
#include <stdint.h>
#include "define.h"
#include "config.h"
#include "common.h"

#ifndef DATAW_wb
#define DATAW_wb NW_BITS + 32 + NUM_THREADS + NR_BITS + (NUM_THREADS * 32) + 1;
#endif
#ifndef NUM_RSPS
#define NUM_RSPS  5
#endif



typedef struct VX_commit
{
    uint64_t       uuid:UUID_BITS;
    unsigned       wid:NW_BITS;
    unsigned       tmask:NUM_THREADS;
    unsigned       PC:32;
    unsigned       rd:NR_BITS;
    unsigned       data[NUM_THREADS];
    unsigned       eop:1;
    unsigned       wb:1;
    unsigned       valid:1;

} VX_commit;

typedef struct VX_cmt_to_csr
{
    unsigned  commit_size:int_log2(6*NUM_THREADS+1);
    unsigned       valid:1;

} VX_cmt_to_csr;

typedef struct VX_writeback
{
    uint64_t       uuid:UUID_BITS;
    unsigned       wid:NW_BITS;
    unsigned       tmask:NUM_THREADS;
    unsigned       PC:32;
    unsigned       rd:NR_BITS;
    unsigned       data[NUM_THREADS];
    unsigned       eop:1;
    unsigned       valid:1;


} VX_writeback;


//============================= FUNCTIONS ============================================

void commit_stage(VX_commit alu_commit, VX_commit ld_commit, VX_commit st_commit,
				  VX_commit csr_commit, VX_commit fpu_commit, VX_commit gpu_commit,
				  bool *ld_commit_ready, bool *fpu_commit_ready, bool *alu_commit_ready,
				  bool *csr_commit_ready, bool *gpu_commit_ready,VX_writeback *writeback,
				  bool *st_commit_ready, VX_cmt_to_csr *cmt_to_csr);

void writeback_stage(VX_commit alu_commit, VX_commit ld_commit, VX_commit st_commit,
				     VX_commit csr_commit, VX_commit fpu_commit, VX_commit gpu_commit,
				     bool *ld_commit_ready, bool *fpu_commit_ready, bool *alu_commit_ready,
					 bool *csr_commit_ready, bool *gpu_commit_ready,VX_writeback *writeback);
void rr_arbiter(bool rsp_valid[NUM_RSPS], bool *grant_onehot, unsigned *grant_index);
void assign_wb_struct(VX_commit commit,VX_writeback *writeback);
void printf_writeback(VX_writeback writeback);
void printf_alu_commit(VX_commit alu_commit);
void printf_gpu_commit(VX_commit gpu_commit);
void printf_fpu_commit(VX_commit fpu_commit);
void printf_ld_commit(VX_commit ld_commit);
void printf_st_commit(VX_commit st_commit);
void printf_csr_commit(VX_commit csr_commit);
void printf_cmt_to_csr_commit(VX_cmt_to_csr cmt_to_csr);
