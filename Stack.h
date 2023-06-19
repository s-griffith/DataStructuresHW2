#ifndef STACK_H
#define STACK_H

#include "Record.h"
class Record;

class Stack {
public:

    Stack(Record* record);
    ~Stack();

    int get_numRecords() const;

    Record* get_records() const;

    void update_records(Record* record);

    void update_numRecords(int num);


private:

    int m_numRecords;
    Record* m_records;

};


#endif //STACK_H