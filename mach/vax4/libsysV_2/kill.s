.sect .text; .sect .rom; .sect .data; .sect .bss
.sect .text
kill = 37
.define	_kill

_kill:
	.data2	0x0000
	chmk	$kill
	bcc 	1f
	jmp 	cerror
1:
	clrl	r0
	ret
