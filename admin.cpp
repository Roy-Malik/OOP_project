#include "admin.h"
#include "stock.h"
#include <iostream>
#include <fstream>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

using namespace std;

void admin::login() {
    const int charsize = 100;
    char user[charsize] = "admin", passw[charsize] = "admin123";
    char use[charsize], pass[charsize];
    bool login_done = false;

    do {
        cout << "Enter the username: ";
        cin >> use;
        User::set_user(use);
        cout << "Enter the password: ";
        cin >> pass;
        User::set_pass(pass);

        if (strcmp(username, user) == 0 && strcmp(password, passw) == 0) {
            login_done = true;
            cout << "You have been logged in as Admin.\n";
        } else {
            cout << "You have entered the wrong username or password. Please try again.\n";
        }
    } while (!login_done);
    do {
        int opt = 0;
        cout
                << "Cafe Digital System Menu:\n1.Handle Stock\n2.Handle credentials\n3.Display notification\n4.See online orders.\n5.Complains.\n6.Stats\n7.Exit\nEnter your option: ";
        cin >> opt;
        switch (opt) {// Use switch case to select requested option
            case 1:
                cout << "Stock Handling.\n";
                stockhandling();
                break;
            case 2:
                cout << "Handle credentials.\n";
                credentials();
                break;
            case 3:
                cout << "Display Notification.\n";
                notifications();
                break;
            case 4:
                cout << "Online Orders.\n";
                orders();
                break;
            case 5:
                cout << "Complains.\n";
                complain();
                break;
            case 6:
                cout << "Stats.\n";
                stats();
                break;
            case 7:
                cout << "Logging out.\n";
                logout();
                return;
            default:
                cout << "Invalid input.\n";
                continue;
        }
    } while (true);
}

void admin::stockhandling() {
    int choice = 0;
    cout << "Enter the option:\n1.Order stock\n2.View items\nEnter your option: "; //asks for choice
    cin >> choice;
    switch (choice) {
        case 1: { // orders the stock
            stock *Stock;
            Stock = new stock[20];
            ifstream f("stocks.dat", ios::binary);
            for (int i = 0; i < 20; ++i) {
                f >> Stock[i].name >> Stock[i].price >> Stock[i].quantity >> Stock[i].total_price >> Stock[i].sold >>
                  Stock[i].profit;
            }
            f.close();
            cout << "Name : Price\n\n";
            for (int i = 0; i < 20; i++) {
                Stock[i].print();
            }
            string search;
            // Ask the user to enter the name of item he wants to search
            cout << "\nEnter the item you want to search: ";
            cin.ignore();
            getline(cin, search);
            bool found = false;
            int num = 0;

            // Search for the item in the stock file
            for (int j = 0; j < 20; j++) {
                if (Stock[j].name == search) {
                    cout << "Name : Price\n\n";
                    Stock[j].print();
                    num = j;
                    found = true;
                    break;
                }
                continue;
            }
            if (!found) {
                cout << "There is no such item.\n"; // tell the user if the item is not found
            } else {
                int opt; // option chosen by the user
                cout << "\nDo you want to add more stock in the item (1 for yes, 0 for no): ";
                cin >> opt;

                switch (opt) {
                    case 0:
                        break;
                    case 1: {
                        int quan;
                        cout << "How many of these items do you want: ";
                        cin >> quan;

                        Stock[num].add_stock(quan);

                        // Update the stock file with new stock data and total price
                        ofstream o("stocks.dat", ios::binary);
                        for (int j = 0; j < 20; j++) {
                            o << Stock[j].name << " " << Stock[j].price << " " << Stock[j].quantity << " "
                              << Stock[j].total_price << " " << Stock[j].sold << " " << Stock[j].profit << endl;
                        }
                        o.close();
                        delete[] Stock;

                        break;
                    }
                }
            }
            break;
        }
        case 2: {
            stock *Stock;
            Stock = new stock[20];
            ifstream l("stocks.dat", ios::binary);
            for (int i = 0; i < 20; ++i) {
                l >> Stock[i].name >> Stock[i].price >> Stock[i].quantity >> Stock[i].total_price
                  >> Stock[i].sold >>
                  Stock[i].profit;
            }
            l.close();
            cout << "Name : Price\n\n";
            for (int i = 0; i < 20; i++) {
                Stock[i].print();
            }
            delete[] Stock;
            break;
        }
        default:
            cout << "Invalid input.\n";
            break;
    }
}

