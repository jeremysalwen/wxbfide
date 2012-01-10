#ifndef BF_TABLE_H
#define BF_TABLE_H
#include <wx/grid.h>

const wxEventType PtrMoveEvent = wxNewEventType();
const wxEventType RepaintEvent = wxNewEventType();

class bf_table:public wxGrid {
public:
    bf_table(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxWANTS_CHARS, const wxString& name = wxPanelNameStr);
    virtual ~bf_table();
protected:
private:
    void OnPtrMove(wxCommandEvent& evt);
    void OnRepaint(wxCommandEvent& evt);
wxDECLARE_EVENT_TABLE();
};

#endif // BF_TABLE_H
