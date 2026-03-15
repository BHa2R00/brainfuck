#include <stdio.h>
#include <string.h>
char i, d[0x10000];
int dp = 0;
FILE* ip;
void inc() { d[dp]++; }
void dec() { d[dp]--; }
void mvr() { dp++; }
void mvl() { dp--; }
void jne() { if(!d[dp]) {int k=1; while(k) { i=fgetc(ip); if(i=='[') k++; if(i==']') k--; } } }
void jeq() { if(d[dp]) {int k=1; fseek(ip,-2,SEEK_CUR); while(k) { i=fgetc(ip); if(i==']') k++; if(i=='[') k--; if(k) fseek(ip,-2,SEEK_CUR); } } }
void put() { fputc(d[dp],stdout); }
void get() { d[dp]=fgetc(stdin); }
typedef void (*cmd_t)(void);
const cmd_t cmd[128] = { ['+']=inc,['-']=dec,['>']=mvr,['<']=mvl,['[']=jne,[']']=jeq,['.']=put,[',']=get, };
int main(int argc, char** argv) { 
  if(argc < 2) { printf("%s <input bf>\n", argv[0]); return 1; }
  if(!(ip=fopen(argv[1], "r"))) return 1;
  memset(d,0,sizeof(d)); while((i=fgetc(ip))!=EOF) if(cmd[i]) cmd[i]();
  return 0;
}
// brainfuck interpreter
// cc -O4 bfi.c -o bfi 
