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

enum runmode_type {stopped,running,paused,stepped};

typedef struct {
    const wxChar* location;
    unsigned int num_newlines;
} brace_entry;
class bf_interpreter_thread : public wxThread
{
    public:
        bf_interpreter_thread(wxMutex* mutex, wxCondition* cond, BFTerm* term,const wxString,bf_vm*, breakpoint_lister*);
        virtual ~bf_interpreter_thread();
        virtual wxThread::ExitCode Entry();
        void processStep();
        void reset(const wxChar*);
        void SetRunmode(runmode_type);
    protected:
    wxMutex* mutex;
    wxCondition* unpaused_condition;
        runmode_type runmode;
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
