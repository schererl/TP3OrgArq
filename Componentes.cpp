#include <string>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include <map>
/*DESCOMENTAR SE FOR DEPURAR APENAS ESTA CLASSE*/
//#include "BaseDados.cpp"
//#include "OperadorBits.cpp"


using namespace std;

class Componentes
{
    public:
    struct Barramento
    {
        string nome;
        string valor;
        Barramento(string nome, int tamanho)
        {
            this->nome = nome;
            this->valor = "0";
            OperadorBits::AdjustBin(valor, tamanho); //inicializa o barramento zerado com o tamanho passado por parâmetro
        }

        void Imprime()
        {
            cout << valor << endl;
        }
    };

    struct Multiplexador
    {
        string nome;
        Barramento **entrada;
        Barramento *saida;
        Barramento *escolhe_entrada;
        Multiplexador(string nome, Barramento **entrada, Barramento *saida, Barramento *escolhe_entrada)//escolhe entrada é o sinal de seleção
        {
            this->nome = nome;
            this->entrada = entrada;
            this->saida = saida;
            this->escolhe_entrada = escolhe_entrada;

        }

        //define o valor de saída
        void Opera()
        {
            string valor_saida = entrada[IndiceEntrada()]->valor;
            this->saida->valor = valor_saida;
        }
    
        void Imprime()
        {
            cout << "******\n" << nome << endl;
            cout << "entrada escolhida: "; escolhe_entrada->Imprime();
            cout << "saida: "; saida->Imprime() ; 
        }
        
        void ImprimeEntradas(int n)
        {
            for(int i = 0; i < n;i++)
            {
                cout << "ENTRADA " << i << ": " << entrada[i]->nome << endl;
            }


        }
        
        int IndiceEntrada()
        {
            string buff =this->escolhe_entrada->valor;
            if (buff.size() < 2) buff =  "0" + buff;

            if(buff == "00") return 0;
            else if(buff == "01") return 1;
            else if(buff == "10") return 2;
            else if(buff == "11") return 3;
            else return -1;
        }
    };

    struct Memoria
    {
        //classe BaseDados guarda dicionário "memoria"

        Barramento *endereco;  //input 1
        Barramento *instrucao; //output 1
        Barramento *dado;      //input 2
        Barramento *ler_mem;
        Barramento *esc_mem;
        Memoria(Barramento *endereco, Barramento*instrucao, Barramento*dado, Barramento *ler_mem, Barramento *esc_mem)
        {
            this->endereco = endereco;
            this->instrucao = instrucao;
            this->dado = dado;
            this->ler_mem = ler_mem;
            this->esc_mem = esc_mem;
        }

        void Opera()
        {
            if(ler_mem->valor == "1") BuscaDado();
            if(esc_mem->valor == "1") GravaDado();
        }

        void BuscaDado()
        {
            auto search = memoria.find(OperadorBits::BinToHexa(endereco->valor));
            if(search != memoria.end())  instrucao -> valor = OperadorBits::HexaToBin(search->second);
            else { cout << "**erro endereço não localizado na memória: " << OperadorBits::BinToHexa(endereco->valor) << endl;}
        }

        void GravaDado()
        {
            memoria[OperadorBits::BinToHexa(endereco->valor)] = OperadorBits::BinToHexa(dado->valor);
        }

        void Imprime()
        {
            cout << "****\nMemoria" << endl;
            cout << "endereço entrada: "; endereco->Imprime();
            cout << "sinal de leitura de memória: "; ler_mem->Imprime();
            cout << "sinal de escrita de memória: "; esc_mem->Imprime();
            cout << "valor de dado as ser escrito: "; dado->Imprime();
            cout << "instrução de saída: "; instrucao->Imprime();
        }
    };

    struct ULA
    {
        Barramento *entradaA;
        Barramento *entradaB;
        Barramento *zero;
        Barramento *saida;
        Barramento *aluop;


        ULA(Barramento *entradaA, Barramento *entradaB, Barramento *saida, Barramento *zero, Barramento *aluop)
        {
            this->entradaA = entradaA;
            this->entradaB = entradaB;
            this->saida = saida;
            this->zero = zero;
            this->aluop = aluop;
        }

