#include "Stack.h"

Stack::Stack(Record* record) :
    m_height(record->get_copies()),
    m_column(record->get_recordID()),
    m_numRecords(INITIAL_SIZE)
{}

int Stack::get_numRecords() const {
    return m_numRecords;
}

int Stack::get_height() const {
    return m_height;
}

int Stack::get_column() const {
    return m_column;
}

void Stack::set_column(int column) {
    m_column = column;
}

void Stack::update_height(int height) {
    m_height += height;
}

void Stack::update_numRecords(int num) {
    m_numRecords += num;
}
