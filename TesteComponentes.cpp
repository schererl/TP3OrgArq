#include "BaseDados.cpp"
#include "OperadorBits.cpp"
#include "Componentes.cpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void TestaCircuitoBarramento()
{
    Componentes c;
    Componentes::Barramento b1 = c.CriaBarramento("Barramento 1");
    Componentes::Barramento b2 = c.CriaBarramento("Barramento 2");
    Componentes::Barramento b3 = c.CriaBarramento("Barramento 3");
    Componentes::Barramento b4 = c.CriaBarramento("Barramento 4");
    Componentes::Barramento b5 = c.CriaBarramento("Barramento 5");
    Componentes::Barramento b6 = c.CriaBarramento("Barramento 6");
    Componentes::Barramento b7 = c.CriaBarramento("Barramento 7");
    Componentes::CircuitoBarramento cb = c.CriaCircuitoBarramento();
    
    /*ENTRADA DE PC ok*/
    b1.valor = "0";
    b2.valor = "0";
    b3.valor = "1";
    cout << "sinal de controle pc: " << b4.valor << endl;
    cb.EntradaPC(&b1, &b2, &b3, &b4);
    cout << "valor atualizado: " << b4.valor << endl;
    

    /*DESLOCA A ESQUERDA BITS ok*/
    b1.valor = "111";
    cb.DeslocametoBits(&b1, &b2);
    cout << "\nteste shift left: " << b1.valor << endl;
    cout << "valor atualizado: " << b2.valor << endl;

    /* SEPARAÇÃO INSTRUÇÕES ok*/
    //250cfff4
    //0010 0101 0000 1100 1111 1111 1111 0100
    b1.valor = "123456789abcdefghijklmnopqrstuvw";
    cb.SeparaInstrucao(&b1, &b2, &b3, &b4, &b5, &b6, &b7);
    cout << "op_code: " << b6.valor << endl;
    cout << "registrador lido 1: " << b2.valor << endl;
    cout << "registrador lido 2: " << b3.valor << endl; 
    cout << "registrador destino: " << b4.valor << endl;
    cout << "imediato: " << b5.valor << endl;
    cout << "funct: " << b7.valor << endl;

    /*  EXTENDE SINAL ok*/
    b1.valor =  "1010010100101111";
    cb.ExtensaoSinal(&b1, &b2);
    cout << b2.valor << endl;
    cout << b2.valor.size() << endl;
    
    /* CONCATENA PC */

    /*BIFURCA PC: última a ser testado*/
    /*
    b1.valor = "00000000010000000000110101110111";
    cout << "bifurca pc: " < b1.valor << endl;
    cb.BifurcaPC(&b1, &b2);
    */

}

void TestaULA()
{

    Componentes c;
    Componentes::Barramento b1 = c.CriaBarramento("Barramento 1");
    Componentes::Barramento b2 = c.CriaBarramento("Barramento 2");
    Componentes::Barramento b3 = c.CriaBarramento("Barramento 3"); //saida
    Componentes::Barramento b4 = c.CriaBarramento("Barramento 4"); //flag
    Componentes::Barramento b5 = c.CriaBarramento("Barramento 5"); //aluop
    Componentes::Barramento b6 = c.CriaBarramento("Barramento 6"); //sinal_controle
    Componentes::Barramento b7 = c.CriaBarramento("Barramento 7"); //funct
    
    Componentes::CircuitoBarramento cb = c.CriaCircuitoBarramento();
    Componentes::ULA ula = c.CriaULA("ula", &b1, &b2, &b3, &b4, &b5);
    
    //* testa soma sem tipo-r *//
    
    cout << "******SOMA != TIPO-R*********" << endl;
    
    b1.valor = "00000000000000000000000000001101";
    b2.valor = "00000000000000000000000000010101";
    b6.valor = "00";
    b7.valor = "100010";
    cb.OperacaoULA(&b6, &b7,&b5);
    ula.Operar();
    cout << "aluop " << b5.valor << endl;
    cout << "saida " << b3.valor << endl;

    
    cout << "******SUB != TIPO-R*********" << endl;
    b6.valor = "01";
    b7.valor = "100010";
    cb.OperacaoULA(&b6, &b7,&b5);
    ula.Operar();
    cout << "aluop " << b5.valor << endl;
    cout << "saida " << b3.valor << endl;
    cout << "flag " << b4.valor << endl;

    cout << "******TIPO-R*********" << endl;
    b6.valor = "10";
    b7.valor = "101010";
    cb.OperacaoULA(&b6, &b7,&b5);
    ula.Operar();
    cout << "aluop " << b5.valor << endl;
    cout << "saida " << b3.valor << endl;
    cout << "flag " << b4.valor << endl;

}


//le arquivo e popula memória com instruções e 
void GeraMemoria(vector<string> instrucoes, vector<string> variaveis)
{
    string endereco_instrucao = "00400000";
    string endereco_variaveis = "00100000";
    
    for(int i = 0;i < instrucoes.size();i++)
    {
        memoria[endereco_instrucao] = instrucoes[i];
        OperadorBits::sum_1(endereco_instrucao); 
    }
    
    for(int j = 0; j < variaveis.size(); j++)
    {
        memoria[endereco_variaveis] = endereco_variaveis;
        OperadorBits::sum_1(endereco_variaveis);
    }
}


int main()
{
    
    //TestaULA();
    TestaCircuitoBarramento();
    vector<string> instr;
    GeraMemoria(instr, instr);
    


    /*
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
    Componentes::Barramento b_saida_reg_B = c.CriaBarramento("Barramento Saída Reg B");                     //entrada 0 do mux 4 entradas (primeira entrada)
    Componentes::Barramento b_incrementa_pc_4 = c.CriaBarramento("Barramento Saída PC + 4");                //entrada pc + 4 do mux 4 entradas (segunda entrada)
    Componentes::Barramento b_saida_sign_ext = c.CriaBarramento("Barramento Extensão de Sinal");            //sign ext(terceira entrada)
    Componentes::Barramento b_saida_desl_esq_2 = c.CriaBarramento("Barramento Deslocamento esquerda 2");    //ssl 2 (quarta entrada)
    Componentes::Barramento b_sinal_mux_A = c.CriaBarramento("Barramento Saída Fonte A do Controle");       //Controle ULAFonteA
    Componentes::Barramento b_sinal_mux_B = c.CriaBarramento("Barramento Saída Fonte B do Controle");       //Controle ULAFonteB


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
    Componentes::Barramento *b_mux_entrada_b = (Componentes::Barramento*)malloc(numero_barramentos * sizeof(Componentes::Barramento));
    b_mux_entrada_b[0] = b_saida_reg_B;
    b_mux_entrada_b[1] = b_incrementa_pc_4;
    b_mux_entrada_b[2] = b_saida_sign_ext;
    b_mux_entrada_b[3] = b_saida_desl_esq_2;
    Componentes::Multiplexador m = c.CriaMultiplexador("Multiplexador Entrada B", b_mux_entrada_b, &b_saida_reg_B, numero_barramentos, &b_sinal_mux_B);

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
    */


}
