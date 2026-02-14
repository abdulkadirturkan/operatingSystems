#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int p1, p2;
    
    p1 = fork();
    p2 = fork();
    printf("%d\n", p1 + p2);
    return 0;
}
