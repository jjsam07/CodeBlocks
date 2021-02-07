#include <iostream>

using namespace std;

int attempts = 0;
int pin;
int input;
int transaction;
char doYouWantToContinue;
float availableBalance = 10000;
float depositAndWithdraw;

int main()
{
    while(1) {
        cout << "Please enter PIN: ";
        cin >> pin;
        if (pin != 445236) {
            attempts++;
            if (attempts == 3) {
                cout << "Maximum of three attempts reached\n";
                return 0;
            }
            cout << "Incorrect PIN. Please try again\n(Attempts left: " << 3 - attempts << ")\n\n";
        } else {
            cout << endl;
            break;
        }
    }

    while(1) {
        cout << "Check Balance\nDeposit\nWithdraw\nExit\n\nEnter Transaction Number Here: ";
        cin >> input;
        switch(input) {
            case 1: //Check Balance
                cout << "Available Balance: " << availableBalance << "\n\n";
                break;
            case 2: //Deposit
                cout << "Enter Amount: ";
                cin >> depositAndWithdraw;
                availableBalance = availableBalance + depositAndWithdraw;
                cout << "\nTransaction Complete...\nYour Account is updated...\n\n";
                break;
            case 3: //Withdraw
                cout << "Enter Amount: ";
                cin >> depositAndWithdraw;
                availableBalance = availableBalance - depositAndWithdraw;
                cout << "\nTransaction Complete...\nYour Account is updated...\n\n";
                break;
            case 4: //Exit
                cout << "Thank you for using this system... Have a great day!\n";
                return 0;
                break;
        }

        while(1) {
            cout << "Do you want to continue?\n[Y or y] Yes\n[N or n] No\n\nEnter here: ";
            cin >> doYouWantToContinue;

            if (doYouWantToContinue == 'N' || doYouWantToContinue == 'n') {
                cout << "Thank you for using this system... Have a great day!\n";
                return 0;
            } else if (doYouWantToContinue == 'Y' || doYouWantToContinue == 'y') {
                cout << endl;
                break;
            } else {
                cout << "Invalid input\n\n";
            }
        }
    }
    return 0;
}
