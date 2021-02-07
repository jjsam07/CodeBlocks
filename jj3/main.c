#include <stdio.h>
#include <stdlib.h>

int main()
{
    float pi = 3.1416;
    float r;

    printf("Enter radius: ");
    scanf("%f", &r);
    printf("Circumference of a circle %f\n", 2 * pi * r);

    return 0;
}
