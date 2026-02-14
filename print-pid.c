#include <stdio.h>
#include <unistd.h>

int main(){
  printf("süreç numarası %d\n", (int)getpid());
  printf("Ana sürecin süreç numarası :%d\n ", (int)getppid());
}
