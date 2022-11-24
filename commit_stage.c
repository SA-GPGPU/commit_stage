#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "define.h"
#include "config.h"
#include "common.h"
#include "commit_stage.h"

//declaration
bool alu_commit_fire;
bool ld_commit_fire;
bool st_commit_fire;
bool csr_commit_fire;
bool fpu_commit_fire;
bool gpu_commit_fire;
bool commit_fire;
unsigned alu_size;
unsigned ld_size;
unsigned st_size;
unsigned csr_size;
unsigned fpu_size;
unsigned gpu_size;
unsigned commit_size;

void commit_stage(VX_commit alu_commit, VX_commit ld_commit, VX_commit st_commit,
				  VX_commit csr_commit, VX_commit fpu_commit, VX_commit gpu_commit,
				  bool *ld_commit_ready, bool *fpu_commit_ready, bool *alu_commit_ready,
				  bool *csr_commit_ready, bool *gpu_commit_ready,VX_writeback *writeback,
				  bool *st_commit_ready, VX_cmt_to_csr *cmt_to_csr)
{
    //commit_fire is signal which represents that the execution unit can out its data when it is valid
    //and when commit stage sends it ready signal to send its data
    alu_commit_fire = alu_commit.valid && *alu_commit_ready;
    ld_commit_fire  = ld_commit.valid  && *ld_commit_ready;
    st_commit_fire  = st_commit.valid  && *st_commit_ready;
    csr_commit_fire = csr_commit.valid && *csr_commit_ready;
    fpu_commit_fire = fpu_commit.valid && *fpu_commit_ready;
    gpu_commit_fire = gpu_commit.valid && *gpu_commit_ready;
    commit_fire = alu_commit_fire
               || ld_commit_fire
               || st_commit_fire
               || csr_commit_fire
               || fpu_commit_fire
               || gpu_commit_fire;

    //count ones in thread masks of fire execution unit
    if(alu_commit_fire)alu_size=Pop_Count( alu_commit.tmask);
    if(ld_commit_fire) ld_size=Pop_Count( ld_commit.tmask);
    if(st_commit_fire) st_size=Pop_Count( st_commit.tmask);
    if(csr_commit_fire)csr_size=Pop_Count( csr_commit.tmask);
    if(fpu_commit_fire)fpu_size=Pop_Count( fpu_commit.tmask);
    if(gpu_commit_fire)gpu_size=Pop_Count( gpu_commit.tmask);
	commit_size=alu_size+ld_size+st_size+csr_size+fpu_size+gpu_size;

	//assign to cmt_to_csr structr
	cmt_to_csr->valid=commit_fire;
	cmt_to_csr->commit_size=commit_size;

	//calling function
    writeback_stage(alu_commit, ld_commit, st_commit,
				    csr_commit, fpu_commit, gpu_commit,
				     &*ld_commit_ready,  &*fpu_commit_ready, &*alu_commit_ready,
					 &*csr_commit_ready, &*gpu_commit_ready, &*writeback);
}
