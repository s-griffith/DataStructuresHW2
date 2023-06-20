#ifndef RECORD_H
#define RECORD_H

#include "Stack.h"
class Stack;

class Record {
public:

    Record(int ID, int copies, int column);

    Record() = delete;
    Record(const Record& other) = delete;
    Record& operator=(const Record& other) = delete;

    ~Record();

    int get_recordID() const;
    int get_copies() const;
    int get_bought() const;
    int get_column() const;
    int get_height() const;
    Record* get_parent() const;

    Stack *get_stack() ;

    void setStack(Stack *stack);

    void set_params(int ID, int copies, int column);

    void buy_record();

    /*
     * Compress the path between the record and the root
     * @param - None
     * @return - None
    */
    Record* find();

    int find_group();

    Record* find_update_parent(Record* tmpRecord);

    Record *record_union(Record *other);

private:

    int m_recordID;
    int m_copies;
    int m_bought;
    int m_column;
    int m_height;
    Record* m_parent;
    Stack* m_stack;
};

#endif //RECORD_H