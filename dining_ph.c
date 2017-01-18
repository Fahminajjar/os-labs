#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int food=100;
pthread_mutex_t chopstick[5];
pthread_mutex_t foodlock;



void get_chopstick(int phil,int c,char hand)
{
    pthread_mutex_lock(&chopstick[c]);
    printf("Philosopher %d: got %c chopstick %d\n", phil, hand, c);
    
}


void leave_chopsticks(int phil ,int c ,char hand)
{
    pthread_mutex_unlock(&chopstick[c]);
    
    printf("Philosopher %d: left %c chopstick %d\n", phil, hand, c);
    
}

void * eat(void* k){
    int n =(int) k;
    
    while(food >0){
        get_chopstick(n,n,'R');
        if(n != 4)
            get_chopstick(n,n+1,'L');
        else
            get_chopstick(n,0,'L');
        
        
        pthread_mutex_lock(&foodlock);
        
        food-=10;
        
        printf("phil number %d is now eating \n", n);
        
        pthread_mutex_unlock (&foodlock);
        
        printf("phil number %d has finished eating \n", n);
        
        
        
        leave_chopsticks(n,n,'R');
        if(n != 4)
            leave_chopsticks(n,n+1,'L');
        else
            leave_chopsticks(n,0,'L');
        
    }
    printf("food has finished !\n");
    
    return NULL;
}

int main(){
    
    pthread_t thr[5];
    
    for(int i=0;i<5;i++){
        pthread_create(&thr[i], NULL, eat, (void *)i);
    }
    
    for( int j=0; j<5; j++)
        pthread_join(thr[j], NULL);
    
    
    return 0;}
