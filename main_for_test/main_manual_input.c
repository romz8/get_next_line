#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"
#include <string.h>

# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define RESET "\033[0m"

int main(int argc, char *argv[])
{
	if (argc < 0)
        return (1);
    int fd = open(argv[1], O_RDONLY);
	char *line;
	int i = 0;
	while (i < 5)
	{		
		line = get_next_line(fd);
		printf("LINE IS : %s", line);
		free(line);
		i++;
	}
	return (0);
}