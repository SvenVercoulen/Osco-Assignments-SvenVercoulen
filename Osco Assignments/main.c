#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    // Print the thread ID using pthread_self()
    printf("Thread ID: %lu\n", pthread_self());
    printf("Thread %d: I will kill myself now.\n", thread_id);

    // Simulate some work
    usleep(500000); // Sleep for 0.5 seconds

    // Terminate the thread
    pthread_exit(NULL);  // Thread kills itself here
}

int main() {
    pthread_t threads[1000];
    int thread_ids[1000];

    // Create 1000 threads
    for (int i = 0; i < 1000; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }

    }

    // Join all threads
    for (int i = 0; i < 1000; i++) {
        pthread_join(threads[i], NULL);
        printf("Main thread: Thread %d has killed itself.\n", i + 1);
    }

    return 0;
}