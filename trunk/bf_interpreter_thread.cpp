#include "bf_interpreter_thread.h"

bf_interpreter_thread::bf_interpreter_thread(std::istream* in,std::ostream* out,const wxString prog, bf_vm * vm,breakpoint_lister* lister):wxThread(wxTHREAD_DETACHED),unpaused_condition(mutex) {
    this->out=out;
    this->in=in;
    this->program=prog;
    program_index=program.c_str();
    this->vm=vm;
    this->breakpoints=lister;
    linenumber=1;
    runmode=stopped;
    Create();
}

bf_interpreter_thread::~bf_interpreter_thread() {
    //Don't manage streams.
}

wxThread::ExitCode bf_interpreter_thread::Entry() {
    while (true) {
        mutex.Lock();

        if (!*program_index) {
            runmode=stopped;
        }
        switch (runmode) {
        case stepped:
            processStep();
            runmode=paused;
            unpaused_condition.Wait();
            break;
        case running:
            if (breakpoints->HasBreakpoint(linenumber)) {
                runmode=paused;
            } else {
                processStep();
            }
            break;
        case stopped:
        case paused:
            unpaused_condition.Wait();
            break;
        }

        mutex.Unlock();
    }
    return 0;
}


void bf_interpreter_thread::processStep() {
    brace_entry b;
    int c;
    switch (*program_index) {
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
        c=in->get();
        std::cout << c<<std::endl;
        vm->set_cell(in->get());
        break;
    case '.':
        *out << vm->get_cell();
        break;
    case '[':
        if (vm->get_cell()) {
            b.location=program_index;
            b.num_newlines=lines_since_last_brace;
            opening_braces.push(b);
            lines_since_last_brace=0;
        } else {
            skip_to_corresponding_brace();
        }
        break;
    case ']':
        b=opening_braces.top();
        if (vm->get_cell()) {
            program_index=b.location-1;//This is so that the increment will cause it to line up.
            linenumber-=b.num_newlines;
            lines_since_last_brace=0;
        } else {
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

void bf_interpreter_thread::skip_to_corresponding_brace() { //assumes program_index points to a '[' finishes pointing to the char after ']'
    unsigned int num_braces=0;
    do {
        switch (*program_index) {
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
    } while (num_braces!=0);
}

void bf_interpreter_thread::reset(const wxChar* prog) {
    mutex.Lock();
    vm->reset_values();
    program=prog;
    program_index=program.c_str();
    linenumber=1;
    runmode=stopped;
    mutex.Unlock();
}

void bf_interpreter_thread::SetRunmode(runmode_type mode) {
   mutex.Lock();
runmode=mode;
   unpaused_condition.Broadcast();
mutex.Unlock();
}
