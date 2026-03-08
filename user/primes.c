#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc, char** argv){
  
	int cur_prime = 2;
	int PRIME_MAX = 35;

  int p[2];
  int write_fd = -1;
  int read_fd = -1;

  pipe(p);

  int pid = fork();
 
  if (pid > 0){
    close(p[0]);
    write_fd = p[1];

		for (int i = 2; i <= PRIME_MAX; i++){
			write(write_fd, &i, sizeof(i));		
		}
    close(write_fd);

		wait(0);

  } else {
		// This is the thread case

    close(p[1]);
    read_fd = p[0];
    printf("prime %d\n", cur_prime);

		while (1) {
			int cur_val;
			int res = read(read_fd, &cur_val, sizeof(cur_val));
      if (res == 0){
        if (write_fd != -1){
          close(write_fd);
          wait(0);
        }
        exit(0);
      }
		
			if (cur_val % cur_prime != 0) {
				if (write_fd != -1) {
					write(write_fd, &cur_val, sizeof(cur_val));		
				} else {
					// Interesting case: new thread time
          pipe(p);
					pid = fork();
					
					if (pid != 0) {
						// Parent
            close(p[0]);
            write_fd = p[1];
					} else {
            close(p[1]);
            read_fd = p[0];
						cur_prime = cur_val;
						printf("prime %d\n", cur_prime);
					}
				}
			}


		}
	}

  exit(0);

}
