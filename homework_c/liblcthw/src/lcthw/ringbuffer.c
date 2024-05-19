#undef NDEBUG
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<lcthw/dbg.h>
#include<lcthw/ringbuffer.h>

RingBuffer *RingBuffer_create(int length)
{
	RingBuffer *ringbuffer = malloc(sizeof(RingBuffer));
	ringbuffer->length = length + 1;
	ringbuffer->start = 0;
	ringbuffer->end = 0;
	ringbuffer->buffer = malloc(ringbuffer->length);

	return ringbuffer;
}

void RingBuffer_destroy(RingBuffer *ringbuffer)
{
	if(ringbuffer)
	{
		if(ringbuffer->buffer)
		{
			free(ringbuffer->buffer);
			ringbuffer->buffer = NULL;
		}
		free(ringbuffer);
		ringbuffer = NULL;
	}
}

int RingBuffer_write(RingBuffer *ringbuffer, char *data, int length)
{
	if(RingBuffer_available_data(ringbuffer) == 0)
	{
		ringbuffer->start = ringbuffer->end = 0;
	}

	check(length <= RingBuffer_available_space(ringbuffer),"Not enough space: %d request, %d available",RingBuffer_available_data(ringbuffer), length);

	void *result = memcpy(RingBuffer_ends_at(ringbuffer), data, length);
	check(result != NULL,"Failed to write data into ringbuffer.");

	RingBuffer_commit_write(ringbuffer, length);

	return length;
error:
	return -1;
}

int RingBuffer_read(RingBuffer *ringbuffer, char *target, int amount)
{
	check_debug(amount <= RingBuffer_available_data(ringbuffer),"Not enough in the ringbuffer: has %d, needs %d",RingBuffer_available_data(ringbuffer), amount);

	void *result = memcpy(target, RingBuffer_starts_at(ringbuffer), amount);
	check(result != NULL, "Failed to write ringbuffer into data.");

	RingBuffer_commit_read(ringbuffer, amount);

	if(ringbuffer->end == ringbuffer->start)
	{
		ringbuffer->start = ringbuffer->end = 0;
	}

	return amount;
error:
	return -1;
}

bstring RingBuffer_gets(RingBuffer *ringbuffer, int amount)
{
	check(amount > 0,"Need more than 0 for gets,you gave: %d ",amount);
	check_debug(amount <= RingBuffer_available_data(ringbuffer),"Not enough in the ringbuffer.");

	bstring result = blk2bstr(RingBuffer_starts_at(ringbuffer), amount);
	check(result != NULL, "Failed to create gets result.");
	check(blength(result) == amount, "Wrong result length.");

	RingBuffer_commit_read(ringbuffer, amount);
	assert(RingBuffer_available_data(ringbuffer) >= 0 && "Error in read commit.");

	return result;
error:
	return NULL;
}


