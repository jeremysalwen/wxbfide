 /*
  *  WxBfIDE - A cross-platform brainfuck IDE
  *  Copyright (C) 2008-2012  Jeremy Salwen
  *
  *  This program is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

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
