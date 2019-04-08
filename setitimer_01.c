#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void                display_timeval(char *, struct timeval *);
void                display_message(int);

void display_timeval(char *label, struct timeval *ref_timeval)
{
     printf("%-20s : %10ld.%06ld\n",
            label,
            ref_timeval->tv_sec,
            ref_timeval->tv_usec);
}

void display_message(int signum)
{
     printf("%s() : received signal %d\n", __func__, signum);
}

int main(int argc, char *argv[])
{
     struct itimerval          _old_value,
                               _new_value;
     unsigned int              _max_loop, _i;

     if (argc != 2) {
          fprintf(stderr, "Usage: %s max_loop\n", argv[0]);
          exit(1);
     }

     _max_loop                          = atol(argv[1]);

    (void) signal(SIGALRM, display_message);

     if (getitimer(ITIMER_REAL, &_old_value) < 0) {
          fprintf(stderr, "%s: getitimer() error !\n", argv[0]);
          perror("getitimer");
          exit(1);
     }

     display_timeval("Old interval", &_old_value.it_interval);
     display_timeval("Old value",    &_old_value.it_value);
     putchar('\n');

     _new_value.it_value.tv_sec         = 2;
     _new_value.it_value.tv_usec        = 500000;

     _new_value.it_interval.tv_sec      = 1;
     _new_value.it_interval.tv_usec     = 250000;

     display_timeval("New interval", &_new_value.it_interval);
     display_timeval("New value",    &_new_value.it_value);
     putchar('\n');

     if (setitimer(ITIMER_REAL, &_new_value, &_old_value) < 0) {
          fprintf(stderr, "%s: setitimer() error !\n", argv[0]);
          perror("setitimer");
          exit(1);
     }

     for (_i = 0; _i < _max_loop; _i++) {
          pause();
     }

     if (getitimer(ITIMER_REAL, &_old_value) < 0) {
          fprintf(stderr, "%s: getitimer() error !\n", argv[0]);
          perror("getitimer");
          exit(1);
     }

     putchar('\n');
     display_timeval("New interval", &_old_value.it_interval);
     display_timeval("New value",    &_old_value.it_value);
     putchar('\n');

     return 0;
}
