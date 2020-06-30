
main:	la 	$t0, a	
	lw 	$t1, 0($t0)  
	
	la 	$t2, b	
	lw 	$t3, 0($t2) 
	
	
	la	$t4, v_xor
	lw	$t5, 0($t4)
	xor	$t5, $t1, $t3
	sw	$t5, 0($t4)
	
	la	$t4, v_sll
	lw	$t5, 0($t4)
	sll	$t5, $t1, 2
	sw	$t5, 0($t4)
	
	la	$t4, v_srl
	lw	$t5, 0($t4)
	srl	$t5, $t3, 1
	sw	$t5, 0($t4)
	
	la	$t4, v_slt
	lw	$t5, 0($t4)
	slt	$t5, $t1, $t3
	sw	$t5, 0($t4)
	
	la	$t4, v_addu
	lw	$t5, 0($t4)
	addu	$t5, $t1, $t3
	sw	$t5, 0($t4)
	
	la	$t4, v_andi
	lw	$t5, 0($t4)
	andi	$t5, $t1, 0x23
	sw	$t5, 0($t4)
.data
a: .word 0x67
b: .word 0x25
v_xor: .word 0
v_sll: .word 0
v_srl: .word 0
v_slt: .word 0
v_addu: .word 0
v_andi: .word 0