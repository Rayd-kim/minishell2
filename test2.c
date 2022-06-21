#include <stdlib.h>
#include <stdio.h>

int     main(int argc, char *argv[])
{
    char    *temp;

    temp = getenv("PATH");
    printf("%s\n", temp);
    printf ("%s\n", argv[0]);
}