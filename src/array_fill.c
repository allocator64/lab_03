#include "common.h"

void array_fill_random( int n, int64 * a )
{
	while( n )
	{
		--n;
		a[n] = rand64();
	}
}

void array_fill_sorted( int n, int64 * a )
{
	while( n )
	{
		--n;
		a[n] = n;
	}
}

void array_fill_rsorted( int n, int64 * a )
{
	int i;

	for( i = 0; i < n; ++i )
	{
		a[i] = n - i - 1;
	}
}