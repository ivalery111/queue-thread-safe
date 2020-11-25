#ifndef QUEUE_UTILS_H
#define QUEUE_UTILS_H

#include <stdlib.h>

static inline void safe_free(void *ptr) { _safe_free((void **)&(ptr)); }

static inline void _safe_free(void **ptr) {
  if (ptr != NULL && *ptr != NULL) {
    free(*ptr);
    *ptr = NULL;
  }
}

#endif
