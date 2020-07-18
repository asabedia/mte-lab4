#include <stdio.h>
#include <cmsis_os2.h>
#include "random.h"
#include <stdbool.h>

#define N_QUEUE 2
#define QLIMIT 10

osMessageQueueId_t queues[N_QUEUE];

struct{
    int total_q; //total messages queued
    int total_p; //total messages processed
    int total_d; //total messages denied (due to full queue)
} system_stats = {0, 0, 0};


uint32_t interarrival_ticks(uint32_t seconds_rate){
		return (next_event()/seconds_rate*osKernelGetTickFreq()) >> 16;
}

void initialize_queues(void){
    for(int i =0; i < N_QUEUE; i++){
        queues[i] = osMessageQueueNew(QLIMIT, sizeof(int), NULL);
    }
}

void arrivals(void* args){
    int arrival_rate = 9; // 9Hz arrival rate
    int queue_index = 0;

    int msg = 0;
    while(1){
        uint32_t iat = interarrival_ticks(arrival_rate); //interarrival time in ticks
        osDelay(iat);
        osStatus_t info = osMessageQueuePut(queues[queue_index], &msg, 0, 0);
        printf("os status: %d\n", info);

        if(info == osErrorResource) system_stats.total_d ++;
        else{ system_stats.total_q ++; }

        msg ++;
        queue_index = (queue_index + 1) % N_QUEUE;
    }
}

void server(void* args);

void monitor(void* args){
    while(1){
        printf(
            "successful sent messages: %d, received messages: %d, overflows: %d\n",
            system_stats.total_q,
            system_stats.total_p,
            system_stats.total_d
            );
        osDelay(osKernelGetTickFreq());
    }
}

int main(void){
    //osKernelInitialize();
}
