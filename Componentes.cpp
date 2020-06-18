#include <string>
#include <stdlib.h>
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
        Barramento(string nome)
        {
            this->nome = nome;
            this->valor = "0x000000";
        }
    };

    struct Multiplexador
    {
        string nome;
        Barramento *entrada;  //vetor de barramentos de entradas
        int numero_entradas;  //numero de barramentos de entradas
        Barramento *saida;
        Barramento *escolhe_entrada;
        Multiplexador(string nome, Barramento *entrada, Barramento *saida, int numero_entradas, Barramento *escolhe_entrada)//escolhe entrada é o sinal de seleção
        {
            this->nome = nome;
            this->entrada = entrada;
            this->numero_entradas = numero_entradas;
            this->saida = saida;
            this->escolhe_entrada = escolhe_entrada;

        }

        //define o valor de saída
        void DefineSaida()
        {
            string valor_saida = this->entrada[stoi(this->escolhe_entrada->valor)].valor;
            this->saida->valor = valor_saida;
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

        void Operar()
        {
            if(ler_mem->valor == "1") BuscaInstrucao();
            if(esc_mem->valor == "1") GravaDado();
        }

        void BuscaInstrucao()
        {
            auto search = memoria.find(endereco->valor);
            if(search != memoria.end())  instrucao -> valor = search->second;

        }

        void GravaDado()
        {
            memoria[endereco->valor] = dado->valor;
        }
    };

    struct ULA
    {
        string nome;
        Barramento *entradaA;
        Barramento *entradaB;
        Barramento *zero;
        Barramento *saida;
        Barramento *aluop;


        ULA(string nome, Barramento *entradaA, Barramento *entradaB, Barramento *saida, Barramento *zero, Barramento *aluop)
        {
            this->nome = nome;
            this->entradaA = entradaA;
            this->entradaB = entradaB;
            this->saida = saida;
            this->zero = zero;
            this->aluop = aluop;
        }

        void Operar()
        {
            string resultado;
            string op = aluop->valor;
            if(op == "000")
                resultado = OperadorBits::OperaAnd(entradaA->valor, entradaB->valor);
            else if(op == "001")
                resultado = OperadorBits::OperaOr(entradaA->valor, entradaB->valor);
            else if(op == "010")
                resultado = OperadorBits::OperaAdd(entradaA->valor, entradaB->valor);
            else if(op == "110")
                resultado = OperadorBits::OperaSub(entradaA->valor, entradaB->valor);
            else if(op == "111")
                resultado = OperadorBits::OperaSetOnLess(entradaA->valor, entradaB->valor);


            saida -> valor = resultado; 
            zero -> valor = resultado; //MUDAR
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

        void BuscaRegistrador()
        {
            auto res1 = banco_reg.find(reg_lido_1->valor);
            auto res2 = banco_reg.find(reg_lido_2->valor);

            if(res1 != banco_reg.end())  dado_lido_1 -> valor = res1->second;
            if(res2 != banco_reg.end())  dado_lido_2 -> valor = res2->second;
        }

        void GravaRegistrador()
        {
            string sinal = esc_reg->valor;
            if (sinal == "1")
                banco_reg[reg_escrito->valor] = dado_escrita->valor;
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

        void BuscaReg() {
            auto busca = banco_reg.find(codigo_registrador);
            if(busca != banco_reg.end())  saida -> valor = busca->second;
        }

        void GravaRegistrador() {
            if(controle == NULL) {
                banco_reg[codigo_registrador] = entrada->valor;
            }else{
                if(controle->valor == "1")
                    banco_reg[codigo_registrador] = entrada->valor;
            }    
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

            
            if(valor_sinal_controle == "00")
            {
                valor_saida  = "010";
            }
            else if(valor_sinal_controle == "01")
            {
                valor_saida = "110";
            }
            else if (valor_sinal_controle == "10") {
                
                if(valor_funct == "100000") valor_saida = "010";
                else if(valor_funct == "100010") valor_saida = "110";
                else if(valor_funct == "100100") valor_saida = "000";
                else if(valor_funct == "100101") valor_saida = "001";
                else if(valor_funct == "101010") valor_saida = "111";
                
                
            }
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

    Barramento CriaBarramento(string nome)
    {
        return Barramento(nome);
    }

    Multiplexador CriaMultiplexador(string nome, Barramento *entrada, Barramento *saida, int numero_entradas, Barramento *escolhe_entrada)
    {
        return Multiplexador(nome, entrada, saida, numero_entradas, escolhe_entrada);
    }

    ULA CriaULA(string nome, Barramento *entradaA, Barramento *entradaB, Barramento *saida, Barramento *zero, Barramento *aluop)
    {
        return ULA(nome, entradaA, entradaB, saida, zero, aluop);
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
