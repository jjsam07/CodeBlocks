#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("DO WHILE LOOP 3\n");
    float num, sum;

	do {
		printf("Enter a number: ");
		scanf("%f", &num);
		sum += num;
		if (num == 0) {
			break;
		}
    } while(1);

	printf("Sum = %f\n", sum);

    return 0;
}
