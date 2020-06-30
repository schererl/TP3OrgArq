# TP3OrgArq
Simulador MIPS com organização Multiciclo arquitetura Von Neumann
 * Victor Scherer Putrich
 * Lucas Augusto
 * Luis Gabriel
 * Rafael Dias

#Instruções de Execução:
	* Binário de execução: run
	* Arquivos de entrada: input/Instrucoes.txt e input/Mem.txt
	* Arquivos de saída: output/memoria_output.txt e log_exec.txt (opcional)
	* Execução step by step: 1 para sim, 0 para não
	* Formatação: ./bin arquivo_instrução.txt arquivo_memória.txt (0 ou 1) >> log.txt 

#Exemplos de Execução:
	1- Direta e sem log:     ./run input/Instrucoes.txt input/Mem.txt 0
	2- Step by step sem log: ./run input/Instrucoes.txt input/Mem.txt 1
	3- Direta com log:       ./run input/Instrucoes.txt input/Mem.txt 0 >> log_exec.txt

#Arquivos de Entrada Disponibilizados:
	* assembler/mips1.asm: Instrucoes.txt Mem.txt
	* assembler/mips2.asm: Instrucoes2.txt Mem2.txt
	* assembler/mips3.asm: Instrucoes3.txt Mem3.txt
	* assembler/mips4.asm: Instrucoes4.txt Mem4.txt

#Formatação de Entrada:
	* simulador le um arquivo referente as instruções (Instrucoes.txt) e outro ao valor de variáveis (Mem.txt)
	* txt não devem conter espaços em branco ou \n
	* leitura de arquivo com instruções e variáveis somente em hexadecimal com 0x na frente
	* para sinalizar ao simulador que a execução deve ser encerrada colocar como última instrução 0x00000000 em (Instrucoes.txt)

#Observação:
	* código desenvolvido no Ubuntu 18.04 LTS, bibliotecas usadas para este sistema operacional (comando step by step e log funcionais para este SO)
	* durante execução step by step: cada ciclo é preciso informar no terminal o próximo passo:
		- 1 para próxima etapa de instrução
		- 2 mostra banco de registradores
		- 3 mostra memória
		- -1 encerra execução
	* quando executado de forma direta com log, cada nova busca de instrução, etapa 0 do bloco de controle, é mostrado o banco de registradores e memória

	**para não sobrescrever arquivos de saída, renomeá-los**
