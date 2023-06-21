#ifndef STACK_H
#define STACK_H

#include "Record.h"
class Record;

/*
* Class Stack
* This class is used to represent a stack of records (not the data structure Stack!) in the RecordsCompany system.
*/
class Stack {
public:

    //The initial size of each stack of records
    static const int INITIAL_SIZE = 1;

    /*
    * Constructor of Stack class
    * @param - the first record in the stack
    * @return - A new instance of Stack
    */
    Stack(Record* record);

    /*
    * Default Constructor, Copy Constructor and Assignment Operator of Stack class
    * RecordsCompany does not allow two objects of the same record (repeating ID's).
    * Therefore the system does not allow a copy constructor or assignment operator.
    * RecordsCompany does not allow a record without a given ID.
    * Therefore the system does not allow a default constructor.
    */
    Stack() = delete;
    Stack(const Stack& other) = delete;
    Stack& operator=(const Stack& other) = delete;

    /*
    * Destructor of Stack class
    * @param - none
    * @return - void
    */
    ~Stack() = default;

    /*
    * Returns the number of records in the stack
    * @param - none
    * @return - the number of records in the stack
    */
    int get_numRecords() const;

    /*
    * Returns the stack's height
    * @param - none
    * @return - the stack's height
    */
    int get_height() const;

    /*
    * Returns the stack's column
    * @param - none
    * @return - the stack's column
    */
    int get_column() const;

    /*
    * Sets the stack's column equal to the given
    * @param - the stack's new column
    * @return - void
    */
    void set_column(int column);

    /*
    * Sets the stack's height equal to the given
    * @param - the stack's new height
    * @return - void
    */
    void update_height(int height);

    /*
    * Adds to the number of records in the stack
    * @param - the new number of records in the stack
    * @return - void
    */
    void update_numRecords(int num);

private:

    /*
     * The internal fields of Stack:
     *   The record's height
     *   The record's column
     *   The number of records in the stack
     */
    int m_height;
    int m_column;
    int m_numRecords;

};


#endif //STACK_H