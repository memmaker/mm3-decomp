/* clangd shim: lets clang parse Borland C++ 2.0 sources for navigation/renaming only (never used to build). */
#define far
#define near
#define huge
#define cdecl
#define pascal
#define interrupt
#define _Cdecl
#define _FAR
#define __MEDIUM__ 1
#define __TURBOC__ 0x0297
#define __BORLANDC__ 0x0200
#define __MSDOS__ 1
extern unsigned _AX, _BX, _CX, _DX, _SI, _DI, _DS, _ES, _SP, _BP, _FLAGS;
extern unsigned char _AL, _AH, _BL, _BH, _CL, _CH, _DL, _DH;
void __emit__();
