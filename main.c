#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"


int main(void)
{
	int fd = open("test2.txt", O_RDONLY);
	char *line;
	int i = 0;
	while (i < 15)
	{		
 	
		line = get_next_line(fd);
		i++;
		printf("LINE IS : %s", line);
		// free(line);
	}
}
