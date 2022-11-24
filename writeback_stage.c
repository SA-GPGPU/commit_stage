#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "define.h"
#include "config.h"
#include "common.h"
#include "commit_stage.h"

//declaration
bool rsp_valid [NUM_RSPS];
bool grant_onehot [NUM_RSPS];
unsigned grant_index;

void writeback_stage(VX_commit alu_commit, VX_commit ld_commit, VX_commit st_commit,
				     VX_commit csr_commit, VX_commit fpu_commit, VX_commit gpu_commit,
				     bool *ld_commit_ready, bool *fpu_commit_ready, bool *alu_commit_ready,
					 bool *csr_commit_ready, bool *gpu_commit_ready,VX_writeback *writeback)
{
    //assign valid signal to arbiter when execution unit is valid and has writeback signal
	rsp_valid[0]=gpu_commit.valid && gpu_commit.wb;
	rsp_valid[1]=csr_commit.valid && csr_commit.wb;
	rsp_valid[2]=alu_commit.valid && alu_commit.wb;
	rsp_valid[3]=fpu_commit.valid && fpu_commit.wb;
	rsp_valid[NUM_RSPS-1]=ld_commit.valid && ld_commit.wb;

	//round_robin_arbiter
    rr_arbiter( rsp_valid, grant_onehot, &grant_index);

	//assign signals from execution unit into writeback
	if(grant_index==0) assign_wb_struct (ld_commit,&*writeback);
	if(grant_index==1) assign_wb_struct(fpu_commit,&*writeback);
	if(grant_index==2) assign_wb_struct(alu_commit,&*writeback);
	if(grant_index==3) assign_wb_struct(csr_commit,&*writeback);
	if(grant_index==4) assign_wb_struct(gpu_commit,&*writeback);

	//assign execution units ready signals when it valid or have no writeback signal
    *ld_commit_ready  = grant_onehot[0] || !ld_commit.wb;
    *fpu_commit_ready = grant_onehot[1] || !fpu_commit.wb;
    *alu_commit_ready = grant_onehot[2] || !alu_commit.wb;
    *csr_commit_ready = grant_onehot[3] || !csr_commit.wb;
    *gpu_commit_ready = grant_onehot[4] || !gpu_commit.wb;
}
