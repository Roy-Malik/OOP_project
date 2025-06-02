#ifndef FINAL_OOP_PROJECT_ADMIN_H
#define FINAL_OOP_PROJECT_ADMIN_H
#include "user.h"



class admin : public User {

public:

    void login() override;

    void stockhandling();
    static void complain();
    static void credentials();
    static void notifications();
    static void orders();
    void stats();

};


#endif //FINAL_OOP_PROJECT_ADMIN_H
