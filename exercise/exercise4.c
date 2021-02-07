#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int day, hour;
	float duration;
	printf("[1] for Monday\n[2] for Tuesday\n[3] for Wednesday\n[4] for Thursday\n[5] for Friday\n[6] for Saturday\n[7] for Sunday\n");
    printf("Input the day the call was made: ");
    scanf("%d", &day);
    printf("Input the time the call started (24-hour format): ");
    scanf("%d", &hour);
    printf("Input the call duration (minutes): ");
    scanf("%f", &duration);


	if (day >= 1 && day <= 5) {\
		if(hour >= 6 && hour <= 18) {
			printf("Your bill: %.2f php\n", ceil(duration) * 2.50);
		} else {
			printf("Your bill: %.2f php\n", ceil(duration) * 2.00);
		}
	} else if (day >= 6 && day <= 7) {
		printf("Your bill: %.2f php\n", ceil(duration) * 1.50);
	} else {
		printf("Invalid day");
	}
    return 0;
}
