#include <stdio.h>
#include <stdlib.h>

int main()
{
    int hourlyRate, numOfHrsWorked; //pwede rin float

    printf("Enter hourly rate: ");
    scanf("%d", &hourlyRate);
    printf("Enter number of hours worked: ");
    scanf("%d", &numOfHrsWorked);

    printf("Salary: %d\n", hourlyRate * numOfHrsWorked);
    return 0;
}
