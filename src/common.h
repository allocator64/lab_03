#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#define SORT_REVERSE
#undef SORT_REVERSE

#define USE_SRAND
#define SAMPLE_OUTPUT

typedef int int32;
typedef unsigned int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;
typedef unsigned char BOOL;

enum BOOL_VARS
{
	FALSE = 0,
	TRUE = 1
};

uint64 timestamp( void );

BOOL cmp( int64 a, int64 b );
BOOL rcmp( int64 a, int64 b );

void swap( int64 * a, int64 * b );

uint64 rand64( void );

uint32 cmp_count();
uint32 swap_count();
void zero_counters();
