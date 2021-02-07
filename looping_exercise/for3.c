#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("FOR LOOP 3\n");
    float num, sum;

	for(;;) {
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
