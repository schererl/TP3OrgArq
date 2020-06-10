#include "Componentes.cpp"
#include <vector>
#include <string>
#include <iostream> 

using namespace std;
int main()
{
    Componentes c;
    cout << "********BARRAMENTOS******" << endl;
    //cria barramentos
    Componentes::Barramento b1 = c.CriaBarramento("Barramento 1");
    Componentes::Barramento b2= c.CriaBarramento("Barramento 2");
    Componentes::Barramento bs= c.CriaBarramento("Barramento saída multiplexador");
    Componentes::Barramento binst = c.CriaBarramento("Barramento instrução");
    Componentes::Barramento bdado = c.CriaBarramento("Barramento de dado");
    Componentes::Barramento bsm= c.CriaBarramento("Barramento sinal mux");
    Componentes::Barramento bsesc_mem= c.CriaBarramento("Barramento sinal escrita memória");
    Componentes::Barramento bsle_mem= c.CriaBarramento("Barramento sinal leitura memória");
    b1.valor = "0x00400006";
    cout << b1.nome << endl;
    b2.valor = "0x00400002";
    cout << b2.nome << endl;
    bs.valor = "0X00000000";
    cout << bs.nome << endl;
    cout << binst.nome << endl;
    cout << bdado.nome << endl;
    cout << bsm.nome << endl;
    cout << bsesc_mem.nome << endl;
    cout << bsle_mem.nome << endl;



    //cria multiplexador e memória
    int numero_barramentos = 2;
    Componentes::Barramento *b = (Componentes::Barramento*)malloc(2 * sizeof(Componentes::Barramento));
    b[0] = b1;
    b[1] = b2;
    Componentes::Multiplexador m1 = c.CriaMultiplexador("Multiplexador 1", b, &bs, numero_barramentos, &bsm);
    Componentes::Memoria mem = c.CriaMemoria(&bs, &binst, &bdado, &bsesc_mem, &bsle_mem);
    
    cout << "***********" << endl ;  

    //faz operações
    string mult;
    cin >> mult;
    bsm.valor = mult;
    m1.DefineSaida();
    cout << "sinal de controle: " << mult << endl;
    cout << "sinal de saida do multiplexador: " << bs.valor << endl;
    mem.BuscaInstrucao();
    cout << "busca por instrucao: " << binst.valor << endl;

}