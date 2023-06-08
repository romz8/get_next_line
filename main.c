#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <string.h>

# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define RESET "\033[0m"


int main(void)
{
	int fd = open("./test/long_HP.txt", O_RDONLY);
	char *line;
	int i = 0;
	while (i < 20)
	{		
		line = get_next_line(fd);
		printf("LINE IS : %s", line);
		free(line);
		i++;
	}
	return (0);
}
