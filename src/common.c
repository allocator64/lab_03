#include "common.h"

extern uint32 cmp_cnt;
extern uint32 swp_cnt;

uint64 rand64( void )
{
#if ( RAND_MAX == 0x7fff )
	return rand() * 1ll * rand() * 1ll * rand() * 1ll * rand();
#elif( RAND_MAX == 0x7fffffff )
	return rand() * 1ll * rand();
#else
	#pragma error( "Unsupported RAND_MAX" )
#endif
}

uint32 cmp_count()
{
	return cmp_cnt;
}
uint32 swap_count()
{
	return swp_cnt;
}
void zero_counters()
{
	cmp_cnt = swp_cnt = 0;
}