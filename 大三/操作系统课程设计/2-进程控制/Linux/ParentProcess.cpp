#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char const* argv[])
{
	struct timeval childpStart, childpEnd;
	pid_t pid = fork();
	if (pid < 0) {
		printf("Failed to create child process");
		return 0;
	}
	else if (pid == 0) {
		if (execv(argv[1], NULL) < 0)
		{
			printf("Failed to open child process");
			return 0;
		}
	}
	else
	{
		gettimeofday(&childpStart, NULL);
		wait(0);
		gettimeofday(&childpEnd, NULL);
		printf("�ӽ��̿�ʼ��%ld��%ld����\n", childpStart.tv_sec, childpStart.tv_usec);
		printf("�ӽ��̽�����%ld��%ld����\n", childpEnd.tv_sec, childpEnd.tv_usec);
		float timecost = (childpEnd.tv_sec - childpStart.tv_sec) * 1000 + (childpEnd.tv_usec - childpStart.tv_usec) / 1000;
		printf("�ӽ���������%f����\n",timecost);
	}
	return 0;
}
