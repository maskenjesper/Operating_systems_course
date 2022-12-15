#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>

const int cylinders = 5000;

int* generateRequestSequence(int len);
int* scheduleFCFS(int* req_seq, int len); // Schedule is not determined by head position
int* scheduleSSTF(int* req_seq, int len, int pos);
int* scheduleSCAN(int* req_seq, int len, int pos);
int* scheduleCSCAN(int* req_seq, int len, int pos);
int* scheduleLook(int* req_seq, int len, int pos);
int* scheduleCLook(int* req_seq, int len, int pos);
int headTravel(int* schedule, int init_pos, int len);

int main (int argc, char *argv[])
{
    if (argc != 2) 
    {
        printf("Usage: main <initial position>");
        exit(1);
    }
    int initPos = atoi(argv[1]); // heads initial direction is always - => +
    int queueSize = 30;
    int* seq = generateRequestSequence(queueSize);
    printf("Request sequence\n\t");
    printArray(seq, queueSize);
    
    int* fcfs = scheduleFCFS(seq, queueSize);
    // int* sstf = scheduleSSTF(seq, queueSize, initPos);
    int* scan = scheduleSCAN(seq, queueSize, initPos);
    int* cscan = scheduleCSCAN(seq, queueSize, initPos);
    // int* look = scheduleLook(seq, queueSize, initPos);
    // int* clook = scheduleCLook(seq, queueSize, initPos);

    printf("Head travel for FCFS: %d\n", headTravel(fcfs, initPos, queueSize));
    // printf("Head travel for SSTF: %d\n", headTravel(sstf, initPos, queueSize));
    printf("Head travel for SCAN: %d\n", headTravel(scan, initPos, queueSize));
    printf("Head travel for C-SCAN: %d\n", headTravel(cscan, initPos, queueSize));
    // printf("Head travel for Look: %d\n", headTravel(look, initPos, queueSize));
    // printf("Head travel for C-Look: %d\n", headTravel(clook, initPos, queueSize));

    return 0;
}

int* generateRequestSequence(int len) 
{
    int* requestSequence = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) 
        requestSequence[i] = rand() % cylinders;
    return requestSequence;
}

int* scheduleFCFS(int* req_seq, int len)
{
    int* schedule = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) 
        schedule[i] = req_seq[i];

    printf("FCFS schedule:\n\t");
    printArray(schedule, len);
    return schedule;
}

int* scheduleSSTF(int* req_seq, int len, int pos) // TODO: implement
{
    int* schedule = malloc(len * sizeof(int));

}

int* scheduleSCAN(int* req_seq, int len, int pos)
{
    int* schedule = malloc(len * sizeof(int));
    int* sorted = copyArray(req_seq, len);
    sort(sorted, len);

    int sched_pos = 0;
    for (int i = pos; i < cylinders; i++)
        if (find(sorted, len, i))
            schedule[sched_pos++] = i;
    for (int i = pos - 1; i >= 0; i--)
        if (find(sorted, len, i))
            schedule[sched_pos++] = i;

    printf("SCAN schedule:\n\t");
    printArray(schedule, len);
    free(sorted);
    return schedule;
}

int* scheduleCSCAN(int* req_seq, int len, int pos) // TODO: implement
{
    int* schedule = malloc(len * sizeof(int));
    int* sorted = copyArray(req_seq, len);
    sort(sorted, len);

    int sched_pos = 0;
    for (int i = pos; i < cylinders; i++)
        if (find(sorted, len, i))
            schedule[sched_pos++] = i;
    for (int i = 0; i < pos; i++)
        if (find(sorted, len, i))
            schedule[sched_pos++] = i;

    printf("C-SCAN schedule:\n\t");
    printArray(schedule, len);
    free(sorted);
    return schedule;
}

int* scheduleLook(int* req_seq, int len, int pos) // TODO: implement
{
    int* schedule = malloc(len * sizeof(int));

}

int* scheduleCLook(int* req_seq, int len, int pos) // TODO: implement
{
    int* schedule = malloc(len * sizeof(int));

}

int headTravel(int* schedule, int init_pos, int len)
{
    int travel = abs(init_pos - schedule[0]);
    for (int i = 1; i < len; i++) 
        travel += abs(schedule[i-1] - schedule[i]);
    return travel;
}
