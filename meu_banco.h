#ifndef MEU_BANCO_H
#define MEU_BANCO_H

#define MAX_CONTAS 100
#define MAX_MOVIMENTOS 50

struct Movimento {
    char operacao[20];
    int tipoConta;
    float valor;
};

struct Conta {
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

extern struct Conta contas[MAX_CONTAS];
extern int qtdContas;
extern int bancoAberto;

float saldoTotalConta(int indice);
float limiteEmprestimo(int indice);
int aptoEmprestimo(int indice);
int aptoTitulo(int indice);
void registrarMovimento(int indice, char operacao[], int tipoConta, float valor);

void abrirBanco();
void consultarHistorico();
void efetuarSorteio();

#endif
