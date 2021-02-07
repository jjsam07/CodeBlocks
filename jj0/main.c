#include <stdio.h>
#include <stdlib.h>

int main()
{
    int netIncome, grossIncome, incomeTax, sssContribution, medicalInsurance; //pwede rin float

    printf("Enter Gross Income: ");
    scanf("%d", &grossIncome);
    printf("Enter Income Tax: ");
    scanf("%d", &incomeTax);
    printf("Enter SSS Contribution: ");
    scanf("%d", &sssContribution);
    printf("Enter Medical Insurance: ");
    scanf("%d", &medicalInsurance);

    netIncome = grossIncome - incomeTax - sssContribution - medicalInsurance;

    printf("Net Income: %d\n", netIncome);
    return 0;
}
