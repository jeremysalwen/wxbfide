#ifndef BF_TABLE_H
#define BF_TABLE_H
#include <wx/grid.h>
#include "IDEFrame.h"
wxDECLARE_EVENT(RepaintEvent, wxCommandEvent);
wxDECLARE_EVENT(PtrMoveEvent, wxCommandEvent);

class bf_table:public wxGrid {
public:
    bf_table(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxWANTS_CHARS, const wxString& name = wxPanelNameStr);
    virtual ~bf_table();

    void OnRepaint(wxCommandEvent& evt);
protected:
private:
    void OnPtrMove(wxCommandEvent& evt);
wxDECLARE_EVENT_TABLE();
};

#endif // BF_TABLE_H
