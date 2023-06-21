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
    //Whether the customer is a member is checked beforehand, so we can return:
    return m_debt;
}

bool Customer::makeMember() {
    if (m_VIP) {
        return false;
    }
    m_VIP = true;
    return true;
}

void Customer::buy(int num) {
    m_debt += (COST + num);
}

void Customer::update_debt() {
    m_debt = 0;
}
