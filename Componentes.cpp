#include <string>
#include <stdlib.h>
#include <map>
#include "OperadorBits.cpp"
#include "BaseDados.cpp"

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
        //entrada: A B C D E
        //sinal de control: 0
        //saida: entrada[0]

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
            zero -> valor = resultado;
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
            if (sinal = "1")
                banco_reg[reg_escrito->valor] = dado_escrita->valor;
        }

    };

    struct Registrador {
        Barramento *entrada;
        Barramento *saida;
        Barramento *controle;
        Barramento *endereco;

        Registrador(Barramento *entrada, Barramento *saida, Barramento *controle, Barramento *endereco) {
            this->entrada = entrada;
            this->saida = saida;
            this->controle = controle;
            this->endereco = endereco;
        };

        void BuscaReg {
            auto busca = banco_reg.find(endereco->valor);
            if(busca != banco_reg.end())  saida -> valor = busca->second;
        }

        void GravaRegistrador {
            if(controle == NULL) {
                banco_reg[endereco->valor] = entrada->valor;
            }else{
                if(controle->valor == 1)
                    banco_reg[endereco->valor] = entrada->valor;
            }    
        }
    }

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

    Registrador CriaRegistrador(Barramento *entrada, Barramento *saida, Barramento *controle, Barramento *endereco) {
        return Registrador(entrada, saida, controle, endereco);
    }

};
