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
    for(int i=0; i<str.size(); i++)
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
