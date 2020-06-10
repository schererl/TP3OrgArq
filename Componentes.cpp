#include <string>
#include <stdlib.h>
#include "OperadorBits.cpp"
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
        Multiplexador(string nome, Barramento *entrada, Barramento *saida, int numero_entradas)
        {
            this->nome = nome;
            this->entrada = entrada;
            this->numero_entradas = numero_entradas;
            this->saida = saida;
            
        }
        
        //define o valor de saída
        void DefineSaida(int op)
        {
            string valor_saida = this->entrada[op].valor;
            this->saida->valor = valor_saida;
        }
    };

    struct ULA
    {
        string nome;
        Barramento *entradaA;
        Barramento *entradaB;
        Barramento *zero;
        Barramento *saida;
        
        ULA(string nome, Barramento *entradaA, Barramento *entradaB)
        {
            this->nome = nome;
            this->entradaA = entradaA;
            this->entradaB = entradaB;
        }

        string Operar(int op)
        {
            string resultado;
            switch(op)
            {
                case "000":
                    resultado = OperadorBits::OperaAnd(entradaA->valor, entradaB->valor);
                    break;
                case "001":
                    resultado = OperadorBits::OperaOr(entradaA->valor, entradaB->valor);
                    break;
                case "010":
                    resultado = OperadorBits::OperaAdd(entradaA->valor, entradaB->valor);
                    break;
                case "110":
                    resultado = OperadorBits::OperaSub(entradaA->valor, entradaB->valor);
                    break;
                case "111":
                    resultado = OperadorBits::OperaSetOnLess(entradaA->valor, entradaB->valor);
                    break;
                default:
                    break;

            }
            saida->valor = resultado;
            flag -> valor = resultado;
        }
        
    
    };

    Barramento CriaBarramento(string nome)
    {
        return Barramento(nome);
    }

    Multiplexador CriaMultiplexador(string nome, Barramento *entrada, Barramento *saida, int numero_entradas)
    {
        return Multiplexador(nome, entrada, saida, numero_entradas);
    }

    ULA CriaULA(string nome, Barramento *entradaA, Barramento *entradaB)
    {
        return ULA(nome, entradaA, entradaB);
    }
};