.section ".text.boot"

.globl _start

_start: 
	mrc p15, #0, r1, c0, c0, #5
