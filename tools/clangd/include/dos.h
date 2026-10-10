/* clangd shim: BCC's dos.h, with FP_OFF/FP_SEG usable as lvalues (BCC allows assigning to them). */
#include_next <dos.h>
#undef FP_OFF
#undef FP_SEG
#define FP_OFF(fp) (((unsigned *)&(fp))[0])
#define FP_SEG(fp) (((unsigned *)&(fp))[1])
