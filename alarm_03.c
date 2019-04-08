#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void fct_alarm(int);

/* FCT_ALARM */
void fct_alarm(int signum)
{
     (void) signal(SIGALRM, fct_alarm);
     (void) alarm(1);

     printf("%s : received signal %d\n",
	       __func__, signum);
}

/* MAIN */
int main()
{
	printf("Initializing ...\n");
	(void) signal(SIGALRM, fct_alarm);
	(void) alarm(2);

	while (1)
	{
		(void) pause();
	}

	return 0;
}
