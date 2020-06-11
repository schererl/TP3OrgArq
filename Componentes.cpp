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
};
