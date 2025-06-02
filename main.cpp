#include "user.h"
#include "admin.h"
#include "admin.cpp"
#include "user.cpp"
#include "employee.h"
#include "employee.cpp"
#include "student.h"
#include "student.cpp"
#include <iostream>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <limits>

using namespace std;

int main() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
    cout << "************************************                ************************************\n";
    cout << "************************************ WELCOME TO CDS ************************************\n"; // Welcome message
    cout << "************************************                ************************************\n";
    int opt;
    cout << "Enter\n1.For Admin\n2.For Employee\n3.Student/Staff\nEnter the choice: "; // Asking user for selection
    cin >> opt;

    // Handling non-numeric inputs
    if (cin.fail()) {
        cin.clear(); // Clear error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input
        cout << "Invalid input, please enter a number." << endl;
        return 1;
    }
    User *use[3];
    use[0] = new admin;
    use[1] = new employee;
    use[2] = new student;


    switch (opt) { // Switch case to handle user choice and call the respective functions
        case 1:
            use[0]->login();
            break;
        case 2:
            use[1]->login();
            break;
        case 3:
            use[2]->login();
            break;
        default:
            cout << "Error. Wrong Selection";
    }
    for (int i = 0; i < 2; ++i) {
        delete[] use[i];
    }
    ofstream f("cart.txt", ios::out | ios::trunc);
    f << "name : quantity : price\n";
    f.close();

    return 0;
}
