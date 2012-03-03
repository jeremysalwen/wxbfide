#include "bf_table.h"

#include "IDEFrame.h"

wxDEFINE_EVENT(RepaintEvent, wxCommandEvent);
wxDEFINE_EVENT(PtrMoveEvent, wxCommandEvent);

wxBEGIN_EVENT_TABLE(bf_table, wxGrid)
    EVT_COMMAND(IDEFrame::ID_GRID1,RepaintEvent,bf_table::OnRepaint)
    EVT_COMMAND(IDEFrame::ID_GRID1,PtrMoveEvent,bf_table::OnPtrMove)
    EVT_COMMAND_ENTER(IDEFrame::ID_GRID1,bf_table::OnRepaint)
wxEND_EVENT_TABLE()


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
void bf_table::ping() {
    std::cout <<"hello world" <<std::endl;
}
