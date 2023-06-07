#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <string.h>

# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define RESET "\033[0m"


int main(void)
{
	int fd = open("./test/42_with_nl.txt", O_RDONLY);
	char *line;
	int i = 0;
	while (i < 4)
	{		
		line = get_next_line(fd);
		printf("LINE IS : %s", line);
		if ( i == 1)
		{
			char *c = "1";
			if (strcmp (line, c))
			{
				printf(RED"NOT OK\n"RESET);
				printf("%s", line);
				printf("%s", c);
			}
		}
		else if (i == 2)
		{
			if (line != NULL)
				printf(RED"NOT OK\n"RESET);
		free(line);
		}
		i++;
	}
	return (0);
}
