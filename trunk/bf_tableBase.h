#ifndef BF_TABLEBASE_H
#define BF_TABLEBASE_H

#include <wx/grid.h>
#include <algorithm>
#include <typeinfo>
#include "bf_vm.h"
#include "IDEFrame.h"

class bf_tableBase : public wxGridTableBase, public bf_vm {
    unsigned char *data;
    unsigned int bf_ptr;
public:
    bf_tableBase(bf_table* p);
    virtual ~bf_tableBase();
    int GetNumberRows();
    int GetNumberCols();
    bool IsEmptyCell(int,int);
    wxString GetValue(int,int);
    void SetValue(int, int, const wxString&);
    virtual void reset_values();
    virtual void inc_cell();
    virtual void dec_cell();
    virtual void set_cell(unsigned char);
    virtual unsigned char get_cell();
    virtual void inc_ptr();
    virtual void dec_ptr();
    virtual unsigned int get_ptr();
    virtual void set_ptr(unsigned int);
protected:
private:
    void update_ptr();
    void update_gui();
    bf_table * parent;
    bool bounds_check(int i);
};

#endif // BF_TABLEBASE_H
