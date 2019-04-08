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
}

/* MAIN */
int main()
{
	int		 _retcode;

	printf("Initializing ...\n");
	(void) signal(SIGALRM, fct_alarm);
	(void) alarm(2);

	_retcode	= sleep(10);
	printf("Return code of sleep is %d\n", _retcode);
	perror("sleep");

	return 0;
}
