#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "queue.h"

int queue_msg_handler(void *buffer, size_t buffer_size) {
  (void)buffer_size;

  assert(buffer != NULL);
  size_t number = *((size_t *)buffer);
  fprintf(stdout, "[HANDLER]: GOT %lu\n", number);
  if (number == 1122) {
    return 1;
  }

  return 0;
}

void *thread_send(void *args) {
  queue_t *queue = (queue_t *)args;
  assert(queue != NULL);

  for (size_t i = 1100; i <= 1122; ++i) {
    const size_t number = i;
    fprintf(stdout, "[1] number = %zu\n", number);
    queue_enqueue(queue, (void *)&number, sizeof(size_t));
  }

  sleep(1);

  return NULL;
}
void *thread_read(void *args) {
  queue_t *queue = (queue_t *)args;
  assert(queue != NULL);

  queue_dequeue(queue, queue_msg_handler);

  sleep(1);

  return NULL;
}

int main(void) {
  queue_t queue;

  queue.msg = NULL;

  queue.lock = calloc(1, sizeof(pthread_mutex_t));
  assert(queue.lock != NULL);
  pthread_mutex_init(queue.lock, NULL);

  queue.ready = calloc(1, sizeof(pthread_cond_t));
  assert(queue.ready != NULL);
  pthread_cond_init(queue.ready, NULL);

  pthread_t send, read;
  pthread_create(&send, NULL, thread_send, (void *)&queue);
  pthread_create(&read, NULL, thread_read, (void *)&queue);

  pthread_join(send, NULL);
  pthread_join(read, NULL);

  /* release queue */
  pthread_mutex_destroy(queue.lock);
  pthread_cond_destroy(queue.ready);
  free(queue.lock);
  free(queue.ready);

  return 0;
}