void admin::complain() {
    int const charsize = 100;
    char text[charsize];
    // open complaint file to read
    ifstream f("complains.txt");

    int y = 1;
    // loop to read each line (complaint) in file and print it
    while (f.getline(text, charsize)) {
        cout << y << "." << text << "\n";
        y++;
    }

    cout << "\nThese are the complaints.\n";

    // close file
    f.close();

    // ask which complaint to edit
    cout << "Which complaint you want to edit: ";
    int choice;
    cin >> choice;

    char newdata[charsize] = "", data1[charsize] = "";

    // open the same file to read and manipulate
    ifstream i("complains.txt");

    int x = 1;
    // loop through each complaint
    while (i.getline(data1, charsize)) {
        if (x == choice) {
            // if the current complaint is chosen one by admin
            int opt = 0;
            cout << "Is it solved, enter 1 if it is or enter 0 if not: ";
            cin >> opt; // get status from admin

            if (opt == 1) {
                // if a complaint is solved, add "Approved" next to it
                strcat(newdata, data1);
                strcat(newdata, " Approved");
                strcat(newdata, "\n");
            } else {
                // Continue saving complaints without change
                strcat(newdata, data1);
                strcat(newdata, "\n");
            }
        } else {
            // Continue saving complaints without change
            strcat(newdata, data1);
            strcat(newdata, "\n");
        }

        x++;
    }

    // overwrite existing file with new data
    ofstream l("complains.txt");
    l << newdata;

    // close file
    l.close();
}

