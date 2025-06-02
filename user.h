#ifndef FINAL_OOP_PROJECT_USER_H
#define FINAL_OOP_PROJECT_USER_H
#include <string>

class User {

protected:

    char username[10];
    char password[10];

public:

    User();

    void set_user(char* use);
    void set_pass(char* pass);
    void searchandorder();

    virtual void login() = 0;
    static void logout();

    virtual ~User();

};


#endif //FINAL_OOP_PROJECT_USER_H
