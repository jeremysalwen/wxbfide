#ifndef BF_INTERPRETER_THREAD_H
#define BF_INTERPRETER_THREAD_H

class bf_interpreter_thread;

#include <wx/thread.h>
#include <iostream>
#include <stack>
#include "bf_ideMain.h"
#include "wx/string.h"
#include "bf_vm.h"


class bf_interpreter_thread : public wxThread
{
    public:
        bf_interpreter_thread(bf_ideFrame*);
        virtual ~bf_interpreter_thread();
        virtual wxThread::ExitCode Entry();
        void processStep();
    protected:
    void skip_to_corresponding_brace();
    bf_vm * vm;
    const wxChar * program;
    const wxChar * program_index;
    std::istream * in;
    std::ostream * out;
    std::stack<const wxChar*> opening_braces;
    bf_ideFrame *frame;
};

#endif // BF_INTERPRETER_THREAD_H
