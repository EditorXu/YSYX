#include<time.h>
#include<string.h>
#include<stdio.h>
#include<lcthw/list_alogs.h>
#include<lcthw/list.h>
#include"minunit.h"
#include<assert.h>

#define NUM_ELEMENTS 1000
#define NUM_ITERATIONS 1000

char *test_performance()
{
	List *list = List_create();
	srand(time(NULL));

	for(int i = 0; i < NUM_ELEMENTS; i++)
	{
		char *str = malloc(20);;

		sprintf(str, "%d", (rand() % 1000));

		List_push(list,(void *)str);
	}

	clock_t start, end;
	double cpu_time_used;

	start = clock();
	for(int i = 0; i < NUM_ITERATIONS; i++)
	{
		List_bubble_sort(list, (List_compare)strcmp);
	}
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Bubble_sorted costs times: %f second\n", cpu_time_used);

	start = clock();
	for(int i = 0; i < NUM_ITERATIONS; i++)
	{
		List *sorted = List_merge_sort_down(list,(List_compare)strcmp);
		List_destroy(sorted);
	}
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Merge_sorted costs times: %f second\n",cpu_time_used);

	List_destroy(list);

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_performance);

	return NULL;
}

int main()
{
	all_tests();

	return 0;
}


