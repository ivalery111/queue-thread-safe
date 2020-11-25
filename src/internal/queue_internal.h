#ifndef QUEUE_INTERNAL_H
#define QUEUE_INTERNAL_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* TODO: queue message create func */
/* TODO: queue message release func */

int _queue_enqueue(queue_t *queue, void *buffer, const size_t buffer_size);
int _queue_dequeue(queue_t *queue, queue_buffer_handler handler);

#endif
