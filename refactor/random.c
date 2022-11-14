#include <stdio.h>
#include <sys/time.h>

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main()
{
	size_t  time;

	time = get_time() % 6;
	printf("member : gyeokim jnam jujeon junkpark mher seunghye\n\n::: Result ::: \n");
	if (time == 0)
		printf("The Driver is gyeokim\n");
	else if (time == 1)
		printf("The Driver is jnam\n");
	else if (time == 2)
		printf("The Driver is jujeon\n");
	else if (time == 3)
		printf("The Driver is junkpark\n");
	else if (time == 4)
		printf("The Driver is mher\n");
	else if (time == 5)
		printf("The Driver is seunghye\n");
	return (0);
}
