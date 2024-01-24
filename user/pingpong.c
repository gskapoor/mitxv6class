#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc, char** argv){

    int p[2];
    int buf[1];
    pipe(p);

    int pid = fork();
    
    if (pid == 0){
        read(p[0], buf, sizeof(buf) );
        printf("%d: received ping\n", buf[0]);
        buf[0] = pid;
        write(p[1], buf, sizeof(buf));
        close(p[1]);
        close(p[0]);
        exit(0);

    } else {
        //fprintf(p[1], "BRUH %d", pid);
        buf[0] = pid;
        write(p[1], buf, sizeof(buf));
        wait(0);
        printf("%d: received pong\n", getpid());
        close(p[1]);
    }

    exit(0);
}