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
