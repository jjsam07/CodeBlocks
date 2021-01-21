#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double celsius(double temp_fahrenheit) {
	return (temp_fahrenheit - 32) * 5/9;
}

double fahrenheit(double temp_celsius) {
	return (temp_celsius * 9/5) + 32;
}

int main()
{
	double temp_celsius, temp_fahrenheit;

	printf("+\t-------\t\t+\t----------\t+\n");
	printf("|\tCelsius\t\t|\tFahrenheit\t|\n");
	printf("+\t-------\t\t+\t----------\t+\n");
	for(temp_celsius = 0; temp_celsius <= 100; temp_celsius++) {
		printf("|\t%lf\t|\t%lf\t|\n", temp_celsius, fahrenheit(temp_celsius));
	}
	printf("+\t----------\t+\t----------\t+\n\n");

	printf("+\t----------\t+\t-------\t\t+\n");
	printf("|\tFahrenheit\t|\tCelsius\t\t|\n");
	printf("+\t----------\t+\t-------\t\t+\n");
	for(temp_fahrenheit = 32; temp_fahrenheit <= 212; temp_fahrenheit++) {
		printf("|\t%lf\t|\t%lf\t|\n", temp_fahrenheit, celsius(temp_fahrenheit));
	}
	printf("+\t----------\t+\t----------\t+\n");
    return 0;
}
