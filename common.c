
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"

uint32_t getBit (uint32_t value , unsigned int b) {
	return (value >>b) &1 ;
}


uint32_t getBits (uint32_t value , unsigned int hi,unsigned int lo) {
	return (value>>lo) & ((1<<(hi-lo+1))-1) ;
}

uint32_t concatenate (uint32_t value1 , unsigned int width1,uint32_t value2 , unsigned int width2) {
	assert((width1+width2) <=32);
	return (value1<<width2) | value2 ;
}

//=====================================================================

// Pop count unit which is used to count number of 1's
// Used in Fetch to detect number of Active Barriers

//=====================================================================
uint32_t Pop_Count( unsigned input)
{
    uint32_t Ones_Count=0;
    for(int i = 0; i < sizeof(input)*8; i++)
    {
		if ((input >> i) & 1) Ones_Count++;
    }
        return Ones_Count;

}

//=====================================================================

//=====================================================================

