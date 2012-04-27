#include "common.h"

static void normalize( int root, int n, int64 * a )
{
	int e1,e2;

	while( 2 * root + 1 < n )
	{
		e1 = 2 * root + 1; // first
		e2 = e1 + 1;       // second

		/*
		check if second ancessor exists and greater than first
		*/
#ifndef SORT_REVERSE
		if( e2 < n && cmp( a[e1], a[e2] ) )
#else
		if( e2 < n && rcmp( a[e1], a[e2] ) )
#endif
			e1 = e2; // swap

		// if a[root] < max( a[e1],a[e2] ), do a swap
#ifndef SORT_REVERSE
		if( cmp( a[root], a[e1] ) )
#else
		if( rcmp( a[root], a[e1] ) )
#endif
		{
			swap(&a[root],&a[e1]);
			root = e1;
		}
		else
			break;
	}
}

void heap_sort( int n, int64 * a )
{
	int i = 0;

	/// build the heap
	for( i = n - 1; i >= 0; --i )
		normalize(i,n,a);
	/// heapsort
	while( n > 0 )
	{
		swap(&a[0],&a[n-1]); // swap top and tail in heap
		--n;
		normalize(0,n,a);
	}
}