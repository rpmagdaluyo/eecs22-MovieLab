#include <stdio.h>

#include "Image.h"

/*
int clip(int x)
{
    if(x < 0)
        x = 0;
    else if(x > 255)
        x = 255;
    return x;
}
*/
int main(void){
    int x1 = 345, x2 = -90, x3 = 45;

    printf("x1 old value: %d.\nAfter clipping: %d.\n\n", x1, clip(x1));
    printf("x2 old value: %d.\nAfter clipping: %d.\n\n", x2, clip(x2));
    printf("x3 old value: %d.\nAfter clipping: %d.\n\n", x3, clip(x3));

    return 0;
}
