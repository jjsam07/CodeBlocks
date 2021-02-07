#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("FOR LOOP 0\n");
    int start, step, end, i;

    printf("Enter three numbers (START STEP END): ");
    scanf("%d %d %d", &start, &step, &end);

    for(i = start; i <= end; i += step) {
		printf("%d\n", i);
    }

    return 0;
}
