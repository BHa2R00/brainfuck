#include <stdio.h>
#include <stdlib.h>

const char ramp[]=" .:-=+*#%@";
const int ramp_len = 10;
int linecount=0;

void putc1(char a) 
{
  if(linecount++ % 80 == 0) fputc('\n',stdout); 
  fputc(a,stdout); 
}

void putc2bf(int t, int* c) 
{
  int d = t - *c;
  if(d > 0) while(d--) putc1('+');
  else if(d < 0) { d = -d; while(d--) putc1('-'); }
  putc1('.');
  *c = t;
}

int main(int argc, char** argv)
{
  if(argc<3) { printf("%s <width> <height>\n", argv[0]); return 1; }
  int w = atoi(argv[1]);
  int h = atoi(argv[2]);
  int row_size = ((w * 3 + 3) & ~3);
  int frame_size = 54 + (row_size * h);
  unsigned char* data = malloc(frame_size);
  int c = 0;
  while(fread(data, 1, frame_size, stdin) == (size_t)frame_size) { 
    putc2bf(27, &c);
    putc2bf('[', &c);
    putc2bf('H', &c);
    for(int y=h-1; y >= 0; y--){
      unsigned char *row = data + 54 + (y * row_size);
      for(int x = 0; x < w; x++){
        int b = row[x * 3];
        int g = row[x * 3 + 1];
        int r = row[x * 3 + 2];
        int a = (r + g + b) / 3;
        putc2bf(ramp[(a * (ramp_len - 1)) / 255], &c);
      }
      putc2bf('\n', &c);
    }
  }
  free(data);
  return 0;
}
