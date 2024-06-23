	.file "syscall.s"
	.text
	.align 2
	.globl	write
	.type	write, @function
write:
	li a7, 64
	ecall
	ret
	.globl	read
	.type	read, @function
read:
	li a7, 63
	ecall
	ret
	.globl	exit
	.type	exit, @function
exit:
	li a7, 93
	ecall
	ret
