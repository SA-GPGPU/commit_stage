#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "define.h"
#include "config.h"
#include "common.h"
#include "commit_stage.h"

//declaration
VX_commit alu_commit;
VX_commit ld_commit;
VX_commit st_commit;
VX_commit csr_commit;
VX_commit fpu_commit;
VX_commit gpu_commit;
bool ld_commit_ready=1;
bool st_commit_ready=1;
bool fpu_commit_ready=1;
bool alu_commit_ready=1;
bool csr_commit_ready=1;
bool gpu_commit_ready=1;
VX_writeback writeback;
VX_cmt_to_csr cmt_to_csr;

int main()
{
    //initialization
    alu_commit.wid=1;
    alu_commit.tmask=6;
    alu_commit.PC=1;
    alu_commit.rd=2;
    alu_commit.data[0]=24;
    alu_commit.data[1]=23;
    alu_commit.data[2]=15;
    alu_commit.data[3]=16;
    alu_commit.eop=1;
    alu_commit.wb=1;
    alu_commit.valid=1;

    //calling functions
    commit_stage( alu_commit, ld_commit,  st_commit,
                  csr_commit, fpu_commit, gpu_commit,
                  &ld_commit_ready,  &fpu_commit_ready,  &alu_commit_ready,
                  &csr_commit_ready, &gpu_commit_ready,  &writeback,
                  &st_commit_ready,  &cmt_to_csr);

    printf_writeback(writeback);
    printf_cmt_to_csr_commit(cmt_to_csr);

    return 0;
}
