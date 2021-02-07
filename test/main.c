#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void usage() {
	printf("Program usage:\n");
	printf("Enter time in minute and seconds: [MINUTES] [SECONDS]\n\n");
	printf("\tExample\n");
	printf("\tEnter time in minute and seconds: 1 30\n\n\n");
	printf("Press any key to continue...\n");
	getch();
	system("cls");
}

int main()
{
	float min, sec, totalTime;

	usage();

	printf("Enter time in minute and seconds: ");
	scanf("%f %f", &min, &sec);

	system("cls");

	totalTime = sec + (min * 60);

	printf("Speed:\n\t%f m/s\n\t%f ft/s\n", ((5280.0/3282.0)*1000)/totalTime, 5280/totalTime);
    return 0;
}
