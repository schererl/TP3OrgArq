#include "Componentes.cpp"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>  
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
using namespace std;
class BlocoControle
{
    
    struct Nodo
    {
        int id_estado, numero_sinais;
        Componentes::Barramento **sinais;
        string* valores_sinais;
        Nodo(int id_estado, int numero_sinais){ 
            
            this->id_estado = id_estado; 
            this->numero_sinais = numero_sinais;
            }
        Nodo(){}
        
        
    }; 
    
    Nodo raiz = Nodo(0, 8);
    Nodo nodo_1 = Nodo(1, 3);
    Nodo nodo_2 = Nodo(2, 3);
    Nodo nodo_3 = Nodo(3, 2);
    Nodo nodo_4 = Nodo(4, 3);
    Nodo nodo_5 = Nodo(5, 2);
    Nodo nodo_6 = Nodo(6, 3);
    Nodo nodo_7 = Nodo(7, 3);
    Nodo nodo_8 = Nodo(8, 6);
    Nodo nodo_9 = Nodo(9, 2);

    Nodo *atual;
    Nodo *caminho_instrucao;
    int index_caminho;
    
    void AlocaMemoria(int num_elementos, int index)
    {
        
        atual->sinais = (Componentes::Barramento **)malloc(num_elementos * sizeof(Componentes::Barramento*));
        for(int i = 0; i < num_elementos;i++) atual->sinais[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
        atual->valores_sinais = (string *)malloc(num_elementos * sizeof(string));
    }
    

    void CriaNodos()
    {
        //***********NODO 0***********//
        atual = &raiz;
        AlocaMemoria(raiz.numero_sinais, raiz.id_estado);
        atual->sinais[0] = ler_mem;
        atual->valores_sinais[0] = "1";
        atual->sinais[1] = ula_fonte_a;
        atual->valores_sinais[1] = "0";
        atual->sinais[2] = i_ou_d;
        atual->valores_sinais[2] = "0";
        atual->sinais[3] = ir_esc;
        atual->valores_sinais[3] = "1";
        atual->sinais[4] = ula_fonte_b;
        atual->valores_sinais[4] = "01";
        atual->sinais[5] = ula_op;
        atual->valores_sinais[5] = "00";
        atual->sinais[6] = pc_esc;
        atual->valores_sinais[6] = "1";
        atual->sinais[7] = fonte_pc;
        atual->valores_sinais[7] = "00";
        //**************Nodo 1************//
        atual = &nodo_1;
        AlocaMemoria(nodo_1.numero_sinais, nodo_1.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "0";
        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "11";
        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "11";
        //***************Nodo 2*************//
        atual = &nodo_2;
        AlocaMemoria(nodo_2.numero_sinais, nodo_2.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "1";
        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "10";
        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "00";
        //***************Nodo 3*************//
        atual = &nodo_3;
        AlocaMemoria(nodo_3.numero_sinais, nodo_3.id_estado);
        atual->sinais[0] = ler_mem;
        atual->valores_sinais[0] = "1";
        atual->sinais[1] = i_ou_d;
        atual->valores_sinais[1] = "1";
        //***************Nodo 4*************//
        atual = &nodo_4;
        AlocaMemoria(nodo_4.numero_sinais, nodo_4.id_estado);
        atual->sinais[0] = esc_reg;
        atual->valores_sinais[0] = "1";
        atual->sinais[1] = mem_para_reg;
        atual->valores_sinais[1] = "1";
        atual->sinais[2] = reg_dst;
        atual->valores_sinais[2] = "0";
        //***************Nodo 5*************//
        atual = &nodo_5;
        AlocaMemoria(nodo_5.numero_sinais, nodo_5.id_estado);
        atual->sinais[0] = esc_mem;
        atual->valores_sinais[0] = "1";
        atual->sinais[1] = i_ou_d;
        atual->valores_sinais[1] = "1";
        //***************Nodo 6*************//
        atual = &nodo_6;
        AlocaMemoria(nodo_6.numero_sinais, nodo_6.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "1";
        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "00";
        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "10";
        //***************Nodo 7*************//
        atual = &nodo_7;
        AlocaMemoria(nodo_7.numero_sinais, nodo_7.id_estado);
        atual->sinais[0] = reg_dst;
        atual->valores_sinais[0] = "1";
        atual->sinais[1] = esc_reg;
        atual->valores_sinais[1] = "1";
        atual->sinais[2] = mem_para_reg;
        atual->valores_sinais[2] = "0";
        //***************Nodo 8*************//
        atual = &nodo_8;
        AlocaMemoria(nodo_8.numero_sinais, nodo_8.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "1";
        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "00";
        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "01";
        atual->sinais[3] = pc_esc_cond;
        atual->valores_sinais[3] = "1";
        atual->sinais[4] = pc_esc;
        atual->valores_sinais[4] = "0";
        atual->sinais[5] = fonte_pc;
        atual->valores_sinais[5] = "01";
        //***************Nodo 9*************//
        atual = &nodo_9;
        AlocaMemoria(nodo_9.numero_sinais, nodo_9.id_estado);
        atual->sinais[0] = pc_esc;
        atual->valores_sinais[0] = "1";
        atual->sinais[1] = fonte_pc;
        atual->valores_sinais[1] = "10"; 
        
        
    }
    
    void ProximaInstrucao()
    {
        atual = &caminho_instrucao[index_caminho];
        index_caminho++;
        if(atual->id_estado == -1)
        {
            IniciaCaminho();
        }
        if(atual->id_estado == 1)
        {
            BuscaInstrucao();
        }
        AtualizaSinais();
    }    

    void BuscaInstrucao()
    {

    }

    void IniciaCaminho()
    {
        cout << "nova instrução" << endl;
        free(caminho_instrucao);
        index_caminho = 0;
        caminho_instrucao = (Nodo*)malloc(2 * sizeof(Nodo));
        caminho_instrucao[0] = raiz;
        caminho_instrucao[1] = nodo_1;
        ProximaInstrucao();
    }

    void CaminhoLoad()
    {
        caminho_instrucao = (Nodo*)malloc(4 * sizeof(Nodo));
        index_caminho = 0;
        caminho_instrucao[0] = nodo_2;
        caminho_instrucao[1] = nodo_3;
        caminho_instrucao[2] = nodo_4;
        caminho_instrucao[3] = Nodo(-1, -1);

    }

    void AtualizaSinais()
    {
        
        for(int i = 0; i < atual->numero_sinais;i++)
        {
            atual->sinais[i]->valor = atual->valores_sinais[i];
        }
        
    }
    
    public:
    Componentes::Barramento *pc_esc_cond;
    Componentes::Barramento *pc_esc;
    Componentes::Barramento *i_ou_d;
    Componentes::Barramento *ler_mem;
    Componentes::Barramento *esc_mem;
    Componentes::Barramento *mem_para_reg;
    Componentes::Barramento *ir_esc;
    Componentes::Barramento *fonte_pc;
    Componentes::Barramento *ula_op;
    Componentes::Barramento *ula_fonte_b;
    Componentes::Barramento *ula_fonte_a;
    Componentes::Barramento *esc_reg;
    Componentes::Barramento *reg_dst;
    Componentes::Barramento *flag_AND_PC_esc_cond;
    Componentes::Barramento *flag_and_PC_esc_cond_OR_pc_sc;

    BlocoControle(Componentes::Barramento *pc_esc_cond, 
        Componentes::Barramento *pc_esc,
        Componentes::Barramento *i_ou_d,
        Componentes::Barramento *ler_mem,
        Componentes::Barramento *esc_mem,
        Componentes::Barramento *mem_para_reg,
        Componentes::Barramento *ir_esc,
        Componentes::Barramento *fonte_pc,
        Componentes::Barramento *ula_op,
        Componentes::Barramento *ula_fonte_b,
        Componentes::Barramento *ula_fonte_a,
        Componentes::Barramento *esc_reg,
        Componentes::Barramento *reg_dst,
        Componentes::Barramento *flag_AND_PC_esc_cond,
        Componentes::Barramento *flag_and_PC_esc_cond_OR_pc_sc
    )
    {
        
        this->pc_esc_cond = pc_esc_cond;
        this->pc_esc = pc_esc;
        this->i_ou_d = i_ou_d;
        this->ler_mem = ler_mem;
        this->esc_mem = esc_mem;
        this->mem_para_reg = mem_para_reg;
        this->ir_esc = ir_esc;
        this->fonte_pc = fonte_pc;
        this->ula_op = ula_op;
        this->ula_fonte_b = ula_fonte_b;
        this->ula_fonte_a = ula_fonte_a;
        this->esc_reg = esc_reg;
        this->reg_dst = reg_dst;
        this->flag_AND_PC_esc_cond = flag_AND_PC_esc_cond;
        this->flag_and_PC_esc_cond_OR_pc_sc = flag_and_PC_esc_cond_OR_pc_sc;
       
        CriaNodos();
        CaminhoLoad();
        ProximaInstrucao();
        ProximaInstrucao();
        ProximaInstrucao();
        ProximaInstrucao();
        ProximaInstrucao();
    }

};

int main()
{
    Componentes c;
    
    Componentes::Barramento b1 = c.CriaBarramento("pc_esc_cond");
    Componentes::Barramento b2 = c.CriaBarramento("pc_esc");
    Componentes::Barramento b3 = c.CriaBarramento("i_ou_d");
    Componentes::Barramento b4 = c.CriaBarramento("ler_mem");
    Componentes::Barramento b5 = c.CriaBarramento("esc_mem");
    Componentes::Barramento b6 = c.CriaBarramento("mem_para_reg");
    Componentes::Barramento b7 = c.CriaBarramento("ir_esc");
    Componentes::Barramento b8 = c.CriaBarramento("fonte_pc");
    Componentes::Barramento b9 = c.CriaBarramento("ula_op");
    Componentes::Barramento b10 = c.CriaBarramento("ula_fonte_b");
    Componentes::Barramento b11 = c.CriaBarramento("ula_fonte_a");
    Componentes::Barramento b12 = c.CriaBarramento("esc_reg");
    Componentes::Barramento b13 = c.CriaBarramento("reg_dst");
    Componentes::Barramento b14 = c.CriaBarramento("flag_AND_PC_esc_cond");
    Componentes::Barramento b15 = c.CriaBarramento("flag_and_PC_esc_cond_OR_pc_sc");
    BlocoControle controle = BlocoControle(&b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9, &b10, &b11, &b12, &b13, &b14, &b15);
   
    cout << b1.nome << ": " << b1.valor << endl;
    cout << b2.nome << ": " << b2.valor << endl;
    cout << b3.nome << ": " << b3.valor << endl;
    cout << b4.nome << ": " << b4.valor << endl;
    cout << b5.nome << ": " << b5.valor << endl;
    cout << b6.nome << ": " << b6.valor << endl;
    cout << b7.nome << ": " << b7.valor << endl;
    cout << b8.nome << ": " << b8.valor << endl;
    cout << b9.nome << ": " << b9.valor << endl;
    cout << b10.nome << ": " << b10.valor << endl;
    cout << b11.nome << ": " << b11.valor << endl;
    cout << b12.nome << ": " << b12.valor << endl;
    cout << b13.nome << ": " << b13.valor << endl;
    cout << b14.nome << ": " << b14.valor << endl;
    cout << b15.nome << ": " << b15.valor << endl;
}