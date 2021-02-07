#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num;
	printf("[1] for Monday\n[2] for Tuesday\n[3] for Wednesday\n[4] for Thursday\n[5] for Friday\n[6] for Saturday\n[7] for Sunday\n");
    printf("Enter a number: ");
    scanf("%d", &num);

    if(num >= 6) {
		printf("WEEKEND\n");
	} else {
		printf("WEEKDAY\n");
	}

    return 0;
}
