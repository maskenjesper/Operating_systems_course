#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void errExit(const char *cause);
unsigned char page_number(int laddr);
unsigned char offset_number(int laddr);
int read_number(int fd);
