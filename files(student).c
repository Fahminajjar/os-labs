#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>

void new_std(){
    
    int fd1, i;
    char stdno[11];
    char mark[4];
    
    fd1 = open("/Users/fahminajjar/Desktop/students.txt", O_WRONLY);
    lseek(fd1, 0, SEEK_END);
    
    printf("Please enter student number: ");
    scanf("%s", stdno);
    
    write(fd1, "\n", 1);
    write(fd1, stdno, 10);
    write(fd1, ":", 1);
    
    i = 1;
    while(i <= 5){
        printf("Please enter mark no. %d: ", i);
        scanf("%s", mark);
        write(fd1, mark, 3);
        if(i != 5)
            write(fd1, ";", 1);
        i++;
    }
    
    close(fd1);
    
}

void read_std_old(){
    
    int fd1;
    fd1 = open("/Users/fahminajjar/Desktop/students.txt", O_RDONLY);
    
    char stdno[11];
    char buff[2];
    char mark[4];
    
    while(read(fd1, stdno, 10)){
        printf("%s\n", stdno);
        read(fd1, buff, 1);
        int i = 1;
        while(i <= 5){
            //reads mark
            read(fd1, mark, 3);
            printf("%s\n", mark);
            
            //reads semicolon
            if(i == 5) break;
            read(fd1, buff, 1);
            i++;
        }
        read(fd1, buff, 1);
        
    }
    
    close(fd1);
    
}


void read_std_new(){
    int fd1, x;
    fd1 = open("/Users/fahminajjar/Desktop/students.txt", O_RDONLY);
    
    char stdno[11];
    char buff[1];
    char mark[4];
    
    while(read(fd1, stdno, 10)){
        printf("%s\n", stdno);
        
        //reads colon
        read(fd1, buff, 1);
        
        x = 0;
        while(read(fd1, buff, 1)){
            if(buff[0] == '\n'){
                mark[x] = '\0';
                printf("%s\n", mark);
                break;
            }else if(buff[0] == ';'){
                mark[x] = '\0';
                printf("%s\n", mark);
                x = 0;
            }else{
                mark[x++] = buff[0];
            }
        }
        printf("\n");
    }
    
}


void search_std(){
    
    int fd1, studentid, student, x;
    char stdno[11], buff[1], mark[4];
    
    fd1 = open("/Users/fahminajjar/Desktop/students.txt", O_RDONLY);
    
    printf("Please enter student number: ");
    scanf("%s", stdno);
    
    studentid = atoi(stdno);
    
    while(read(fd1, stdno, 10)){
        student = atoi(stdno);
        if(student == studentid){
            //read colon
            read(fd1, buff, 1);
            
            printf("%d\n", student);
            
            x = 0;
            while(read(fd1, buff, 1)){
                if(buff[0] == '\n'){
                    mark[x] = '\0';
                    printf("%s\n", mark);
                    return;
                }else if(buff[0] == ';'){
                    mark[x] = '\0';
                    printf("%s\n", mark);
                    x = 0;
                }else{
                    mark[x++] = buff[0];
                }
            }
        }else{
            while(read(fd1, buff, 1)){
                if(buff[0] == '\n')
                    break;
            }
        }
        
    }
    
    close(fd1);
    
}

int main()
{
    
    read_std_new();
    printf("\n");
    search_std();
    
    
    return 0;
}
