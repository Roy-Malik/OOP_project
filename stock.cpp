#include "stock.h"
#include <windows.h>

using namespace std;

stock::stock(string n, int quan, double cost, double total, int c, double p) : name(n), quantity(quan), price(cost),
                                                                               total_price(total), profit(p), sold(c) {}

void stock::update_quant(int data) {
    quantity -= data;
    total_price -= data * price;
    sold += data;
    profit += data * price;
}

stock::stock() : name(""), quantity(0), price(0), total_price(0), profit(0), sold(0) {}

stock::~stock() {}

void stock::print() {
    if (quantity <= 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // Setting console color to Yellow
    } else if (quantity <= 15) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Setting console color to Red
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Setting console color to
        // Green
    }
    cout << name << " : " << price << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
}

void stock::add_stock(int data) {
    quantity += data;
    total_price += data * price;
}
