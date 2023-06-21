#ifndef RECORD_H
#define RECORD_H

#include "Stack.h"
class Stack;

/*
* Class Record
* This class is used to represent a Record in the RecordsCompany system.
*/
class Record {
public:

    /*
    * Constructor of Record class
    * @param - the record's ID, its number of copies, and its column 
    * @return - A new instance of Record
    */
    Record(int ID, int copies, int column);

    /*
    * Default Constructor, Copy Constructor and Assignment Operator of Record class
    * RecordsCompany does not allow two objects of the same record (repeating ID's).
    * Therefore the system does not allow a copy constructor or assignment operator.
    * RecordsCompany does not allow a record without a given ID.
    * Therefore the system does not allow a default constructor.
    */
    Record() = delete;
    Record(const Record& other) = delete;
    Record& operator=(const Record& other) = delete;

    /*
    * Destructor of Record class
    * @param - none
    * @return - void
    */
    ~Record();

    /*
    * Returns the record's ID
    * @param - none
    * @return - the record's ID
    */
    int get_recordID() const;

    /*
    * Returns the record's number of copies
    * @param - none
    * @return - the number of copies of the record
    */
    int get_copies() const;

    /*
    * Returns the number of bought records of that type
    * @param - none
    * @return - the number of bought records
    */
    int get_bought() const;

    /*
    * Returns the record's column
    * @param - none
    * @return - the record's column
    */
    int get_column() const;

    /*
    * Returns the record's height
    * @param - none
    * @return - the record's height
    */
    int get_height() const;

    /*
    * Returns the record's parent in the up-tree in the UF structure
    * @param - none
    * @return - the record's parent
    */
    Record* get_parent() const;

    /*
    * Returns the record's stack
    * @param - none
    * @return - the record's stack
    */
    Stack *get_stack() const;

    /*
    * Sets the record's stack to the given stack
    * @param - the record's new stack
    * @return - void
    */
    void setStack(Stack *stack);

    /*
    * Adds one purchase to the number of records bought
    * @param - none
    * @return - void
    */
    void buy_record();

    /*
     * Compress the path between the record and the root
     * @param - None
     * @return - A pointer to the record's root
    */
    Record* find();

    /*
     * Unites two stacks of records
     * @param - The root of the stack to be united with "this"
     * @return - void
    */
    void record_union(Record *other);

private:

    /*
     * Updates the height of the record after find() is called.
     * @param - The record, the record's new height
     * @return - A pointer to the record's parent
    */
    Record* find_update_parent(Record* tmpRecord, int* prevH);

    /*
     * The internal fields of Record:
     *   The record's ID
     *   The number of copies of the record
     *   The number of times the record has been bought
     *   The record's column
     *   The record's height
     *   A pointer to the record's parent in the up-tree
     *   A pointer to the record's stack
     */
    int m_recordID;
    int m_copies;
    int m_bought;
    int m_column;
    int m_height;
    Record* m_parent;
    Stack* m_stack;
};

#endif //RECORD_H