#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"
#include "AVLTree.h"
#include "Customer.h"
#include "Exception.h"
#include "Node.h"
#include "GenericNode.h"
#include "RankNode.h"
#include "Record.h"
#include "Stack.h" 

class RecordsCompany {
  private:

    //The initial size of the hash table
    static const int INITIAL_HASH = 7;

    /*
     * The internal fields of RecordsCompany:
     *   The number of records in the system
     *   The current size of the hash table
     *   The number of customers in the system
     *   An AVL tree of members
     *   A hash table of AVL trees of customers
     *   An array of pointers to records
     */
    int m_numRecords;
    int m_currentHashSize;
    int m_numCustomers;
    Tree<RankNode<Customer*>, Customer*> m_members;
    Tree<GenericNode<Customer*>, Customer*>** m_customersHashTable;
    Record** m_records;

    //-------------------------------------------Helper Functions----------------------------------------------

    /*
    * When the number of customers = size of table, the table needs to be enlarged to ensure time complexity of O(1)
    *   for inserting + searching for customers
    * @return - none
    */
    void enlarge_hash_table();

    /*
    * Deallocate memory of previous hash table
    * @return - none
    */    
    void destroy_old_hash_table(Tree<GenericNode<Customer*>, Customer*>** tmpTable);

    /*
    * Insert a new customer to hash table
    * @return - none
    */
    void insert_customer_hash_table(Customer* tmpCustomer);

    /*
    * Calculate placement of customer in hash table according to the hash function
    * @return - integer that is equal to the customer's index in the hash table
    */
    int hash_function(int id);

  public:
    RecordsCompany();
    ~RecordsCompany();
    StatusType newMonth(int *records_stocks, int number_of_records);
    StatusType addCostumer(int c_id, int phone);
    Output_t<int> getPhone(int c_id);
    StatusType makeMember(int c_id);
    Output_t<bool> isMember(int c_id);
    StatusType buyRecord(int c_id, int r_id);
    StatusType addPrize(int c_id1, int c_id2, double  amount);
    Output_t<double> getExpenses(int c_id);
    StatusType putOnTop(int r_id1, int r_id2);
    StatusType getPlace(int r_id, int *column, int *hight);
};

#endif