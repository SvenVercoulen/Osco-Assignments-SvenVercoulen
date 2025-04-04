#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 25  
#define TOTAL_THREADS 1000  

pthread_mutex_t print_lock; 

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    pthread_mutex_lock(&print_lock);
    printf("Thread ID: %lu, Thread Number: %d\n", pthread_self(), thread_id);
    pthread_mutex_unlock(&print_lock);

    usleep(500000);

    pthread_exit(NULL); 
}

int main() {
    pthread_t threads[MAX_THREADS];
    int thread_ids[TOTAL_THREADS];

    pthread_mutex_init(&print_lock, NULL);  

    for (int i = 0; i < TOTAL_THREADS; i++) {
        thread_ids[i] = i + 1;

        if (pthread_create(&threads[i % MAX_THREADS], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }

        if (i % MAX_THREADS == MAX_THREADS - 1) {
            for (int j = 0; j < MAX_THREADS; j++) {
                pthread_join(threads[j], NULL);
            }
        }
    }

    for (int j = 0; j < TOTAL_THREADS % MAX_THREADS; j++) {
        pthread_join(threads[j], NULL);
    }

    pthread_mutex_destroy(&print_lock); 

    return 0;
} // "gcc threads.c -o threads.exe -pthread" for setup
 // "./threads.exe" to run