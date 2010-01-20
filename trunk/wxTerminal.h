#ifndef WXTERMINAL_H_INCLUDED
#define WXTERMINAL_H_INCLUDED

#include <sstream>
#include <wx/textctrl.h>
#include <wx/clipbrd.h>
#include <wx/dataobj.h>

class wxTerminal:public wxTextCtrl {
public:
    wxTerminal(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name);
    ~wxTerminal();
    void OnKeyPressed(wxKeyEvent& event);
    void OnTextPaste(wxClipboardTextEvent& event);
    void OnTextCut(wxClipboardTextEvent& event);
    void Clear();
    void ClearExcess();
    std::stringstream * output;
    std::ostream* input;
protected:
    DECLARE_EVENT_TABLE()
};


#endif // WXTERMINAL_H_INCLUDED
