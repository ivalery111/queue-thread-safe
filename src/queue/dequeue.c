#include "queue_internal.h"

int queue_dequeue(queue_t *queue, queue_buffer_handler handler) {
  if (queue == NULL) return Q_ERR_INVALID;

  return _queue_dequeue(queue, handler);
}
