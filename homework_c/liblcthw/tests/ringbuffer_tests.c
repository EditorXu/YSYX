#include"minunit.h"
#include<lcthw/ringbuffer.h>
#include<assert.h>

static RingBuffer *buffer = NULL;

char *test_create()
{
	buffer = RingBuffer_create(10);
	mu_assert(buffer != NULL, "Failed to create RingBuffer.");

	return NULL;
}

char *test_destroy()
{
	mu_assert(buffer != NULL, "Failed to make RingBuffer #2");
	RingBuffer_destroy(buffer);
	//mu_assert(buffer == NULL, "Failed to destroy RingBuffer.");

	return NULL;
}

char *test_write_read()
{
	char *data = "Hello!";
	int length = strlen(data);

	int rc = RingBuffer_write(buffer,data,length);
	mu_assert(rc == length, "Failed to write data to RingBuffer.");

	char *target = malloc(length);
	rc = RingBuffer_read(buffer,target,length);
	mu_assert(rc == length, "Failed to read data from RingBuffer.");

	mu_assert(strcmp(target,data) == 0,"Data read does not match data written.");

	if(target)
	{
		free(target);
		target = NULL;
	}

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_write_read);
	mu_run_test(test_destroy);

	return NULL;
}

RUN_TESTS(all_tests);

