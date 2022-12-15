#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void errExit(const char *cause);
void printArray(int* array, int len);
int* copyArray(int* arrar, int len);
void sort(int* array, int len);
int find(int* array, int len, int value); // Assumes array in ascending order
