#include <pthread.h>
#include <stdio.h>

void * ThreadFunction(void * i){
    int tno = (int)i;
    printf("I am thread: %d\n", tno);
    return NULL;
}


void task2(){
    int iter;
    printf("Testing Multithreading with pthreads.\n");
    pthread_t threads[3];
    
    for(iter = 0; iter < 3; iter++)
        pthread_create(&threads[iter], NULL, ThreadFunction, (void *) iter);
    
    for(iter = 0; iter < 3; iter++)
        pthread_join(threads[iter], NULL);

}

//-------------------//

float account_balance = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void * add_balance(void * amount){
    pthread_mutex_lock(&mutex1);
    account_balance += *(float *) amount;
    pthread_mutex_unlock(&mutex1);
    return NULL;
}


void task4(){
    pthread_t threads[2];
    
    float x = 5, y = 10;
    
    pthread_create(&threads[0], NULL, add_balance, &x);
    printf("%f\n", account_balance);
    
    
    pthread_create(&threads[0], NULL, add_balance, &y);
    printf("%f\n", account_balance);
    
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
}

int main(){
    
    task4();
    printf("%f\n", account_balance);
    
    return 0;
}
