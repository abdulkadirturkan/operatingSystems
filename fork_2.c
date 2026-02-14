#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(char *program, char** arg_list){
    pid_t cocuk_pid;
    
    cocuk_pid = fork();
    if(cocuk_pid != 0){
        return cocuk_pid;
    } else{
        execvp(program, arg_list);
        //eğer hata oluşmuşsa alt kısım çalışır
        fprintf(stderr, "execvp de hata oluştu\n");
        abort();
    }
}
int main(){
    char * arg_list[] = {"ls", "-1", "/", NULL};
    spawn("ls", arg_list);
    printf("ls", arg_list);
    return 0;
}
