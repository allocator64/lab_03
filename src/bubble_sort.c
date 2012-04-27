#include "common.h"

void bubble_sort( int n, int64 * a )
{
	int i;
	BOOL flag = TRUE;

	while( flag )
	{
		flag = FALSE;

		for( i = 0; i < n - 1; ++i )
		{
#ifndef SORT_REVERSE
			if( cmp(a[i+1], a[i]) )
#else
			if( rcmp(a[i+1], a[i]) )
#endif
			{
				swap( &a[i], &a[i+1] );
				flag = TRUE;
			}
		}
	}
}