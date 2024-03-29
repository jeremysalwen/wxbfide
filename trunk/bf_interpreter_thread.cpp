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

#include "bf_interpreter_thread.h"

bf_interpreter_thread::bf_interpreter_thread(wxEvtHandler* events,breakpoint_lister* lister, wxMutex* m, wxCondition* c, BFTerm* term,const wxString prog, bf_vm * vm):wxThread(wxTHREAD_DETACHED),evt(events),breakpoints(lister),mutex(m),unpaused_condition(c)
{
    this->term=term;
    this->program=prog;
    program_index=program.c_str();
    this->vm=vm;
    linenumber=1;
    runmode=stopped;
    Create();
}

bf_interpreter_thread::~bf_interpreter_thread()
{

}

bool bf_interpreter_thread::skip_comments()
{
    while(true)
    {
        switch(*program_index)
        {
        case '+':
        case '-':
        case '<':
        case '>':
        case ',':
        case '.':
        case '[':
        case ']':
            return true;
        case '\0':
            return false;
        }
        program_index++;
    }
}
wxThread::ExitCode bf_interpreter_thread::Entry()
{
    while (true)
    {
        runmode_type tmp;
        bool finished=false;
        {
            wxMutexLocker l(*mutex);
            if (!*program_index)
            {
                runmode=stopped;
                finished=true;
            }
            tmp=runmode;
        }
        if(finished)
        {
            wxCommandEvent e(EVT_VM_FINISHED,wxID_ANY);
            evt->AddPendingEvent(e);
        }
        switch (tmp)
        {
        case stepped:
            processStep();
            if(skip_comments())
            {
                {
                    wxCommandEvent ev(EVT_VM_BREAKPOINTED,wxID_ANY);
                    ev.SetInt(getProgramIndex());
                    evt->AddPendingEvent(ev);
                }

                {
                    wxMutexLocker l(*mutex);

                    runmode=stopped;
                    unpaused_condition->Wait();
                }
            }
            else
            {
                {
                    wxCommandEvent ev(EVT_VM_FINISHED,wxID_ANY);
                    evt->AddPendingEvent(ev);
                }
                {
                    wxMutexLocker l(*mutex);

                    runmode=stopped;
                    unpaused_condition->Wait();
                }
            }
            break;
        case running:
            if (breakpoints->HasBreakpoint(linenumber))
            {
                {
                    wxMutexLocker l(*mutex);
                    runmode=stopped;
                }
                if(skip_comments())
                {
                    wxCommandEvent e(EVT_VM_BREAKPOINTED,wxID_ANY);
                    e.SetInt(getProgramIndex());
                    evt->AddPendingEvent(e);
                }
                else
                {
                    wxCommandEvent e(EVT_VM_FINISHED,wxID_ANY);
                    evt->AddPendingEvent(e);
                }
            }
            else
            {
                processStep();
            }
            break;
        case continued:
            processStep();
            {
                wxMutexLocker l(*mutex);
                runmode=running;
            }
            break;
        case stopped:
            if(skip_comments())
            {
                wxCommandEvent e(EVT_VM_BREAKPOINTED,wxID_ANY);
                e.SetInt(getProgramIndex());
                evt->AddPendingEvent(e);
            }
            else
            {
                wxCommandEvent e(EVT_VM_FINISHED,wxID_ANY);
                evt->AddPendingEvent(e);
            }
            {
                wxMutexLocker l(*mutex);
                unpaused_condition->Wait();
                break;
            }
        }
    }
    return 0;
}


void bf_interpreter_thread::processStep()
{
    brace_entry b;
    switch (*program_index)
    {
    case '+':
        vm->inc_cell();
        break;
    case '-':
        vm->dec_cell();
        break;
    case '>':
        vm->inc_ptr();
        break;
    case '<':
        vm->dec_ptr();
        break;
    case ',':
        unsigned char c;
        {
            wxMutexLocker l(*mutex);
            while(term->empty())
            {
                if(runmode==stopped)
                {
                    return;
                }
                unpaused_condition->Wait();
            }
            c=term->getChar();
        }
        std::cout << c<<std::endl;
        vm->set_cell(c);
        break;
    case '.':
        term->DisplayChars(wxString((char)vm->get_cell()));
        break;
    case '[':
        if (vm->get_cell())
        {
            b.location=program_index;
            b.num_newlines=lines_since_last_brace;
            opening_braces.push(b);
            lines_since_last_brace=0;
        }
        else
        {
            skip_to_corresponding_brace();
        }
        break;
    case ']':
        b=opening_braces.top();
        if (vm->get_cell())
        {
            program_index=b.location-1;//This is so that the increment will cause it to line up.
            linenumber-=b.num_newlines;
            lines_since_last_brace=0;
        }
        else
        {
            lines_since_last_brace+=b.num_newlines;
        }
        opening_braces.pop();
        break;
    case '\n':
        linenumber++;
        lines_since_last_brace++;
        break;
    }
    program_index++;
}

void bf_interpreter_thread::skip_to_corresponding_brace()   //assumes program_index points to a '[' finishes pointing to the char after ']'
{
    unsigned int num_braces=0;
    do
    {
        switch (*program_index)
        {
        case '[':
            num_braces++;
            break;
        case ']':
            num_braces--;
            break;
        case '\n':
            linenumber++;
            lines_since_last_brace++;
            break;
        }
        program_index++;
    }
    while (num_braces!=0);
}

void bf_interpreter_thread::reset(const wxChar* prog)
{
    wxMutexLocker l(*mutex);
    vm->reset_values();
    program=prog;
    program_index=program.c_str();
    linenumber=0;
    runmode=stopped;
}

void bf_interpreter_thread::SetRunmode(runmode_type mode)
{
    wxMutexLocker l(*mutex);
    runmode=mode;
    unpaused_condition->Broadcast();
}
int bf_interpreter_thread::getProgramIndex()
{
    return program_index-program.c_str();
}
