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

#include "BFTerm.h"

BFTerm::BFTerm(wxWindow* parent, wxMutex* mutex, wxCondition* cond,
               wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               const wxString& name):TerminalWx(parent,id,pos,80,24,name),
                    mutex(mutex),cond(cond)
{
    SetSize(size);
}

BFTerm::~BFTerm()
{
    //dtor
}

void BFTerm::OnUserInput(wxString str)
{
    wxMutexLocker l(*mutex);
    for(unsigned int i=0; i<str.size(); i++)
    {
        inputbuffer.push(str.GetChar(i));
    }
    cond->Signal(); //better be only one guy waiting or we're screwed anyway
}

wxChar BFTerm::getChar()
{
    wxChar c=inputbuffer.front();
    inputbuffer.pop();
    return c;
}

bool BFTerm::empty() const
{
    return inputbuffer.empty();
}
