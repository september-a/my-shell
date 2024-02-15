#include <stdio.h>
#include <string.h>

#define MAX 20

int main(int argc, char *argv[])
{
    char *p, input[256]; // p = token
    char *A[MAX];
    int i;

    strcpy(input, argv[1]);

    p = strtok(input, " ");
    for(i = 0; p != 0 && i < (MAX - 1); ++i)
    {
        A[i] = p;
        p = strtok(0, " ");
    }
    A[i] = 0;

    for(i = 0; A[i]; ++i)
    {
        printf("A[%d] = %s\n", i, A[i]);
    }
    return 0;
}