#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

int main(){
    
    char filepath[100];
    char keyword;
    
    printf("Please enter filepath: ");
    scanf("%s", filepath);
    
    printf("Please enter keyword: ");
    scanf("%s", &keyword);
    
    int file = open(filepath, O_RDONLY);
    
    char * buff = new char[1];
    int counter = 0;
    
    while(read(file, buff, 1)){
        if(buff[0] == keyword){
            printf("Found at index %d\n", counter);
            return 0;
        }
        counter++;
    }
    
    printf("Not found! %d\n", -1);
    return 0;
    
}
