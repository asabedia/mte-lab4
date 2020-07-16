#include <stdio.h>
#include <cmsis_os2.h>
#include "random.h"
#include <stdbool.h>


uint32_t interarrival_ticks(uint32_t seconds_rate){
		return (next_event()/seconds_rate*osKernelGetTickFreq()) >> 16;
}

void arrivals(void* args);

void server(void* args);

void monitor(void* args);

int main(void){
    //osKernelInitialize();
}
