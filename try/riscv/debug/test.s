	.file	"test.c"
	.option pic
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"%d,%d"
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	sw	zero,-24(s0)
	li	a5,1
	sw	a5,-20(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	mv	a2,a4
	mv	a1,a5
	lla	a0,.LC0
	call	printf@plt
	li	a5,0
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits