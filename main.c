#include <stdio.h>
#include <cmsis_os2.h>
#include "random.h"
#include <stdbool.h>

#define N_QUEUE 2
#define QLIMIT 10

osMessageQueueId_t queues[N_QUEUE];

uint32_t interarrival_ticks(uint32_t seconds_rate){
		return (next_event()/seconds_rate*osKernelGetTickFreq()) >> 16;
}

void initialize_queues(void){
    for(int i =0; i < N_QUEUE; i++){
        queues[i] = osMessageQueueNew(QLIMIT, sizeof(int), NULL);
    }
}

void arrivals(void* args);

void server(void* args);

void monitor(void* args);

int main(void){
    //osKernelInitialize();
}
