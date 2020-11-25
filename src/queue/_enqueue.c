#include "queue_internal.h"

int _queue_enqueue(queue_t *queue, void *buffer, const size_t buffer_size) {
  pthread_mutex_lock(queue->lock);

  queue_msg_t *msg = calloc(1, sizeof(*msg));
  assert(msg != NULL);

  msg->buffer = calloc(1, sizeof(buffer_size));
  assert(msg->buffer != NULL);
  memcpy(msg->buffer, buffer, buffer_size);
  msg->buffer_size = buffer_size;
  msg->next = NULL;

  msg->next = queue->msg;
  queue->msg = msg;

  pthread_mutex_unlock(queue->lock);

  pthread_cond_signal(queue->ready);

  return Q_SUCCESS;
}
