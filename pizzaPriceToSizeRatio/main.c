#include <stdio.h>
#include <stdlib.h>

int main()
{
	float price, size, area, pi = 3.1415;
    printf("Enter Price and Size (diameter) in inches: ");
    scanf("%f %f", &price, &size);

    area = pi * size * size / 4;

    printf("Price to Size ratio: Php %f per sq. In\n", price/area);
    return 0;
}
