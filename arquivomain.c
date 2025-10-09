#include <stdio.h>
#include <stdlib.h>

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
void cadastraAluno(stAluno [], int);
void cadastraDisciplina(stDisciplina [], int);
void cadastraMatricula(stMatricula [], int, stAluno [],  int, stDisciplina [], int);
void cadastraCompromisso(stCompromisso *, int *, stAluno *, int);

// Funções de validação
int verificaData(stData *);
int verificaHorario(stHora *);
int verificaEmail(char []);

// Funções de busca
int encontraAluno(stAluno *, int, int);
int encontraDisciplina(stDisciplina *, int, int);
int procuraData(stCompromisso *, int, stData *, int);
int procuraHorario(stCompromisso *, int, stHora *, stData *, int);

// Funções de impressão
void imprimeVetorDeAlunos(stAluno [], int);
void imprimeRelatorioAlunos(stAluno *, int);
void imprimeRelatorioCompromissos(stCompromisso *, int);

// Funções de alocação dinâmica
stAluno* criaVetorAlunos(int tamanhoInicial);
stDisciplina* criaVetorDisciplinas(int tamanhoInicial);
stMatricula* criaVetorMatriculas(int tamanhoInicial);
stCompromisso* criaVetorCompromissos(int tamanhoInicial);

stAluno* realocaVetorAlunos(stAluno *vetor, int novoTamanho);
stDisciplina* realocaVetorDisciplinas(stDisciplina *vetor, int novoTamanho);
stMatricula* realocaVetorMatriculas(stMatricula *vetor, int novoTamanho);
stCompromisso* realocaVetorCompromissos(stCompromisso *vetor, int novoTamanho);

// Funções auxiliares para qsort
int comparaAlunoRa(const void *a, const void *b);
int comparaCompromissoDataHoraRa(const void *a, const void *b);
int comparaCompromissoHoraRa(const void *a, const void *b);
int comparaCompromissoRaDataHora(const void *a, const void *b);

// Funções opcionais
void leHorario(stHora *);
void leData(stData *);

// Função menu
int menu();

int main(){

return 0;
}

// Função menu
int menu()
{
    int opcao;

    printf("Menu:\n");
    printf("1. Cadastrar Aluno\n");
    printf("2. Cadastrar Disciplina\n");
    printf("3. Cadastrar Matrícula\n");
    printf("4. Cadastrar Compromisso\n");
    printf("5. Imprimir Relatório de Compromissos\n");
    printf("6. Imprimir Relatório de um aluno\n");
    printf("7. Imprimir dados de todos os alunos\n");
    printf("8. Sair\n");
    scanf("%d", &opcao);

    return opcao;
}

// Funções de alocação dinâmica
stAluno* criaVetorAlunos(int tamanhoInicial){
    stAluno *vetor = malloc(tamanhoInicial * sizeof(stAluno));
    if(vetor == NULL){
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    return vetor;
}
stDisciplina* criaVetorDisciplinas(int tamanhoInicial){
    stDisciplina *vetor = malloc(tamanhoInicial * sizeof(stDisciplina));
    if(vetor == NULL){
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    return vetor;
}
stMatricula* criaVetorMatriculas(int tamanhoInicial){
    stMatricula *vetor = malloc(tamanhoInicial * sizeof(stMatricula));
    if(vetor == NULL){
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    return vetor;
}
stCompromisso* criaVetorCompromissos(int tamanhoInicial){
    stCompromisso *vetor = malloc(tamanhoInicial * sizeof(stCompromisso));
    if(vetor == NULL){
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    return vetor;
}

// Funções de realocação dinâmica
stAluno* realocaVetorAlunos(stAluno *vetor, int novoTamanho){
    stAluno *novoVetor = realloc(vetor, novoTamanho * sizeof(stAluno));
    if(novoVetor == NULL){
        printf("Erro de realocação de memória!\n");
        free(vetor);
        exit(1);
    }
    return novoVetor;
}
stDisciplina* realocaVetorDisciplinas(stDisciplina *vetor, int novoTamanho){
    stDisciplina *novoVetor = realloc(vetor, novoTamanho * sizeof(stDisciplina));
    if(novoVetor == NULL){
        printf("Erro de realocação de memória!\n");
        free(vetor);
        exit(1);
    }
    return novoVetor;
}
stMatricula* realocaVetorMatriculas(stMatricula *vetor, int novoTamanho){
    stMatricula *novoVetor = realloc(vetor, novoTamanho * sizeof(stMatricula));
    if(novoVetor == NULL){
        printf("Erro de realocação de memória!\n");
        free(vetor);
        exit(1);
    }
    return novoVetor;
}
stCompromisso* realocaVetorCompromissos(stCompromisso *vetor, int novoTamanho){
    stCompromisso *novoVetor = realloc(vetor, novoTamanho * sizeof(stCompromisso));
    if(novoVetor == NULL){
        printf("Erro de realocação de memória!\n");
        free(vetor);
        exit(1);
    }
    return novoVetor;
}

// Funções de cadastro
void cadastraAluno(stAluno alunos[], int qtdAlunos){
    printf("\nCadastro de Aluno\n");

    printf("Digite o RA: ");
    scanf("%d", &alunos[qtdAlunos].ra);
    getchar(); 

    printf("Digite o nome do aluno: ");
    fgets(alunos[qtdAlunos].nome, sizeof(alunos[qtdAlunos].nome), stdin);
    alunos[qtdAlunos].nome[strcspn(alunos[qtdAlunos].nome, "\n")] = '\0';

    printf("Digite o email do aluno: ");
    fgets(alunos[qtdAlunos].email, sizeof(alunos[qtdAlunos].email), stdin);
    alunos[qtdAlunos].email[strcspn(alunos[qtdAlunos].email, "\n")] = '\0';

    printf("\nAluno cadastrado com sucesso!\n");
}