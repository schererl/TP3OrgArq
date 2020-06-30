
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "BaseDados.cpp"
#include "OperadorBits.cpp"
#include "Componentes.cpp"
#include "BlocoControle.cpp"


void ImprimeBanco()
{
    cout << "===BANCO DE REGISTRADORES===" << endl;
    cout << "________________________" << endl;
    for (auto const& x : banco_reg)
    {
        cout << "|" <<  x.first << "| " << x.second << "|" << endl;
    }
    cout << "________________________" << endl;
}

void ImprimeMemoria()
{
    cout << "===MEMORIA===" << endl;
    cout << "________________________" << endl;
    for (auto const& x : memoria)
    {
        cout << "|" <<  x.first << "| " << x.second << "|" << endl;
    }
    cout << "________________________" << endl;
}

string GeraMemoria(char* instr, char* dado)
{
    string endereco_instrucao = "0x00400000";
    string endereco_variaveis = "0x10010000";
    
    vector<string> instrucoes;
    vector<string> dados;

    std::ifstream file(instr);
    std::string buff_inst;
    std::ifstream file2(dado);
    std::string buff_dado;

    while (std::getline(file, buff_inst)) 
    {
        instrucoes.push_back(buff_inst);
    }
    
    while (std::getline(file2, buff_dado)) 
    {
        dados.push_back(buff_dado);
    }

    if(instrucoes.size() <= 1)
    { 
        cout << "Arquivo não encontrado" << endl;
        return "-1";
    }

    for(int i = 0;i < instrucoes.size();i++)
    {
        memoria[endereco_instrucao] = instrucoes[i];
        OperadorBits::SumHex_1(endereco_instrucao);
        OperadorBits::SumHex_1(endereco_instrucao);
        OperadorBits::SumHex_1(endereco_instrucao);
        OperadorBits::SumHex_1(endereco_instrucao); 
    }
    
    for(int j = 0; j < dados.size(); j++)
    {
        memoria[endereco_variaveis] = dados[j];
        OperadorBits::SumHex_1(endereco_variaveis);
        OperadorBits::SumHex_1(endereco_variaveis);
        OperadorBits::SumHex_1(endereco_variaveis);
        OperadorBits::SumHex_1(endereco_variaveis);
    }

    return OperadorBits::HexaToBin(endereco_instrucao);
}

void SalvaSaida()
{
    std::ofstream myfile("output/memoria_output.txt");
    if(myfile.is_open())
    {
        myfile << "===BANCO DE REGISTRADORES===" << endl;
        myfile << "________________________" << endl;
        for (auto const& x : banco_reg)
        {
            myfile << "|" <<  x.first << "| " << x.second << "|" << endl;
        }
        myfile << "________________________" << endl; 

        myfile << "\n\n===MEMORIA===" << endl;
        myfile << "________________________" << endl;
        for (auto const& x : memoria)
        {
            myfile << "|" <<  x.first << "| " << x.second << "|" << endl;
        }
        myfile << "________________________" << endl;
        myfile.close();
    }
}