        void Opera()
        {
            /*falta shift left e shift right*/

            string resultado;
            string op = aluop->valor;
            if(op == "0000")
                resultado = OperadorBits::OperaAnd(entradaA->valor, entradaB->valor);
            else if(op == "0001")
                resultado = OperadorBits::OperaOr(entradaA->valor, entradaB->valor);
            else if(op == "0010")
                resultado = OperadorBits::OperaAdd(entradaA->valor, entradaB->valor);
            else if(op == "0110")
                resultado = OperadorBits::OperaSub(entradaA->valor, entradaB->valor);
            else if(op == "0111")
                resultado = OperadorBits::OperaSetOnLess(entradaA->valor, entradaB->valor);
            else if( op == "0011")
                resultado = OperadorBits::OperaXor(entradaA->valor, entradaB->valor);
            else if( op == "1000")
                resultado = OperadorBits::OperaShiftLeft(entradaA->valor, entradaB->valor);
            else if(op == "1001")
            {
                resultado = entradaB->valor; 
                OperadorBits::ShiftLeft(resultado, 16);
                cout << "========RESULTADO SHIFT LEFT: " << resultado << endl;
            }
            else
            {
                cout << "**ERRO OPERAÇÃO DE ULA NÃO DEFINIDA" << endl;
            }
            
            //else if sll
            //else if srl
            //else if xor talvez

            saida -> valor = resultado; 

            if(resultado == "00000000000000000000000000000000") 
                zero -> valor = "1"; //MUDAR
            else
                zero -> valor = "0";
            
        }

        void Imprime()
        {
            cout << "********\nULA" << endl;
            cout << "entrada A: "; entradaA->Imprime();
            cout << "entrada B: "; entradaB->Imprime();
            cout << "aluop: "; aluop->Imprime();
            cout << "saida: "; saida->Imprime();
            cout << "zero: "; zero->Imprime();
        }

    };

    struct BancoReg {
        Barramento *reg_lido_1; //entrada 1
        Barramento *reg_lido_2; //entrada 2
        Barramento *reg_escrito; //entrada 3
        Barramento *dado_escrita; //entrada 4
        Barramento *dado_lido_1; //saída 1
        Barramento *dado_lido_2; //saída 2
        Barramento *esc_reg; //sinal de controle

        BancoReg(Barramento *reg_lido_1, Barramento *reg_lido_2, Barramento *reg_escrito, Barramento *dado_escrita, Barramento *dado_lido_1, Barramento *dado_lido_2, Barramento *esc_reg)
        {
            this->reg_lido_1 = reg_lido_1;
            this->reg_lido_2 = reg_lido_2;
            this->reg_escrito = reg_escrito;
            this->dado_escrita = dado_escrita;
            this->dado_lido_1 = dado_lido_1;
            this->dado_lido_2 = dado_lido_2;
            this->esc_reg = esc_reg;
        }

        void Opera()
        {
            if(esc_reg->valor == "1") GravaRegistrador();
            BuscaRegistrador();
        }

        void BuscaRegistrador()
        {
            string buffer_bin = reg_lido_1->valor;
            OperadorBits::AdjustBin(buffer_bin, 32);

            string buffer_bin2 = reg_lido_2->valor;
            OperadorBits::AdjustBin(buffer_bin2, 32);

            auto res1 = banco_reg.find(OperadorBits::BinToHexa(buffer_bin));
            auto res2 = banco_reg.find(OperadorBits::BinToHexa(buffer_bin2));

            if(res1 != banco_reg.end())  dado_lido_1 -> valor = OperadorBits::HexaToBin(res1->second);
            if(res2 != banco_reg.end())  dado_lido_2 -> valor = OperadorBits::HexaToBin(res2->second);
        }

        void GravaRegistrador()
        {
            string sinal = esc_reg->valor;


            if (sinal == "1")
            {
                string buff_bin = reg_escrito->valor;
                OperadorBits::AdjustBin(buff_bin, 32); //TODO::VERIFICAR AQUI
                banco_reg[OperadorBits::BinToHexa(buff_bin)] = OperadorBits::BinToHexa(dado_escrita->valor);
            }
        }

