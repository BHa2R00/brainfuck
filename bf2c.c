#include <stdio.h>
void inc() { printf("++*p; "); }
void dec() { printf("--*p; "); }
void mvr() { printf("++p; "); }
void mvl() { printf("--p; "); }
void jne() { printf("while(*p){ "); }
void jeq() { printf("} "); }
void put() { printf("putchar(*p); "); }
void get() { printf("*p=getchar(); "); }
typedef void (*cmd_t)(void);
const cmd_t cmd[128] = { ['+']=inc,['-']=dec,['>']=mvr,['<']=mvl,['[']=jne,[']']=jeq,['.']=put,[',']=get, };
void conv() { char c; do { c=fgetc(stdin); if(cmd[c]) cmd[c](); } while(c!=EOF); }
void main() { printf("#include<stdio.h>\nint main(){ char d[0x10000]; char* p=d; "); conv(); printf(" return 0; }"); }
// brainfuck to c
// cc bf2c.c -o bf2c 
