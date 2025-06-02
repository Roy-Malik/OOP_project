#include "user.h"
#include "stock.cpp"
#include "stock.h"
#include <iostream>
#include <cstring>

using namespace std;

User::User() = default;

void User::logout() {
    cout << "You have been logged out. Exiting the program now.\n";
    exit(0);
}

void User::set_pass(char *pass) {
    strcpy(password, pass);
}

void User::set_user(char *use) {
    strcpy(username, use);
}

void User::searchandorder() {
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
    bool end1 = false;
    do {
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
            cout << "\nDo you want to add this item in the cart(1 for yes, 0 for no): ";
            cin >> opt;

            switch (opt) {
                case 0:
                    break;
                case 1: {
                    int quan;
                    cout << "How many of these items do you want: ";
                    cin >> quan;

                    // checking if desired quantity is available in the stock
                    while (quan > Stock[num].quantity) {
                        cout << "We do not have that much item in the stock,\nHow many of these items do you want: ";
                        cin >> quan;
                    }
                    Stock[num].update_quant(quan);

                    // Update the stock file with new stock data and total price
                    ofstream o("stocks.dat", ios::binary);
                    for (int j = 0; j < 20; j++) {
                        o << Stock[j].name << " " << Stock[j].price << " " << Stock[j].quantity << " "
                          << Stock[j].total_price << " " << Stock[j].sold << " " << Stock[j].profit << endl;
                    }
                    o.close();

                    // Update the cart file with new item
                    ofstream k("cart.txt", ios::app);
                    k << Stock[num].name << " " << quan << " " << Stock[num].price * quan << "$" << endl;
                    k.close();
                    break;
                }

                default:
                    cout << "Invalid input.\n"; // tell the user if the entered option is invalid
                    break;
            }
        }
        int cont;
        cout << "Do you want to add another item?(1 for yes, 2 to end): ";
        cin >> cont;
        if (cont == 2){
            end1 = true;
        } else if (cont < 1 || cont > 2){
            while (cont >= 1 && cont <= 2){
                cout << "Invalid input.\n";
                cout << "Do you want to add another item?(1 for yes, 2 to end): ";
                cin >> cont;
            }
        }
    }while(!end1);
    string data;
    ifstream q("cart.txt");
    while(!q.eof()) {
        getline(q, data);
        cout << data << endl;
    }
    delete[] Stock;
}

User::~User() {}