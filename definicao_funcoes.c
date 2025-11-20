#include "structs_prototipos.h"


// FUNÇÕES DE CADASTRO
void cadastraAluno(stAluno alunos[], int *qtdAlunos){
    int continua = 1;
    while(continua) {
    printf("\n--- Cadastro de Aluno ---\n");

    do{
    printf("Digite o RA: (sem 'a') ");
    scanf("%d", &alunos[*qtdAlunos].ra);
    getchar(); 
    if (encontraAluno(alunos, *qtdAlunos, alunos[*qtdAlunos].ra) != -1) {
        printf("\nErro: RA já cadastrado. Tente novamente.\n");
    }
    } while (encontraAluno(alunos, *qtdAlunos, alunos[*qtdAlunos].ra) != -1);

    printf("Digite o nome do aluno: ");
    fgets(alunos[*qtdAlunos].nome, sizeof(alunos[*qtdAlunos].nome), stdin);
    alunos[*qtdAlunos].nome[strcspn(alunos[*qtdAlunos].nome, "\n")] = '\0';

    do{
        printf("Digite o email do aluno: ");
        fgets(alunos[*qtdAlunos].email, sizeof(alunos[*qtdAlunos].email), stdin);
        alunos[*qtdAlunos].email[strcspn(alunos[*qtdAlunos].email, "\n")] = '\0';
    } while(verificaEmail(alunos[*qtdAlunos].email) == 0 || procuraEmail(alunos, *qtdAlunos, alunos[*qtdAlunos].email) != -1);

    printf("\nAluno cadastrado com sucesso!\n");
    (*qtdAlunos)++;
    
    int opcao;
    do {
        printf("\nDeseja inserir um novo aluno? (1=Sim, 0=Voltar ao menu): ");
        scanf("%d", &opcao);
        if (opcao != 0 && opcao != 1) {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0 && opcao != 1);
    
    if (opcao == 0) {
        continua = 0;
    }
    }
}

void cadastraDisciplina(stDisciplina disciplinas[], int *qtdDisciplinas){
    int continua = 1;
    while(continua) {
    printf("\n--- Cadastro de Disciplinas ---\n");

    printf("Digite o código da disciplina: ");
    scanf("%d", &disciplinas[*qtdDisciplinas].codigoDis);
    getchar();
        if (procuracodigoDisciplina(disciplinas, *qtdDisciplinas, disciplinas[*qtdDisciplinas].codigoDis) != -1) {
        printf("\nErro: Código da disciplina já cadastrado. Tente novamente.\n");
        return;
    }

    printf("Digite o nome da disciplina: ");
    fgets(disciplinas[*qtdDisciplinas].disciplina, sizeof(disciplinas[*qtdDisciplinas].disciplina), stdin);
    disciplinas[*qtdDisciplinas].disciplina[strcspn(disciplinas[*qtdDisciplinas].disciplina, "\n")] = '\0';

    printf("\nDisciplina cadastrada com sucesso!\n");
    (*qtdDisciplinas)++;
    
    int opcao;
    do {
        printf("\nDeseja inserir uma nova disciplina? (1=Sim, 0=Voltar ao menu): ");
        scanf("%d", &opcao);
        if (opcao != 0 && opcao != 1) {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0 && opcao != 1);
    
    if (opcao == 0) {
        continua = 0;
    }
    }
}

void cadastraMatricula (stMatricula matriculas[], int *qtdMatriculas, stAluno alunos[], int qtdAlunos, stDisciplina disciplinas[], int qtdDisciplinas){
    int continua = 1;
    while(continua) {
    int raDigitado;
    int codigoDigitado;
    int indiceAluno;
    int indiceDisciplina;

    printf("\n--- Cadastro de Matrícula ---\n");

    do {
        printf("Digite o RA do aluno: ");
        scanf("%d", &raDigitado);
        indiceAluno = encontraAluno(alunos, qtdAlunos, raDigitado);
        if (indiceAluno == -1) {
            printf("Erro: Aluno não encontrado. Tente novamente.\n");
        }
    } while (indiceAluno == -1); 

    printf("Aluno: %s\n", alunos[indiceAluno].nome);

    do {
        printf("Digite o código da disciplina: ");
        scanf("%d", &codigoDigitado);
        indiceDisciplina = encontraDisciplina(disciplinas, qtdDisciplinas, codigoDigitado);
        if (indiceDisciplina == -1) {
            printf("Erro: Disciplina não encontrada. Tente novamente.\n");
        }
    } while (indiceDisciplina == -1); 

    printf("Disciplina: %s\n", disciplinas[indiceDisciplina].disciplina);

    matriculas[*qtdMatriculas].ra = raDigitado;
    matriculas[*qtdMatriculas].codigoDis = codigoDigitado;

    printf("\nMatrícula realizada com sucesso!\n"); 
    (*qtdMatriculas)++;
    
    int opcao;
    do {
        printf("\nDeseja inserir uma nova matrícula? (1=Sim, 0=Voltar ao menu): ");
        scanf("%d", &opcao);
        if (opcao != 0 && opcao != 1) {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0 && opcao != 1);
    
    if (opcao == 0) {
        continua = 0;
    }
    }
}

void cadastraCompromisso(stCompromisso *compromissos, int *qtdCompromissos, stAluno *alunos, int qtdAlunos) {
    int continua = 1;
    while(continua) {
    int raDigitado;
    int indiceAluno;
    stData novaData;
    stHora novaHora;
    int compromissosNaData = 0;

    printf("\n--- Cadastro de Compromisso ---\n");

    do {
        printf("Digite o RA do aluno: ");
        scanf("%d", &raDigitado);
        indiceAluno = encontraAluno(alunos, qtdAlunos, raDigitado);
        if (indiceAluno == -1) {
            printf("Erro: Aluno não encontrado. Tente novamente.\n");
        }
    } while (indiceAluno == -1);

    printf("Aluno selecionado: %s\n", alunos[indiceAluno].nome);

    printf("Digite a data do compromisso:\n");
    leData(&novaData);

    printf("Digite o horário do compromisso:\n");
    leHorario(&novaHora);
    getchar(); // Limpa buffer após ler hora

    if (procuraHorario(compromissos, *qtdCompromissos, &novaHora, &novaData, raDigitado) != -1) {
        printf("\nErro: Já existe um compromisso para este aluno neste mesmo dia e horário.\n");
        return;
    }

    for (int i = 0; i < *qtdCompromissos; i++) {
        if (compromissos[i].aluno.ra == raDigitado &&
            compromissos[i].data.dia == novaData.dia &&
            compromissos[i].data.mes == novaData.mes &&
            compromissos[i].data.ano == novaData.ano) {
            compromissosNaData++;
        }
    }

    if (compromissosNaData >= 2) {
        printf("\nErro: O aluno já possui dois compromissos agendados para esta data.\n");
        return;
    }

    compromissos[*qtdCompromissos].aluno = alunos[indiceAluno];
    compromissos[*qtdCompromissos].data = novaData;
    compromissos[*qtdCompromissos].horario = novaHora;

    printf("Digite a descrição do compromisso: ");
    fgets(compromissos[*qtdCompromissos].descricao, sizeof(compromissos[*qtdCompromissos].descricao), stdin);
    compromissos[*qtdCompromissos].descricao[strcspn(compromissos[*qtdCompromissos].descricao, "\n")] = '\0';

    printf("\nCompromisso cadastrado com sucesso!\n");
    (*qtdCompromissos)++;
    
    int opcao;
    do {
        printf("\nDeseja inserir um novo compromisso? (1=Sim, 0=Voltar ao menu): ");
        scanf("%d", &opcao);
        if (opcao != 0 && opcao != 1) {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0 && opcao != 1);
    
    if (opcao == 0) {
        continua = 0;
    }
    }
}


// FUNÇÕES DE VALIDAÇÃO
int verificaData(stData * data) {
    if(data->ano < 1900 || data->ano > 2100){
        printf("Ano inválido.\n");
        return 0;
    }
    if(data->mes < 1 || data->mes > 12) {
        printf("Mês inválido.\n");
        return 0;
    }
    int diasNoMes;
    switch(data->mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: diasNoMes = 31; break;
        case 4: case 6: case 9: case 11: diasNoMes = 30; break;
        case 2:
            if((data->ano % 4 == 0 && data->ano % 100 != 0) || (data->ano % 400 == 0)) diasNoMes = 29; 
            else diasNoMes = 28;
            break;
        default: return 0; 
    }
    if(data->dia < 1 || data->dia > diasNoMes) {
        printf("Dia inválido para este mês.\n");
        return 0;
    }
    return 1;
}

int verificaHorario(stHora * hora) {
    if(hora->hora < 0 || hora->hora > 23) return 0;
    if(hora->min < 0 || hora->min > 59) return 0;
    return 1;
}

int verificaEmail(char email[]) {
    if(strchr(email, '@') == NULL || strchr(email, '.') == NULL) {
        printf("Email inválido (deve conter @ e .)\n");
        return 0;
    }
    return 1;
}

// FUNÇÕES DE BUSCA
int encontraAluno(stAluno *alunos, int qtdAlunos, int ra) {
    for (int i = 0; i < qtdAlunos; i++) {
        if (alunos[i].ra == ra) return i; 
    }
    return -1; 
}

int encontraDisciplina(stDisciplina *disciplinas, int qtdDisciplinas, int codigo) {
    for (int i = 0; i < qtdDisciplinas; i++) {
        if (disciplinas[i].codigoDis == codigo) return i; 
    }
    return -1; 
}

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
    }
    return -1;
}

int procuraEmail(stAluno *alunos, int qtdAlunos, char email[]) {
    for (int i = 0; i < qtdAlunos; i++) {
        if (strcmp(alunos[i].email, email) == 0) {
            printf("\nErro: Email já cadastrado. Tente novamente.\n");
            return i; 
        }
    }
    return -1;
}

int procuracodigoDisciplina(stDisciplina *disciplinas, int qtdDisciplinas, int codigo) {
    for (int i = 0; i < qtdDisciplinas; i++) {
        if (disciplinas[i].codigoDis == codigo) {
            return i; 
        }
    }
    return -1;
}

// FUNÇÕES DE RELATÓRIO (OPÇÃO 5)
// a. Relatório de um aluno específico (ordenado por Data/Hora)
void relatorioCompromissoUmAluno(stCompromisso *compromissos, int qtdCompromissos, stAluno *alunos, int qtdAlunos) {
    if(qtdCompromissos == 0) { printf("Nenhum compromisso cadastrado.\n"); return; }

    int ra, indice;
    printf("\nDigite o RA do aluno: ");
    scanf("%d", &ra);
    
    indice = encontraAluno(alunos, qtdAlunos, ra);
    if(indice == -1){
        printf("Aluno não encontrado.\n");
        return;
    }

    // Ordena por Data e Hora
    qsort(compromissos, qtdCompromissos, sizeof(stCompromisso), comparaCompromissoDataHoraRa);

    printf("\n--- Compromissos de %s (RA: %d) ---\n", alunos[indice].nome, ra);
    int encontrou = 0;
    for(int i=0; i<qtdCompromissos; i++){
        if(compromissos[i].aluno.ra == ra){
            printf("%02d/%02d/%d as %02d:%02d - %s\n", 
                compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano,
                compromissos[i].horario.hora, compromissos[i].horario.min,
                compromissos[i].descricao);
            encontrou = 1;
        }
    }
    if(!encontrou) printf("Nenhum compromisso encontrado para este aluno.\n");
}

// b. Relatório de todos os alunos (ordenado por RA, depois Data, depois Hora)
void relatorioCompromissoTodosAlunos(stCompromisso *compromissos, int qtdCompromissos){
    if(qtdCompromissos == 0) { printf("Nenhum compromisso cadastrado.\n"); return; }

    // Ordena por RA, depois Data, depois Hora
    qsort(compromissos, qtdCompromissos, sizeof(stCompromisso), comparaCompromissoRaDataHora);

    printf("\n--- Relatório Geral (Ordenado por RA) ---\n");
    for(int i=0; i<qtdCompromissos; i++){
        printf("RA: %d (%s) | %02d/%02d/%d as %02d:%02d | %s\n", 
            compromissos[i].aluno.ra, compromissos[i].aluno.nome,
            compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano,
            compromissos[i].horario.hora, compromissos[i].horario.min,
            compromissos[i].descricao);
    }
}

// c. Relatório de uma data específica (ordenado por Hora, depois RA)
void relatorioCompromissoUmaData(stCompromisso *compromissos, int qtdCompromissos){
    if(qtdCompromissos == 0) { printf("Nenhum compromisso cadastrado.\n"); return; }

    stData d;
    printf("\nDigite a data para o relatório:\n");
    leData(&d);

    // Ordena por Hora e RA
    qsort(compromissos, qtdCompromissos, sizeof(stCompromisso), comparaCompromissoHoraRa);

    printf("\n--- Compromissos do dia %02d/%02d/%d ---\n", d.dia, d.mes, d.ano);
    int encontrou = 0;
    for(int i=0; i<qtdCompromissos; i++){
        if(compromissos[i].data.dia == d.dia && 
           compromissos[i].data.mes == d.mes && 
           compromissos[i].data.ano == d.ano){
            
            printf("%02d:%02d - Aluno: %s (RA: %d) - %s\n", 
                compromissos[i].horario.hora, compromissos[i].horario.min,
                compromissos[i].aluno.nome, compromissos[i].aluno.ra,
                compromissos[i].descricao);
            encontrou = 1;
        }
    }
    if(!encontrou) printf("Nenhum compromisso nesta data.\n");
}

// d. Relatório de todas as datas (ordenado por Data, depois Hora, depois RA)
void relatorioCompromissoTodasDatas(stCompromisso *compromissos, int qtdCompromissos){
    if(qtdCompromissos == 0) { printf("Nenhum compromisso cadastrado.\n"); return; }

    // Ordena por Data, Hora e RA
    qsort(compromissos, qtdCompromissos, sizeof(stCompromisso), comparaCompromissoDataHoraRa);

    printf("\n--- Agenda Completa (Ordenado por Data) ---\n");
    for(int i=0; i<qtdCompromissos; i++){
        printf("%02d/%02d/%d as %02d:%02d | RA: %d (%s) | %s\n", 
            compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano,
            compromissos[i].horario.hora, compromissos[i].horario.min,
            compromissos[i].aluno.ra, compromissos[i].aluno.nome,
            compromissos[i].descricao);
    }
}

// OUTRAS FUNÇÕES DE IMPRESSÃO
void imprimeVetorDeAlunos(stAluno *alunos, int qtdAlunos){
    printf("\n--- Lista de Alunos Cadastrados ---\n");
    for(int i = 0; i < qtdAlunos; i++){
        printf("RA: %d | Nome: %s | Email: %s\n", alunos[i].ra, alunos[i].nome, alunos[i].email);
    }
}

void imprimeRelatorioAlunos(stAluno *alunos, int qtdAlunos){
    if (qtdAlunos == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }
    qsort(alunos, qtdAlunos, sizeof(stAluno), comparaAlunoRa);
    printf("\n--- Relatório de Alunos (Ordenado por RA) ---\n");
    for (int i = 0; i < qtdAlunos; i++) {
        printf("RA: %d | Nome: %s\n", alunos[i].ra, alunos[i].nome);
    }
}

// FUNÇÕES DE LEITURA
void leData(stData *d) {
    do {
        printf("Dia Mês Ano (ex: 21 11 2025): ");
        scanf("%d %d %d", &d->dia, &d->mes, &d->ano);
        if (!verificaData(d)) {
            printf("Tente novamente.\n");
        } else break;
    } while (1);
}

void leHorario(stHora *h) {
    do {
        printf("Hora Minuto (ex: 14 30): ");
        scanf("%d %d", &h->hora, &h->min);
        if (!verificaHorario(h)) {
            printf("Horário inválido (0-23h 0-59min). Tente novamente.\n");
        } else break;
    } while (1);
}

// FUNÇÕES DE COMPARAÇÃO (QSORT)
int comparaAlunoRa(const void *a, const void *b){
    const stAluno *alunoA = (const stAluno *)a;
    const stAluno *alunoB = (const stAluno *)b;
    return alunoA->ra - alunoB->ra;
}

int comparaCompromissoDataHoraRa(const void *a, const void *b){
    const stCompromisso *cA = (const stCompromisso *)a;
    const stCompromisso *cB = (const stCompromisso *)b;
    // 1. Ano
    if (cA->data.ano != cB->data.ano) return cA->data.ano - cB->data.ano;
    // 2. Mes
    if (cA->data.mes != cB->data.mes) return cA->data.mes - cB->data.mes;
    // 3. Dia
    if (cA->data.dia != cB->data.dia) return cA->data.dia - cB->data.dia;
    // 4. Hora
    if (cA->horario.hora != cB->horario.hora) return cA->horario.hora - cB->horario.hora;
    // 5. Minuto
    if (cA->horario.min != cB->horario.min) return cA->horario.min - cB->horario.min;
    // 6. RA
    return cA->aluno.ra - cB->aluno.ra;
}

int comparaCompromissoHoraRa(const void *a, const void *b){
    const stCompromisso *cA = (const stCompromisso *)a;
    const stCompromisso *cB = (const stCompromisso *)b;
    // 1. Hora
    if (cA->horario.hora != cB->horario.hora) return cA->horario.hora - cB->horario.hora;
    // 2. Minuto
    if (cA->horario.min != cB->horario.min) return cA->horario.min - cB->horario.min;
    // 3. RA
    return cA->aluno.ra - cB->aluno.ra;
}

int comparaCompromissoRaDataHora(const void *a, const void *b){
    const stCompromisso *cA = (const stCompromisso *)a;
    const stCompromisso *cB = (const stCompromisso *)b;
    // 1. RA
    if (cA->aluno.ra != cB->aluno.ra) return cA->aluno.ra - cB->aluno.ra;
    // 2. Data/Hora (copiando lógica)
    if (cA->data.ano != cB->data.ano) return cA->data.ano - cB->data.ano;
    if (cA->data.mes != cB->data.mes) return cA->data.mes - cB->data.mes;
    if (cA->data.dia != cB->data.dia) return cA->data.dia - cB->data.dia;
    if (cA->horario.hora != cB->horario.hora) return cA->horario.hora - cB->horario.hora;
    if (cA->horario.min != cB->horario.min) return cA->horario.min - cB->horario.min;
    return 0;
}

// MENU PRINCIPAL
int menu(stAluno *alunos, int *qtdAlunos,
        stDisciplina *disciplinas, int *qtdDisciplinas,
        stMatricula *matriculas, int *qtdMatriculas,
        stCompromisso *compromissos, int *qtdCompromissos){

    int opcao;
    char opcrelatorio;

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Cadastrar Disciplina\n");
        printf("3. Cadastrar Matrícula\n");
        printf("4. Cadastrar Compromisso\n");
        printf("5. Relatórios de Compromissos\n");
        printf("6. Relatório de Alunos (Ordenado por RA)\n");
        printf("7. Imprimir dados brutos de todos os alunos\n");
        printf("8. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                cadastraAluno(alunos, qtdAlunos);
                break;
            case 2:
                cadastraDisciplina(disciplinas, qtdDisciplinas);
                break;
            case 3:
                cadastraMatricula(matriculas, qtdMatriculas, alunos, *qtdAlunos, disciplinas, *qtdDisciplinas);
                break;
            case 4:
                cadastraCompromisso(compromissos, qtdCompromissos, alunos, *qtdAlunos);
                break;
            case 5:
                printf("\n--- Menu de Relatórios ---\n");
                printf("a. De um aluno específico (ordenado por data/hora)\n");
                printf("b. De todos os alunos (ordenado por RA/Data/Hora)\n");
                printf("c. De uma data específica (ordenado por hora/RA)\n");
                printf("d. De todas as datas (ordenado por data/hora/RA)\n");
                printf("Opção: ");
                
                // IMPORTANTE: O espaço antes do %c ignora o 'enter' anterior
                scanf(" %c", &opcrelatorio); 

                switch(opcrelatorio){
                    case 'a':
                    case 'A':
                        relatorioCompromissoUmAluno(compromissos, *qtdCompromissos, alunos, *qtdAlunos);
                        break;
                    case 'b':
                    case 'B':
                        relatorioCompromissoTodosAlunos(compromissos, *qtdCompromissos);
                        break;
                    case 'c':
                    case 'C':
                        relatorioCompromissoUmaData(compromissos, *qtdCompromissos);
                        break;
                    case 'd':
                    case 'D':
                        relatorioCompromissoTodasDatas(compromissos, *qtdCompromissos);
                        break;
                    default:
                        printf("Opção de relatório inválida.\n");
                }
                break;

            case 6:
                imprimeRelatorioAlunos(alunos, *qtdAlunos);
                break;
            case 7:
                imprimeVetorDeAlunos(alunos, *qtdAlunos);
                break;
            case 8:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 8);
    return 0;
}
