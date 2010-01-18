#include "bf_interpreter_thread.h"

bf_interpreter_thread::bf_interpreter_thread(bf_ideFrame *b):wxThread(wxTHREAD_DETACHED) {
    out=new ostream(b->OutputBox);
    in=new istream(b->InputBox);
}

bf_interpreter_thread::~bf_interpreter_thread() {
}

wxThread::ExitCode bf_interpreter_thread::Entry() {
    frame->prep_running();

    while (true) {

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
            opening_braces.push(program_index);
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
    }
    program_index++;
}
void bf_interpreter_thread::skip_to_corresponding_brace() { //assumes program_index points to a '[' finishes pointing to the char after ']'
    unsigned int num_braces=0;
    do {
        if (*program_index=='[') {
            num_braces++;
        } else if (*program_index==']') {
            num_braces--;
        }
        program_index++;
    } while (num_braces!=0);
}

