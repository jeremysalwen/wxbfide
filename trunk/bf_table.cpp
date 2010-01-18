#include "bf_table.h"

bf_table::bf_table(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name):wxGrid(parent,id,pos,size,style,name) {
    wxGridCellAttr *w=new wxGridCellAttr();  //memory leak?
    w->SetReadOnly(true);
    this->SetRowAttr(1,w);
    this->SetColumnWidth(1,10);
    this->SetRowLabelSize(0);
    this->SetColLabelSize(0);
    this->DisableDragGridSize();
    bf_tableBase * b =new bf_tableBase;
    this->SetTable(b,true);
    this->SetMargins(0,0);
    this->SetOrCalcColumnSizes(false);
    this->SetOrCalcRowSizes(false);
}

bf_table::~bf_table() {
    //dtor
}

