#include "bf_tableBase.h"


bf_tableBase::bf_tableBase() {
    data=new unsigned char[30000];
    reset_values();
}

bf_tableBase::~bf_tableBase() {
    delete[] data;
}

int bf_tableBase::GetNumberRows() {
    return 3;
}
int bf_tableBase::GetNumberCols() {
    return 30000;
}
bool bf_tableBase::IsEmptyCell(int row,int col) {
    if(!bounds_check(col)) {
        return false;
    }
    return data[col]!=0;
}

wxString bf_tableBase::GetValue(int row ,int col) {
    wxString result;
    switch (row) {
    case 0:
        result<< ((int)col);
        break;
    case 1:
        result<<((int)data[col]);
        break;
    case 2:
        result<<((char)data[col]);
        break;
    }
    return result;
}

void bf_tableBase::SetValue(int row, int col, const wxString& value) {

}

void bf_tableBase::set_data(int index,unsigned char value) {
    this->data[index]=value;
}
void bf_tableBase::reset_values() {
    std::fill_n(data,30000,0);
}

void bf_tableBase::inc_cell(int cell) {
    data[cell]++;
}
void bf_tableBase::dec_cell(int cell) {
    data[cell]--;
}

unsigned char bf_tableBase::get_cell(int cell) {
    return data[cell];
}

void bf_tableBase::set_cell(int cell, unsigned char value) {
    data[cell]=value;
}

inline bool bf_tableBase::bounds_check(int i) {
    return (i>=0 && i<30000);
}
