#include "structs_prototipos.h"

// Funções de cadastro
// Cadastra aluno
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


// Cadastra disciplina
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

// Cadastra matrícula
void cadastraMatricula (stMatricula matriculas[], int qtdMatriculas, stAluno alunos[], int qtdAlunos, stDisciplina disciplinas[], int qtdDisciplinas){
    int ra, codDisciplina;
    int indAluno, indDisciplina;
    char opcao;

    printf("\nCadastro de Matrícula\n");

    while (1) {
        printf("Digite o RA do aluno: ");
        scanf("%d", &ra);

        indAluno = encontraAluno(alunos, qtdAlunos, ra);
        
    if (indAluno == -1) {
        printf("Aluno não encontrado!\n\n");
        printf("Deseja tentar novamente? (S/N): ");
        scanf(" %c", &opcao);
            if (opcao == 'N' || opcao == 'n')
                return; 
        } else {
            printf("Aluno encontrado: %s\n", alunos[indAluno].nome);
            break;
        }
    }

    while (1) {
        printf("Digite o código da disciplina: ");
        scanf("%d", &codDisciplina);

        indDisciplina = encontraDisciplina(disciplinas, qtdDisciplinas, codDisciplina);

        if (indDisciplina == -1) {
            printf("Disciplina não encontrada!\n\n");
            printf("Deseja tentar novamente? (S/N): ");
            scanf(" %c", &opcao);
            if (opcao == 'N' || opcao == 'n')
                return;
        } else {
            printf("Disciplina encontrada: %s\n", disciplinas[indDisciplina].disciplina);
            break;
        }
    }

    matriculas[qtdMatriculas].ra = ra;
    matriculas[qtdMatriculas].codigoDis = codDisciplina;

    printf("Digite a data da matrícula:\n");
    leData(&matriculas[qtdMatriculas].dataMatricula);

    for (int i = 0; i < 4; i++) {
        matriculas[qtdMatriculas].notas[i] = 0.0;
    }

    printf("\nMatrícula cadastrada com sucesso!\n");

}

// Cadastra compromisso
void cadastraCompromisso(stCompromisso *compromissos, int *qtdCompromissos, stAluno *alunos, int qtdAlunos) {
    int ra;
    int indiceAluno = -1;
    char opcao;

    printf("\nCadastro de Compromisso\n");

    if (qtdAlunos == 0) {
        printf("Nenhum aluno cadastrado! Cadastre um aluno primeiro.\n");
        return;
    }

    while (1) {
        printf("Digite o RA do aluno: ");
        scanf("%d", &ra);
        getchar(); 


        for (int i = 0; i < qtdAlunos; i++) {
            if (alunos[i].ra == ra) {
                indiceAluno = i;
                break;
            }
        }

        if (indiceAluno == -1) {
            printf("Aluno não encontrado!\n");
            printf("Deseja tentar novamente? (S/N): ");
            scanf(" %c", &opcao);
            if (opcao == 'N' || opcao == 'n')
                return;
        } else {
            printf("Aluno encontrado: %s\n", alunos[indiceAluno].nome);
            break;
        }
    }

    stData data;
    stHora hora;
    printf("\nDigite a data do compromisso:\n");
    leData(&data);

    printf("Digite a hora (HH MM): ");
    scanf("%d %d", &hora.hora, &hora.min);
    getchar();

    int compromissosMesmoDia = 0;
    for (int i = 0; i < *qtdCompromissos; i++) {
        if (compromissos[i].aluno.ra == ra &&
            compromissos[i].data.dia == data.dia &&
            compromissos[i].data.mes == data.mes &&
            compromissos[i].data.ano == data.ano) {
            compromissosMesmoDia++;

            if (compromissos[i].horario.hora == hora.hora &&
                compromissos[i].horario.min == hora.min) {
                printf("\nJá existe um compromisso nesse mesmo horário!\n");
                return;
            }
        }
    }

    if (compromissosMesmoDia >= 2) {
        printf("\nEste aluno já possui dois compromissos nesta data!\n");
        return;
    }

    stCompromisso novo;
    novo.aluno = alunos[indiceAluno];
    novo.data = data;
    novo.horario = hora;

    printf("Digite a descrição do compromisso: ");
    fgets(novo.descricao, sizeof(novo.descricao), stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

    compromissos[*qtdCompromissos] = novo;
    (*qtdCompromissos)++;

    printf("\nCompromisso cadastrado com sucesso!\n");
}

// Funções de validação
// Valida data
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
                diasNoMes = 29; 
            else
                diasNoMes = 28;
            break;
        default:
            return 0; 
    }

    if(data->dia < 1 || data->dia > diasNoMes) return 0;

    return 1;
}

