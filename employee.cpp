#include "employee.h"
#include <iostream>
#include <fstream>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

using namespace std;

void employee::login() {
    const int emp = 5;
    const int charsize = 100;
    char user[emp][charsize], passw[emp][charsize], sale1[emp][charsize];
    int x = 0;
    bool login_done = false;

    do {
        cout << "Enter the username: ";
        cin >> username;
        cout << "Enter the password: ";
        cin >> password;

        ifstream f("Login_emp.txt");

        while (!f.eof()) {
            f.getline(user[x], charsize, ' ');
            f.getline(passw[x], charsize, ' ');
            f.getline(sale1[x], charsize, '\n');

            if (strcmp(user[x], username) == 0 && strcmp(passw[x], password) == 0) {
                strcpy(sale, sale1[x]);
                login_done = true;
                cout << "You have been logged in as " << user[x] << ".\n";
            }
            x++;
        }

        f.close();

        if (!login_done) {
            cout << "You have entered the wrong username or password. Please try again.\n";
        }
    } while (!login_done);

    // Loop for menu until exit option is chosen
    do {
        int opt = 0;
        cout << "Cafe Digital System Menu:\n1.Search items and take orders.\n2.See online orders.\n3.Exit\nEnter your option: ";
        cin >> opt; // Take the option chosen by user
        int data = stoi(sale);
        switch (opt) {
            case 1:
                cout << "Search items.\n";
                searchandorder(); // Call the function to search items and take orders
                data++;
                break;
            case 2:
                cout << "See online orders.\n";
                orders(); // Call the function to see online orders
                break;
            case 3:
                cout << "Logging out.\n"; // Logout and exit
                {
                    strcpy(sale, to_string(data).c_str());
                    ofstream l("Login_emp.txt");
                    // Update the login details file
                    for (int i = 0; i < emp; i++) {
                        if (strcmp(user[i], username) == 0 && strcmp(passw[i], password) == 0) {
                            l << user[i] << " " << passw[i] << " " << sale << endl;
                        } else {
                            l << user[i] << " " << passw[i] << " " << sale1[i] << endl;
                        }
                    }
                    l.close();
                }
                logout();
                return;
            default:
                cout << "Incorrect input.\n"; // Handle invalid input
                break;
        }
    } while (true);
}

void employee::orders() {
    int const charsize = 100;
    // Set the console text attribute to 2 (Green)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);

    char data1[charsize] = "";
    // Open the order file to read
    ifstream i("orders.txt");

    // Loop to read each line (order) in the file and print it
    while (i.getline(data1, charsize)) {
        cout << data1 << "\n";
    }

    // Reset the console text attribute to 5 (Purple)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
}
