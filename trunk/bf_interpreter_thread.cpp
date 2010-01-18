#include "bf_interpreter_thread.h"

bf_interpreter_thread::bf_interpreter_thread(std::istream* in,std::ostream* out,const wxString prog, bf_vm * vm):wxThread(wxTHREAD_DETACHED),unpaused_condition(mutex) {
    this->out=out;
    this->in=in;
    this->program=prog;
    program_index=program.c_str();
    this->vm=vm;
    linenumber=1;
    runmode=stopped;
    Create();
}

bf_interpreter_thread::~bf_interpreter_thread() {
    delete in;
    delete out;
}

wxThread::ExitCode bf_interpreter_thread::Entry() {
    while (true) {
        mutex.Lock();
        switch(runmode) {
            case stepped:
                processStep();
                runmode=paused;
                unpaused_condition.Wait();
                break;
            case running:
                processStep();
                break;
            case debugging:
                processStep();
                break;
            case stopped:
            case paused:
                unpaused_condition.Wait();
            break;
        }
        if(!*program) {
            std::cout<<"error!"<<std::endl;
        }
        mutex.Unlock();
    }
}


void bf_interpreter_thread::processStep() {
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
        vm->set_cell(in->get());
        break;
    case '.':
        *out << vm->get_cell();
        break;
    case '[':
        if (vm->get_cell()) {
            opening_braces.push({program_index,lines_since_last_brace});
            lines_since_last_brace=0;
        } else {
            skip_to_corresponding_brace();
        }
        break;
    case ']':
        if (vm->get_cell()) {
            program_index=opening_braces.top();
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
        switch(*program_index) {
            case '[':
            num_braces++;
            break;
        case ']':
            num_braces--;
            break;
        case '\n':
            lines_since_last_brace++;
            linenumber++;
            break;
        }
        program_index++;
    } while (num_braces!=0);
}
void bf_interpreter_thread::reset(std::istream* i, std::ostream* o, const wxChar* prog) {
    mutex.Lock();
    delete in;
    in=i;
    delete out;
    out=o;
    delete program;
    program=prog;
    linenumber=1;
    runmode=stopped;
    mutex.Unlock();
}
