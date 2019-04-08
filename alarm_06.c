#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void fct_alarm(int);
void run_process(void);
int  child_pid                = 0;

/* FCT_ALARM */
void fct_alarm(int signum)
{
     printf("%s : received signal %d\n",
            __func__, signum);
     printf("Child process (PID %d) not responding : killing it !\n",
            child_pid);
     if (kill(child_pid, SIGTERM) < 0) {
          fprintf(stderr, "Cannot kill process !%d\n",
                  child_pid);
     }
     else {
          printf("Termination signal successfully sent to child process\n");
     }
}

void run_process()
{
     int             _status;

     switch ((child_pid = fork())) {

     case  0:
          /* Child process */
          execl("/bin/sleep", "sleep", "60", NULL);
          fprintf(stderr, "Cannot execute \"sleep\" !\n");
          exit(1);
          break;

     case -1:
          /* Fork error */
          fprintf(stderr, "Cannot fork !\n");
          perror("fork");
          exit(1);
          break;

     default:
          /* Parent process */
          wait(&_status);
		break;
     }
}

/* MAIN */
int main()
{
     printf("Initializing ...\n");
     (void) signal(SIGALRM, fct_alarm);
     (void) alarm(10);

     run_process();

     return 0;
}
