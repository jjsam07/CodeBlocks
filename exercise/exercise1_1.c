#include <stdio.h>
#include <stdlib.h>

int main()
{
	double num;
    printf("Enter a number: ");
    scanf("%lf", &num);

    if(num > 0) printf("POSITIVE\n");
    if(num < 0) printf("NEGATIVE");

    return 0;
}