void admin::credentials() {
    int const charsize = 100;
    int opt = 0;

    // Present choices to the user
    cout << "What do you want to do?\n1.View credentials.\n2.Edit credentials.\nEnter choice: ";
    cin >> opt;


    switch (opt) {
        // Case 1: View credentials
        case 1: {
            int choice = 0;

            // Ask the user which credentials they want to view
            cout << "Which credentials you want to view:\n1.Employee\n2.Students/Staff\nEnter your choice: ";
            cin >> choice;

            // Handle the user's choice using a switch case
            switch (choice) {
                // Case 1: View employee credentials
                case 1: {
                    int x = 1;
                    char user[charsize], pass[charsize], selling[charsize];

                    cout << "Employee credentials: \n";

                    // Open Employee Login file
                    ifstream f("Login_emp.txt");

                    // Loop through each line in the file and print it
                    while (!f.eof()) {
                        // Read user, password, and selling info for each employee
                        f.getline(user, charsize, ' ');
                        f.getline(pass, charsize, ' ');
                        f.getline(selling, charsize, '\n');

                        // Print the employee credentials
                        cout << x << ". Username: " << user << " Password: " << pass << endl;
                        x++;
                    }

                    // Close the file
                    f.close();

                    break;
                }
                    // Case 2: View Student/Staff credentials
                case 2: {
                    int x = 1;
                    char user[charsize], pass[charsize];

                    cout << "Student credentials: \n";

                    // Open the Student/Staff Login file
                    ifstream f("login_std.txt");

                    // Loop through each line in the file and print it
                    while (!f.eof()) {
                        // Read user, password for each student
                        f.getline(user, charsize, ' ');
                        f.getline(pass, charsize, '\n');

                        // Print the student credentials
                        cout << x << ". Username: " << user << " Password: " << pass << endl;
                        x++;
                    }

                    // Close the file
                    f.close();

                    break;
                }
                default:
                    cout << "Invalid Input.\n";
                    break;
            }

            break;
        }
            // Case 2: Edit credentials
        case 2: {
            int choice = 0;
            // Ask the user which credentials they want to edit
            cout << "Which credentials you want to edit:\n1.Employee\n2.Students/Staff\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                // Case 1: Edit Employee credentials
                case 1: {
                    int x = 1;
                    char user[charsize], pass[charsize], selling[charsize];

                    cout << "Employee credentials: \n";

                    // Open the Employee Login file
                    ifstream f("Login_emp.txt");

                    // Loop through each line in the file and print it
                    while (!f.eof()) {
                        // Read user, password, and selling for each employee
                        f.getline(user, charsize, ' ');
                        f.getline(pass, charsize, ' ');
                        f.getline(selling, charsize, '\n');

                        // Print the Employee credentials
                        cout << x << ". Username: " << user << " Password: " << pass << endl;
                        x++;
                    }

                    // Close the file
                    f.close();

                    int data = 0, y = 1;
                    char data1[charsize] = "", newdata[10000] = "", newuser[charsize] = "", newpass[charsize] = "";

                    cout << "Enter the number of the user you want to edit: ";
                    cin >> data;

                    cout << "Enter new username: ";
                    cin >> newuser;

                    cout << "Enter new password: ";
                    cin >> newpass;

                    // Process each line in the file and update the specified user
                    ifstream k("Login_emp.txt");

                    while (!k.eof()) {
                        // If this is the user we want to edit
                        if (y == x - 1 && y == data) {
                            k.getline(data1, charsize, ' ');
                            k.getline(data1, charsize, ' ');
                            k.getline(data1, charsize, '\n');
                            strcat(newdata, newuser);
                            strcat(newdata, " ");
                            strcat(newdata, newpass);
                            strcat(newdata, " ");
                            strcat(newdata, data1);
                            y++;
                        } else if (data == y) {
                            k.getline(data1, charsize, ' ');
                            k.getline(data1, charsize, ' ');
                            k.getline(data1, charsize, '\n');
                            strcat(newdata, newuser);
                            strcat(newdata, " ");
                            strcat(newdata, newpass);
                            strcat(newdata, " ");
                            strcat(newdata, data1);
                            strcat(newdata, "\n");
                            y++;
                        } else if (y == x - 1) {
                            k.getline(data1, charsize, '\n');
                            strcat(newdata, data1);
                            y++;
                        }
                            // If this is not the user, we want to edit
                        else {
                            k.getline(data1, charsize, '\n');
                            strcat(newdata, data1);
                            strcat(newdata, "\n");
                            y++;
                        }
                    }

                    // Close the file
                    k.close();

                    // Create a new file to save the updated records
                    ofstream l("Login_emp.txt");
                    l << newdata;

                    // Close the file
                    l.close();

                    break;
                }
                    // Case 2: Edit Student/Staff credentials
                case 2: {
                    // Initialize variables
                    int x = 1;
                    char user[charsize], pass[charsize];

// Prompt for student credentials
                    cout << "Student credentials: \n";

// Open the file login_std.txt for reading
                    ifstream f("login_std.txt");

// Read data from file until an end of file
                    while (!f.eof()) {
                        // Get the username until the space character
                        f.getline(user, charsize, ' ');
                        cout << x << ". Username: " << user;

                        // Get the password until the newline character
                        f.getline(pass, charsize, '\n');
                        cout << " Password: " << pass << endl;

                        // Increment the counter
                        x++;
                    }

// Close the file
                    f.close();

// Initialize variables for editing
                    int data = 0, y = 1;
                    char data1[charsize] = "", newdata[10000] = "", newuser[charsize] = "", newpass[charsize] = "";

// Ask user for index of student's credentials
                    cout << "Enter the number of the user you want to edit: ";
                    cin >> data;

// Open the file again for reading
                    ifstream k("login_std.txt");

// Ask user for the new username and password
                    cout << "Enter new username: ";
                    cin >> newuser;
                    cout << "Enter new password: ";
                    cin >> newpass;

// Read data from file until an end of file
                    while (!k.eof()) {
                        // If current line is the one user wants to edit
                        if (data == y && y == x - 1) {
                            k.getline(data1, charsize, '\n');
                            // Concatenate new username and password to newdata
                            strcat(newdata, newuser);
                            strcat(newdata, " ");
                            strcat(newdata, newpass);

                            // Increment y
                            y++;
                        } else if (data == y) {
                            k.getline(data1, charsize, '\n');
                            // Concatenate new username and password to newdata
                            strcat(newdata, newuser);
                            strcat(newdata, " ");
                            strcat(newdata, newpass);
                            strcat(newdata, "\n");

                            // Increment y
                            y++;
                        } else if (y == x - 1) {

                            k.getline(data1, charsize, '\n');
                            strcat(newdata, data1);
                            y++;
                        } else {
                            // Read the current line
                            k.getline(data1, charsize, '\n');

                            // Concatenate the current line to newdata
                            strcat(newdata, data1);
                            strcat(newdata, "\n");

                            // Increment y
                            y++;
                        }
                    }

// Close the file
                    k.close();

                    // Open the file for writing
                    ofstream l("login_std.txt");

                    // Write newdata to file
                    l << newdata;

                    // Close the file
                    l.close();
                    break;
                }
                default:
                    cout << "Invalid input.\n";
                    break;
            }
            break;
        }
        default:
            cout << "Invalid input.\n";
            break;
    }

    cout << "Done.\n";
}

