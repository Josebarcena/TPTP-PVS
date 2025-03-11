#include <pthread.h>
#include <limits.h> 

#define MAX_FILES 10000

pthread_mutex_t availability_mutex;
pthread_mutex_t queue_mutex;
pthread_t threads[NUM_THREADS];

char *taskQueue[MAX_FILES];
int taskCount = 0;

void AddTask(const char *filePath) {
    pthread_mutex_lock(&queue_mutex);
    strcpy(taskQueue[taskCount++].file_path, filePath);
    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);
}

char *GetTask() {
    pthread_mutex_lock(&queue_mutex);
    char task[PATH_MAX];
    strcpy(task,taskQueue[--taskCount])
    pthread_mutex_unlock(&queue_mutex);
    return task;
}

void CreateThreadPool() {
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, ProcessFile, NULL) != 0) {
            perror("Cannot create thread");
            exit(EXIT_FAILURE);
        }
    }
}

void FreeThread(int numThread){
    pthread_mutex_lock(&availability_mutex);
        if(thread_available[numThread] == 0){
            thread_available[numThread] = 1;
            pthread_mutex_unlock(&availability_mutex);
            return;
        }
        else{
            perror("ERROR: 487 ");
            pthread_mutex_unlock(&availability_mutex);
            return;
        }
}


int FindAvailableThread(int numThreads){
    pthread_mutex_lock(&availability_mutex);
    for(int i = 0; i < numThreads; i++){
        if(thread_available[i] == 1){
            thread_available[i] = 0;
            pthread_mutex_unlock(&availability_mutex);
            return i;
        }
    }
    pthread_mutex_unlock(&availability_mutex);
    return -1;
}

void FreeThreads(){
    for(int i = 0; i < NUM_THREADS; i++){
        FreeThread(i);
    }
}