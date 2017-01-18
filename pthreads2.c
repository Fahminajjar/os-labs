#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void * printHelloThread(void * num){
    int threadNum = (int)num;
    printf("Hello I am thread number %d!\n", threadNum);
    return NULL;
}


void * printThreadId(){
    int id = pthread_self();
    printf("Thread id is %d\n", id);
    return NULL;
}


void * printMainThreadId(void * num){
    int id = (int)num;
    printf("Main thread id is %d\n", id);
    return NULL;
}


void task1(){
    int retVal, l;
    pthread_t thr[10];
    
    int mainId = pthread_self();
    for(int i = 0; i < 10; i++){
        retVal = pthread_create(&thr[i], NULL, printMainThreadId, (void*)mainId);
        if(retVal != 0){
            printf("Error: return code from pthread_create is %d\n", retVal);
            exit(1);
        }
        printf("New thread number %d created\n", i);
        pthread_exit(NULL);
    }

}



// task 3 -----------------------------



void * printWord(char * word){
//    char w[] = (char*)word;
    printf("Hello %s!\n", (char*)word);
    return NULL;
}

void task3(char * argv[]){
    pthread_t threads[3];
    
    for(int i = 1; i <= 3; i++){
        pthread_create(&threads[i-1], NULL, printWord, (void*)argv[i]);
        pthread_join(threads[i-1], NULL);
    }
}




// task 6 ------------------------

struct threadData{
    int threadId;
    int sum;
    char *message;
};


void * printData(struct threadData * data){
    printf("%d\n", data->threadId);
    printf("%d\n", data->sum);
    printf("%s\n", data->message);

    return NULL;
}


void task6(){
    struct threadData arrayOfThreadData[3];

    pthread_t threads[3];
    for(int i = 0; i < 3; i++){
        arrayOfThreadData[i].threadId = 1;
        arrayOfThreadData[i].sum = 10;
        arrayOfThreadData[i].message = "Fahmi";
//        printf("%d\n", arrayOfThreadData[i].threadId);

        pthread_create(&threads[i], NULL, printData, &arrayOfThreadData[i]);
    }
    
}




// task 7 -----------------------------

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 200;


void * modifyFile(){
    pthread_mutex_lock(&mutex1);
    
    int fd = open("/Users/fahminajjar/Desktop/os/data.txt", O_WRONLY);
    lseek(fd, 0, SEEK_END);
    
    counter++;
    char buff[] = "10";
    
    write(fd, buff, 2);
    
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void task7(){
    int ret1, ret2;
    pthread_t thread1, thread2;

    
    if((ret1 = pthread_create(&thread1, NULL, modifyFile, NULL)))
        printf("Sorry! Thread creation faild: %d\n", ret1);
    
    if((ret2 = pthread_create(&thread1, NULL, modifyFile, NULL)))
        printf("Sorry! Thread creation faild: %d\n", ret1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

}


int main(int argc, char * argv[]){

    task7();
    
    return 0;
}
