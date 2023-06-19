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

void Record::find() {
    if (m_parent == nullptr || m_parent->m_parent == nullptr) {
        return;
    }
    find_update_parent(this);
}

Record* Record::find_update_parent(Record* tmpRecord) {
    if (tmpRecord->m_parent == nullptr) {
        return tmpRecord;
    }
    tmpRecord->m_parent = find_update_parent(tmpRecord->m_parent);
    return tmpRecord->m_parent;
}

Record* Record::record_union(Record* other, int currentNum, int otherNum) {
    //Other stack is smaller - it will be joining the current stack's upside-down tree 
    if (currentNum >= otherNum) {
        other->m_parent = this;
        return this;
    }
    //Change root of current stack to other stack's root
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
