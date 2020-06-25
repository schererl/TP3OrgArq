#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

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
    Nodo nodo_10 = Nodo(10, 3);
    Nodo nodo_11 = Nodo(11, 3);
    Nodo nodo_12 = Nodo(12, 3);
    Nodo nodo_13 = Nodo(13, 3);
    Nodo nodo_14 = Nodo(14, 3);
    Nodo nodo_15 = Nodo(15, 3);
    Nodo nodo_16 = Nodo(16, 3);

    Nodo *atual;
    Nodo *caminho_instrucao;
    Nodo auxiliar;
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
        atual->valores_sinais[1] = "00";
        atual->sinais[2] = i_ou_d;
        atual->valores_sinais[2] = "0";
        atual->sinais[3] = ir_esc;
        atual->valores_sinais[3] = "1";
        atual->sinais[4] = ula_fonte_b;
        atual->valores_sinais[4] = "01";
        atual->sinais[5] = ula_op;
        atual->valores_sinais[5] = "000";
        atual->sinais[6] = pc_esc;
        atual->valores_sinais[6] = "1";
        atual->sinais[7] = fonte_pc;
        atual->valores_sinais[7] = "00";
        //**************Nodo 1************//
        atual = &nodo_1;
        AlocaMemoria(nodo_1.numero_sinais, nodo_1.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "00";
        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "11";
        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "000";
        //***************Nodo 2*************//
        atual = &nodo_2;
        AlocaMemoria(nodo_2.numero_sinais, nodo_2.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "01";
        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "10";
        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "000";
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
        atual->valores_sinais[0] = "01";
        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "00";
        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "010";
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
        atual->valores_sinais[0] = "01";
        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "00";
        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "001";
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
        //**************Nodo 10**************//
        atual = &nodo_10;
        AlocaMemoria(nodo_10.numero_sinais, nodo_10.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "01";

        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "10";

        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "000"; //VERIRIFICAR

        //*************Nodo 11******************// 10 -> 11 && 12 -> 11
        atual = &nodo_11;
        
        AlocaMemoria(nodo_11.numero_sinais, nodo_11.id_estado);
        atual->sinais[0] = mem_para_reg;
        atual->valores_sinais[0] = "0";
        atual->sinais[1] = reg_dst;
        atual->valores_sinais[1] = "0";
        atual->sinais[2] = esc_reg;
        atual->valores_sinais[2] = "1";
    
        //************Nodo 12 *****************//
        
        atual = &nodo_12; 
        AlocaMemoria(nodo_12.numero_sinais, nodo_12.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "01";

        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "10";

        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "011"; 

        //*************** Nodo 13 *********************//
        atual = &nodo_13;
        AlocaMemoria(nodo_13.numero_sinais, nodo_13.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "01";

        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "10";

        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "100"; //VERIRIFICAR

        //*************** Nodo 14 *********************//
        atual = &nodo_14;
        AlocaMemoria(nodo_14.numero_sinais, nodo_14.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "01";

        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "10";

        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "101"; //VERIRIFICAR
        //************** Nodo 15 ******************//
        atual = &nodo_15; //sll srl
        AlocaMemoria(nodo_15.numero_sinais, nodo_15.id_estado);
        atual->sinais[0] = ula_fonte_a;
        atual->valores_sinais[0] = "10";

        atual->sinais[1] = ula_fonte_b;
        atual->valores_sinais[1] = "10";

        atual->sinais[2] = ula_op;
        atual->valores_sinais[2] = "010"; 
        //**************** Nodo 16 ******************//
        atual = &nodo_16; //sll srl
        AlocaMemoria(nodo_16.numero_sinais, nodo_16.id_estado);
        atual->sinais[0] = mem_para_reg;
        atual->valores_sinais[0] = "0";
        atual->sinais[1] = reg_dst;
        atual->valores_sinais[1] = "1";
        atual->sinais[2] = esc_reg;
        atual->valores_sinais[2] = "1";

    }

    void ZeraSinais()
    {
        ler_mem->valor = "0";
        ir_esc->valor = "0";
        pc_esc->valor = "0";
        ler_mem->valor = "0";
        esc_reg->valor = "0";
        esc_mem->valor = "0";
        pc_esc_cond->valor = "0";
        pc_esc->valor = "0";
        mem_para_reg-> valor = "0";
    }

    void CaminhoShift()
    {
        caminho_instrucao = (Nodo*)malloc(3 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_15;
        caminho_instrucao[1] = nodo_16;
        caminho_instrucao[2] = Nodo(-1, -1);
    }

    void CaminhoLoad()
    {
        caminho_instrucao = (Nodo*)malloc(4 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_2;
        caminho_instrucao[1] = nodo_3;
        caminho_instrucao[2] = nodo_4;
        caminho_instrucao[3] = Nodo(-1, -1);

    }

    void CaminhoStore()
    {
        caminho_instrucao = (Nodo*)malloc(3 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_2;
        caminho_instrucao[1] = nodo_5;
        caminho_instrucao[2] = Nodo(-1, -1);
    }

    void CaminhoTipoR()
    {
        caminho_instrucao = (Nodo*)malloc(3 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_6;
        caminho_instrucao[1] = nodo_7;
        caminho_instrucao[2] = Nodo(-1, -1);
    }

    void CaminhoBranchEq()
    {
        caminho_instrucao = (Nodo*)malloc(2 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_8;
        caminho_instrucao[1] = Nodo(-1, -1);
    }

    void CaminhoJump()
    {
        caminho_instrucao = (Nodo*)malloc(2 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_9;
        caminho_instrucao[1] = Nodo(-1, -1);
    }

    void CaminhoAddiu()
    {
        caminho_instrucao = (Nodo*)malloc(3 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_10;
        caminho_instrucao[1] = nodo_11;
        caminho_instrucao[2] = Nodo(-1, -1);
    }

    void CaminhoAndi()
    {
        caminho_instrucao = (Nodo*)malloc(3 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_12;
        caminho_instrucao[1] = nodo_11;
        caminho_instrucao[2] = Nodo(-1, -1);
    }

    void CaminhoLui()
    {
        caminho_instrucao = (Nodo*)malloc(3 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_13;
        caminho_instrucao[1] = nodo_11;
        caminho_instrucao[2] = Nodo(-1, -1);
    }

    void CaminhoOri()
    {
        caminho_instrucao = (Nodo*)malloc(3 * sizeof(Nodo));
        caminho_instrucao[0] = nodo_14;
        caminho_instrucao[1] = nodo_11;
        caminho_instrucao[2] = Nodo(-1, -1);
    }

    void AtualizaSinais()
    {

        for(int i = 0; i < auxiliar.numero_sinais;i++)
        {
            auxiliar.sinais[i]->valor = auxiliar.valores_sinais[i];
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


    Componentes::Barramento *opcode_instrucao;
    Componentes::Barramento *funct;
    
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
        Componentes::Barramento *opcode_instrucao,
        Componentes::Barramento *funct
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
        this->opcode_instrucao = opcode_instrucao;
        this->funct = funct;
        CriaNodos();
        IniciaCaminho();
    }

    void IniciaCaminho()
    {
        //free(caminho_instrucao);
        index_caminho = 0;
        caminho_instrucao = (Nodo*)malloc(2 * sizeof(Nodo));
        caminho_instrucao[0] = raiz;
        caminho_instrucao[1] = nodo_1;
        ProximaInstrucao();
    }


    void ProximaInstrucao()
    {
        ZeraSinais();
        //atual = caminho_instrucao[index_caminho];
        auxiliar = caminho_instrucao[index_caminho];
        index_caminho++;
        if(auxiliar.id_estado == -1)
        {
            IniciaCaminho();
            return;
        }
        /*
        else if(auxiliar.id_estado == 1) {
            
            cout<< "INSTRUÇÃO ATUAL: " << auxiliar.id_estado << endl;
            BuscaInstrucao();
            //return;
        }
        */
        AtualizaSinais();
        
    }


    void BuscaInstrucao()
    {
        if(auxiliar.id_estado != 1) return;
        
        string opcode = opcode_instrucao->valor;
        free(caminho_instrucao);
        index_caminho = 0;
        if(opcode == "100011") CaminhoLoad();

        else if(opcode == "101011") CaminhoStore();

        else if(opcode == "000000")
        { 
            if(funct->valor == "000000" || funct->valor == "000010") CaminhoShift();
            
            else CaminhoTipoR();
        }
        else if(opcode == "000100") CaminhoBranchEq();

        else if(opcode == "000010") CaminhoJump();

        else if(opcode == "001001") CaminhoAddiu();

        else if(opcode == "001100") CaminhoAndi();
        
        else if(opcode == "001111") CaminhoLui();

        else if(opcode == "001101") CaminhoOri();
        //else IniciaCaminho();
        //ProximaInstrucao();
    }

    
    void Imprime()
    {
        cout << "\n=======================================================================\nestado atual: " << auxiliar.id_estado << endl;
        cout << "sinais atualizados: " << auxiliar.numero_sinais << endl;
        for(int i = 0; i < auxiliar.numero_sinais;i++)
        {
            cout << auxiliar.sinais[i]->nome << " = " << auxiliar.valores_sinais[i] << endl;
        }
        cout << "PROXIMA INSTRUÇÃO: " << caminho_instrucao[index_caminho].id_estado << endl;
        
    }
};

/*
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

    Componentes::Barramento instrucao = c.CriaBarramento("opcode_instrucao");
    instrucao.valor = "100011";


   BlocoControle controle = BlocoControle(&b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9, &b10, &b11, &b12, &b13, &instrucao);
   while(true)
   {

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
    int n;
    cin >> n;

    if(n == -1) break;
    if(n == 2)
    {
        string str;
        cin >> str;
        instrucao.valor = str;
    }
    controle.ProximaInstrucao();

   }
   
}
*/