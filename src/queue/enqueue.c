#include "queue_internal.h"

int queue_enqueue(queue_t *queue, void *buffer, const size_t buffer_size) {
  if (queue == NULL || buffer == NULL) return Q_ERR_INVALID;

  return _queue_enqueue(queue, buffer, buffer_size);
}
