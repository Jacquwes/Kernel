.set ALIGN, 1
.set MEMINFO, 2
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
	push %eax
	push %ebx
	call _init
	call main
	cli
1:	hlt
	jmp 1b

.section .bss
