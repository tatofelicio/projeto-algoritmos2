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