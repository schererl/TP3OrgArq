#include <string>
#include <cmath>
using namespace std;

class OperadorBits
{


public:
/*
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
*/
static string ExtrairBinario(string binario_entrada, int pos_inicial, int numero_bits)
{
    return binario_entrada.substr(pos_inicial, numero_bits);
}

//shift dos binário
static void ShiftLeft(string &binario, int numero_shifts)
{
    int size = binario.size() + numero_shifts;
    while(binario.size() < size) binario = binario + "0";
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
    /* VERIFICAR SE A OPERAÇÃO DA ULA FAZ ISSO
    for(int i=0; i<A.length(); i++){
        if(A[i]=='1' && B[i]=='1'){
            result += '1';
        }else{
            result += '0';
        }
    }
    return result;
    */
   /*VERIFICAR ISSO*/
   bool tem_1 = false;
   for(int i=0; i<A.length(); i++){
        if(! ((A[i] == '1' && B[i] == '1') || (A[i] == '0' && B[i] == '0'))) return "0";
        if(A[i] == '1' || B[i] == '1') tem_1 = true;
    }
    if(!tem_1) return "0";
    return "1";
}
static string OperaOr(string A, string B)
{   
    if(A.length() != B.length()){
        return "Entradas de tamanhos diferentes!";
    }
    /*
    string result;
    for(int i=0; i<A.length(); i++){
        if(A[i]=='1' || B[i]=='1'){
            result += '1';
        }else{
            result += '0';
        }
    }
    return result;
    */
    for(int i=0; i<A.length(); i++){
        if(A[i] == '0' && B[i] == '0') return "0";
    }
    return "1";
}
static string OperaAdd(string A, string B) 
{
    if(A.length() != B.length()){
        return "Entradas de tamanhos diferentes!";
    }
     string resp = ""; 
    int s = 0;
    int i = A.size() - 1, j = B.size() - 1; 
    while (i >= 0 || j >= 0 || s == 1) 
    {
        s += ((i >= 0)? A[i] - '0': 0); 
        s += ((j >= 0)? B[j] - '0': 0);
        resp = char(s % 2 + '0') + resp;
        s /= 2;
        i--; j--; 
    } 
    return resp;
}
static string OperaSub(string A, string B)
{
    int alength = A.size();
    int blength = B.size();
    string resp;
    if(alength != blength){
        return "Entradas de tamanhos diferentes!";
    }
    int adecimal = 0;
    int bdecimal = 0;
    int ai, bi;
    for(int i=alength-1; i>=0; i--){
        ai = A[i] - '0';
        bi = B[i] - '0';
        if(i != 0){
            adecimal += ai * pow(2, alength-(i+1));
            bdecimal += bi * pow(2, blength-(i+1));
        }else{
            adecimal -= ai * pow(2, alength-(i+1));
            bdecimal -= bi * pow(2, blength-(i+1));
        }
    }
    int respint = adecimal - bdecimal;
    char res[1000];
    itoa(respint, res, 2);
    return res;
}
static string OperaSetOnLess(string A, string B){
    string resp = "0000000000000000000000000000000";
    int alength = A.size();
    int blength = B.size();
    if(alength != blength){
        return "Entradas de tamanhos diferentes!";
    }
    int adecimal = 0;
    int bdecimal = 0;
    int ai, bi;
    for(int i=alength-1; i>=0; i--){
        ai = A[i] - '0';
        bi = B[i] - '0';
        if(i != 0){
            adecimal += ai * pow(2, alength-(i+1));
            bdecimal += bi * pow(2, blength-(i+1));
        }else{
            adecimal -= ai * pow(2, alength-(i+1));
            bdecimal -= bi * pow(2, blength-(i+1));
        }
    }
    if(adecimal<bdecimal){
        resp = resp + '1';
    }else{
        resp = resp + '0';
    }
    return resp;
}
};
