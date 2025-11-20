#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
    int dia;
    int mes;
    int ano;
} stData;

typedef struct{
    int hora;
    int min;
} stHora;

typedef struct{
    int codigoDis;
    char disciplina[100];
} stDisciplina;

typedef struct{
    int ra;
    char nome[100];
    char email[100];
} stAluno;

typedef struct{
    int ra;
    int codigoDis;
    stData dataMatricula;
    float notas[4];
} stMatricula;

typedef struct{
    stAluno aluno;
    stHora horario;
    stData data;
    char descricao[300];
} stCompromisso;

// Funções de cadastro
void cadastraAluno(stAluno [], int *);
void cadastraDisciplina(stDisciplina [], int *);
void cadastraMatricula(stMatricula [], int *, stAluno [],  int, stDisciplina [], int);
void cadastraCompromisso(stCompromisso *, int *, stAluno *, int);

// Funções de validação
int verificaData(stData *);
int verificaHorario(stHora *);
int verificaEmail(char []);

// Funções de busca
int encontraAluno(stAluno *, int, int);
int procuracodigoDisciplina(stDisciplina *, int, int);
int encontraDisciplina(stDisciplina *, int, int);
int procuraData(stCompromisso *, int, stData *, int);
int procuraHorario(stCompromisso *, int, stHora *, stData *, int);
int procuraEmail(stAluno *, int, char []);

// Funções de impressão e Relatórios
void imprimeVetorDeAlunos(stAluno [], int);
void imprimeRelatorioAlunos(stAluno *, int);

// Novos relatórios detalhados
void relatorioCompromissoUmAluno(stCompromisso *compromissos, int qtdCompromissos, stAluno *alunos, int qtdAlunos);
void relatorioCompromissoTodosAlunos(stCompromisso *compromissos, int qtdCompromissos);
void relatorioCompromissoUmaData(stCompromisso *compromissos, int qtdCompromissos);
void relatorioCompromissoTodasDatas(stCompromisso *compromissos, int qtdCompromissos);

// Funções de alocação dinâmica
stAluno* criaVetorAlunos(int tamanhoInicial);
stDisciplina* criaVetorDisciplinas(int tamanhoInicial);
stMatricula* criaVetorMatriculas(int tamanhoInicial);
stCompromisso* criaVetorCompromissos(int tamanhoInicial);

// Funções de realocação dinâmica
stAluno* realocaVetorAlunos(stAluno *vetor, int novoTamanho);
stDisciplina* realocaVetorDisciplinas(stDisciplina *vetor, int novoTamanho);
stMatricula* realocaVetorMatriculas(stMatricula *vetor, int novoTamanho);
stCompromisso* realocaVetorCompromissos(stCompromisso *vetor, int novoTamanho);

// Funções auxiliares para qsort
int comparaAlunoRa(const void *a, const void *b);
int comparaCompromissoDataHoraRa(const void *a, const void *b);
int comparaCompromissoHoraRa(const void *a, const void *b);
int comparaCompromissoRaDataHora(const void *a, const void *b);

// Funções de leitura
void leHorario(stHora *);
void leData(stData *);

// Função menu
int menu(stAluno *alunos, int *qtdAlunos,
        stDisciplina *disciplinas, int *qtdDisciplinas,
        stMatricula *matriculas, int *qtdMatriculas,
        stCompromisso *compromissos, int *qtdCompromissos);
