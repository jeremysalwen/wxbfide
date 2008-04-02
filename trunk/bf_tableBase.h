#ifndef BF_TABLEBASE_H
#define BF_TABLEBASE_H

#include <wx/grid.h>
#include <algorithm>
#include <typeinfo>

class bf_tableBase : public wxGridTableBase {
     unsigned char *data;
public:
    unsigned char get_data(int index);
    void set_data(int index, unsigned char value);
    bf_tableBase();
    virtual ~bf_tableBase();
    int GetNumberRows();
    int GetNumberCols();
    bool IsEmptyCell(int,int);
    wxString GetValue(int,int);
    void SetValue(int, int, const wxString&);
    void reset_values();
    void inc_cell(int);
    void dec_cell(int);
    void set_cell(int,unsigned char);
    unsigned char get_cell(int);
protected:
private:
    bool bounds_check(int i);
};

#endif // BF_TABLEBASE_H
