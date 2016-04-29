#include "gui.h"
#include "gui_defs.h"
#include "x.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

gui *gui_init(void)
{
  struct gui *ret;

  x_init_threading();

  ret = calloc(1, sizeof(struct gui));
  if (ret == NULL) OOM;

  ret->lock = malloc(sizeof(pthread_mutex_t));
  if (ret->lock == NULL) OOM;
  if (pthread_mutex_init(ret->lock, NULL))
    ERR("mutex initialization failed\n");

  if (pipe(ret->event_pipe))
    ERR("%s\n", strerror(errno));

  ret->x = x_open();

  return ret;
}
