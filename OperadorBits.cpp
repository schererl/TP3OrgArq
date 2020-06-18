#include <string>
#include <cmath>
#include <bitset>
/*DESCOMENTAR SE FOR DEPURAR APENAS ESTA CLASSE*/
//#include "BaseDados.cpp"
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

static string ExtendeBits(string binario_entrada, int numero_bits)
{
    char bit_m_significativo = binario_entrada[0];
    for(int i = 0; i < numero_bits;i++) binario_entrada = bit_m_significativo + binario_entrada;
    return binario_entrada; 
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

static string OperaOr(string A, string B)
{   
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
    //char res[1000];
    //itoa(respint, res, 2);
    //resp = res;
    resp = bitset<32>(respint).to_string();
    
    while(resp.size()<32){
        resp = '0' + resp;
    }
    return resp;
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

static void sum_1(std::string &imediate)
{
    for(int i = imediate.size() - 1; i >= 0; i--)
    {
        if(imediate[i] == '0') 
        {
            imediate[i] = '1';
            return;
        }
        else
        {
            imediate[i] = '0';
        }
    }
}


//hexadecial para binário
static string HexaToBin(std::string hexa)
{
    string tmp;
    string bin;
    hexa = ReplaceAll(hexa, string("0x"), string("")); 
        
    for(char i: hexa)
    {
        tmp = i;
        auto search = tb_hexa_bin.find(tmp); 
        if(search != tb_hexa_bin.end()) 
            bin =   bin + search->second;
    }
    return bin;

}

//binário para hexadecimal
static string BinToHexa(string bin)
{

    string tmp_bin;
    string hexa = "0x";
    for(char i: bin) 
    {
        tmp_bin = tmp_bin + i;
        if(tmp_bin.size() == 4)
        {
            auto search = tb_bin_hexa.find(tmp_bin); 
            if(search != tb_bin_hexa.end()) 
                hexa = hexa + search->second;
            tmp_bin = "";   
        }
    
        
    }
    return hexa;

}

//substitui numa string um conjunto de caracteres por outro
static string ReplaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); 
    }
    return str;
}


};
