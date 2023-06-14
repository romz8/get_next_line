#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line_bonus.h"
#include <string.h>

# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define RESET "\033[0m"
# define BBLU "\e[1;34m"
# define BGRN "\e[1;32m"
# define BCYN "\e[1;36m"

int main(void)
{
	int fd = open("./test/long_HP.txt", O_RDONLY);
	int fd2 = open("./test/starwars.txt", O_RDONLY);
	int fd3 = open("./test/one_line_dune.txt", O_RDONLY);
    int fd4 = open("./test/seneca.txt", O_RDONLY);
	char *line;
	
	printf(YELLOW"\n\n TESTING ONE LINE FROM EACH FILE  ONE AT A TIME \n\n"RESET);
	int i = 0;
	printf("fd HP is : %i and fd SW is : %i \n\n", fd, fd2);
	while (i < 20)
	{
		line = get_next_line(fd);
		printf(BBLU"LINE Harry Potter #%i : %s" RESET , i, line);
		free(line);
		printf("\n\n ======================= other fd line =======================\n\n");

		line = get_next_line(fd2);
		printf(RED"LINE IS STAR WARS #%i: %s"RESET, i, line);
		free(line);
		printf("\n\n ======================= other fd line =======================\n\n");

		line = get_next_line(fd3);
		printf(BGRN"LINE IS DUNE #%i: %s"RESET, i, line);
		free(line);
		printf("\n\n ======================= other fd line =======================\n\n");

		line = get_next_line(fd4);
		printf(BCYN"LINE IS SENECA #%i: %s"RESET, i, line);
		free(line);
		printf("\n\n ======================= other fd line =======================\n\n");

		i++;
	}
	close(fd);
	close(fd2);
	close (fd3);
	close(fd4);
	return (0);
}
