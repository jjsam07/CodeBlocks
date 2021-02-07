#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("DO WHILE LOOP 0\n");
    int start, step, end, i;

    printf("Enter three numbers (START STEP END): ");
    scanf("%d %d %d", &start, &step, &end);

    i = start;

	do {
		printf("%d\n", i);
		i += step;
    } while(i <= end);

    return 0;
}
