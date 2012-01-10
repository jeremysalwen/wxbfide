#include "bf_tableBase.h"

#include <wx/event.h>
#include <wx/grid.h>
#include "bf_table.h"



bf_tableBase::bf_tableBase(wxGrid* p):parent(p) {
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
    if (!bounds_check(col)) {
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

inline bool bf_tableBase::bounds_check(int i) {
    return (i>=0 && i<30000);
}

void bf_tableBase::reset_values() {
    std::fill_n(data,30000,0);
    bf_ptr=0;
    update_gui();
}

void bf_tableBase::inc_cell() {
    data[bf_ptr]++;
    update_gui();
}
void bf_tableBase::dec_cell() {
    data[bf_ptr]--;
    update_gui();
}

unsigned char bf_tableBase::get_cell() {
    return data[bf_ptr];
}

void bf_tableBase::set_cell(unsigned char value) {
    data[bf_ptr]=value;
    update_gui();
}
void bf_tableBase::inc_ptr() {
    bf_ptr++;
    update_ptr();
}
void bf_tableBase::dec_ptr() {
    bf_ptr--;
    update_ptr();
}

unsigned int bf_tableBase::get_ptr() {
    return bf_ptr;
}
void bf_tableBase::set_ptr(unsigned int i) {
    bf_ptr=i;
    update_ptr();
}


void bf_tableBase::update_ptr() {
    wxCommandEvent* evt=new wxCommandEvent(PtrMoveEvent,wxID_ANY);
    evt->SetInt(bf_ptr);
    parent->GetEventHandler()->QueueEvent(evt);
}

void bf_tableBase::update_gui() {
    wxGridTableMessage* m=new wxGridTableMessage(this,wxGRIDTABLE_REQUEST_VIEW_GET_VALUES );//very poorly documented
    //GetView()->ProcessTableMessage(*m); bad bad bad unsafe... but works.
    wxCommandEvent* e=new wxCommandEvent(RepaintEvent,wxID_ANY);
    e->SetClientData(m);
    parent->GetEventHandler()->QueueEvent(e);
}
