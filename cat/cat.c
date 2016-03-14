#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char a[4096];
	while (1)
	{ 
		int c = read(STDIN_FILENO, a, 4096);
		if (c == 0)
			{
				return 0;
			}
		if (c < 0)
			{
				printf("Wrong read");
				return -1;		
			}
		int b = write(STDOUT_FILENO, a, c);
		if (b < 0)
			{
                                printf("Wrong write");
                                return -2;
                        }
	}
	return 0;
}
