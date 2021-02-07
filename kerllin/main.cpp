#include <iostream>

using namespace std;

int main()
{
    int previous = 0;
    int fibonacci = 1;
    cout << "[1]: " << previous << endl;
    for (int i = 0; i < 29; i++) {
        fibonacci = previous + fibonacci;
        previous = fibonacci - previous;

        cout << "[" << i + 2 << "]: " << previous << endl;
    }

    return 0;
}
