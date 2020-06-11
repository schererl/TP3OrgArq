#include <string>
using namespace std;

class OperadorBits
{


public:
//move os N primeiros bits de entrada para o parâmetro de saída (remove esses bits do binário de entrada)
static void ExtrairBinario(string &binario_entrada, string &binario_saida, int numero_bits)
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
static void ShiftLeft(string &binario, int numero_shifts)
{
    while(binario.size() < binario.size() + numero_shifts) binario = binario + "0";
}

//trunca binário
static void Trunc(string &binario, int bits_cortados)
{
    binario.erase(0, bits_cortados);
}


//Operações da ULA
static string OperaAnd(string A, string B)
{   
    if(A.length() != B.length()){
        return "Entradas de tamanhos diferentes!";
    }
    string result;
    for(int i=0; i<A.length(); i++){
        if(A[i]=='1' || B[i]=='1'){
            result += '1';
        }else{
            result += '0';
        }
    }
    return result;
}
static string OperaOr(string A, string B)
{   
    if(A.length() != B.length()){
        return "Entradas de tamanhos diferentes!";
    }
    string result;
    for(int i=0; i<A.length(); i++){
        if(A[i]=='1' && B[i]=='1'){
            result += '1';
        }else{
            result += '0';
        }
    }
    return result;
}
static string OperaAdd(string A, string B)
{
    if(A.length() != B.length()){
        return "Entradas de tamanhos diferentes!";
    }
    string result;
    for(int i=A.length()-1; i>=0; i--){
         
    }
    return "";
}
static string OperaSub(string A, string B)
{
    return "";
}
static string OperaSetOnLess(string A, string B){return "";}
};
