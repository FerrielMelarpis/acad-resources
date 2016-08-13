/*
 * CS460: Operating Systems
 * Jim Plank / Rich Wolski
 * dphil_6.c -- Dining philosophers solution #6 -- a starvation-free
   solution using a global queue.
 */


#include <stdio.h>
#include <pthread.h>
#include "dphil.h"
#include "dllist.h"
#include "jval.h"

#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct {
  pthread_mutex_t *mon;
  pthread_cond_t **cv;
  int *state;
  Dllist q;
  int phil_count;
} Phil;


/* It is assumed that you have locked pp->mon */

test_queue(Phil *pp)
{
  int id;
  int phil_count;
  
  phil_count = pp->phil_count;

  if (!dll_empty(pp->q)) {
    id = pp->q->flink->val.i;
    if (pp->state[(id+1)%phil_count] != EATING && 
		    pp->state[(id+(phil_count-1))%phil_count] != EATING) {
      pthread_cond_signal(pp->cv[id]);
    }
  }
}
    
/* If the queue is empty and your neighbors are not eating, then
   go ahead and eat.  Otherwise, put yourself on the queue and
   wait */

void pickup(Phil_struct *ps)
{
  Phil *pp;
  int phil_count;

  pp = (Phil *) ps->v;
  phil_count = pp->phil_count;
  
  pthread_mutex_lock(pp->mon);
  if (dll_empty(pp->q) && 
		  pp->state[(ps->id+(phil_count-1))%phil_count] != EATING &&
                     pp->state[(ps->id+1)%phil_count] != EATING) {
    pp->state[ps->id] = EATING;
  } else {
    dll_append(pp->q, new_jval_i(ps->id));
    pthread_cond_wait(pp->cv[ps->id], pp->mon);
    dll_delete_node(pp->q->flink);
    pp->state[ps->id] = EATING;
    test_queue(pp);
  }
  pthread_mutex_unlock(pp->mon);
}
     
/* Set state to thinking and then signal the first person on the
   queue if they can eat */

void putdown(Phil_struct *ps)
{
  Phil *pp;

  pp = (Phil *) ps->v;

  pthread_mutex_lock(pp->mon);
  pp->state[ps->id] = THINKING;
  test_queue(pp);
  pthread_mutex_unlock(pp->mon);
}

void *initialize_v(int phil_count)
{
  Phil *pp;
  int i;

  pp = (Phil *) malloc(sizeof(Phil));
  pp->phil_count = phil_count;
  pp->mon = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pp->cv = (pthread_cond_t **) malloc(sizeof(pthread_cond_t *)*phil_count);
  if (pp->cv == NULL) { perror("malloc"); exit(1); }
  pp->state = (int *) malloc(sizeof(int)*phil_count);
  if (pp->state == NULL) { perror("malloc"); exit(1); }
  pthread_mutex_init(pp->mon, NULL);
  pp->q = new_dllist();
  for (i = 0; i < phil_count; i++) {
    pp->cv[i] = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    pthread_cond_init(pp->cv[i], NULL);
    pp->state[i] = THINKING;
  }

  return (void *) pp;
}

