#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc, char** argv){
  
  int p[2]; 
  int buf[1];

  pipe(p);

  int pid = fork();
  
child:
  if (pid == 0){

    if (0 == read(p[0], buf, sizeof(buf))){
      exit(0);
    }

    int base = buf[0];

    printf("primes %d\n", base);
    pid = fork();
    if (pid == 0){
      goto child;
    }

    while ( read(p[0], buf, sizeof(buf))){
      if (buf[0] % base != 0){
        write(p[1], buf, sizeof(buf));
      }
    }
      write(p[1], buf, sizeof(buf));
      wait(0);
      close(p[1]);
      exit(0);
  } else {
    printf("primes %d\n", 2);
    for (int i = 3; i <= 35; i++){
      if (i % 2 != 0) {
        buf[0] = i;
        write(p[1], buf, sizeof(buf));
      }
    }
    wait(0);
    close(p[1]);
  }

  exit(0);

}
