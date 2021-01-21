#include <stdio.h>
#include <stdlib.h>

int cube(int side);

int main()
{
	int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    printf("The area is: %d\n", cube(num));
    return 0;
}

int cube(int side) {
	return side * side * side;
}
