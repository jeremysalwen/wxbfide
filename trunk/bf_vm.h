#ifndef BF_INTERPRETER_H_INCLUDED
#define BF_INTERPRETER_H_INCLUDED

class bf_vm {
    public:
        virtual void reset_values()=0;
        virtual void inc_cell()=0;
        virtual void dec_cell()=0;
        virtual void set_cell(unsigned char)=0;
        virtual unsigned char get_cell()=0;
        virtual void inc_ptr()=0;
        virtual void dec_ptr()=0;
        virtual unsigned int get_ptr()=0;
        virtual void set_ptr(unsigned int)=0;
    protected:
        bf_vm(){};
};


#endif // BF_INTERPRETER_H_INCLUDED