        void Imprime()
        {
            cout << "******\nBANCO DE REGISTRADORES" << endl;
            cout << "registrador lido 1: "; reg_lido_1->Imprime();
            cout << "registrador lido 2: "; reg_lido_2->Imprime();
            cout << "registrador escrito: "; reg_escrito->Imprime();
            cout << "dado escrito: "; dado_escrita->Imprime();
            cout << "dado lido 1: "; dado_lido_1->Imprime();
            cout << "dado lido 2: "; dado_lido_2->Imprime();
            cout << "sinal escrita registrador: "; esc_reg->Imprime();
            
        }

    };

    //registradores invisíveis para salvar dados entre ciclos de relógio
    struct RegistradorInvisivel {
        string nome, codigo_registrador;
        Barramento *entrada;
        Barramento *saida;
        Barramento *controle;
        RegistradorInvisivel(string nome, Barramento *entrada, Barramento *saida, Barramento *controle, string codigo_registrador) {
            this->entrada = entrada;
            this->saida = saida;
            this->controle = controle;
            this->codigo_registrador = codigo_registrador;
            this-> nome = nome;
        };

        void Opera()
        {
            BuscaReg();
            GravaRegistrador();
            
        }

        void BuscaReg() {
            auto busca = banco_reg.find(codigo_registrador);
            string tmp;
            if(busca != banco_reg.end())  /*saida -> valor*/tmp = OperadorBits::HexaToBin(busca->second);
            saida -> valor = tmp;
        }

        void GravaRegistrador() {
            if(controle == NULL) {
                banco_reg[codigo_registrador] = OperadorBits::BinToHexa(entrada->valor);
                //BuscaReg();
            }else{
                if(controle->valor == "1"){
                    banco_reg[codigo_registrador] = OperadorBits::BinToHexa(entrada->valor);
                    //BuscaReg();
                }
            }    
        }

        void Imprime()
        {
            cout << "*****\nRegistrador invisível " << nome << endl;
            cout << "entrada: "; entrada->Imprime();
            
            if(controle != NULL)
            {
                cout << "sinal de controle: "; controle->Imprime();
            }
            cout << "grava valor em: " << codigo_registrador << endl;
            cout << "saida: "; saida->Imprime();

            auto busca = banco_reg.find(codigo_registrador);
            string tmp;
            if(busca != banco_reg.end())  cout << "valor no registrador: " << (busca->second) << endl;
            

            
        }
    };

    //Operacoes de bits nos barramentos
    struct CircuitoBarramento
    {
        CircuitoBarramento(){}
        //circuito de pc
        void EntradaPC(Barramento *entrada_1, Barramento *entrada_2, Barramento *entrada_3, Barramento *saida)
        {
            string result_and, result_or;
            result_and = OperadorBits::OperaAnd(entrada_1->valor, entrada_2->valor);
            result_or = OperadorBits::OperaOr(entrada_3->valor, result_and);
            saida->valor = result_or;
        }

        /* VERIRIFCAR ESTES DOIS CIRCUITOS  */
        //circuito de deslocamento de bits
        void DeslocametoBits(Barramento *entrada, Barramento *saida)
        {

            string valor = entrada->valor;
            OperadorBits::ShiftLeft(valor, 2);
            saida -> valor = valor;
        }

        //circuito de extensao de sinal
        //TODO
        void ExtensaoSinal(Barramento *entrada, Barramento *saida)
        {
            string valor = OperadorBits::ExtendeBits(entrada->valor, 16);
            saida -> valor = valor;
        }

        //circuito de operação da ULA
        //TODO                                 //verificar//
        void OperacaoULA(Barramento *sinal_controle, Barramento *funct, Barramento *saida)
        {
            string valor_sinal_controle = sinal_controle->valor;
            string valor_funct = funct->valor;
            string valor_saida;

            
            if(valor_sinal_controle == "000")
            {
                valor_saida  = "0010"; //executa soma
            }
            else if(valor_sinal_controle == "001")
            {
                valor_saida = "0110"; //beq subtração
            }
            else if (valor_sinal_controle == "010") {
                
                if(valor_funct == "100000") valor_saida = "0010";
                else if(valor_funct == "100010") valor_saida = "0110";
                else if(valor_funct == "100100") valor_saida = "0000";
                else if(valor_funct == "100101") valor_saida = "0001";
                else if(valor_funct == "101010") valor_saida = "0111";
                else if(valor_funct == "100110") valor_saida = "0011";
                else if(valor_funct == "000000") valor_saida = "1000"; 
                else{ cout << "**ERRO: funct não identificado " << valor_funct << endl;}
                //000000 sll
                //000010 srl
                
                
            }
            else if (valor_sinal_controle == "011")
            {
                valor_saida = "0000";
            }
            else if (valor_sinal_controle == "100")
            {
                valor_saida =  "1001";
            }
            else if (valor_sinal_controle == "101")
            {
                valor_saida = "0011";
            }
            else{ cout << "**ERRO: sinal de controle não identificado " << valor_sinal_controle << endl;}
            //ori 111 -> or bit a bit
            //lui 011 -> soma 
            //addiu 101 -> soma

            saida->valor = valor_saida;
         }

