#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t cocuk_pid;
    
    printf("Ana sürecin pid = %d\n", (int)getpid());
    
    cocuk_pid = fork(); if(cocuk_pid != 0){
        printf("burası ana süreçtir, surec id pid = %d\n", (int)getpid());
        printf("çocuk sürecin idsi pid = %d\n", (int)cocuk_pid);
    } else{
        printf("burası çocuk süreçtir, pid = %d\n", (int)getpid());
    }
    
    return 0;
}