void admin::notifications() {
    int const charsize = 100;
    int opt;
    // Present the menu to the user and collect the option
    cout
            << "Do you want to\n1.Add a notification.\n2.View notifications.\n3.Remove a notification.\nChoose the option: ";
    cin >> opt;

    char data[charsize] = "";

    // Handle the user's option using a switch case
    switch (opt) {
        // Case 1: Add a notification
        case 1: {
            cout << "Enter the Notification: ";
            // Open the notification file in appended mode
            fstream k("notifications.txt", ios::app);
            cin.ignore();
            // Get the notification from the user
            cin.getline(data, charsize);
            // Write the notification to the file
            k << data << "\n";
            // Close the file
            k.close();
            break;
        }
            // Case 2: View notifications
        case 2: {
            // Open the notification file to read
            ifstream f("notifications.txt");
            int count = 1;
            // Loop to read each line (notification) in the file and print it
            while (f.getline(data, charsize)) {
                cout << count << "." << data << "\n";
                count++;
            }
            f.close();
            break;
        }
            // Case 3: Remove a notification
        case 3: {
            int count = 1;
            // Open the notification file to read
            ifstream j("notifications.txt");
            // Loop to read and print all notifications
            while (j.getline(data, charsize)) {
                cout << count << "." << data << "\n";
                count++;
            }
            j.close();
            // Ask which notification to remove
            int choice;
            cout << "Enter the number of notification you want to remove: ";
            cin >> choice;
            // Prepare to update notification file
            char newdata[10000] = "", data1[charsize] = "";
            ifstream i("notifications.txt");
            int x = 1;
            // Loop through each notification
            while (i.getline(data1, charsize)) {
                if (x != choice) {
                    // If it is not the one to remove, append it
                    strcat(newdata, data1);
                    strcat(newdata, "\n");
                }
                x++;
            }
            // Overwrite existing notifications with updated data
            ofstream l("notifications.txt");
            l << newdata;
            l.close();
            break;
        }
            // Default case for invalid inputs
        default: {
            cout << "Invalid Input.\n";
            break;
        }
    }
}

void admin::orders() {
    const int charsize = 100;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);

    char data1[charsize];
    ifstream i("orders.txt");

    // Check if the file was opened successfully
    if (!i) {
        cerr << "Error: File could not be opened." << endl;
        return; // Return an error code
    }

    // Loop to read each line (order) in the file and print it
    while (i.getline(data1, charsize)) {
        cout << data1 << "\n";
    }

    // Close the file
    i.close();

    // Reset the console text attribute to red
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
}

int findMax(int arr[], int size) {
    int idx = 0; // Start with the first element as the maximum
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[idx]) {
            idx = i; // Update idx if current element is greater
        }
    }
    return idx;
}

int findMin(int arr[], int size) {
    int idx = 0; // Start with the first element as the minimum
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[idx]) {
            idx = i; // Update idx if current element is smaller
        }
    }
    return idx;
}

void admin::stats() {
    const int size_emp = 5;
    string user[size_emp], pass[size_emp], sale[size_emp];
    ifstream file("Login_emp.txt");
    for (int i = 0; i < size_emp; i++) {
        getline(file, user[i], ' ');
        getline(file, pass[i], ' ');
        getline(file, sale[i], '\n');
    }
    file.close();
    int sale1[size_emp];
    for (int i = 0; i < size_emp; i++) {
        sale1[i] = stoi(sale[i]);
    }
    int greatest = findMax(sale1, size_emp);
    int lowest = findMin(sale1, size_emp);
    for (int i = 0; i < size_emp; i++) {
        if (i == greatest) {
            cout << "The best Employee of the month is: " << user[i] << " with " << sale1[i] << " Sales.\n";
        } else if (i == lowest) {
            cout << "The worst Employee of the month is: " << user[i] << " with " << sale1[i] << " Sales.\n";
        } else {
            continue;
        }
    }
    cout << endl;
    stock *Stock;
    Stock = new stock[20];
    ifstream f("stocks.dat", ios::binary);
    for (int i = 0; i < 20; ++i) {
        f >> Stock[i].name >> Stock[i].price >> Stock[i].quantity >> Stock[i].total_price >> Stock[i].sold >>
          Stock[i].profit;
    }
    int sold[20];
    for (int i = 0; i < 20; i++) {
        sold[i] = Stock[i].sold;
    }
    greatest = findMax(sold, 20);
    lowest = findMin(sold, 20);
    for (int i = 0; i < 20; i++) {
        if (i == greatest) {
            cout << "The best selling stock of the month is: " << Stock[i].name << " with " << Stock[i].sold << " "
                                                                                                                "Sales.\n";
        } else if (i == lowest) {
            cout << "The worst selling stock of the month is: " << Stock[i].name << " with " << Stock[i].sold
                 << " Sales.\n";
        } else {
            continue;
        }
    }
    double total = 0;
    for (int i = 0; i < 20; i++) {
        total += Stock[i].profit;
    }
    cout << "Total profit: " << total << " $.\n";

    delete[] Stock;
}
