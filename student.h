#ifndef FINAL_OOP_PROJECT_STUDENT_H
#define FINAL_OOP_PROJECT_STUDENT_H
#include "user.h"




class student : public User{

public:

    void login() override;

    void sch_order();
    void notification();
    void complain();

};


#endif //FINAL_OOP_PROJECT_STUDENT_H
