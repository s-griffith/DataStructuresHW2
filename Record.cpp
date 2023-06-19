#include "Record.h"

Record::Record(int ID, int copies, int column) :
    m_recordID(ID),
    m_copies(copies),
    m_bought(0),
    m_column(column),
    m_height(0),
    m_parent(nullptr)
{}

Record::~Record() {
    m_parent = nullptr;
}

int Record::get_recordID() const {
    return m_recordID;
}

int Record::get_copies() const {
    return m_copies;
}

int Record::get_bought() const {
    return m_bought;
}

int Record::get_column() const {
    return m_column;
}

int Record::get_height() const {
    return m_height;
}

Record* Record::get_parent() const {
    return m_parent;
}

void Record::buy_record() {
    m_bought++;
    m_copies--;
}

Stack * Record::find() {
    if (m_parent == nullptr || m_parent->m_parent == nullptr) {
        return m_stack;
    }
    return find_update_parent(this)->m_stack;
}

Record* Record::find_update_parent(Record* tmpRecord) {
    if (tmpRecord->m_parent == nullptr) {
        return tmpRecord;
    }
    tmpRecord->m_parent = find_update_parent(tmpRecord->m_parent);
    return tmpRecord->m_parent;
}

Record* Record::record_union(Record* other, int currentNum, int otherNum) {
    //Other m_stack is smaller - it will be joining the current m_stack's upside-down tree
    if (other->find()->get_numRecords()<=this->find()->get_numRecords()) {
        int num_of_recs = other->find()->get_numRecords();
        delete other->find();
        Record* other_parent = other->m_parent;
        while(other_parent->m_parent){
            other_parent = other_parent->m_parent;
        }
        other_parent->m_stack = m_stack;
        other_parent->m_height -= m_height;
        m_stack->update_numRecords(num_of_recs);
        return this;
    }else{
        int num_of_recs = this->find()->get_numRecords();
        delete this->find();
        Record* this_root = this->find()->get_records();
        Record* other_root = other->find()->get_records();
        this_root->m_stack = other->m_stack;
        this_root->m_height -= other->m_height;
        m_stack->update_numRecords(num_of_recs);
        return this;
    }
    //Change root of current m_stack to other m_stack's root
    m_parent = other;
    return other;
}



void Record::set_params(int ID, int copies, int column) {
    m_recordID=ID;
    m_copies=copies;
    m_column=column;
}

int Record::find_group() {
    Record* parent = m_parent;
    if(!parent){
        return m_recordID;
    }
    while(parent->m_parent){
        parent = parent->m_parent;
    }
    return parent->m_recordID;
}

void Record::setStack(Stack *stack) {
    Record::m_stack = stack;
}
