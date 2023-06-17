#include "Customer.h"

Customer::Customer(int ID, int phone) :
    m_customerID(ID),
    m_phone(phone),
    m_VIP(false),
    m_debt(0)
{}

int Customer::get_customerID() const {
    return m_customerID;
}

int Customer::get_phone() const {
    return m_phone;
}

bool Customer::isVIP() const {
    return m_VIP;
}

int Customer::get_debt() const {
    if (m_VIP) {
        return m_debt; //Debating if should search in the tree here or in system
    }
    else {
        throw InvalidID(); //Might not need this later on, might need to make this a different exception
    }
}

bool Customer::makeMember() {
    if (m_VIP) {
        return false;
    }
    m_VIP = true;
    return true;
}

void Customer::buy(int num) {
    m_debt += (100 + num);
}