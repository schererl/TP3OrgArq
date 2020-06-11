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
    Componentes::Barramento b_entrada_ula_a = c.CriaBarramento("Barramento de entrada da Ula A");
    Componentes::Barramento b_entrada_ula_b = c.CriaBarramento("Barramento de entrada da Ula B");
    Componentes::Barramento b_saida_ula_flag = c.CriaBarramento("Barramento de Flag da Ula");
    Componentes::Barramento b_saida_ula_resultado = c.CriaBarramento("Barramento de saída da Ula");
    Componentes::Barramento b_ula_aluop = c.CriaBarramento("Barramento Aluop");
    Componentes::Barramento b_saida_pc = c.CriaBarramento("Barramento Saída PC");
    Componentes::Barramento b_saida_reg_A = c.CriaBarramento("Barramento Saída Reg A");
    Componentes::Barramento b_saida_reg_B = c.CriaBarramento("Barramento Saída Reg B");
    Componentes::Barramento b_incrementa_pc_4 = c.CriaBarramento("Barramento Saída PC + 4");
    Componentes::Barramento b_saida_sign_ext = c.CriaBarramento("Barramento Extensão de Sinal");
    Componentes::Barramento b_saida_desl_esq_2 = c.CriaBarramento("Barramento Deslocamento esquerda 2");
    Componentes::Barramento b_sinal_mux_A = c.CriaBarramento("Barramento Saída Fonte A do Controle");
    Componentes::Barramento b_sinal_mux_B = c.CriaBarramento("Barramento Saída Fonte B do Controle");


    b1.valor = "0x00400006";
    cout << b1.nome << endl;
    b2.valor = "0x00400002";
    cout << b2.nome << endl;
    bs.valor = "0X00000000";
    b_incrementa_pc_4.valor = "000000000000000000000100";
    cout << bs.nome << endl;
    cout << binst.nome << endl;
    cout << bdado.nome << endl;
    cout << bsm.nome << endl;
    cout << bsesc_mem.nome << endl;
    cout << bsle_mem.nome << endl;

    //cria multiplexador e memória
    int numero_barramentos = 2;
    Componentes::Barramento *b = (Componentes::Barramento*)malloc(numero_barramentos * sizeof(Componentes::Barramento));
    b[0] = b1;
    b[1] = b2;
    Componentes::Multiplexador m1 = c.CriaMultiplexador("Multiplexador 1", b, &bs, numero_barramentos, &bsm);


    //cria multiplexador
    numero_barramentos = 2;
    Componentes::Barramento *b_mux_entrada_a = (Componentes::Barramento*)malloc(numero_barramentos * sizeof(Componentes::Barramento));

    b_mux_entrada_a[0] = b_saida_reg_A;
    b_mux_entrada_a[1] = b_incrementa_pc_4;
    Componentes::Multiplexador mux_entrada_a = c.CriaMultiplexador("Multiplexador Entrada A", b_mux_entrada_a, &b_saida_reg_A, numero_barramentos, &b_sinal_mux_A);


    //cria multiplexador
    numero_barramentos = 4;
    Componentes::Barramento *b = (Componentes::Barramento*)malloc(numero_barramentos * sizeof(Componentes::Barramento));
    b[0] = b1;
    b[1] = b2;
    b[2] = b2;
    b[3] = b2;
    Componentes::Multiplexador m = c.CriaMultiplexador("Multiplexador 1", b, &, numero_barramentos, &bsm);






    //cria memória
    Componentes::Memoria mem = c.CriaMemoria(&bs, &binst, &bdado, &bsesc_mem, &bsle_mem);



    //Cria ULA
    Componentes::ULA ula = c.CriaULA("ULA", &b_entrada_ula_a, &b_entrada_ula_b, &b_saida_ula_resultado, &b_saida_ula_flag, &b_ula_aluop);


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