        /* avaliar esta separação */
        //buscar pelo shamt
        //implementar barramento de salto incondicional
        void SeparaInstrucao(Barramento *instrucao, Barramento *reg_lido_1, Barramento *reg_lido_2, Barramento *reg_destino, Barramento *imediato, Barramento *op_code, Barramento *funct)
        {
            string buffer_binario = instrucao->valor;
            string op_code_valor, reg_lido_1_valor, reg_lido_2_valor, reg_destino_valor, imediato_valor, funct_valor;
            op_code_valor = OperadorBits::ExtrairBinario(buffer_binario, 0, 6);
            reg_lido_1_valor = OperadorBits::ExtrairBinario(buffer_binario, 6, 5);
            reg_lido_2_valor = OperadorBits::ExtrairBinario(buffer_binario, 11, 5);
            reg_destino_valor = OperadorBits::ExtrairBinario(buffer_binario, 16, 5);
            imediato_valor = OperadorBits::ExtrairBinario(buffer_binario, 16, 16);
            funct_valor = OperadorBits::ExtrairBinario(buffer_binario, 26, 6);

            op_code -> valor = op_code_valor;
            reg_lido_1 -> valor = reg_lido_1_valor;
            reg_lido_2 -> valor = reg_lido_2_valor;
            reg_destino -> valor = reg_destino_valor;
            imediato -> valor = imediato_valor; 
            funct -> valor = funct_valor;
        }

        void BifurcaPC(Barramento *pc, Barramento *pc_truncado)
        {
            string bin_pc = pc->valor;
            OperadorBits::Trunc(bin_pc, 4);
            pc_truncado->valor = bin_pc;
        }

    
        void ConcatenaPCSalto(Barramento *pc_truncado, Barramento *endereco_salto, Barramento *saida)
        {
            saida->valor = endereco_salto->valor + pc_truncado->valor;
        }

    };

    Barramento CriaBarramento(string nome, int numero_bits)
    {
        return Barramento(nome, numero_bits);
    }

    Multiplexador CriaMultiplexador(string nome, Barramento **entrada, Barramento *saida, Barramento *escolhe_entrada)
    {
        return Multiplexador(nome, entrada, saida, escolhe_entrada);
    }

    ULA CriaULA(Barramento *entradaA, Barramento *entradaB, Barramento *saida, Barramento *zero, Barramento *aluop)
    {
        return ULA(entradaA, entradaB, saida, zero, aluop);
    }

    Memoria CriaMemoria(Barramento *endereco, Barramento*instrucao, Barramento*dado, Barramento *ler_mem, Barramento *esc_mem)
    {
        return Memoria(endereco, instrucao, dado, ler_mem, esc_mem);
    }

    BancoReg CriaBancoReg(Barramento *reg_lido_1, Barramento *reg_lido_2, Barramento *reg_escrito, Barramento *dado_escrita, Barramento *dado_lido_1, Barramento *dado_lido_2, Barramento *esc_reg)
    {
        return BancoReg(reg_lido_1, reg_lido_2, reg_escrito, dado_escrita, dado_lido_1, dado_lido_2, esc_reg);
    }

    RegistradorInvisivel CriaRegistradorInvisivel(string nome, Barramento *entrada, Barramento *saida, Barramento *controle, string codigo_registrador) 
    {
        return RegistradorInvisivel(nome, entrada, saida, controle, codigo_registrador);
    }

    CircuitoBarramento CriaCircuitoBarramento()
    {
        return CircuitoBarramento();
    }

};
