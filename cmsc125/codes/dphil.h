#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;                /* The philosopher's id: 0 to 5 */
  long t0;               /* The time when the program started */
  long ms;               /* The maximum time that philosopher sleeps/eats */
  void *v;               /* The void * that you define */
  int *blocktime;        /* Total time that a philosopher is blocked */
  int *blockstarting;    /* If a philsopher is currently blocked, the time that he
                            started blocking */
  int phil_count;
  pthread_mutex_t *blockmon;   /* monitor for blocktime */             
} Phil_struct;

extern void *initialize_v(int phil_count);
extern void pickup(Phil_struct *);
extern void putdown(Phil_struct *);

