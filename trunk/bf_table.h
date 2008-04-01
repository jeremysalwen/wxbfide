#ifndef BF_TABLE_H
#define BF_TABLE_H
#include <wx/grid.h>
#include "bf_tableBase.h"

class bf_table:public wxGrid {
public:
    bf_table(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxWANTS_CHARS, const wxString& name = wxPanelNameStr);
    virtual ~bf_table();
    virtual bf_tableBase * GetTable();
    virtual void SetTable(wxGridTableBase*,bool takeOwnership=false, wxGridSelectionModes selMode=wxGridSelectCells);
protected:
private:
};

#endif // BF_TABLE_H
