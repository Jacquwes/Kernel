.macro isr_error_stub num
isr_stub_\num:
	call exception_handler
	iret
.endm

.macro isr_no_error_stub num
isr_stub_\num:
	call exception_handler
	iret
.endm

.altmacro

.macro isr_insert number
	.long isr_stub_\number
.endm

.global exception_handler
isr_no_error_stub 0
isr_no_error_stub 1
isr_no_error_stub 2
isr_no_error_stub 3
isr_no_error_stub 4
isr_no_error_stub 5
isr_no_error_stub 6
isr_no_error_stub 7
isr_error_stub    8
isr_no_error_stub 9
isr_error_stub    10
isr_error_stub    11
isr_error_stub    12
isr_error_stub    13
isr_error_stub    14
isr_no_error_stub 15
isr_no_error_stub 16
isr_error_stub    17
isr_no_error_stub 18
isr_no_error_stub 19
isr_no_error_stub 20
isr_no_error_stub 21
isr_no_error_stub 22
isr_no_error_stub 23
isr_no_error_stub 24
isr_no_error_stub 25
isr_no_error_stub 26
isr_no_error_stub 27
isr_no_error_stub 28
isr_no_error_stub 29
isr_error_stub    30
isr_no_error_stub 31

.global isr_stub_table
isr_stub_table:
.set i,0
.rept 32
	isr_insert %i
	.set i, i+1
.endr
