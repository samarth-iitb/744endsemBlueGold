#include<pthread.h>

#define TRUE 1
#define FALSE 0
#define BLUE 1
#define GOLD 0

typedef struct mc_lock {
    pthread_mutex_t lock;
    int held;
    int blue_requests;
    pthread_cond_t cond_wait;
}mc_lock_t;

void mc_lock_init (mc_lock_t * mc_lock);

void mc_lock_acquire(mc_lock_t * mc_lock, int color);

void mc_lock_release(mc_lock_t * mc_lock);

mc_lock_t bg_lock;
