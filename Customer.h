#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Exception.h" //May not need this later - check get_debt

class Customer{
public:
    Customer(int ID, int phone);

    Customer() = delete;
    Customer(const Customer& other) = delete;
    Customer& operator=(const Customer& other) = delete;

    ~Customer() = default; //If add a pointer to customer's node in tree, must set equal to nullptr here

    int get_customerID() const;
    int get_phone() const;
    bool isVIP() const;
    int get_debt() const;
    bool makeMember();
    void buy(int num);

private:

    int m_customerID;
    int m_phone;
    bool m_VIP;
    int m_debt;
    //Might need a pointer to the customer's node in an AVL tree for VIP customers - GenericNode

};

#endif //CUSTOMER_H