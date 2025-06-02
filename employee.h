#ifndef FINAL_OOP_PROJECT_EMPLOYEE_H
#define FINAL_OOP_PROJECT_EMPLOYEE_H
#include "user.h"




class employee : public User{
private:

    char sale[10] = "";

public:

    void login() override;

    void orders();

};

#endif //FINAL_OOP_PROJECT_EMPLOYEE_H
