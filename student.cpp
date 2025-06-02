#include "student.h"
#include <iostream>
#include <fstream>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

using namespace std;

void student::login() {
    int const charsize = 100;
    // Variables to store actual user names and passwords
    char user[charsize], pass[charsize];

    // Variables to store entered username and password
    bool login = false;  // Flag to check login status

    do {
        cout << "Enter the username: ";
        cin >> username;
        cout << "Enter the password: ";
        cin >> password;

        // Open file with login data
        ifstream f("login_std.txt");

        // Read the file until reached its end
        while (!f.eof()) {
            // Read username and password from file
            f.getline(user, charsize, ' ');
            f.getline(pass, charsize, '\n');

            // If entered username and password match with any in file, set login to true
            if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) {
                login = true;
                cout << "You have been logged in as " << user << ".\n";
            }
        }

        // If a login attempt failed, notify the user
        if (!login) {
            cout << "You have entered the wrong username or password. Please try again.\n";
            login = false;
        }
    } while (!login);  // Repeat until successful login

    do {
        // Display the menu and get user's choice
        int opt = 0;
        cout
                << "Cafe Digital System Menu:\n1.Search and Order\n2.Complaints.\n3.Give or Schedule order.\n4.See notifications\n5.Exit\nEnter your option: ";
        cin >> opt;

        // Execute the appropriate function based on the user's choice
        switch (opt) {
            case 1:
                cout << "Search and Order.\n";
                searchandorder();
                break;
            case 2:
                cout << "Complaints.\n";
                complain();
                break;
            case 3:
                cout << "Give or schedule orders.\n";
                sch_order();
                break;
            case 4:
                cout << "Notifications.\n";
                notification();
                break;
            case 5:
                cout << "Logging out.\n"; // Logout from the system
                logout();
                return;
            default:
                cout << "Invalid input.\n";  // Notify user of invalid input and repeat the menu
                continue;
        }
    } while (true);  // Keep repeating until the user chooses to exit
}

void student::notification() {
    int const charsize = 100;
    // Array to store individual notifications
    char data[charsize] = "";

    // Open the file that contains notifications
    ifstream f("notifications.txt");

    // Counter for numbering the notifications
    int count = 1;

    // Iterate through all the lines (notifications) in the file
    while (f.getline(data, charsize)) {
        // Print the number and content of the notification
        cout << count << "." << data << "\n";

        // Increase the counter for the next notification
        count++;
    }

    f.close();
}

void student::complain() {
    int const charsize = 100;
    // Array to hold the user's complaint
    char data[charsize] = "";

    // Open the complaint file in appending mode - this enables adding new complaints at the end of the file
    fstream f("complains.txt", ios::app);

    // Prompt user to enter their complaint
    cout << "Enter the complaint: ";

    // Ignore the newline character remaining in the buffer from previous input operations
    cin.ignore();

    // Get user's complaint
    cin.getline(data, charsize);

    // Output the user's complaint to the file, followed by a newline
    f << data << "\n";

    // Close the complaint file
    f.close();
}

void student::sch_order() {
    int const charsize = 100;
    int const maxsize = 20;
    // Call search and order function
    searchandorder();

    // Array to store the delivery time input by the user
    char time1[charsize];

    // Prompt the user to enter the time they want their order delivered
    cout << "Enter the time you want it to be delivered: ";
    cin >> time1;

    // Initialize arrays to store the cart lines and title
    char title[charsize], line[maxsize][charsize] = {};

    // Counter for lines
    int i = 0;

    // Open the cart file to read the current order
    ifstream f("cart.txt");

    // Get the title of the cart and all the lines (items) in the cart
    f.getline(title, charsize, '\n');
    while (!f.eof()) {
        f.getline(line[i], charsize, '\n');
        i++;
    }

    // Close the cart file
    f.close();

    // Open the order file to append the new order
    ofstream k("orders.txt", ios::app);

    // Write the new order to the file
    k << "\nOrder:\n";
    for (int j = 0; j < maxsize; j++) {
        if (line[j][0] == '\0') {
            break;
        } else {
            k << line[j] << endl;
        }
    }

    // Get the current time and write it to the file
    time_t time10 = time(0);
    char *timestring = ctime(&time10);
    k << "At time: " << timestring;

    // Write the delivery time to the file
    k << "To be delivered at: " << time1;

    // Close the order file
    k.close();

}