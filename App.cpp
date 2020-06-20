#include "BaseDados.cpp"
#include "OperadorBits.cpp"
#include "Componentes.cpp"
#include "BlocoControle.cpp"

int main()
{
    Componentes c;
    
    //** BARRAMENTOS **/

    // CONTROLE
    //Lado Direito Bloco de Controle
    Componentes::Barramento b_fonte_pc = c.CriaBarramento("FontePC");    //Controle

    //inverter nomes, aluop é o sinal de entrada da ula
    Componentes::Barramento b_ula_op = c.CriaBarramento("UlaOP");    //Controle
    
    Componentes::Barramento b_ula_fonte_b = c.CriaBarramento("UlaFonteB");    //Controle
    Componentes::Barramento b_ula_fonte_a = c.CriaBarramento("UlaFonteA");    //Controle
    Componentes::Barramento b_esc_reg = c.CriaBarramento("EscReg");    //Controle
    Componentes::Barramento b_reg_dest = c.CriaBarramento("RegDest");    //Controle
    //Lado Esquerdol Bloco de Controle
    Componentes::Barramento b_pc_esc_cond = c.CriaBarramento("PCEscCond");    // Controle
    Componentes::Barramento b_pc_esc = c.CriaBarramento("PCEsc");    // Controle
    Componentes::Barramento b_controle_pc = c.CriaBarramento("Controle PC");

    Componentes::Barramento b_ioud = c.CriaBarramento("IouD");    //Controle
    Componentes::Barramento b_ler_mem = c.CriaBarramento("LerMem");    //Controle
    Componentes::Barramento b_esc_mem = c.CriaBarramento("EscMem");    //Controle
    Componentes::Barramento b_mem_para_reg = c.CriaBarramento("MemParaReg");    //Controle
    Componentes::Barramento b_ir_esc = c.CriaBarramento("IREsc");    //Controle
    // FIM CONTROLE

    //Seguindo o fluxo de dados...
    Componentes::Barramento b_pc_in = c.CriaBarramento("Barramento Entrada PC");
    Componentes::Barramento b_pc_out = c.CriaBarramento("Barramento Saída PC");
    
    //Componentes::Barramento b_pc_out_mux = c.CriaBarramento("Barramento Saída PC para mux");
    Componentes::Barramento b_mem_in = c.CriaBarramento("Barramento Endereço Memória");
    Componentes::Barramento b_mem_out = c.CriaBarramento("Barramento Saída Memória de Dados");
    Componentes::Barramento b_ir_out = c.CriaBarramento("Barramento Saída IR");
    Componentes::Barramento b_data_reg_out = c.CriaBarramento("Barramento Registrador de dados da Memória");
    Componentes::Barramento b_op_code_controle = c.CriaBarramento("Barramento Entrada Bloco de Controle - OP Code");
    
    Componentes::Barramento b_end_salto_incond = c.CriaBarramento("Barramento de Endereço de Salto Incondicional");
    Componentes::Barramento b_end_salto_incond_desloc = c.CriaBarramento("Barramento de Endereço de Salto Incondicional DESLOCADO");

    Componentes::Barramento b_reg_in_1 = c.CriaBarramento("Registrador a ser lido 1");
    Componentes::Barramento b_reg_in_2 = c.CriaBarramento("Registrador a ser lido 2");
    Componentes::Barramento b_reg_escr = c.CriaBarramento("Registrador a ser escrito");
    Componentes::Barramento b_reg_escr_out = c.CriaBarramento("Registrador a ser escrito saida mux");
    
    Componentes::Barramento b_imediato = c.CriaBarramento("Barramento de Imediato");
    Componentes::Barramento b_funct = c.CriaBarramento("Barramento Funct");
    Componentes::Barramento b_controle_ula_op = c.CriaBarramento("Controle ULA"); //saida do circuito combinaciona que entra no sinal de controle da ula

    Componentes::Barramento b_dado_escr_reg_in = c.CriaBarramento("Barramento dado a ser escrito em banco de registradores");
    Componentes::Barramento b_entrada_reg_A = c.CriaBarramento("Barramento Entrada Reg A");
    Componentes::Barramento b_entrada_reg_B = c.CriaBarramento("Barramento Entrada Reg B");
    Componentes::Barramento b_saida_reg_A = c.CriaBarramento("Barramento Saída Reg A");
    Componentes::Barramento b_saida_reg_B = c.CriaBarramento("Barramento Saída Reg B");
    Componentes::Barramento b_ext_sinal = c.CriaBarramento("Barramento Extensão de sinal");
    Componentes::Barramento b_desl_esq = c.CriaBarramento("Barramento Deslocamento à esquerda");
    Componentes::Barramento b_incrementa_pc_4 = c.CriaBarramento("Barramento Saída PC + 4");
    Componentes::Barramento b_entrada_ula_a = c.CriaBarramento("Barramento de entrada da Ula A");
    Componentes::Barramento b_entrada_ula_b = c.CriaBarramento("Barramento de entrada da Ula B");
    Componentes::Barramento b_saida_ula_op = c.CriaBarramento("Barramento de Operação da Ula");
    Componentes::Barramento b_saida_ula_flag = c.CriaBarramento("Barramento de Saída da Ula flag");
    Componentes::Barramento b_desl_esq_ir_out = c.CriaBarramento("Barramento de Deslocamento à esquerda da saída do IR");
    
    Componentes::Barramento b_trunca_pc = c.CriaBarramento("Barramento com 4 bits de PC para concatenar com novo endereço");
    Componentes::Barramento b_salto_pc = c.CriaBarramento("Barramento Entrada do MUX de entrada de PC para salto Incondicional"); //b_end_salto_indond_desloc + b_trunca_pc


    Componentes::Barramento b_saida_r_ula = c.CriaBarramento("Barramento do Registrador de Saída da Ula");


    //**MULTIPLEXADORES**/
    //Componentes::Barramento *vb_pc_mem = (Componentes::Barramento*)malloc(2 * sizeof(Componentes::Barramento));
    
    Componentes::Barramento **vb_pc_mem;
    vb_pc_mem = (Componentes::Barramento**)malloc(2 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 2;i++) vb_pc_mem[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_pc_mem[0] = &b_pc_out;
    vb_pc_mem[1] = &b_saida_r_ula;
    Componentes::Multiplexador m_pc_memoria = c.CriaMultiplexador("Mux de entrada para memória", *vb_pc_mem, &b_mem_in, &b_ioud);
    
    Componentes::Barramento **vb_reg_esc;
    vb_reg_esc = (Componentes::Barramento**)malloc(2 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 2;i++) vb_reg_esc[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_reg_esc[0] = &b_reg_in_2;
    vb_reg_esc[1] = &b_reg_escr;
    Componentes::Multiplexador m_instr_bancoreg = c.CriaMultiplexador("Mux de registrador a ser escrito", *vb_reg_esc, &b_reg_escr_out, &b_reg_dest);
    
    Componentes::Barramento **vb_dadomem_bancoreg;
    vb_dadomem_bancoreg = (Componentes::Barramento**)malloc(2 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 2;i++) vb_dadomem_bancoreg[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_dadomem_bancoreg[0] = &b_saida_r_ula;
    vb_dadomem_bancoreg[1] = &b_data_reg_out;
    Componentes::Multiplexador m_dadomem_bancoreg = c.CriaMultiplexador("Mux de dado para escrita em reg", *vb_dadomem_bancoreg, &b_dado_escr_reg_in, &b_mem_para_reg);
    
    Componentes::Barramento **vb_ulta_fonte_1;
    vb_ulta_fonte_1 = (Componentes::Barramento**)malloc(2 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 2;i++) vb_ulta_fonte_1[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_ulta_fonte_1[0] = &b_pc_out;
    vb_ulta_fonte_1[1] = &b_saida_reg_A;
    Componentes::Multiplexador m_fonte_ula_1 = c.CriaMultiplexador("Mux de 1º fonte para ULA", *vb_ulta_fonte_1, &b_saida_reg_A, &b_ula_fonte_a);
    
    Componentes::Barramento **vb_ulta_fonte_2;
    vb_ulta_fonte_2 = (Componentes::Barramento**)malloc(4* sizeof(Componentes::Barramento*));
    for(int i = 0; i < 4;i++) vb_reg_esc[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_ulta_fonte_2[0] = &b_saida_reg_B;
    vb_ulta_fonte_2[1] = &b_incrementa_pc_4;
    vb_ulta_fonte_2[2] = &b_ext_sinal;
    vb_ulta_fonte_2[3] = &b_desl_esq;
    Componentes::Multiplexador m_fonte_ula_2 = c.CriaMultiplexador("Mux de 2º fonte para ULA", *vb_ulta_fonte_2, &b_entrada_ula_b, &b_ula_fonte_b);
    
    Componentes::Barramento **vb_define_pc;
    vb_define_pc = (Componentes::Barramento**)malloc(3 * sizeof(Componentes::Barramento*));
    for(int i = 0; i < 3;i++) vb_define_pc[i] = (Componentes::Barramento*)malloc(1 * sizeof(Componentes::Barramento));
    vb_ulta_fonte_2[0] = &b_saida_ula_op;
    vb_ulta_fonte_2[1] = &b_saida_r_ula;
    vb_ulta_fonte_2[2] = &b_salto_pc;
    Componentes::Multiplexador m_define_pc = c.CriaMultiplexador("Mux para a proxima instrução", *vb_define_pc, &b_fonte_pc, &b_ula_op);
    
    //** MEMORIA **/
    Componentes::Memoria memoria = c.CriaMemoria(&b_mem_in, &b_mem_out, &b_saida_r_ula, &b_ler_mem, &b_esc_mem);

    //** BANCO REGISTRADORES **/
    Componentes::BancoReg banco_registradores = c.CriaBancoReg(&b_reg_in_1, &b_reg_in_2, &b_reg_escr_out, &b_dado_escr_reg_in, &b_entrada_reg_A, &b_entrada_reg_B, &b_esc_reg);
   
    //** REGISTRADORES INVISIVEIS **/
    Componentes::RegistradorInvisivel r_pc = c.CriaRegistradorInvisivel("registrador de PC", &b_pc_in, &b_pc_out, &b_controle_pc, "verificar");
    Componentes::RegistradorInvisivel r_instrucao = c.CriaRegistradorInvisivel("Registrador de Instrução", &b_mem_out, &b_ir_out, &b_ir_esc, "verificar");
    Componentes::RegistradorInvisivel r_dado = c.CriaRegistradorInvisivel("Registrador de Instrução", &b_mem_out, &b_data_reg_out, NULL, "verificar");
    Componentes::RegistradorInvisivel r_A = c.CriaRegistradorInvisivel("Registrador A", &b_entrada_reg_A, &b_saida_reg_A, NULL, "verificar");
    Componentes::RegistradorInvisivel r_B = c.CriaRegistradorInvisivel("Registrador B", &b_entrada_reg_B, &b_saida_reg_B, NULL, "verificar");
    Componentes::RegistradorInvisivel r_ula = c.CriaRegistradorInvisivel("Registrador ULA", &b_saida_ula_op, &b_saida_r_ula, NULL, "verificar");

    //** ULA **//
    Componentes::ULA ula = c.CriaULA(&b_entrada_ula_a, &b_entrada_ula_b, &b_saida_ula_op, &b_saida_ula_flag, &b_controle_ula_op);

    //** BLOCO DE CONTROLE **//
    BlocoControle bloco_controle = BlocoControle(&b_pc_esc_cond, &b_pc_esc, &b_ioud, &b_ler_mem, &b_esc_mem, &b_mem_para_reg, &b_ir_esc, &b_fonte_pc, &b_ula_op, &b_ula_fonte_b, &b_ula_fonte_a, &b_esc_reg, &b_reg_dest, &b_op_code_controle);

    //** CIRCUITOS COMBINACIONAIS NOS BARRAMENTOS **//
    Componentes::CircuitoBarramento cb = c.CriaCircuitoBarramento();
    cb.EntradaPC(&b_saida_ula_flag, &b_pc_esc_cond, &b_pc_esc, &b_controle_pc);
    
    //slipt instrução
    cb.SeparaInstrucao(&b_ir_out, &b_reg_in_1, &b_reg_in_2, &b_reg_escr, &b_imediato ,&b_op_code_controle, &b_funct);
    cb.ExtensaoSinal(&b_imediato, &b_ext_sinal);
    cb.DeslocametoBits(&b_ext_sinal, &b_desl_esq);
    
    //pc
    cb.BifurcaPC(&b_pc_out, &b_trunca_pc);
    cb.DeslocametoBits(&b_end_salto_incond, &b_end_salto_incond_desloc);
    cb.ConcatenaPCSalto(&b_trunca_pc, &b_end_salto_incond_desloc, &b_salto_pc);

    //sinal da ula
    cb.OperacaoULA(&b_ula_op, &b_funct, &b_controle_ula_op);

}

