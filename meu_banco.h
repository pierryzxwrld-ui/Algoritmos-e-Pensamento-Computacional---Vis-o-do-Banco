#ifndef MEU_BANCO_H
#define MEU_BANCO_H

#define MAX_CLIENTES 100
#define MAX_MOVIMENTOS 50


struct Movimento {
    char operacao[20];   
    int tipoConta;       
    float valor;
};


struct Cliente {
    char nome[50];
    int numero;             

    int temCorrente;        
    int temSalario;
    int temPoupanca;

    float saldoCorrente;
    float saldoSalario;
    float saldoPoupanca;

    int fezEmprestimo;      
    int temTitulo;           

    struct Movimento historico[MAX_MOVIMENTOS];
    int qtdMovimentos;
};

extern struct Cliente clientes[MAX_CLIENTES];
extern int qtdClientes;
extern int bancoAberto;


float saldoTotalCliente(int i);
float limiteEmprestimo(int i);
int aptoEmprestimo(int i);
int aptoTitulo(int i);
void registrarMovimento(int i, char operacao[], int tipoConta, float valor);
int buscarCliente(int numero);


void cadastrarCliente();
int escolherConta(int i);
void depositar(int i);
void sacar(int i);
void solicitarEmprestimo(int i);
void comprarTitulo(int i);
void verExtrato(int i);
void acessarConta();


void abrirBanco();
void consultarHistorico();
void efetuarSorteio();

#endif
