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

#ifndef BFTERM_H
#define BFTERM_H

#include "terminalWx/terminalwx.h"
#include <wx/thread.h>
#include <queue>


class BFTerm : public TerminalWx
{
public:
    BFTerm(wxWindow* parent, wxMutex* mutex,
           wxCondition* cond, wxWindowID id,
           const wxPoint& pos = wxDefaultPosition,
           const wxSize& size=wxDefaultSize,
           const wxString& name = "Brainfuck Terminal");
    virtual ~BFTerm();
    virtual void OnUserInput(wxString str);
    wxChar getChar();
    bool empty() const;
protected:
private:
    std::queue<wxChar> inputbuffer;
    wxMutex* mutex;
    wxCondition* cond;
};

#endif // BFTERM_H
