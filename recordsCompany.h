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
#include "Stack.h" //MIGHT WANT TO GET RID OF THIS CLASS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


class RecordsCompany {
  private:
    int m_numRecords;
    int m_currentHashSize;
    int m_numCustomers;
    Tree<RankNode<Customer*>, Customer*> m_members;
    Tree<GenericNode<Customer*>, Customer*>** m_customersHashTable;
    Record** m_records;

    void enlarge_hash_table();
    void destroy_old_hash_table(Tree<GenericNode<Customer*>, Customer*>** tmpTable);
    void insert_customer_hash_table(Customer* tmpCustomer);
    int hash_function(int id);
    void update_customers_debt(Tree<GenericNode<Customer*>, Customer*>** tmpTable);


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