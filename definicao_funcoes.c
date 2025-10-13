#include "structs_prototipos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Funções de validação
int verificaData(stData * data) {

    if(data->ano < 1900 || data->ano > 2100){
        printf("Ano inválido. Deve estar entre 1900 e 2100.\n");
        return 0;
    }
    if(data->mes < 1 || data->mes > 12) {
        printf("Mês inválido. Deve estar entre 1 e 12.\n");
        return 0;
    }

    int diasNoMes;
    switch(data->mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasNoMes = 31; break;
        case 4: case 6: case 9: case 11:
            diasNoMes = 30; break;
        case 2:
            if((data->ano % 4 == 0 && data->ano % 100 != 0) || (data->ano % 400 == 0))
                diasNoMes = 29; // Ano bissexto
            else
                diasNoMes = 28;
            break;
        default:
            return 0; // Mês inválido
    }

    if(data->dia < 1 || data->dia > diasNoMes) return 0;

    return 1; // Data válida
}
int verificaHorario(stHora * hora) {
    if(hora->hora < 0 || hora->hora > 23) {
        printf("Hora inválida. Deve estar entre 0 e 23.\n");
        return 0;
    }
    if(hora->min < 0 || hora->min > 59) {
        printf("Minuto inválido. Deve estar entre 0 e 59.\n");
        return 0;
    }
    return 1; // Horário válido
}

int verificaEmail(char email[]) {
    // Verifica se o email contém um '@' e um '.'
    if(strchr(email, '@') == NULL || strchr(email, '.') == NULL) {
        printf("Email inválido.\n");
        return 0;
    }
    return 1; // Email válido
}

/*
// Funções de busca
int encontraAluno(stAluno *, int, int);
int encontraDisciplina(stDisciplina *, int, int);
int procuraData(stCompromisso *, int, stData *, int);
int procuraHorario(stCompromisso *, int, stHora *, stData *, int);
*/

/*
// Funções de impressão
void imprimeVetorDeAlunos(stAluno [], int);
void imprimeRelatorioAlunos(stAluno *, int);
void imprimeRelatorioCompromissos(stCompromisso *, int);
*/

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

/*
// Funções auxiliares para qsort
int comparaAlunoRa(const void *a, const void *b);
int comparaCompromissoDataHoraRa(const void *a, const void *b);
int comparaCompromissoHoraRa(const void *a, const void *b);
int comparaCompromissoRaDataHora(const void *a, const void *b);
*/

/*
// Funções opcionais
void leHorario(stHora *);
void leData(stData *);
*/

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

void cadastraDisciplina(stDisciplina disciplinas[], int qtdDisciplinas){
    printf("\nCadastro de Disciplinas\n");

    printf("Digite o código da disciplina: ");
    scanf("%d", &disciplinas[qtdDisciplinas].codigoDis);
    getchar();

    printf("Digite o nome da disciplina: ");
    fgets(disciplinas[qtdDisciplinas].disciplina, sizeof(disciplinas[qtdDisciplinas].disciplina), stdin);
    disciplinas[qtdDisciplinas].disciplina[strcspn(disciplinas[qtdDisciplinas].disciplina, "\n")] = '\0';

    printf("\nDisciplina cadastrada com sucesso!\n");
}