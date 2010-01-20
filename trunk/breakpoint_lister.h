#ifndef BREAKPOINT_LISTER_H_INCLUDED
#define BREAKPOINT_LISTER_H_INCLUDED

class breakpoint_lister {
    public:
        virtual bool HasBreakpoint(unsigned int line)=0;
};

#endif // BREAKPOINT_LISTER_H_INCLUDED
