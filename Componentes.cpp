using std namespace;
class Componentes
{
    struct Barramento
    {
        string nome_barramento;
        string valor;
        Barramento(string nome_barramento)
        {
            this->nome_barramento = nome_barramento;
            this->valor = 0;
        }
    };

    struct Multiplexador
    {
        string nome_multiplexador;
        Barramento *entrada;  //vetor de barramentos de entradas
        int numero_entradas;  //numero de barramentos de entradas
        Barramento *saida;   //barramento de saída

        Multiplexador(string nome_multiplexador, Barramento *entrada, int numero_entradas, Barramento *saida)
        {
            this->nome_multiplexador = nome_multiplexador;
            this->entrada -> entrada;
            this->numero_entradas = numero_entradas;
            this->saida -> saida;
        }
    };
}