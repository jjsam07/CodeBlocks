#include <stdio.h>
#include <stdlib.h>

int main()
{
	int years;
	float salary;
    printf("Enter the number of years you have served: ");
    scanf("%d", &years);
    printf("Input your salary: ");
    scanf("%f", &salary);

    switch(years) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			printf("Your bonus: %.2f php\n", salary * 0.20);
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			printf("Your bonus: %.2f php\n", salary * 0.25);
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			printf("Your bonus: %.2f php\n", salary * 0.30);
			break;
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
			printf("Your bonus: %.2f php\n", salary * 0.35);
			break;
		default:
			printf("Your bonus: %.2f php\n", salary * 0.50);
    }

    return 0;
}
