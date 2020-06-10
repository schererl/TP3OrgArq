#include <string>
using namespace std;

//move os N primeiros bits de entrada para o parâmetro de saída (remove esses bits do binário de entrada)
void ExtrairBinario(string &binario_entrada, string &binario_saida, int numero_bits)
{
    string buffer;
    for(char i : binario_entrada)
    {
        buffer  = i;
        binario_saida += buffer;
        if(binario_saida.size() == numero_bits) break;
    }
    binario_entrada.erase(0, numero_bits);
}

//shift dos binário
void ShiftLeft(string &binario, int numero_shifts)
{
    while(binario.size() < binario.size() + numero_shifts) binario = binario + "0";
}

//trunca binário
void Trunc(string &binario, int bits_cortados)
{
    binario.erase(0, bits_cortados);
}

//Operações da ULA
string OperaAnd(string A, string B){}
string OperaOr(string A, string B){}
string OperaAdd(string A, string B){}
string OperaSub(string A, string B){}
string OperaSetOnLess(string A, string B){}