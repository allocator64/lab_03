#include "common.h"
#include "array_fill.h"
#include "bubble_sort.h"
#include "heap_sort.h"

typedef struct
{
	uint32 swaps,cmps;
	uint64 timestamp;
}test_res;

enum tests
{
	SORTED = 0,
	REVERSE_SORTED = 1,
	RANDOM_1 = 2,
	RANDOM_2 = 3,
	TEST_COUNT
};

const char * test_names[TEST_COUNT+1] = 
{
	"sorted         ",
	"reverse sorted ",
	"random 1       ",
	"random 2       ",
	"average        "
};

typedef void (callback)(int n,int64 * a);

void test_sort( int n, callback func, test_res test[TEST_COUNT] )
{
	int64 * a = ( int64 * )calloc( n, sizeof(int64) );
	uint64 tb;
	uint64 te;
	int i;


	/// direct sorted array
	array_fill_sorted(n,a);

	zero_counters();
	tb = timestamp();
	func(n,a);
	te = timestamp();

	test[SORTED].cmps = cmp_count();
	test[SORTED].swaps = swap_count();
	test[SORTED].timestamp = te - tb;

	/// reverse sorted array
	array_fill_rsorted(n,a);
	
	zero_counters();
	tb = timestamp();
	func(n,a);
	te = timestamp();

	test[REVERSE_SORTED].cmps = cmp_count();
	test[REVERSE_SORTED].swaps = swap_count();
	test[REVERSE_SORTED].timestamp = te - tb;

	/// random array #1
	array_fill_random(n,a);

	zero_counters();
	tb = timestamp();
	func(n,a);
	te = timestamp();

	test[RANDOM_1].cmps = cmp_count();
	test[RANDOM_1].swaps = swap_count();
	test[RANDOM_1].timestamp = te - tb;

	/// random array #2
	array_fill_random(n,a);

	zero_counters();
	tb = timestamp();
	func(n,a);
	te = timestamp();

	test[RANDOM_2].cmps = cmp_count();
	test[RANDOM_2].swaps = swap_count();
	test[RANDOM_2].timestamp = te - tb;

	free(a);
}

void test( const char * sort_name,callback sort_function,int test_count,... )
{
	int i,j,n;
	double cmpd,swpd,timed;
	test_res res[TEST_COUNT];
	va_list vlist;

	va_start(vlist,test_count);
	printf("Testing %s\n",sort_name);

	for( i = 0; i < test_count; ++i )
	{
		n = va_arg(vlist,int);
		printf("\nCurrent n is %d\n",n);

		test_sort(n,sort_function,res);

		cmpd = swpd = timed = 0;

		for( j = 0; j < TEST_COUNT; ++j )
		{
#ifdef WIN32
			printf("%s: cmp %12d swap %12d timestamp %12I64d\n",test_names[j],res[j].cmps,res[j].swaps,res[j].timestamp);
#else
			printf("%s: cmp %12d swap %12d timestamp %12lld\n",test_names[j],res[j].cmps,res[j].swaps,res[j].timestamp);
#endif
			cmpd += res[j].cmps;
			swpd += res[j].swaps;
			timed += res[j].timestamp;
		}
		cmpd /= 4;
		swpd /= 4;
		timed /=4;

		printf("%s: cmp %12.2lf swap %12.2lf timestamp %12.2lf\n",test_names[TEST_COUNT],cmpd,swpd,timed);
	}
}

int main( int argc, char **argv, char **envp )
{
	test("Bubble sort",bubble_sort,5,10,20,50,100,10000);
	printf("\n");
	test("Heap sort",heap_sort,5,10,20,50,100,10000);

	return 0;
}