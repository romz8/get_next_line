#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;
    line = get_next_line(fd);
    printf("THE LINE IS : %s", line);
}
