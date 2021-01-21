#include <stdio.h>
#include <stdlib.h>

double hypotenuse(double leg1, double leg2) {
	return sqrt(((leg1*leg1)+(leg2*leg2)));
}

int main()
{
	double num1, num2;
    printf("Enter the measurement of the legs of the triangle: ");
    scanf("%lf %lf", &num1, &num2);
    printf("Hypotenuse: %lf", hypotenuse(num1, num2));
    return 0;
}
