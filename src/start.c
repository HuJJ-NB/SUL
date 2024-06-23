#include <syscall.h>

int main();

void _start() {
    exit(main());
}
