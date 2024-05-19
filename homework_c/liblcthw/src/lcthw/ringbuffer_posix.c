#include<lcthw/ringbuffer_posix.h>
#include<stdlib.h>
#include<string.h>

RingBufferPosix *RingBufferPosix_create(int length)
{
	RingBufferPosix *ringbuffer = malloc(sizeof(RingBufferPosix));
	ringbuffer->length = length + 1;
	ringbuffer->start = 0;
	ringbuffer->end = 0;
	ringbuffer->buffer = malloc(ringbuffer->length);

	sem_init(&ringbuffer->mutex,0,1);
	sem_init(&ringbuffer->empty,0,length);
	sem_init(&ringbuffer->full,0,0);

	return ringbuffer;
}

void RingBufferPosix_destroy(RingBufferPosix *ringbuffer)
{
	if(ringbuffer)
	{
		if(ringbuffer->buffer)
		{
			free(ringbuffer->buffer);
			ringbuffer->buffer = NULL;
		}
		sem_destroy(&ringbuffer->mutex);
		sem_destroy(&ringbuffer->empty);
		sem_destroy(&ringbuffer->full);
		free(ringbuffer);
		ringbuffer = NULL;
	}
}

int RingBufferPosix_write(RingBufferPosix *ringbuffer, char *data, int length)
{
	sem_wait(&ringbuffer->empty);
	sem_wait(&ringbuffer->mutex);

	for(int i = 0; i < length; i++)
	{
		ringbuffer->buffer[ringbuffer->end] = data[i];
		ringbuffer->end = (ringbuffer->end + 1) % ringbuffer->length;
	}

	sem_post(&ringbuffer->mutex);
	sem_post(&ringbuffer->full);

	return length;
}

int RingBufferPosix_read(RingBufferPosix *ringbuffer, char *target, int amount)
{
	sem_wait(&ringbuffer->full);
	sem_wait(&ringbuffer->mutex);

	for(int i = 0; i < amount; i++)
	{
		target[i] = ringbuffer->buffer[ringbuffer->start];
		ringbuffer->start = (ringbuffer->start + 1) % ringbuffer->length;
	}

	sem_post(&ringbuffer->mutex);
	sem_post(&ringbuffer->empty);

	return amount;
}


