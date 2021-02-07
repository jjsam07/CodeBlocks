#include <stdio.h>
#include <stdlib.h>

int main()
{
	int message;
    printf("Input number of text messages incurred: ");
    scanf("%d", &message);

	if (message > 200) {
		printf("You are charged %.2f peso/s\n", (message - 200) * 0.5);
	} else if (message <= 200 && message >= 0) {
		printf("You are not charged\n");
	} else {
		printf("Invalid");
	}

    return 0;
}
