#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meu_banco.h"

struct Conta contas[MAX_CONTAS];
int qtdContas = 0;
int bancoAberto = 0;

int qtdContemplados = 0;
int contemplado[MAX_CONTAS];
float premioContemplado[MAX_CONTAS];

float saldoTotalConta(int indice) {
    return contas[indice].saldoCorrente + contas[indice].saldoSalario + contas[indice].saldoPoupanca;
}

float limiteEmprestimo(int indice) {
    return 0.25 * (10 * saldoTotalConta(indice));
}

int aptoEmprestimo(int indice) {
    if (contas[indice].temCorrente == 1 && contas[indice].temPoupanca == 1 && contas[indice].saldoPoupanca > 0 && contas[indice].fezEmprestimo == 0) {
        return 1;
    }
    return 0;
}

int aptoTitulo(int indice) {
    if (contas[indice].temSalario == 1 && contas[indice].saldoSalario >= 1000 && contas[indice].saldoSalario <= 1500) {
        return 1;
    }
    return 0;
}

void registrarMovimento(int indice, char operacao[], int tipoConta, float valor) {
    int pos = contas[indice].qtdMovimentos;
    if (pos < MAX_MOVIMENTOS) {
        strcpy(contas[indice].historico[pos].operacao, operacao);
        contas[indice].historico[pos].tipoConta = tipoConta;
        contas[indice].historico[pos].valor = valor;
        contas[indice].qtdMovimentos++;
    }
}

void abrirBanco() {
    int qtd, cont;

    if (bancoAberto == 0) {
        bancoAberto = 1;
        printf("\nBanco aberto!\n");
        printf("Quantas contas deseja inicializar? ");
        scanf("%d", &qtd);

        for (cont = 0; cont < qtd && qtdContas < MAX_CONTAS; cont++) {
            contas[qtdContas].numero = 1000 + qtdContas;
            contas[qtdContas].temCorrente = 1;
            contas[qtdContas].temSalario = 0;
            contas[qtdContas].temPoupanca = 1;
            contas[qtdContas].saldoCorrente = 0;
            contas[qtdContas].saldoSalario = 0;
            contas[qtdContas].saldoPoupanca = 0;
            contas[qtdContas].fezEmprestimo = 0;
            contas[qtdContas].temTitulo = 0;
            contas[qtdContas].qtdMovimentos = 0;
            printf("Conta inicializada: %d\n", contas[qtdContas].numero);
            qtdContas++;
        }
    } else {
        printf("\nO banco ja esta aberto.\n");
    }
}

void consultarHistorico() {
    int cont;
    float total = 0;

    for (cont = 0; cont < qtdContas; cont++) {
        total += saldoTotalConta(cont);
    }

    printf("\n== Saldo Total do banco ==\n");
    printf("%d | R$ %.2f\n", qtdContas, total);

    printf("== Contas Aptas a Emprestimos ==\n");
    for (cont = 0; cont < qtdContas; cont++) {
        if (aptoEmprestimo(cont) == 1) {
            printf("%d-01|R$ %.2f\n", contas[cont].numero, limiteEmprestimo(cont));
        }
    }

    printf("== Contas com Saldo Negativo na Conta Salario ==\n");
    for (cont = 0; cont < qtdContas; cont++) {
        if (contas[cont].temSalario == 1 && contas[cont].saldoSalario < 0) {
            printf("%d-02|R$ %.2f\n", contas[cont].numero, contas[cont].saldoSalario);
        }
    }

    printf("== Contas Aptas a Compra de Titulos ==\n");
    for (cont = 0; cont < qtdContas; cont++) {
        if (aptoTitulo(cont) == 1 && contas[cont].temTitulo == 0) {
            printf("%d-02|R$ %.2f\n", contas[cont].numero, contas[cont].saldoSalario);
        }
    }

    printf("== Contas Contempladas no Sorteio ==\n");
    for (cont = 0; cont < qtdContemplados; cont++) {
        int idx = contemplado[cont];
        printf("%d|R$ %.2f\n", contas[idx].numero, premioContemplado[cont]);
    }
}

void efetuarSorteio() {
    int ordem[MAX_CONTAS];
    int cont, cont2, aux;
    int termo, fib, anterior, atual;
    int posicao, vencedor;
    float premio;

    if (qtdContas < 5) {
        printf("Sao necessarios pelo menos 5 registros para o sorteio.\n");
        return;
    }

    for (cont = 0; cont < qtdContas; cont++) {
        ordem[cont] = cont;
    }

    for (cont = 0; cont < qtdContas - 1; cont++) {
        for (cont2 = 0; cont2 < qtdContas - 1 - cont; cont2++) {
            if (saldoTotalConta(ordem[cont2]) < saldoTotalConta(ordem[cont2 + 1])) {
                aux = ordem[cont2];
                ordem[cont2] = ordem[cont2 + 1];
                ordem[cont2 + 1] = aux;
            }
        }
    }

    for (cont = 0; cont < 5; cont++) {
        if (contas[ordem[cont]].temTitulo == 0) {
            printf("Sorteio cancelado: conta %d nao possui titulo de capitalizacao.\n", contas[ordem[cont]].numero);
            return;
        }
    }

    termo = rand() % 20 + 10;
    anterior = 0;
    atual = 1;
    for (cont = 0; cont < termo; cont++) {
        fib = anterior + atual;
        anterior = atual;
        atual = fib;
    }
    fib = anterior;
    posicao = fib % 5;
    vencedor = ordem[posicao];

    premio = 10 * saldoTotalConta(vencedor);
    contas[vencedor].saldoCorrente += premio;
    registrarMovimento(vencedor, "Premio", 1, premio);

    contemplado[qtdContemplados] = vencedor;
    premioContemplado[qtdContemplados] = premio;
    qtdContemplados++;

    printf("Vencedor: conta %d | Premio: R$ %.2f\n", contas[vencedor].numero, premio);
}
