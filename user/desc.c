#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main (int argc, char** argv) {

  int p[2];
  int buf[1];
  pipe(p);

  int pid = fork();

begin_child:
  if (pid == 0) {
    pid = fork();
    if (pid == 0){
      goto begin_child;
    }

    read(p[0], buf, sizeof(buf));
    
    printf("%d\n", buf[0]);
    if (buf[0] == 0){
      printf("GOT ALL THE WAY HERE\n");
      exit(0);
    }
    buf[0] -= 1;
    write(p[1], buf, sizeof(buf));
    wait(0);
    exit(0);

  } else{
    buf[0] = 10;
    write(p[1], buf, sizeof(buf));
    wait(0);
  }

  exit(0);

}



