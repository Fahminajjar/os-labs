#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

int main(){
    
    char filepath[100];
    
    printf("Please enter filepath: ");
    scanf("%s", filepath);
    
    int file = open(filepath, O_RDONLY);
    
    int lines = 0, chars = 0, words = 0;
    char * buff = new char[1];
    
    while(read(file, buff, 1)){
        chars++;
        if(buff[0] == '\n'){
            lines++;
            words++;
        }
        if(buff[0] == ' ')
            words++;
    }
    
    printf("Lines: %d | charachters: %d | Words: %d\n", lines, chars, words);
    return 0;
    
}
