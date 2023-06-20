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
   Record* parent = m_parent;
   int height = m_height;
   while(parent){
       height += parent->m_height;
       parent = parent->m_parent;
   }
   return height;
}

Record* Record::get_parent() const {
    return m_parent;
}

void Record::buy_record() {
    m_bought++;
}

Record* Record::find() {
    if (m_parent == nullptr) {
        return this;
    }
    return find_update_parent(this);
}

Record* Record::find_update_parent(Record* tmpRecord) {
    if (tmpRecord->m_parent == nullptr) {
        return tmpRecord;
    }
    tmpRecord->m_parent = find_update_parent(tmpRecord->m_parent);
    return tmpRecord->m_parent;
}

Record * Record::record_union(Record *other) {
    //Other m_stack is smaller - it will be joining the current m_stack's upside-down tree
    int num_of_recs_other = other->find()->get_stack()->get_numRecords();
    int num_of_recs_this = this->find()->get_stack()->get_numRecords();
    Record* other_root = other->find()->get_stack()->get_records();
    Record* this_root = this->find()->get_stack()->get_records();
    Stack* other_stack = other->find()->get_stack();
    Stack* this_stack = this->find()->get_stack();
    if (num_of_recs_other<=num_of_recs_this) {
        other_root->m_parent = this_root;
        other_root->m_stack = nullptr;
        other_root->m_height += (this_stack->get_height() - this_root->m_height);
        this_root->m_stack->update_numRecords(num_of_recs_other);
        delete other_stack;
        return this;
    }
    else{
        this_root->m_stack = nullptr;
        int other_height = other_root->m_height;
        other_root->m_height += this_stack->get_height();
        this_root->m_height -= other_height;
        other_root->m_stack->update_numRecords(num_of_recs_this);
        other_root->m_stack->set_column(this_stack->get_column());
        this_root->m_parent = other_root;
        delete this_stack;
        return other;
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

Stack *Record::get_stack()  {
    return m_stack;
}
