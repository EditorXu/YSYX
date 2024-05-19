#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<lcthw/ringbuffer.h>
#include<lcthw/ringbuffer_posix.h>

#define DATA_SIZE 1000
#define TEST_ITERATIONS 10000

void generate_random_data(char *data, int length)
{
	for(int i = 0; i < length; i++)
	 {
		 data[i] = 'A' + rand() % 26;
	 }
}

void performance_test_ringbuffer(RingBuffer *ringbuffer)
{
	char data[DATA_SIZE];
	char target[DATA_SIZE];
	srand(time(NULL));

	for(int i = 0; i < TEST_ITERATIONS; i++)
	{
		generate_random_data(data, DATA_SIZE);
		RingBuffer_write(ringbuffer, data, DATA_SIZE);
		RingBuffer_read(ringbuffer, target, DATA_SIZE);
	}
}

void performance_test_ringbuffer_posix(RingBufferPosix *ringbuffer)
{
	char data[DATA_SIZE];
	char target[DATA_SIZE];
	srand(time(NULL));

	for(int i = 0; i < TEST_ITERATIONS; i++)
	{
		generate_random_data(data, DATA_SIZE);
		RingBuffer_write(ringbuffer, data, DATA_SIZE);
		RingBuffer_read(ringbuffer, target, DATA_SIZE);
	}
}

int main()
{
	RingBuffer *ringbuffer = RingBuffer_create(DATA_SIZE);
	RingBufferPosix *ringbuffer_posix = RingBuffer_create(DATA_SIZE);

	clock_t start = clock();
	performance_test_ringbuffer(ringbuffer);
	clock_t end = clock();
	double time_spent = (double)(end -start) / CLOCKS_PER_SEC;
	printf("RingBuffer Performance Test Time: %f seconds\n", time_spent);

	start = clock();
	performance_test_ringbuffer_posix(ringbuffer_posix);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("RingBufferPosix Performance Test Time: %f seconds\n", time_spent);

	RingBuffer_destroy(ringbuffer);
	RingBufferPosix_destroy(ringbuffer_posix);

	return 0;
}