int main(int argc, char **argv)
{
    if(argc < 4)
    {
        std::cout << "executar no forma ./run (nome_arquivo) (operacao)";
        return -1;
    }
    bool step_by_step = false;
    if(atoi(argv[3]) == 1) step_by_step = true;    
    
    Componentes c;
    
    //** BARRAMENTOS **/

    // CONTROLE
    Componentes::Barramento b_fonte_pc = c.CriaBarramento("FontePC", 1);    //Controle
    Componentes::Barramento b_ula_op = c.CriaBarramento("UlaOP", 2);    //Controle
    Componentes::Barramento b_ula_fonte_b = c.CriaBarramento("UlaFonteB", 2);    //Controle
    Componentes::Barramento b_ula_fonte_a = c.CriaBarramento("UlaFonteA", 1);    //Controle
    Componentes::Barramento b_esc_reg = c.CriaBarramento("EscReg" ,1);    //Controle
    Componentes::Barramento b_reg_dest = c.CriaBarramento("RegDest", 1);    //Controle
    Componentes::Barramento b_pc_esc_cond = c.CriaBarramento("PCEscCond",1);    // Controle
    Componentes::Barramento b_pc_esc = c.CriaBarramento("PCEsc", 1);    // Controle
    Componentes::Barramento b_controle_pc = c.CriaBarramento("Controle PC", 1);
    Componentes::Barramento b_ioud = c.CriaBarramento("IouD", 1);    //Controle
    Componentes::Barramento b_ler_mem = c.CriaBarramento("LerMem", 1);    //Controle
    Componentes::Barramento b_esc_mem = c.CriaBarramento("EscMem", 1);    //Controle
    Componentes::Barramento b_mem_para_reg = c.CriaBarramento("MemParaReg", 1);    //Controle
    Componentes::Barramento b_ir_esc = c.CriaBarramento("IREsc", 1);    //Controle
    
    // DADOS
    Componentes::Barramento b_pc_in = c.CriaBarramento("Barramento Entrada PC", 32);
    Componentes::Barramento b_pc_out = c.CriaBarramento("Barramento Saída PC", 32);
    Componentes::Barramento b_mem_in = c.CriaBarramento("Barramento Endereço Memória", 32);
    Componentes::Barramento b_mem_out = c.CriaBarramento("Barramento Saída Memória de Dados", 32);
    Componentes::Barramento b_ir_out = c.CriaBarramento("Barramento Saída IR", 32);
    Componentes::Barramento b_data_reg_out = c.CriaBarramento("Barramento Registrador de dados da Memória", 32);
    Componentes::Barramento b_op_code_controle = c.CriaBarramento("Barramento Entrada Bloco de Controle - OP Code", 32);
    Componentes::Barramento b_end_salto_incond = c.CriaBarramento("Barramento de Endereço de Salto Incondicional", 26);
    Componentes::Barramento b_end_salto_incond_desloc = c.CriaBarramento("Barramento de Endereço de Salto Incondicional DESLOCADO", 28);
    Componentes::Barramento b_reg_in_1 = c.CriaBarramento("Registrador a ser lido 1", 5);
    Componentes::Barramento b_reg_in_2 = c.CriaBarramento("Registrador a ser lido 2", 5);
    Componentes::Barramento b_reg_escr = c.CriaBarramento("Registrador a ser escrito", 5);
    Componentes::Barramento b_reg_escr_out = c.CriaBarramento("Registrador a ser escrito saida mux", 5);
    Componentes::Barramento b_imediato = c.CriaBarramento("Barramento de Imediato", 16);
    Componentes::Barramento b_funct = c.CriaBarramento("Barramento Funct", 6);
    Componentes::Barramento b_controle_ula_op = c.CriaBarramento("Controle ULA", 3); //saida do circuito combinaciona que entra no sinal de controle da ula
    Componentes::Barramento b_dado_escr_reg_in = c.CriaBarramento("Barramento dado a ser escrito em banco de registradores", 32);
    Componentes::Barramento b_entrada_reg_A = c.CriaBarramento("Barramento Entrada Reg A", 32);
    Componentes::Barramento b_entrada_reg_B = c.CriaBarramento("Barramento Entrada Reg B", 32);
    Componentes::Barramento b_saida_reg_A = c.CriaBarramento("Barramento Saída Reg A", 32);
    Componentes::Barramento b_saida_reg_B = c.CriaBarramento("Barramento Saída Reg B", 32);
    Componentes::Barramento b_ext_sinal = c.CriaBarramento("Barramento Extensão de sinal", 32);
    Componentes::Barramento b_desl_esq = c.CriaBarramento("Barramento Deslocamento à esquerda", 32);
    Componentes::Barramento b_incrementa_pc_4 = c.CriaBarramento("Barramento Saída PC + 4", 32);
    b_incrementa_pc_4.valor = "00000000000000000000000000000100";
    Componentes::Barramento b_entrada_ula_a = c.CriaBarramento("Barramento de entrada da Ula A", 32);
    Componentes::Barramento b_entrada_ula_b = c.CriaBarramento("Barramento de entrada da Ula B", 32);
    Componentes::Barramento b_saida_ula_op = c.CriaBarramento("Barramento de Operação da Ula", 32);
    Componentes::Barramento b_saida_ula_flag = c.CriaBarramento("Barramento de Saída da Ula flag", 1);
    Componentes::Barramento b_desl_esq_ir_out = c.CriaBarramento("Barramento de Deslocamento à esquerda da saída do IR", 32);
    Componentes::Barramento b_trunca_pc = c.CriaBarramento("Barramento com 4 bits de PC para concatenar com novo endereço", 4);
    Componentes::Barramento b_salto_pc = c.CriaBarramento("Barramento Entrada do MUX de entrada de PC para salto Incondicional", 32); //b_end_salto_indond_desloc + b_trunca_pc
    Componentes::Barramento b_saida_r_ula = c.CriaBarramento("Barramento do Registrador de Saída da Ula", 32);


    //**MULTIPLEXADORES**/
   
    Componentes::Barramento **vb_pc_mem;
    vb_pc_mem = (Componentes::Barramento**)malloc(2 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 2;i++) vb_pc_mem[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_pc_mem[0] = &b_pc_out;
    vb_pc_mem[1] = &b_saida_r_ula;
    Componentes::Multiplexador m_pc_memoria = c.CriaMultiplexador("Mux de entrada para memória", vb_pc_mem, &b_mem_in, &b_ioud);
    
    Componentes::Barramento **vb_reg_esc;
    vb_reg_esc = (Componentes::Barramento**)malloc(2 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 2;i++) vb_reg_esc[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_reg_esc[0] = &b_reg_in_2;
    vb_reg_esc[1] = &b_reg_escr;
    Componentes::Multiplexador m_instr_bancoreg = c.CriaMultiplexador("Mux de registrador a ser escrito", vb_reg_esc, &b_reg_escr_out, &b_reg_dest);
    
    Componentes::Barramento **vb_dadomem_bancoreg;
    vb_dadomem_bancoreg = (Componentes::Barramento**)malloc(2 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 2;i++) vb_dadomem_bancoreg[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_dadomem_bancoreg[0] = &b_saida_r_ula;
    vb_dadomem_bancoreg[1] = &b_data_reg_out;
    Componentes::Multiplexador m_dadomem_bancoreg = c.CriaMultiplexador("Mux de dado para escrita em reg", vb_dadomem_bancoreg, &b_dado_escr_reg_in, &b_mem_para_reg);
    
    Componentes::Barramento **vb_ulta_fonte_1;
    vb_ulta_fonte_1 = (Componentes::Barramento**)malloc(2 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 3;i++) vb_ulta_fonte_1[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_ulta_fonte_1[0] = &b_pc_out;
    vb_ulta_fonte_1[1] = &b_saida_reg_A;
    vb_ulta_fonte_1[2] = &b_saida_reg_B;
    Componentes::Multiplexador m_fonte_ula_1 = c.CriaMultiplexador("Mux de 1º fonte para ULA", vb_ulta_fonte_1, &b_entrada_ula_a, &b_ula_fonte_a);
    
    Componentes::Barramento **vb_ulta_fonte_2;
    vb_ulta_fonte_2 = (Componentes::Barramento**)malloc(4* sizeof(Componentes::Barramento*));
    for(int i = 0; i < 4;i++) vb_ulta_fonte_2[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_ulta_fonte_2[0] = &b_saida_reg_B;
    vb_ulta_fonte_2[1] = &b_incrementa_pc_4;
    vb_ulta_fonte_2[2] = &b_ext_sinal;
    vb_ulta_fonte_2[3] = &b_desl_esq;
    Componentes::Multiplexador m_fonte_ula_2 = c.CriaMultiplexador("Mux de 2º fonte para ULA", vb_ulta_fonte_2, &b_entrada_ula_b, &b_ula_fonte_b);
    
    Componentes::Barramento **vb_define_pc;
    vb_define_pc = (Componentes::Barramento**)malloc(3 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 3;i++) vb_define_pc[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_define_pc[0] = &b_saida_ula_op;
    vb_define_pc[1] = &b_saida_r_ula;
    vb_define_pc[2] = &b_salto_pc;
    Componentes::Multiplexador m_define_pc = c.CriaMultiplexador("Mux para a proxima instrução", vb_define_pc, &b_pc_in, &b_fonte_pc);
    
    //** MEMORIA **/
    Componentes::Memoria memoria = c.CriaMemoria(&b_mem_in, &b_mem_out, &b_saida_reg_B, &b_ler_mem, &b_esc_mem);
    //** BANCO REGISTRADORES **/
    Componentes::BancoReg banco_registradores = c.CriaBancoReg(&b_reg_in_1, &b_reg_in_2, &b_reg_escr_out, &b_dado_escr_reg_in, &b_entrada_reg_A, &b_entrada_reg_B, &b_esc_reg);
    //** REGISTRADORES INVISIVEIS **/
    Componentes::RegistradorInvisivel r_pc = c.CriaRegistradorInvisivel("Registrador de PC", &b_pc_in, &b_pc_out, &b_controle_pc, "0xffffffff");
    Componentes::RegistradorInvisivel r_instrucao = c.CriaRegistradorInvisivel("Registrador de Instrução", &b_mem_out, &b_ir_out, &b_ir_esc, "0xfffffffe");
    Componentes::RegistradorInvisivel r_dado = c.CriaRegistradorInvisivel("Registrador de Dado", &b_mem_out, &b_data_reg_out, NULL, "0xfffffffd");
    Componentes::RegistradorInvisivel r_A = c.CriaRegistradorInvisivel("Registrador A", &b_entrada_reg_A, &b_saida_reg_A, NULL, "0xfffffffc");
    Componentes::RegistradorInvisivel r_B = c.CriaRegistradorInvisivel("Registrador B", &b_entrada_reg_B, &b_saida_reg_B, NULL, "0xfffffffb");
    Componentes::RegistradorInvisivel r_ula = c.CriaRegistradorInvisivel("Registrador ULA", &b_saida_ula_op, &b_saida_r_ula, NULL, "0xfffffffa");
    //** ULA **//
    Componentes::ULA ula = c.CriaULA(&b_entrada_ula_a, &b_entrada_ula_b, &b_saida_ula_op, &b_saida_ula_flag, &b_controle_ula_op);
    //** BLOCO DE CONTROLE **//
    BlocoControle bloco_controle = BlocoControle(&b_pc_esc_cond, &b_pc_esc, &b_ioud, &b_ler_mem, &b_esc_mem, &b_mem_para_reg, &b_ir_esc, &b_fonte_pc, &b_ula_op, &b_ula_fonte_b, &b_ula_fonte_a, &b_esc_reg, &b_reg_dest, &b_op_code_controle, &b_funct);
    //** CIRCUITOS COMBINACIONAIS NOS BARRAMENTOS **//
    Componentes::CircuitoBarramento cb = c.CriaCircuitoBarramento();
    
    vector<string> output;
    string addr_pop = GeraMemoria(argv[1], argv[2]);
    if(addr_pop == "-1") return-1;
    
    while(true)
    {

    if(step_by_step)
    {
        int i = 0;
        cin >> i;
        if(i == -1) break;
        if(i == 2)
        {
            ImprimeBanco();
            continue;
        }
        if(i==3)
        {
            ImprimeMemoria();
            continue;
        }
    }
    else
    {
        if(bloco_controle.GetEtapa() == 0)
        {
            ImprimeBanco();
            ImprimeMemoria();
        }
    }
    


    bloco_controle.Imprime();
    
    //leitura de registradores multiciclo
    r_pc.BuscaReg();
    r_ula.BuscaReg();
    r_A.BuscaReg();
    r_B.BuscaReg();
    
    cb.BifurcaPC(&b_pc_out, &b_trunca_pc); //calculo para jump
    
    m_pc_memoria.Opera();
    
    if(b_mem_in.valor ==  addr_pop)
    {
        cout << "FIM EXECUÇÃO" << endl;
        SalvaSaida();
        break;
    }

    //consulta em memória
    m_pc_memoria.Imprime();
    memoria.Opera();
    memoria.Imprime();

    //grava instrução/dado nos registradores
    r_instrucao.Opera();
    r_instrucao.Imprime();
    r_dado.BuscaReg();
    r_dado.GravaRegistrador();
    r_dado.Imprime();
    
    
    //separação de instrução
    cb.SeparaInstrucao(&b_ir_out, &b_reg_in_1, &b_reg_in_2, &b_reg_escr, &b_imediato ,&b_op_code_controle, &b_funct);
    m_instr_bancoreg.Opera();
    m_instr_bancoreg.Imprime();
    m_instr_bancoreg.ImprimeEntradas(2);
    m_dadomem_bancoreg.Opera();
    m_dadomem_bancoreg.Imprime();
    m_dadomem_bancoreg.ImprimeEntradas(2);
    //duas últimas entradas de ula fonte 2
    cb.ExtensaoSinal(&b_imediato, &b_ext_sinal); 
    cb.DeslocametoBits(&b_ext_sinal, &b_desl_esq); 
    
    bloco_controle.BuscaInstrucao(); //recebe opcode: arrumar isto

    //acesso ao banco de registradores
    banco_registradores.Opera();
    banco_registradores.Imprime();
    r_A.GravaRegistrador();
    r_A.Imprime();
    r_B.GravaRegistrador();
    r_B.Imprime();

    //opera ula
    m_fonte_ula_1.Opera();
    m_fonte_ula_1.Imprime();
    m_fonte_ula_1.ImprimeEntradas(3);
    m_fonte_ula_2.Opera();
    m_fonte_ula_2.Imprime();
    m_fonte_ula_2.ImprimeEntradas(4);
    cb.OperacaoULA(&b_ula_op, &b_funct, &b_controle_ula_op);
    ula.Opera();
    ula.Imprime();
    r_ula.GravaRegistrador();
    r_ula.Imprime();
    
    //define pc
    cb.DeslocametoBits(&b_end_salto_incond, &b_end_salto_incond_desloc); //instrução de salto incondicional
    cb.ConcatenaPCSalto(&b_trunca_pc, &b_end_salto_incond_desloc, &b_salto_pc);
    m_define_pc.Opera();
    m_define_pc.Imprime();
    
    //leitura de instrução
    cb.EntradaPC(&b_saida_ula_flag, &b_pc_esc_cond, &b_pc_esc, &b_controle_pc);
    r_pc.GravaRegistrador();
    r_pc.Imprime();
    
    bloco_controle.ProximaInstrucao();
    }
}


