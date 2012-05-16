#ifndef BF_INTERPRETER_THREAD_H
#define BF_INTERPRETER_THREAD_H

class bf_interpreter_thread;

#include <wx/thread.h>
#include <iostream>
#include <stack>
#include "wx/string.h"
#include "bf_vm.h"
#include "breakpoint_lister.h"
#include "BFTerm.h"
#include "IDEFrame.h"

class IDEFrame;

enum runmode_type {stopped,running,stepped,continued};

typedef struct {
    const wxChar* location;
    unsigned int num_newlines;
} brace_entry;
class bf_interpreter_thread : public wxThread
{
    public:
        bf_interpreter_thread(wxEvtHandler*, breakpoint_lister*, wxMutex*,wxCondition*, BFTerm*,const wxString,bf_vm*);
        virtual ~bf_interpreter_thread();
        virtual wxThread::ExitCode Entry();
        void processStep();
        void reset(const wxChar*);
        void SetRunmode(runmode_type);
        int getProgramIndex();
    protected:
    wxEvtHandler* evt;
    wxMutex* mutex;
    wxCondition* unpaused_condition;
    runmode_type runmode;
    bool skip_comments();
    void skip_to_corresponding_brace();
    bf_vm * vm;
    wxString program;
    const wxChar * program_index;
    BFTerm* term;
    std::stack<brace_entry> opening_braces;
    breakpoint_lister * breakpoints;
    unsigned int linenumber;
    unsigned int lines_since_last_brace;
};

#endif // BF_INTERPRETER_THREAD_H
