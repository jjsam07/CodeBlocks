#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("WHILE 3\n");
    float num, sum;

	while(1) {
		printf("Enter a number: ");
		scanf("%f", &num);
		sum += num;
		if (num == 0) {
			break;
		}
    }

	printf("Sum = %f\n", sum);

    return 0;
}
