#include <stdio.h>
#include <stdlib.h>

int main()
{
    int l, w; //pwede rin float

    printf("Enter length of rectangle: ");
    scanf("%d", &l);
    printf("Enter width of rectangle: ");
    scanf("%d", &w);

    printf("Area of rectangle: %d", l * w);
    return 0;
}
