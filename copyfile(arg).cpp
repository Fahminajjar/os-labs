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
    char * to_path = argv[2];
    
    
    int readfile = open(from_path, O_RDONLY);
    
    char *buff[10];
    
    int writefile = open(to_path, O_WRONLY | O_CREAT);
    
    while(read(readfile, buff, 1)){
        write(writefile, buff, 1);
    }
    
    close(readfile);
    close(writefile);
    
    return 0;
    
}
