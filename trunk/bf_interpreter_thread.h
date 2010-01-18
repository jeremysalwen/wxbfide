#ifndef BF_INTERPRETER_THREAD_H
#define BF_INTERPRETER_THREAD_H

class bf_interpreter_thread;

#include <wx/thread.h>
#include <iostream>
#include <stack>
#include "NewFrame.h"
#include "wx/string.h"
#include "bf_vm.h"

enum runmode_type {stopped,running,debugging,paused,stepped};

typedef struct {
    wxChar* location;
    unsigned int num_newlines;
} brace_entry;
class bf_interpreter_thread : public wxThread
{
    public:
        bf_interpreter_thread(std::istream*,std::ostream*,const wxString,bf_vm*);
        virtual ~bf_interpreter_thread();
        virtual wxThread::ExitCode Entry();
        void processStep();
        wxMutex mutex;
        wxCondition unpaused_condition;
        runmode_type runmode;
        void reset(std::istream*, std::ostream*, const wxChar*);
    protected:
    void skip_to_corresponding_brace();
    bf_vm * vm;
    wxString program;
    const wxChar * program_index;
    std::istream* in;
    std::ostream* out;
    std::stack<brace_entry> opening_braces;
    unsigned int linenumber;
    unsigned int lines_since_last_brace;
};

#endif // BF_INTERPRETER_THREAD_H
