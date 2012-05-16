#include "bf_table.h"

 /*
  *  WxBfIDE - A cross-platform brainfuck IDE
  *  Copyright (C) 2008-2012  Jeremy Salwen
  *
  *  This program is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
#include "IDEFrame.h"

wxDEFINE_EVENT(RepaintEvent, wxCommandEvent);
wxDEFINE_EVENT(PtrMoveEvent, wxCommandEvent);

wxBEGIN_EVENT_TABLE(bf_table, wxGrid)
    EVT_COMMAND(IDEFrame::ID_GRID1,RepaintEvent,bf_table::OnRepaint)
    EVT_COMMAND(IDEFrame::ID_GRID1,PtrMoveEvent,bf_table::OnPtrMove)
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
