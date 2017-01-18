#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>

// Lab 6 Task 4

void parent_waits_child(){
    int status;
    
    int list = fork();
    if(list == 0){
        execlp("/bin/ls", "ls", "-l", "/etcA/", 0);
    }else{
        wait(&status);
    }
    
    int copy = fork();
    if(copy == 0){
        execlp("/bin/cp", "cp", "/etc/hosts", "/Users/fahminajjar/Desktop/hosts.txt", 0);
    }else{
        wait(&status);
    }
    
    int cat = fork();
    if(cat == 0){
        execlp("/bin/cat", "cat", "/Users/fahminajjar/Desktop/hosts.txt", 0);
    }else{
        wait(&status);
    }
    
}



// Task DIY(Do It Yourself)

void printFile(char * filepath){
    int fd = open(filepath , O_RDONLY);
    
    int buff[1];
    
    while(read(fd, buff, 1)){
        printf("%c", buff[0]);
    }
    printf("\n");
    
    close(fd);
}

void writeOnFile(char * filepath, char * buff, int size){
    int fd = open(filepath , O_WRONLY);
    lseek(fd, 0, SEEK_END);
    
    write(fd, buff, size);
    
    close(fd);
}



int main(int argc, char * argv[]){
    
    int retFork = fork();
    int status;
    char filepath[] = "/Users/fahminajjar/Desktop/shared.txt";
    
    if(retFork == 0){
        sleep(1);
        char buff[] = "Line from child\n";
        writeOnFile(filepath, buff, 16);
    }
    else{
        char buff[] = "Line from parent\n";
        sleep(2);
        writeOnFile(filepath, buff, 17);
        wait(&status);
        printFile(filepath);
    }
    
    return 0;
}
