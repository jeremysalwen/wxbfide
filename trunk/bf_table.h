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

#ifndef BF_TABLE_H
#define BF_TABLE_H
#include <wx/grid.h>


class bf_table : public wxGrid {
public:
    bf_table(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxWANTS_CHARS, const wxString& name = wxPanelNameStr);
    virtual ~bf_table();

    void OnRepaint(wxCommandEvent& evt);
protected:
private:
    void OnPtrMove(wxCommandEvent& evt);
wxDECLARE_EVENT_TABLE();
};

wxDECLARE_EVENT(RepaintEvent, wxCommandEvent);
wxDECLARE_EVENT(PtrMoveEvent, wxCommandEvent);

#endif // BF_TABLE_H
