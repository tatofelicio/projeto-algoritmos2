#include <stdio.h>
#include <stdlib.h>

typedef struct td_data{
    int dia;
    int mes;
    int ano;
} td_data;

typedef struct td_hora{
    int hora;
    int min;
} td_hora;

typedef struct td_disciplina{
    int codigo_dis;
    char disciplina[100];
} td_disciplina;

typedef struct td_aluno{
    int ra;
    char nome[100];
    char email[100];
} td_aluno;

typedef struct td_matricula{
    int ra;
    int codigo_dis;
    td_data data_matricula;
    float notas[4];
} td_matricula;

typedef struct td_compromisso{
    td_aluno aluno;
    td_hora horario;
    td_data data;
    char descricao[300];
} td_compromisso;

void cadastra_aluno(td_aluno [], int);

void cadastra_disciplina(td_disciplina [], int);

void cadastra_matricula(td_matricula [], int, td_aluno [],  int,td_disciplina [], int);

int verifica_data(td_data *);

int verifica_horario(td_hora *);

void cadastra_compromisso(td_compromisso *, int *, td_aluno *, int);

void imprime_vetor_de_alunos(td_aluno [], int);

int encontra_aluno(td_aluno *, int, int);

int encontra_disciplina(td_lista_disciplinas *, int, int);

int procura_data(td_compromisso *, int, td_data *, int);

int procura_horario(td_compromisso *, int, td_hora *, td_data *, int);