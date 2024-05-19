#ifndef _ringbuffer_posix_h
#define _ringbuffer_posix_h

#include<pthread.h>
#include<semaphore.h>

typedef struct
{
	char *buffer;
	int length;
	int start;
	int end;
	sem_t mutex;
	sem_t empty;
	sem_t full;
} RingBufferPosix;

RingBufferPosix *RingBufferPosix_create(int length);

void RingBufferPosix_destroy(RingBufferPosix *ringbuffer);

int RingBufferPosix_write(RingBufferPosix *ringbuffer, char *data, int length);

int RingBufferPosix_read(RingBufferPosix *ringbuffer, char *target, int amount);

#endif

