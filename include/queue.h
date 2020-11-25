#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

enum {
  Q_SUCCESS = 0,
  Q_ERR_INVALID = -1,
};

typedef int (*queue_buffer_handler)(void *, size_t);

typedef struct _queue_msg {
  struct _queue_msg *next;

  void *buffer;
  size_t buffer_size;
} queue_msg_t;

typedef struct {
  queue_msg_t *msg;

  pthread_mutex_t *lock;
  pthread_cond_t *ready;
} queue_t;

/* TODO: queue create func */
/* TODO: queue release func */

int queue_enqueue(queue_t *queue, void *buffer, const size_t buffer_size);
int queue_dequeue(queue_t *queue, queue_buffer_handler handler);

#endif
