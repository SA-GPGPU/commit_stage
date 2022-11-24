#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "define.h"
#include "config.h"
#include "common.h"
#include "commit_stage.h"


void assign_wb_struct(VX_commit commit,VX_writeback *writeback)
{
    writeback->wid      = commit.wid      	;
    writeback->tmask 	= commit.tmask    	;
    writeback->PC       = commit.PC       	;
    writeback->rd       = commit.rd       	;
    writeback->eop      = commit.eop        ;
	for(int i = 0; i <NUM_THREADS; i++)
	writeback->data[i] = commit.data[i] ;
}

