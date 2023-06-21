#include "Record.h"

//----------------------------------------Constructor and Destructor-------------------------------------------

Record::Record(int ID, int copies, int column) :
    m_recordID(ID),
    m_copies(copies),
    m_bought(0),
    m_column(column),
    m_height(0),
    m_parent(nullptr),
    m_stack(nullptr)
{}

Record::~Record() {
    m_parent = nullptr;
    m_stack = nullptr;
}


//--------------------------------------Getters and Setters---------------------------------------------------

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

Stack *Record::get_stack() const {
    return m_stack;
}

void Record::setStack(Stack *stack) {
    Record::m_stack = stack;
}

void Record::buy_record() {
    m_bought++;
}


//--------------------------------------Union Find---------------------------------------------------

Record* Record::find() {
    if (m_parent == nullptr) {
        return this;
    }
    int sum = 0;
    return find_update_parent(this, &sum);
}


void Record::record_union(Record *other) {
    Stack* other_stack = other->get_stack();
    Stack* this_stack = this->get_stack();
    int num_of_recs_other = other_stack->get_numRecords();
    int num_of_recs_this = this_stack->get_numRecords();
    //Other m_stack is smaller - it will be joining the current m_stack's upside-down tree
    if (num_of_recs_other <= num_of_recs_this) {
        other->m_parent = this;
        other->m_stack = nullptr;
        other->m_height += (this_stack->get_height() - m_height);
        this_stack->update_height(other_stack->get_height());
        m_stack->update_numRecords(num_of_recs_other);
        delete other_stack;
    }
    else {
        m_stack = nullptr;
        other->m_height += this_stack->get_height();
        m_height -= other->m_height;
        other_stack->update_height(this_stack->get_height());
        other->m_stack->update_numRecords(num_of_recs_this);
        other->m_stack->set_column(this_stack->get_column());
        m_parent = other;
        delete this_stack;
    }
}


//--------------------------------------Private Helper Function---------------------------------------------------

Record* Record::find_update_parent(Record* tmpRecord, int* prevH) {
    if (tmpRecord->m_parent == nullptr) {
        return tmpRecord;
    }
    tmpRecord->m_parent = find_update_parent(tmpRecord->m_parent, prevH);
    tmpRecord->m_height += *prevH;
    *prevH = tmpRecord->m_height;
    return tmpRecord->m_parent;
}

//----------------------------------------------------------------------------------------------------
