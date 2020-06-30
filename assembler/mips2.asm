
main:	la 	$t3, a	# $t3 é escrito com o valor do endereço da variável a
	lw 	$t0, 0($t3)  # $t0 é escrito com o conteúdo da variável a
	
	la 	$t2, b	# $t2 é escrito com o valor do endereço da variável b
	lw 	$t1, 0($t2)  # $t1 é escrito com o conteúdo da variável b
	
loop:	beq	$t0, $t1, igual	# compara se os valores de a e b são iguais. Se forem iguais, salta para o label igual, senão continua na próxima instrução
	addiu	$t1, $t1, 1	# adiciona 1 ao valor do registrador
	sw	$t1, 0($t2)	# armazena o conteúdo do regsitrador na posição de memória da variável b
	bne 	$t0, $t1, loop
igual:	addiu	$t0, $t0, 1	# adiciona 1 ao valor do registrador
	sw	$t0, 0($t3)	# armazena o conteúdo do regsitrador na posição de memória da variável a
	
.data
a: .word 4
b: .word 1
