#ifndef __SYLIB_H_
#define __SYLIB_H_

#include<stdarg.h>

/* Input & output functions */
int getint(),getch(),getarray(int a[]);
void putint(int a),putch(int a),putarray(int n,int a[]);
void putf(char a[], ...);

#endif
