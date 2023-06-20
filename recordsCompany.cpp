#include "recordsCompany.h"

RecordsCompany::RecordsCompany() : 
    m_numRecords(0),
    m_currentHashSize(7),
    m_numCustomers(0),
    m_members(),
    m_records(nullptr)
{
    m_customersHashTable = new Tree<GenericNode<Customer*>, Customer*>*[m_currentHashSize];
    for (int i = 0; i < m_currentHashSize; i++) {
        m_customersHashTable[i] = new Tree<GenericNode<Customer*>, Customer*>();
    }
}


RecordsCompany::~RecordsCompany()
{
    for (int i = 0; i < m_currentHashSize; i++) {
        if (m_customersHashTable[i]->m_node->get_height() >= 0) {
            m_customersHashTable[i]->erase_data(m_customersHashTable[i]->m_node);
        }
        delete m_customersHashTable[i];
    }
    /*if (m_members.m_node->get_height() >= 0) {
        m_members.erase_data(m_members.m_node);
    }*/
    delete[] m_customersHashTable;
    //delete previous data
    //delete previous data
    for (int i = 0; i < m_numRecords; i++) {
        if(m_records[i]->get_stack())
            delete m_records[i]->get_stack();
        delete m_records[i];
    }
    delete[] m_records;
}


StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if(number_of_records<0){
        return StatusType::INVALID_INPUT;
    }
    update_customers_debt(m_customersHashTable);

    //delete previous data
    for (int i = 0; i < m_numRecords; i++) {
        delete m_records[i]->find();
        delete m_records[i];
    }
    delete[] m_records;

    try {
        m_records = new Record *[number_of_records];
    }
    catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }

    for (int i = 0; i < number_of_records; ++i) {
        try{
            m_records[i]= new Record(i, records_stocks[i], i);
            Stack* stack = new Stack(m_records[i]);
            m_records[i]->setStack(stack);
        }
        catch (const std::bad_alloc& e) {
            delete m_records;
            return StatusType::ALLOCATION_ERROR;
        }
    }
    m_numRecords = number_of_records;
    return StatusType::SUCCESS;
}


StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(c_id<0||phone<0){
        return StatusType::INVALID_INPUT;
    }

    Customer* newCustomer = new Customer(c_id, phone);

    //Update the hash table if needed:
    if (m_numCustomers + 1 == m_currentHashSize) {
        try {
            enlarge_hash_table();
        }
        catch (const std::bad_alloc& e) {
            delete newCustomer;
            return StatusType::ALLOCATION_ERROR;
        }
    }

    int arrayIndex = hash_function(c_id);
    try {
        m_customersHashTable[arrayIndex]->insert(newCustomer, c_id);
    }
    catch (const InvalidID& e) {
        delete newCustomer;
        return StatusType::ALREADY_EXISTS;
    }
    catch (const std::bad_alloc& e) {
        delete newCustomer;
        return StatusType::ALLOCATION_ERROR;
    }
    m_numCustomers++;
    return StatusType::SUCCESS;
}


Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if (c_id < 0) {
        return Output_t<int>(StatusType::INVALID_INPUT);
    }
    int arrayIndex = hash_function(c_id);
    Customer* tmpCustomer;
    try {
        tmpCustomer = m_customersHashTable[arrayIndex]->search_and_return_data(c_id);
    }
    catch (const NodeNotFound& e) {
        return Output_t<int>(StatusType::DOESNT_EXISTS);
    }
    return Output_t<int>(tmpCustomer->get_phone());
}


StatusType RecordsCompany::makeMember(int c_id)
{
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }
    int arrayIndex = hash_function(c_id);
    Customer* tmpCustomer;
    try {
        tmpCustomer = m_customersHashTable[arrayIndex]->search_and_return_data(c_id);
    }
    catch (const NodeNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
    if (tmpCustomer->makeMember()) {
        try {
            m_members.insert(tmpCustomer, c_id);
        }
        catch (const std::bad_alloc& e) {
            return StatusType::ALLOCATION_ERROR;
        }
        return StatusType::SUCCESS;
    }
    return StatusType::ALREADY_EXISTS;
}


Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if (c_id < 0) {
        return Output_t<bool>(StatusType::INVALID_INPUT);
    }
    int arrayIndex = hash_function(c_id);
    Customer* tmpCustomer;
    try {
        tmpCustomer = m_customersHashTable[arrayIndex]->search_and_return_data(c_id);
    }
    catch (const NodeNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
    return Output_t<bool>(tmpCustomer->isVIP());
}


StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if (c_id < 0 || r_id < 0) {
        return StatusType::INVALID_INPUT;
    }
    if (r_id >= m_numRecords) {
        return StatusType::DOESNT_EXISTS;
    }
    int arrayIndex = hash_function(c_id);
    Customer* tmpCustomer;
    try {
        tmpCustomer = m_customersHashTable[arrayIndex]->search_and_return_data(c_id);
    }
    catch (const NodeNotFound& e) {
        return StatusType::DOESNT_EXISTS;
    }
    if (tmpCustomer->isVIP()) {
        tmpCustomer->buy(m_records[r_id]->get_bought());
    }
    m_records[r_id]->buy_record();
    return StatusType::SUCCESS;
}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if (c_id1 < 0 || c_id2 < 0 || amount <= 0 ||c_id2 < c_id1) {
        return StatusType::INVALID_INPUT;
    }
    m_members.add_prize(amount, c_id1, c_id2);
    return StatusType::SUCCESS;
}


Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if (c_id < 0) {
        return Output_t<double>(StatusType::INVALID_INPUT);
    }
    Customer* tmpCustomer;
    try {
        tmpCustomer = m_members.search_and_return_data(c_id);
    }
    catch(const NodeNotFound& e) {
        return Output_t<double>(StatusType::DOESNT_EXISTS);
    }
    return Output_t<double>(tmpCustomer->get_debt() - m_members.calculate_prize(&(m_members.search_specific_id(c_id))));
}


StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if(r_id1<0 || r_id2<0 ){
        return INVALID_INPUT;
    }
    if(r_id1>= m_numRecords || r_id2>= m_numRecords){
        return DOESNT_EXISTS;
    }
    Record* rec1= m_records[r_id1];
    Record* rec2 = m_records[r_id2];

    if(rec1->find()==rec2->find()){
        return FAILURE;
    }
    rec2->record_union(rec1);
    return SUCCESS;
}


StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if(r_id<0|| !column || !hight){
        return INVALID_INPUT;
    }
    if(r_id>=m_numRecords){
        return DOESNT_EXISTS;
    }
    *hight = m_records[r_id]->get_height();
    *column = m_records[r_id]->find()->get_column();
    return StatusType::SUCCESS;
}


//-----------------------------------Helper Functions-------------------------------------------

void RecordsCompany::enlarge_hash_table()
{
    int newSize = ((m_currentHashSize + 1 ) * 2 ) - 1;
    Tree<GenericNode<Customer*>, Customer*>** newTable = new Tree<GenericNode<Customer*>, Customer*>*[newSize];
    for (int i = 0; i < newSize; i++) {
        try {
            newTable[i] = new Tree<GenericNode<Customer*>, Customer*>();
        }
        catch (const std::bad_alloc& e) {
            delete[] newTable;
            throw e;
        }
    }
    int arrayIndex = 0;
    Customer** all_customers = new Customer*[m_currentHashSize];
    for (int i = 0; i < m_currentHashSize; i++) {
        all_customers[i] = nullptr;
    }
    Customer** tmpCustomers = all_customers;
    for (int i = 0; i < m_currentHashSize; i++) {
        m_customersHashTable[i]->get_all_data(all_customers);
        while (*all_customers != nullptr) {
            arrayIndex = (*all_customers)->get_customerID() % newSize;
            newTable[arrayIndex]->insert(*all_customers, (*all_customers)->get_customerID());
            all_customers++;
        }
    }
    delete[] tmpCustomers;
    Tree<GenericNode<Customer*>, Customer*>** tmpTable = m_customersHashTable;
    m_customersHashTable = newTable;
    destroy_old_hash_table(tmpTable);
    m_currentHashSize = newSize;
}


void RecordsCompany::destroy_old_hash_table(Tree<GenericNode<Customer*>, Customer*>** tmpTable)
{
    for (int i = 0; i < m_currentHashSize; i++) {
        delete tmpTable[i];
    }
    delete[] tmpTable;
}


void RecordsCompany::insert_customer_hash_table(Customer* tmpCustomer)
{
    int arrayIndex = hash_function(tmpCustomer->get_customerID());
    m_customersHashTable[arrayIndex]->insert(tmpCustomer, tmpCustomer->get_customerID());
}


int RecordsCompany::hash_function(int id)
{
    return id % m_currentHashSize;
}

// Assume we have a HashTable class with a member variable "buckets" of type AVLTreeNode**

void TraverseAVLTree(GenericNode<Customer*>* node) {
    if (node == nullptr) {
        return;
    }

    TraverseAVLTree(node->get_left());

    node->get_data()->update_debt();

    TraverseAVLTree(node->get_right());
}

void RecordsCompany::update_customers_debt(Tree<GenericNode<Customer*>, Customer*>** tmpTable) {

    for (int i = 0; i < m_currentHashSize; i++) {
        GenericNode<Customer*>* bucket = tmpTable[i]->m_node;
        if(bucket->get_data()) {
            TraverseAVLTree(bucket);
        }
    }
}
