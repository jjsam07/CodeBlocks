#include <stdio.h>
#include <stdlib.h>

int main()
{
	float grade;

    printf("Enter grade: ");
    scanf("%f", &grade);
    printf("Your grade = %f\n", 112.5 - (grade*12.5));
    return 0;
}
