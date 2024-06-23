#include <stdarg.h>
#include <syscall.h>
#include <printf.h>

#define BUFLEN 256
#define stdin  0
#define EOF    255

struct readbuf {
    char data[BUFLEN];
    unsigned int next;
};
static struct readbuf buf = {
    .next = BUFLEN,
};

static int isspace(char c) {
    if (c == ' ') return 1;
    if (c == '\t') return 1;
    if (c == '\n') return 1;
    return 0;
}

static int getc(void) {
    int nrread;
    if (buf.next == BUFLEN) {
        nrread = read(stdin, buf.data, BUFLEN);
        if (nrread < BUFLEN) {
            buf.data[nrread] = EOF;
        }
        buf.next = 0;
    }
    return buf.data[buf.next++] & 0xff;
}

static void ungetc(int num) {
    if (buf.next - num >= 0) {
        buf.next -= num;
        return;
    }
    printf("can not ungetc\n");
    exit(-1);
}

static char eat_white(int *nrchar) {
  int old = *nrchar;
  char c;
  do{
    ++*nrchar;
    c = getc();
  }
  while(isspace(c));
  --*nrchar;
  ungetc(1);
  return c;
}

#define INC()  (++nrchar,getc())
#define DEC(n) (nrchar -= n,ungetc(n))
#define EAT()  eat_white(&nrchar)

static int c2i(char c, int base) {
    int num;
    if (c >= '0' && c <= '9') {
        num = c - '0';
    }
    else if (c >= 'a' && c <= 'f') {
        num = c + 10 - 'a';
    }
    else if (c >= 'A' && c <= 'F') {
        num = c + 10 - 'A';
    }
    else {
        num = -1;
    }

    if (num < base) {
        return num;
    }
    return -1;
}

static int getint(int *xx, int base, int sgn) {
  int nrchar, neg, num;
  nrchar = 0;

  EAT();

  neg = 0;
  if(sgn){
    while(INC() == '-'){
      neg = neg ^ 1;
    }
    DEC(1);
  }

  int tmp = c2i(INC(), base);
  if(tmp < 0){
    DEC(nrchar);
  }
  else {
    num = 0;
    while(tmp >= 0){
      num = num * base + tmp;
      tmp = c2i(INC(), base);
    }
    DEC(1);

    if (neg) num = -num;
    *xx = num;
  }
  return nrchar;
}

int
vscanf(const char *fmt, va_list ap)
{
  int nrchar, getnrchar;

  char *s;
  int get, c, i, state;

  nrchar = 0;
  state = 0;
  for(i = 0; fmt[i]; i++){
    c = fmt[i] & 0xff;

    if(state == 0){
      if(isspace(c)){
        EAT();
        do{
          c = fmt[++i] & 0xff;
        }
        while(isspace(c));
      }

      if(!c) break;
      get = INC();DEC(1);
      if(EOF == get){
        nrchar = EOF;
        break;
      }

      if(c == '%'){
        state = '%';
        continue;
      }
      get = INC();
      if(c == get){
        continue;
      }
      DEC(1);
      break;
    }

    if(c == 'd'){
      nrchar += getnrchar = getint(va_arg(ap, int *), 10, 1);
      if(!getnrchar){
        break;
      }
    } else if(c == 'x'){
      nrchar += getnrchar = getint(va_arg(ap, int *), 16, 0);
      if(!getnrchar){
        break;
      }
    } else if(c == 's'){
      s = va_arg(ap, char*);
      if(s == 0){
        printf("scanf to nullptr");
        exit(-1);
      }
      EAT();
      while(!isspace(get = INC())){
        if(get == EOF){
          break;
        }
        *s++ = get;
      }
      DEC(1);
      *s = '\0';
    } else if(c == 'c'){
      s = va_arg(ap, char *);
      if(s == 0){
        printf("scanf to nullptr");
        exit(-1);
      }
      get = INC();
      if(EOF == get){
        nrchar = EOF;
        DEC(1);
        break;
      }
      *s = get;
    } else if(c == '%'){
      get = INC();
      if(EOF == get){
        nrchar = EOF;
        DEC(1);
        break;
      }
      if('%' != get){
        DEC(1);
        break;
      }
    } else {
      break;
    }
    state = 0;
  }
  return nrchar;
}

int
scanf(const char *fmt, ...)
{
  va_list ap;
  int ret;

  va_start(ap, fmt);
  ret = vscanf(fmt, ap);
  va_end(ap);
  return ret;
}
