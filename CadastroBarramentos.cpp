//
// Created by rafael on 18/06/2020.
//

class CadastroBarramentos{
    // CONTROLE
    //Lado Direito Bloco de Controle
    Componentes::Barramento b_fonte_pc = c.CriaBarramento("FontePC")    //Controle
    Componentes::Barramento b_ula_op = c.CriaBarramento("UlaOP")    //Controle
    Componentes::Barramento b_ula_fonte_b = c.CriaBarramento("UlaFonteB")    //Controle
    Componentes::Barramento b_ula_fonte_a = c.CriaBarramento("UlaFonteA")    //Controle
    Componentes::Barramento b_esc_reg = c.CriaBarramento("EscReg")    //Controle
    Componentes::Barramento b_reg_dest = c.CriaBarramento("RegDest")    //Controle
    //Lado Esquerdol Bloco de Controle
    Componentes::Barramento b_pc_esc_cond = c.CriaBarramento("PCEscCond")    // Controle
    Componentes::Barramento b_pc_esc = c.CriaBarramento("PCEsc")    // Controle
    Componentes::Barramento b_ioud = c.CriaBarramento("IouD")    //Controle
    Componentes::Barramento b_ler_mem = c.CriaBarramento("LerMem")    //Controle
    Componentes::Barramento b_esc_mem = c.CriaBarramento("EscMem")    //Controle
    Componentes::Barramento b_mem_para_reg = c.CriaBarramento("MemParaReg")    //Controle
    Componentes::Barramento b_ir_esc = c.CriaBarramento("IREsc")    //Controle
    // FIM CONTROLE

    //Seguindo o fluxo de dados...
    Componentes::Barramento b_pc_in = c.CriaBarramento("Barramento Entrada PC");
    Componentes::Barramento b_pc_out = c.CriaBarramento("Barramento Saída PC");
    Componentes::Barramento b_pc_out_mux = c.CriaBarramento("Barramento Saída PC para mux");

    Componentes::Barramento b_mem_in = c.CriaBarramento("Barramento Endereço Memória");
    Componentes::Barramento b_mem_out = c.CriaBarramento("Barramento Saída Memória de Dados");
    Componentes::Barramento b_ir_out = c.CriaBarramento("Barramento Saída IR");
    Componentes::Barramento b_data_reg_out = c.CriaBarramento("Barramento Registrador de dados da Memória");
    Componentes::Barramento b_op_code_controle = c.CriaBarramento("Entrada Bloco de Controle - OP Code");
    Componentes::Barramento b_b_reg_in_1 = c.CriaBarramento("Registrador a ser lido 1");
    Componentes::Barramento b_reg_in_2 = c.CriaBarramento("Registrador a ser lido 2");
    Componentes::Barramento b_reg_escr = c.CriaBarramento("Registrador a ser escrito");

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
    Componentes::Barramento b_saida_ula = c.CriaBarramento("Barramento de Saída da Ula");

    Componentes::Barramento b_desl_esq_ir_out = c.CriaBarramento("Barramento de Deslocamento à esquerda da saída do IR");
    Componentes::Barramento b_desl_esq_mux_in = c.CriaBarramento("Barramento Entrada do MUX da Saída de deslocamento a esq IR");

    Componentes::Barramento b_saida_ula = c.CriaBarramento("Barramento do Registrador de Saída da Ula");


};