// Valida horário
int verificaHorario(stHora * hora) {
    if(hora->hora < 0 || hora->hora > 23) {
        printf("Hora inválida. Deve estar entre 0 e 23.\n");
        return 0;
    }
    if(hora->min < 0 || hora->min > 59) {
        printf("Minuto inválido. Deve estar entre 0 e 59.\n");
        return 0;
    }
    return 1;
}

int verificaEmail(char email[]) {
    if(strchr(email, '@') == NULL || strchr(email, '.') == NULL) {
        printf("Email inválido.\n");
        return 0;
    }
    return 1;
}

// Funções de busca
// Busca aluno
int encontraAluno(stAluno *alunos, int qtdAlunos, int ra) {
    for (int i = 0; i < qtdAlunos; i++) {
        if (alunos[i].ra == ra) {
            return i; 
        }
    }
    return -1; 
}

// Busca disciplina
int encontraDisciplina(stDisciplina *disciplinas, int qtdDisciplinas, int codigo) {
    for (int i = 0; i < qtdDisciplinas; i++) {
        if (disciplinas[i].codigoDis == codigo) {
            return i; 
        }
    }
    return -1; 
}

// Busca data
int procuraData(stCompromisso *compromissos, int qtdComp, stData *data, int codAluno) {
    for (int i = 0; i < qtdComp; i++) {
        if (compromissos[i].aluno.ra == codAluno &&
            compromissos[i].data.dia == data->dia &&
            compromissos[i].data.mes == data->mes &&
            compromissos[i].data.ano == data->ano) {
            return i;
        }
    }
    return -1;
}

// Busca horário
int procuraHorario(stCompromisso *compromissos, int qtdComp, stHora *hora, stData *data, int codAluno) {
    for (int i = 0; i < qtdComp; i++) {
        if (compromissos[i].aluno.ra == codAluno &&
            compromissos[i].data.dia == data->dia &&
            compromissos[i].data.mes == data->mes &&
            compromissos[i].data.ano == data->ano &&
            compromissos[i].horario.hora == hora->hora &&
            compromissos[i].horario.min == hora->min) {
            return i; 
    }
    return -1;
}
}

// Funções de impressão
//
//
//

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

// Funções de leitura
void leData(stData *d) {
    do {
        printf("Dia: ");
        scanf("%d", &d->dia);
        printf("Mês: ");
        scanf("%d", &d->mes);
        printf("Ano: ");
        scanf("%d", &d->ano);
        if (!verificaData(d)) {
            printf("Data inválida. Tente novamente.\n");
        } else break;
    } while (1);
}

void leHorario(stHora *h) {
    do {
        printf("Hora (hora minuto): ");
        scanf("%d %d", &h->hora, &h->min);
        if (!verificaHorario(h)) {
            printf("Horário inválido. Tente novamente.\n");
        } else break;
    } while (1);
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

// Funções auxiliares para qsort
// int comparaAlunoRa(const void *a, const void *b);
// int comparaCompromissoDataHoraRa(const void *a, const void *b);
// int comparaCompromissoHoraRa(const void *a, const void *b);
// int comparaCompromissoRaDataHora(const void *a, const void *b);
