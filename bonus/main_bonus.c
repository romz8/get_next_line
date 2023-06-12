#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"
#include <string.h>

# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define RESET "\033[0m"
#define BBLU "\e[1;34m"


int main(void)
{
	int fd = open("../test/long_HP.txt", O_RDONLY);
	int fd2 = open("../test/starwars.txt", O_RDONLY);
	char *line;
	int i = 0;
	printf(YELLOW"\n\n TESTING TEXT IN SEQUENCE \n\n"RESET);
	printf(RED"\n\n Harry Potter \n\n"RESET);
	i = 0;
	while (i < 30)
	{		
		line = get_next_line(fd);
		printf("LINE IS : %s", line);
		free(line);
		i++;
	}
	printf(RED"\n\n STAR WARS \n\n"RESET);
	i = 0;
	while (i < 30)
	{		
		line = get_next_line(fd2);
		printf("LINE IS : %s", line);
		free(line);
		i++;
	}
	close (fd);
	close (fd2);
	printf(YELLOW"\n\n NOW TESTING ONE LEACH FOR EACH AND READIG AT THE SAME TIME \n\n"RESET);
	fd = open("../test/long_HP.txt", O_RDONLY);
	fd2 = open("../test/starwars.txt", O_RDONLY);
	i = 0;
	printf("fd HP is : %i and fd SW is : %i \n\n", fd, fd2);
	while (i < 20)
	{		
		line = get_next_line(fd);
		printf(BBLU"LINE Harry Potter #%i : %s" RESET , i, line);
		free(line);
		line = get_next_line(fd2);
		printf(RED"LINE IS STAR WARS #%i: %s"RESET, i, line);
		free(line);
		i++;
	}
	close(fd);
	close(fd2);
	return (0);
}
