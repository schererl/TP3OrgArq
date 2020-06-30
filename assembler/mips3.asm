
main:	la 	$t3, a	# $t3 é escrito com o valor do endereço da variável a
	lw 	$t0, 0($t3)  # $t0 é escrito com o conteúdo da variável a
	
	la 	$t2, b	# $t2 é escrito com o valor do endereço da variável b
	lw 	$t1, 0($t2)  # $t1 é escrito com o conteúdo da variável b
	
	la	$t6, c
	
	
	andi   $t4, $t0, 4
	andi   $t5, $t1, 3
	sw     $t4, 0($t3)	# armazena o conteúdo do regsitrador na posição de memória da variável b
	sw     $t5, 0($t2)		
	sll    $t5, $t5, 2
	srl    $t5, $t5, 1 
	sw     $t5, 0($t6)
	
.data
a: .word 5
b: .word 0xa
c: .word 0
