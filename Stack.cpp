#include "Stack.h"

Stack::Stack(Record* record) :
    m_numRecords(1),
    m_records(record)
{
    m_height= record->get_copies();
    m_column = record->get_recordID();
}

Stack::~Stack() {
    m_records = nullptr;
}

int Stack::get_numRecords() const {
    return m_numRecords;
}

Record* Stack::get_records() const {
    return m_records;
}

void Stack::update_records(Record* record) {
    m_records = record;
}

void Stack::update_numRecords(int num) {
    m_numRecords += num;
}

void Stack::set_column(int column) {
    m_column = column;
}

void Stack::update_height(int height) {
    m_height += height;
}

int Stack::get_height() const {
    return m_height;
}

int Stack::get_column() const {
    return m_column;
}
