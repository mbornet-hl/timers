#define _GNU_SOURCE

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void fct_alarm(int);

/* FCT_ALARM */
void fct_alarm(int signum)
{
     printf("%s : received signal %d\n",
            __func__, signum);

     if ((signal(SIGALRM, fct_alarm)) == SIG_ERR) {
          fprintf(stderr, "%s : signal returned an error !\n",
                  __func__);
          exit(1);
     }
}

/* MAIN */
int main(int argc, char *argv[])
{
     sighandler_t         _prev_sig;
     useconds_t           _time         = 0, _interval      = 0;
     int                  _retcode      = 0;

     if (argc != 3) {
          fprintf(stderr, "Usage: %s time_useconds interval_useconds\n", argv[0]);
          exit(1);
     }

     _time               = atol(argv[1]);
     _interval           = atol(argv[2]);

     printf("Initializing ...\n");

     if ((_prev_sig =  signal(SIGALRM, fct_alarm)) == SIG_ERR) {
          fprintf(stderr, "%s : signal returned an error !\n",
                  argv[0]);
          exit(1);
     }

     if ((_retcode = ualarm(_time, _interval)) < 0) {
          fprintf(stderr, "%s : ualarm returned %d !\n",
                  argv[0], _retcode);
          perror("ualarm");
          exit(1);
     }

     for (;;) {
          pause();
     }

     return 0;
}
