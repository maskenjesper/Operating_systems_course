#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const int cylinders = 5000;

int* generateRequestSequence(int len);
int* pathFCFS(int* req_seq, int len); // path is not determined by head position
int* pathSSTF(int* req_seq, int len, int pos);
int* pathSCAN(int* req_seq, int len, int pos);
int* pathCSCAN(int* req_seq, int len, int pos);
int* pathLook(int* req_seq, int len, int pos);
int* pathCLook(int* req_seq, int len, int pos);
int headTravel(int* path, int init_pos, int len);

int main (int argc, char *argv[])
{
    if (argc != 2) 
    {
        printf("Usage: main <initial position>");
        exit(1);
    }
    int initPos = atoi(argv[1]); // heads initial direction is always - => +
    int queueSize = 1000;
    int* seq = generateRequestSequence(queueSize);
    printf("Request sequence\n\t");
    printArray(seq, queueSize);

    int* fcfs = pathFCFS(seq, queueSize);
    int* sstf = pathSSTF(seq, queueSize, initPos);
    int* scan = pathSCAN(seq, queueSize, initPos);
    int* cscan = pathCSCAN(seq, queueSize, initPos);
    int* look = pathLook(seq, queueSize, initPos);
    int* clook = pathCLook(seq, queueSize, initPos);

    printf("Head travel for FCFS: %d\n", headTravel(fcfs, initPos, queueSize));
    printf("Head travel for SSTF: %d\n", headTravel(sstf, initPos, queueSize));
    printf("Head travel for SCAN: %d\n", headTravel(scan, initPos, queueSize + 1));
    printf("Head travel for C-SCAN: %d\n", headTravel(cscan, initPos, queueSize + 2));
    printf("Head travel for Look: %d\n", headTravel(look, initPos, queueSize));
    printf("Head travel for C-Look: %d\n", headTravel(clook, initPos, queueSize));

    return 0;
}

int* generateRequestSequence(int len) 
{
    int* requestSequence = malloc(len * sizeof(int));
    unsigned int seed = time(NULL);
    for (int i = 0; i < len; i++) 
        requestSequence[i] = rand_r(&seed) % cylinders;
    return requestSequence;
}

int* pathFCFS(int* req_seq, int len) // Stupid function but I wanted consistency
{
    int* path = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) 
        path[i] = req_seq[i];

    printf("FCFS path:\n\t");
    printArray(path, len);
    return path;
}

int* pathSSTF(int* req_seq, int len, int pos)
{
    int* path = malloc(len * sizeof(int));
    int* sorted = copyArray(req_seq, len);
    sort(sorted, len);
    int path_pos = 0, head = pos, i = 1, lo, hi;

    // Find the two closest requests 
    while (sorted[i++] < head);
    lo = i-1;
    hi = i;

    // Compare until either end
    while (lo >= 0 && hi < len)
    {
        if (head - sorted[lo] < sorted[hi] - head)
            head = sorted[lo--];
        else
            head = sorted[hi++];
        path[path_pos++] = head;
    }

    // path the rest
    if (lo < 0) 
        for (int i = hi; i < len; i++)
            path[path_pos++] = sorted[i];
    else
        for (int i = lo; i >= 0; i--)
            path[path_pos++] = sorted[i];

    printf("SSTF path:\n\t");
    printArray(path, len);
    free(sorted);
    return path;
}

int* pathSCAN(int* req_seq, int len, int pos)
{
    int* path = malloc(len * sizeof(int) + sizeof(int));
    int* sorted = copyArray(req_seq, len);
    sort(sorted, len);

    int path_pos = 0;
    for (int i = pos; i < cylinders; i++)
    {
        int occurences = find(sorted, len, i);
        while (occurences-- > 0)
            path[path_pos++] = i;
    }
    path[path_pos++] = cylinders - 1; 
    for (int i = pos - 1; i >= 0; i--)
    {
        int occurences = find(sorted, len, i);
        while (occurences-- > 0)
            path[path_pos++] = i;
    }

    printf("SCAN path:\n\t");
    printArray(path, len);
    free(sorted);
    return path;
}

int* pathCSCAN(int* req_seq, int len, int pos) 
{
    int* path = malloc(len * sizeof(int) + 2 * sizeof(int));
    int* sorted = copyArray(req_seq, len);
    sort(sorted, len);

    int path_pos = 0;
    for (int i = pos; i < cylinders; i++)
    {
        int occurences = find(sorted, len, i);
        while (occurences-- > 0)
            path[path_pos++] = i;
    }
    path[path_pos++] = cylinders - 1; 
    path[path_pos++] = 0; 
    for (int i = 0; i < pos; i++)
    {
        int occurences = find(sorted, len, i);
        while (occurences-- > 0)
            path[path_pos++] = i;
    }

    printf("C-SCAN path:\n\t");
    printArray(path, len);
    free(sorted);
    return path;
}

int* pathLook(int* req_seq, int len, int pos) // TODO: implement
{
    int* path = malloc(len * sizeof(int));
    int* sorted = copyArray(req_seq, len);
    sort(sorted, len);

    int path_pos = 0;
    for (int i = pos; i < cylinders; i++)
    {
        int occurences = find(sorted, len, i);
        while (occurences-- > 0)
            path[path_pos++] = i;
    }
    for (int i = pos - 1; i >= 0; i--)
    {
        int occurences = find(sorted, len, i);
        while (occurences-- > 0)
            path[path_pos++] = i;
    }

    printf("Look path:\n\t");
    printArray(path, len);
    free(sorted);
    return path;
}

int* pathCLook(int* req_seq, int len, int pos) // TODO: implement
{
    int* path = malloc(len * sizeof(int));
    int* sorted = copyArray(req_seq, len);
    sort(sorted, len);

    int path_pos = 0;
    for (int i = pos; i < cylinders; i++)
    {
        int occurences = find(sorted, len, i);
        while (occurences-- > 0)
            path[path_pos++] = i;
    }
    for (int i = 0; i < pos; i++)
    {
        int occurences = find(sorted, len, i);
        while (occurences-- > 0)
            path[path_pos++] = i;
    }

    printf("C-Look path:\n\t");
    printArray(path, len);
    free(sorted);
    return path;
}

int headTravel(int* path, int init_pos, int len)
{
    int travel = abs(init_pos - path[0]);
    for (int i = 1; i < len; i++) 
        travel += abs(path[i-1] - path[i]);
    return travel;
}
