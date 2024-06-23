#include<printf.h>
#include<scanf.h>
#include<syscall.h>

/* Input & output functions */
int getch() {
    char c;
    scanf("%c", &c);
    return c;
}
int getint() {
    int num = 0;
    scanf("%d", &num);
    return num;
}
int getarray(int a[]){
  int n = getint();
  for(int i=0;i<n;i++) a[i] = getint();
  return n;
}

void putint(int a){ printf("%d",a);}
void putch(int a){ printf("%c",a); }
void putarray(int n,int a[]){
  printf("%d:",n);
  for(int i=0;i<n;i++)printf(" %d",a[i]);
  printf("\n");
}

void putf(char a[], ...) {
    va_list args;
    va_start(args, a);
    vprintf(a, args);
    va_end(args);
}

