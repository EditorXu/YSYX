#include"minunit.h"
#include<lcthw/ringbuffer_posix.h>

char *test_create_destroy()
{
	RingBufferPosix *ringbuffer = RingBufferPosix_create(10);
	mu_assert(ringbuffer != NULL, "Failed to create RingBufferPosix.");

	RingBufferPosix_destroy(ringbuffer);

	return NULL;
}

char *test_write_read()
{
	RingBufferPosix *ringbuffer = RingBufferPosix_create(10);
	mu_assert(ringbuffer != NULL, "Failed to create RingBufferPosix.");

	char *data = "Hello!";
	int length = strlen(data);

	int rc = RingBufferPosix_write(ringbuffer, data, length);
	mu_assert(rc == length, "Failed to write data to RingBufferPosix.");

	char *target = malloc(length);
	rc = RingBufferPosix_read(ringbuffer,target,length);
	mu_assert(rc == length, "Failed to read data from RingBufferPosix.");

	mu_assert(strcmp(target,data) == 0, "Data read does not match data written.");

	RingBufferPosix_destroy(ringbuffer);
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

	mu_run_test(test_create_destroy);
	mu_run_test(test_write_read);

	return NULL;
}

RUN_TESTS(all_tests);

