#include <stdio.h>
int *fd()
{
    static int file_descriptor = -1;
    return &file_descriptor;
}

int main()
{
    int c = *fd();
    printf("%d\n", c);
}