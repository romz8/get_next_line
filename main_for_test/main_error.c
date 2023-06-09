#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <string.h>

# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define RESET "\033[0m"

void test_gnl(int fd, char *comp)
{
    char *line = get_next_line(fd);
    if (!comp)
    {   if (line != NULL)
        {
            printf(RED"NOT OK\n"RESET);
            printf("GNL IS: %s\n EXPECTED: %s\n", line, comp);
        }
    }
    else if (strcmp(line, comp) != 0)
    {
        printf(RED"NOT OK\n"RESET);
        printf("GNL IS: %s\n EXPECTED: %s\n", line, comp);
    }
    else
        printf(YELLOW"OK\n"RESET);
}

int main(void)
{
	int fd = open("./test/read_error.txt", O_RDONLY);
	// set the next read call to return -1
    if (BUFFER_SIZE <= 100)
    {
        printf("\n\nFOR BUFFER < 100\n\n");
        test_gnl(fd, "aaaaaaaaaa\n");
	    test_gnl(fd, "bbbbbbbbbb\n");
	    test_gnl(fd, "cccccccccc\n");
	    test_gnl(fd, "dddddddddd\n");
    }
	if (BUFFER_SIZE > 100) 
    {
		printf("\n\nNOW FOR BUFFER > 100\n\n");
        char *temp;
		do 
        {
			temp = get_next_line(fd);
			free(temp);
		} 
        while (temp != NULL);

	    printf("test3 : is it NULL?\n");
        test_gnl(fd, NULL);
	    close(fd);
		fd = open("./test/read_error.txt", O_RDONLY);
        test_gnl(fd, "aaaaaaaaaa\n");
	    test_gnl(fd, "bbbbbbbbbb\n");
	    test_gnl(fd, "cccccccccc\n");
	    test_gnl(fd, "dddddddddd\n");
	    test_gnl(fd, NULL);
    }
}