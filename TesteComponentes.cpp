#include "Componentes.cpp"
#include <vector>
#include <string>
#include <iostream> 
using namespace std;
int main()
{
    Componentes c;
    Componentes::Barramento b1 = c.CriaBarramento("Barramento 1");
    b1.valor = "0X00000001";
    cout << b1.nome << endl;

    Componentes::Barramento b2= c.CriaBarramento("Barramento 2");
    b2.valor = "0X11100001";
    cout << b2.nome << endl;

    Componentes::Barramento bs= c.CriaBarramento("Barramento saida");
    bs.valor = "0X00000000";
    cout << bs.nome << endl;

    int numero_barramentos = 2;
    Componentes::Barramento *b = (Componentes::Barramento*)malloc(2 * sizeof(Componentes::Barramento));
    
    b[0] = b1;
    b[1] = b2;
    Componentes::Multiplexador m1 = c.CriaMultiplexador("Multiplexador 1", b, &bs, numero_barramentos);
    cout << "sinal de controle: " << 1 << endl;
    m1.DefineSaida(1);
    cout << "sinal de saida: " << bs.valor << endl;
}