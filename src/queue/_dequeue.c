#include "queue_internal.h"

int _queue_dequeue(queue_t *queue, queue_buffer_handler handler) {
  queue_msg_t *msg = NULL;

  for (;;) {
    pthread_mutex_lock(queue->lock);

    while (queue->msg == NULL) {
      pthread_cond_wait(queue->ready, queue->lock);
    }

    msg = queue->msg;
    queue->msg = msg->next;

    pthread_mutex_unlock(queue->lock);

    if (handler(msg->buffer, msg->buffer_size) == 1) { /* Exit */
      msg->buffer_size = 0;
      safe_free(msg->buffer);
      safe_free(msg);
      return 1;
    }

    msg->buffer_size = 0;
    safe_free(msg->buffer);
    safe_free(msg);
  }
}
