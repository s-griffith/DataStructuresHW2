#ifndef CUSTOMER_H
#define CUSTOMER_H

/*
* Class Customer
* This class is used to represent a Customer in the RecordsCompany system.
*/
class Customer{
public:

    //The constant value added to the price of a purchase
    static const int COST = 100;

    /*
    * Constructor of Customer class
    * @param - the customer's ID and phone
    * @return - A new instance of Customer
    */
    Customer(int ID, int phone);

    /*
    * Default Constructor, Copy Constructor and Assignment Operator of Customer class
    * RecordsCompany does not allow two of the same customer (repeating ID's).
    * Therefore the system does not allow a copy constructor or assignment operator.
    * RecordsCompany does not allow a customer without a given ID.
    * Therefore the system does not allow a default constructor.
    */
    Customer() = delete;
    Customer(const Customer& other) = delete;
    Customer& operator=(const Customer& other) = delete;

    /*
    * Destructor of Customer class
    * @param - none
    * @return - void
    */
    ~Customer() = default;

    /*
    * Returns the customer's ID
    * @param - none
    * @return - the customer's ID
    */
    int get_customerID() const;

    /*
    * Returns the customer's phone number
    * @param - none
    * @return - the customer's phone number
    */
    int get_phone() const;

    /*
    * Returns whether the customer is a member
    * @param - none
    * @return - bool, whether the customer is a member
    */
    bool isVIP() const;

    /*
    * Returns how much the customer has spent
    * @param - none
    * @return - int, how much the customer has spent
    */
    int get_debt() const;

    /*
    * Makes the customer a member
    * @param - none
    * @return - bool, whether the action succeeded
    */
    bool makeMember();

    /*
    * The customer purchases a record
    * @param - The cost of the record (not including COST)
    * @return - void
    */
    void buy(int num);

    /*
    * Resets the customer's debt to zero
    * @param - none
    * @return - void
    */
    void update_debt();

private:

    /*
     * The internal fields of Customer:
     *   The customer's ID
     *   The customer's phone number
     *   Whether the customer is a member
     *   The customer's debt
     */
    int m_customerID;
    int m_phone;
    bool m_VIP;
    int m_debt;

};

#endif //CUSTOMER_H