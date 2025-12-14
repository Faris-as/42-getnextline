#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int main()
{
    int fd = open("hello.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }
    char *line;
    int count = 0;

    line = get_next_line(fd);
    printf("Line %d: %s", ++count, line);
    line = get_next_line(fd);
    printf("Line %d: %s", ++count, line);
    free(line);
    close(fd);
    return (0);
}