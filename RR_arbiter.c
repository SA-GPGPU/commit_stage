#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "define.h"
#include "config.h"
#include "common.h"
#include "commit_stage.h"


//declaration
bool ptr [NUM_RSPS]={1,1,1,1,1,1};
bool unmask_higher_pri [NUM_RSPS];
bool grant_unmasked [NUM_RSPS];
bool req_masked [NUM_RSPS];
bool mask_higher_pri [NUM_RSPS];
bool grant_masked [NUM_RSPS];
bool req_masked_flag;
bool rsp_valid_flag;

void rr_arbiter(bool rsp_valid[NUM_RSPS], bool *grant_onehot, unsigned *grant_index)
{
	//round robin arbiter
	for (int i=0; i<NUM_RSPS; i++)
	{
		if(rsp_valid[i]==1)
		{
			for (int j=i+1; j<NUM_RSPS; j++) unmask_higher_pri[j]=1;
			break;
		}
	}
	for (int i=0; i<NUM_RSPS; i++) grant_unmasked[i]=rsp_valid[i]&& !unmask_higher_pri[i];
	for (int i=0; i<NUM_RSPS; i++) req_masked[i]=ptr[i]&&rsp_valid[i];
	for (int i=0; i<NUM_RSPS; i++)
	{
		if(req_masked[i]==1)
		{
			for (int j=i+1; j<NUM_RSPS; j++) mask_higher_pri[j]=1;
			break;
		}
	}
	for (int i=0; i<NUM_RSPS; i++) grant_masked[i]=req_masked[i]&& !mask_higher_pri[i];
	for (int i=0; i<NUM_RSPS; i++) if(req_masked[i]==1) req_masked_flag=1;
	for (int i=0; i<NUM_RSPS; i++) if(rsp_valid[i]==1) rsp_valid_flag=1;
	if (req_masked_flag)
	{
		for (int i=0; i<NUM_RSPS; i++)
		{
			grant_onehot[i]=grant_masked[i];
			ptr[i]=mask_higher_pri[i];
		}
	}
	else
	{
		for (int i=0; i<NUM_RSPS; i++)
		{
		grant_onehot[i]=grant_unmasked[i];
		}
		if(rsp_valid_flag)
		{
			for (int i=0; i<NUM_RSPS; i++)
			{
				ptr[i]=unmask_higher_pri[i];
			}
		}
	}
	req_masked_flag=0;
	rsp_valid_flag=0;
	for (int i=0; i<NUM_RSPS; i++) if(grant_onehot[i]==1) *grant_index=i;

}
