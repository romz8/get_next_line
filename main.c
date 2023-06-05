#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define RESET "\033[0m"

int main(void)
{
	int fd = open("./test/42_with_nl.txt", O_RDONLY);
	char *line;
	int i = 0;
	while (i < 6)
	{		
		line = get_next_line(fd);
		i++;
		printf("LINE IS : %s", line);
		free(line);
	}
	return (0);
}
