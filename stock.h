#ifndef FINAL_OOP_PROJECT_STOCK_H
#define FINAL_OOP_PROJECT_STOCK_H
#include <string>

using namespace std;



class stock {

public:
    string name;
    int quantity;
    double price;
    double total_price;
    int sold;
    double profit;

    stock();
    stock(string n, int quan, double cost, double total, int c, double p);

    void print();
    void update_quant(int data);
    void add_stock(int data);

    ~stock();

};


#endif //FINAL_OOP_PROJECT_STOCK_H
