#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>

int exec_time[100], arrival_time[100], rt[100], n = 0;

void readProcesses(){
    char buff[1], arrival[10], exec[10];

    char filepath[] = "/Users/fahminajjar/Desktop/os/processes.txt";
    int fd = open(filepath, O_RDONLY);
    
    int processNo = 0;
    while(read(fd, buff, 1)){
        lseek(fd, -1, SEEK_CUR);
        
        int i = 0;
        while(read(fd, buff, 1)){
            if(buff[0] == ',')
                break;
            
            arrival[i] = buff[0];
            i++;
        }
        arrival[i] = '\0';
        arrival_time[processNo] = atoi(arrival);
        
        i = 0;
        while(read(fd, buff, 1)) {
            if(buff[0] == '\n')
                break;
            
            exec[i] = buff[0];
            i++;
        }
        exec[i] = '\0';
        exec_time[processNo] = atoi(exec);
        rt[processNo] = exec_time[processNo];
        
        n++;
        processNo++;
    }
    
    close(fd);
}


int main(int argc, char * argv[]){
    
    readProcesses();
    
    
    int slice, remain = n;
    printf("Enter Time Quantum:\t");
    scanf("%d",&slice);
    
    printf("\n----------------------------------------\n");
    printf("Process | Turnaround Time | Waiting Time\n");
    printf("----------------------------------------\n");

    int current_time = 0, flag = 0;
    int waiting_time_all = 0, turn_around_time_all = 0;
    
    int i = 0;
    while(remain != 0){
        if(rt[i] <= slice && rt[i] > 0){
            current_time += rt[i];
            rt[i] = 0;
            flag = 1;
        }else if(rt[i] > 0){
            current_time += slice;
            rt[i] -= slice;
        }
        
        if(rt[i] == 0 && flag == 1){
            remain--;
            printf("P[%d]\t\t| %d\t\t\t\t| %d\t\t\t|\n", i+1, current_time - arrival_time[i], current_time - arrival_time[i] - exec_time[i]);
            waiting_time_all += current_time - arrival_time[i] - exec_time[i];
            turn_around_time_all += current_time - arrival_time[i];
            flag = 0;
        }
        
        if(i == n-1)
            i = 0;
        else if(arrival_time[i+1] <= current_time)
            i++;
        else
            i = 0;
    }
    
    printf("----------------------------------------\n");
    printf("Average Waiting Time= %.2f\n", waiting_time_all * 1.0/n);
    printf("Average Turnaround Time = %.2f\n", turn_around_time_all * 1.0/n);
    printf("----------------------------------------\n\n");
    
    return 0;
}
