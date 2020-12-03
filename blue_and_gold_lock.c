#include "blue_and_gold_lock.h"

void mc_lock_init (mc_lock_t * mc_lock) {
    mc_lock->held = FALSE;
    mc_lock->blue_requests = 0;
    pthread_mutex_init(&mc_lock->lock, NULL);
    pthread_cond_init(&mc_lock->cond_wait, NULL);
}

void mc_lock_acquire(mc_lock_t * mc_lock, int color) {
    pthread_mutex_lock(&mc_lock->lock);
    if(color) {
        mc_lock->blue_requests++;
        while(mc_lock->held) {
            pthread_cond_wait(&mc_lock->cond_wait, &mc_lock->lock);
        }
        mc_lock->blue_requests--;
    } else {
        // gold should wait if there are blue requests remaining 
        // or if the lock is held by another thread
        while(mc_lock->blue_requests>0 || mc_lock->held) {  
            pthread_cond_wait(&mc_lock->cond_wait, &mc_lock->lock);
        }
    }
    mc_lock->held = TRUE;
    pthread_mutex_unlock(&mc_lock->lock);
}

void mc_lock_release(mc_lock_t * mc_lock) {
    pthread_mutex_lock(&mc_lock->lock);
    mc_lock->held = FALSE;
    pthread_cond_broadcast(&mc_lock->cond_wait);
    // broadcast will wake up blue as well as gold
    // but gold will not be able to enter critical section
    // unless blue_requests are 0

    pthread_mutex_unlock(&mc_lock->lock);
}
