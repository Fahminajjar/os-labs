#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

int main(int argc, char * argv[]){
    
    if(argc != 3){
        printf("error!");
        return 0;
    }
    
    char * from_path = argv[1];
    char * str = argv[2];
    
    int strc = 0;
    char c = str[0];
    while(c != '\0'){
        strc++;
        c = str[strc];
    }
    
    int file = open(from_path, O_RDWR);
    
    char buff[1];
    
    int i = 0, wordSz = 0;
    while(read(file, buff, 1)){
        if(wordSz >= strc){
            wordSz = 0;
            break;
        }
        if(buff[0] == str[wordSz]){
            wordSz++;
        }else{
            wordSz = 0;
        }
        i++;
    }
    int index = i - strc;
    printf("%d\n", index);
    
    lseek(file, 0, SEEK_SET);

    i = 1;
    while(i <= index){
        read(file, buff, 1);
        i++;
    }
    
    for(i = 0; i < strc; i++){
        buff[0] = (char)str[i] - 32;
        write(file, buff, 1);
    }
    
    close(file);
    
    return 0;
    
}
