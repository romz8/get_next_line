#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"


int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s", line);

}
