#include <stdio.h>
#include <stdlib.h>

int main()
{
	double num1, num2;
    printf("Enter first number: ");
    scanf("%lf", &num1);
	printf("Enter second number: ");
    scanf("%lf", &num2);

    if(num1 < num2) printf("NUMBER1 IS SMALLER\n");
    if(num1 > num2) printf("NUMBER2 IS SMALLER\n");
    if(num1 == num2) printf("NUMBER1 AND NUMBER2 ARE EQUAL	\n");

    return 0;
}
