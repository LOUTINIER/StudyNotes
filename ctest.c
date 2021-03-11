
#include <stdio.h>
typedef struct
{
    /* data */
    int a : 4;
    int c : 4;
    int  : 0;
}S;

int main()
{
    S ss;
    printf("%d\n", sizeof(ss));
}
