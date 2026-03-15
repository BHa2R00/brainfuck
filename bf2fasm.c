#include <stdio.h>
int s[0x10000];
int l=0, sp=0;
void inc() { printf("inc byte [ebx]\n"); }
void dec() { printf("dec byte [ebx]\n"); }
void mvr() { printf("inc ebx\n"); }
void mvl() { printf("dec ebx\n"); }
void jne() { s[sp++]=l++; printf("L%d:\ncmp byte [ebx], 0\nje E%d\n", s[sp-1], s[sp-1]); }
void jeq() { printf("jmp L%d\nE%d:\n", s[sp-1], s[sp-1]); sp--; }
void put() { printf("mov eax, 4\nmov ecx, ebx\nmov edx, 1\nmov ebx, 1\nint 0x80\nmov ebx, ecx\n"); }
void get() { printf("mov eax, 3\nmov ecx, ebx\nmov edx, 1\nmov ebx, 0\nint 0x80\nmov ebx, ecx\n"); }
typedef void (*cmd_t)(void);
const cmd_t cmd[128] = { ['+']=inc,['-']=dec,['>']=mvr,['<']=mvl,['[']=jne,[']']=jeq,['.']=put,[',']=get, };
void conv() { char c; do { c=fgetc(stdin); if(cmd[c]) cmd[c](); } while(c!=EOF); }
void main() { printf("format ELF executable 3\nentry start\n\nsegment readable executable\nstart:\nmov ebx, data_ptr\n"); conv(); printf("mov eax, 1\nxor ebx, ebx\nint 0x80\n\nsegment readable writeable\ndata_ptr rb 0x10000\n"); }
// brainfuck to FASM
// cc bf2fasm.c -o bf2fasm 
