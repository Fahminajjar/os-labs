#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 50

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int pepsi = 0;
int counter = 0;

void * produce(){
    while(pepsi < MAX && counter == 0){
        pthread_mutex_lock(&mutex1);
        counter++;
        pthread_mutex_unlock(&mutex1);
        printf("Producer has produced 1\n");
        pepsi++;
    }
    pthread_exit(NULL);
    
    return NULL;
}

void * consume(){
    while(pepsi < MAX && counter > 0){
        pthread_mutex_lock(&mutex1);
        counter--;
        pthread_mutex_unlock(&mutex1);
        printf("Consumer has consume 1\n");
    }
    
    
    return NULL;
}

int main(){
    pthread_t producer, consumers[10];
    
    pthread_create(&producer, NULL, produce, NULL);
    
    for(int i = 0; i < 10; i++){
        pthread_create(&consumers[i], NULL, consume, NULL);
        sleep(2);
    }
    
    pthread_join(producer, NULL);
    for(int i = 0; i < 10; i++)
        pthread_join(consumers[i], NULL);
    
    return 0;
}
