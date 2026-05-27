	.file	"sender.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "127.0.0.1\0"
LC1:
	.ascii "Enter message: \0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB25:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$1476, %esp
	call	___main
	leal	-412(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$514, (%esp)
	call	_WSAStartup@8
	subl	$8, %esp
	movl	$0, 8(%esp)
	movl	$1, 4(%esp)
	movl	$2, (%esp)
	call	_socket@12
	subl	$12, %esp
	movl	%eax, -12(%ebp)
	movw	$2, -428(%ebp)
	movl	$LC0, (%esp)
	call	_inet_addr@4
	subl	$4, %esp
	movl	%eax, -424(%ebp)
	movl	$8080, (%esp)
	call	_htons@4
	subl	$4, %esp
	movw	%ax, -426(%ebp)
	movl	$16, 8(%esp)
	leal	-428(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_connect@12
	subl	$12, %esp
L2:
	movl	$LC1, (%esp)
	call	_printf
	movl	__imp___iob, %eax
	movl	%eax, 8(%esp)
	movl	$1024, 4(%esp)
	leal	-1452(%ebp), %eax
	movl	%eax, (%esp)
	call	_fgets
	leal	-1452(%ebp), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	$0, 12(%esp)
	movl	%eax, 8(%esp)
	leal	-1452(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_send@16
	subl	$16, %esp
	jmp	L2
	.cfi_endproc
LFE25:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_WSAStartup@8;	.scl	2;	.type	32;	.endef
	.def	_socket@12;	.scl	2;	.type	32;	.endef
	.def	_inet_addr@4;	.scl	2;	.type	32;	.endef
	.def	_htons@4;	.scl	2;	.type	32;	.endef
	.def	_connect@12;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_fgets;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_send@16;	.scl	2;	.type	32;	.endef
