#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "blue_and_gold_lock.h"

mc_lock_t bg_lock;

void *blue_thread(void * args) {
    mc_lock_acquire(&bg_lock, BLUE);
    printf("Blue acquired lock\n");
    sleep(2);
    mc_lock_release(&bg_lock);
}

void *gold_thread(void * args) {
    mc_lock_acquire(&bg_lock, GOLD);
    printf("Gold acquired lock\n");
    sleep(2);
    mc_lock_release(&bg_lock);
}

void main(int argc, int argv) {
    int num_of_threads = 10;
    int blue_threads = 5;

    mc_lock_init(&bg_lock);

    pthread_t *tinfo = malloc(num_of_threads * sizeof(*tinfo));
    if (tinfo == NULL) {
        perror("malloc");
	    exit(1);
    }
    for(int i=0; i<num_of_threads; i++) {
	    if(i<blue_threads)
            pthread_create( &tinfo[i], NULL, blue_thread, NULL );
	    else
            pthread_create( &tinfo[i], NULL, gold_thread, NULL ); 
    }

    for(int i=0; i<num_of_threads; i++) {
        pthread_join(tinfo[i], NULL);
    }
    free(tinfo);

}

