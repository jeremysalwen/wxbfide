#include "bf_table.h"



bf_table::bf_table(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name):wxGrid(parent,id,pos,size,style,name) {

    this->SetOrCalcColumnSizes(false);
    this->SetOrCalcRowSizes(false);
}

bf_table::~bf_table() {
    //dtor
}

void bf_table::OnPtrMove(wxCommandEvent& c) {
    int index=c.GetInt();
    MakeCellVisible(0,index);
}
void bf_table::OnRepaint(wxCommandEvent& c) {
    wxGridTableMessage* m= static_cast<wxGridTableMessage*>(c.GetClientData());
    GetTable()->GetView()->ProcessTableMessage(*m);
    delete m;
}

wxBEGIN_EVENT_TABLE(bf_table, wxGrid)
    EVT_COMMAND(wxID_ANY,PtrMoveEvent,bf_table::OnPtrMove)
    EVT_COMMAND(wxID_ANY,RepaintEvent,bf_table::OnRepaint)
wxEND_EVENT_TABLE()
