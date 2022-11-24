#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "define.h"
#include "config.h"
#include "common.h"
#include "commit_stage.h"

void printf_cmt_to_csr_commit(VX_cmt_to_csr cmt_to_csr)
{
    printf("cmt_to_csr.commit_size=%d\n",cmt_to_csr.commit_size);
    printf("cmt_to_csr.valid=%d\n",cmt_to_csr.valid);
}

void printf_alu_commit(VX_commit alu_commit)
{
    printf("alu_commit.wid=%d\n",alu_commit.wid);
    printf("alu_commit.tmask=%d\n",alu_commit.tmask);
    printf("alu_commit.PC=%d\n",alu_commit.PC);
    printf("alu_commit.rd=%d\n",alu_commit.rd);
    printf("alu_commit.eop=%d\n",alu_commit.eop);
    for ( int i = 0; i <NUM_THREADS; i++)
    printf("alu_commit.data[%d]=%d\n",i,alu_commit.data[i]);

}

void printf_gpu_commit(VX_commit gpu_commit)
{
    printf("gpu_commit.wid=%d\n",gpu_commit.wid);
    printf("gpu_commit.tmask=%d\n",gpu_commit.tmask);
    printf("gpu_commit.PC=%d\n",gpu_commit.PC);
    printf("gpu_commit.rd=%d\n",gpu_commit.rd);
    printf("gpu_commit.eop=%d\n",gpu_commit.eop);
    for ( int i = 0; i <NUM_THREADS; i++)
    printf("gpu_commit.data[%d]=%d\n",i,gpu_commit.data[i]);

}

void printf_fpu_commit(VX_commit fpu_commit)
{
    printf("fpu_commit.wid=%d\n",fpu_commit.wid);
    printf("fpu_commit.tmask=%d\n",fpu_commit.tmask);
    printf("fpu_commit.PC=%d\n",fpu_commit.PC);
    printf("fpu_commit.rd=%d\n",fpu_commit.rd);
    printf("fpu_commit.eop=%d\n",fpu_commit.eop);
    for ( int i = 0; i <NUM_THREADS; i++)
    printf("fpu_commit.data[%d]=%d\n",i,fpu_commit.data[i]);

}

void printf_ld_commit(VX_commit ld_commit)
{
    printf("ld_commit.wid=%d\n",ld_commit.wid);
    printf("ld_commit.tmask=%d\n",ld_commit.tmask);
    printf("ld_commit.PC=%d\n",ld_commit.PC);
    printf("ld_commit.rd=%d\n",ld_commit.rd);
    printf("ld_commit.eop=%d\n",ld_commit.eop);
    for ( int i = 0; i <NUM_THREADS; i++)
    printf("ld_commit.data[%d]=%d\n",i,ld_commit.data[i]);

}

void printf_st_commit(VX_commit st_commit)
{
    printf("st_commit.wid=%d\n",st_commit.wid);
    printf("st_commit.tmask=%d\n",st_commit.tmask);
    printf("st_commit.PC=%d\n",st_commit.PC);
    printf("st_commit.rd=%d\n",st_commit.rd);
    printf("st_commit.eop=%d\n",st_commit.eop);
    for ( int i = 0; i <NUM_THREADS; i++)
    printf("st_commit.data[%d]=%d\n",i,st_commit.data[i]);

}

void printf_csr_commit(VX_commit csr_commit)
{
    printf("csr_commit.wid=%d\n",csr_commit.wid);
    printf("csr_commit.tmask=%d\n",csr_commit.tmask);
    printf("csr_commit.PC=%d\n",csr_commit.PC);
    printf("csr_commit.rd=%d\n",csr_commit.rd);
    printf("csr_commit.eop=%d\n",csr_commit.eop);
    for ( int i = 0; i <NUM_THREADS; i++)
    printf("csr_commit.data[%d]=%d\n",i,csr_commit.data[i]);

}

void printf_writeback(VX_writeback writeback)
{
    printf("writeback.wid=%d\n",writeback.wid);
    printf("writeback.tmask=%d\n",writeback.tmask);
    printf("writeback.PC=%d\n",writeback.PC);
    printf("writeback.rd=%d\n",writeback.rd);
    for ( int i = 0; i <NUM_THREADS; i++)
    printf("writeback.data[%d]=%d\n",i,writeback.data[i]);
    printf("writeback.eop=%d\n",writeback.eop);

}

