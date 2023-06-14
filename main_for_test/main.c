#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"
#include <string.h>

# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define RESET "\033[0m"

//possible test : one_line_dune.txt / starwars.txt / seneca.txt / long_HP.txt

int main(void)
{
	int fd = open("./test/starwars.txt", O_RDONLY);
	char *line;
	int i = 0;
	while (i < 30)
	{		
		line = get_next_line(fd);
		printf("LINE IS : %s", line);
		free(line);
		i++;
	}
	return (0);
}
