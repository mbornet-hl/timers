#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void fct_alarm(int);

void fct_alarm(int signum)
{
     (void) signal(SIGALRM, fct_alarm);
     (void) alarm(1);

     printf("%s : received signal %d\n",
	       __func__, signum);
}


int main(int argc, char *argv[])
{
     unsigned int              _max_loop, _i;

     if (argc != 2) {
          fprintf(stderr, "Usage: %s max_loop\n", argv[0]);
          exit(1);
     }

	printf("Initializing ...\n");
     _max_loop                          = atol(argv[1]);

    (void) signal(SIGALRM, fct_alarm);
    (void) alarm(2);

     for (_i = 0; _i < _max_loop; _i++) {
          (void) pause();
     }

	return 0;
}
