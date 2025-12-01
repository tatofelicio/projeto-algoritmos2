#include "structs_prototipos.h"


// FUNÇÕES DE CADASTRO
void cadastraAluno(stAluno alunos[], int *qtdAlunos){
    int continua = 1;
    while(continua) {
    printf("\n========== CADASTRO DE ALUNOS ==========\n");

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
        printf("\nDeseja inserir um novo aluno? (1= Sim, 0= Voltar ao menu): ");
        scanf("%d", &opcao);
        if (opcao != 0 && opcao != 1) {
            printf("Opção invalida. Tente novamente.\n");
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
    printf("\n========== CADASTRO DE DISCIPLINAS ==========\n");

    printf("Digite o codigo da disciplina: ");
    scanf("%d", &disciplinas[*qtdDisciplinas].codigoDis);
    getchar();
        if (procuracodigoDisciplina(disciplinas, *qtdDisciplinas, disciplinas[*qtdDisciplinas].codigoDis) != -1) {
        printf("\nErro: Codigo da disciplina ja cadastrado. Tente novamente.\n");
        return;
    }

    printf("Digite o nome da disciplina: ");
    fgets(disciplinas[*qtdDisciplinas].disciplina, sizeof(disciplinas[*qtdDisciplinas].disciplina), stdin);
    disciplinas[*qtdDisciplinas].disciplina[strcspn(disciplinas[*qtdDisciplinas].disciplina, "\n")] = '\0';

    printf("\nDisciplina cadastrada com sucesso!\n");
    (*qtdDisciplinas)++;
    
    int opcao;
    do {
        printf("\nDeseja inserir uma nova disciplina? (1= Sim, 0= Voltar ao menu): ");
        scanf("%d", &opcao);
        if (opcao != 0 && opcao != 1) {
            printf("Opção invalida. Tente novamente.\n");
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

    printf("\n========== CADASTRO DE MATRICULA ==========\n");

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
        printf("\nDeseja inserir uma nova matrícula? (1= Sim, 0= Voltar ao menu): ");
        scanf("%d", &opcao);
        if (opcao != 0 && opcao != 1) {
            printf("Opção invalida. Tente novamente.\n");
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

    printf("\n========== CADASTRO DE COMPROMISSO ==========\n");

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
        printf("\nDeseja inserir um novo compromisso? (1= Sim, 0= Voltar ao menu): ");
        scanf("%d", &opcao);
        if (opcao != 0 && opcao != 1) {
            printf("Opção invalida. Tente novamente.\n");
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
        printf("Ano invAlido.\n");
        return 0;
    }
    if(data->mes < 1 || data->mes > 12) {
        printf("Mês invalido.\n");
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
        printf("Dia invalido para este mês.\n");
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
        printf("Email invalido (deve conter @ e .)\n");
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
            printf("\nErro: Email ja cadastrado. Tente novamente.\n");
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

    printf("\n========== RELATORIO GERAL (Ordenado por RA) ==========\n");
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
    printf("\nDigite a data para o relatorio:\n");
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

    printf("\n========== AGENDA COMPLETA (Ordenado por Data) ==========\n");
    for(int i=0; i<qtdCompromissos; i++){
        printf("%02d/%02d/%d as %02d:%02d | RA: %d (%s) | %s\n", 
            compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano,
            compromissos[i].horario.hora, compromissos[i].horario.min,
            compromissos[i].aluno.ra, compromissos[i].aluno.nome,
            compromissos[i].descricao);
    }
}

// FUNÇÕES DE IMPRESSÃO E RELATORIO
void imprimeVetorDeAlunos(stAluno *alunos, int qtdAlunos){
    printf("\n========== LISTA DE ALUNOS CADASTRADOS ==========\n");
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
    printf("\n========== RELATORIO DE ALUNOS (Ordenado por RA) ==========\n");
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

    // --- CARREGAR DADOS NO INÍCIO ---
    printf("Carregando base de dados...\n");
    carregarDados(alunos, qtdAlunos, disciplinas, qtdDisciplinas, matriculas, qtdMatriculas, compromissos, qtdCompromissos);
    printf("Dados carregados! Alunos: %d | Disciplinas: %d\n", *qtdAlunos, *qtdDisciplinas);
    // -------------------------------

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Cadastrar Disciplina\n");
        printf("3. Cadastrar Matricula\n");
        printf("4. Cadastrar Compromisso\n");
        printf("5. Relatorios de Compromissos\n");
        printf("6. Relatorio de Alunos\n");
        printf("7. Imprimir dados todos os alunos\n");
        printf("8. Sair e Salvar\n");
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
                printf("\n========== MENU DE RELATORIOS ==========\n");
                printf("a. De um aluno especifico (ordenado por data/hora)\n");
                printf("b. De todos os alunos (ordenado por RA/Data/Hora)\n");
                printf("c. De uma data especifica (ordenado por hora/RA)\n");
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
                        printf("Opção de relatorio inválida.\n");
                }
                break;

            case 6:
                imprimeRelatorioAlunos(alunos, *qtdAlunos);
                break;
            case 7:
                imprimeVetorDeAlunos(alunos, *qtdAlunos);
                break;
            case 8:
                // --- SALVAR DADOS AO SAIR ---
                printf("Salvando dados e saindo...\n");
                salvarDados(alunos, *qtdAlunos, disciplinas, *qtdDisciplinas, matriculas, *qtdMatriculas, compromissos, *qtdCompromissos);
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (opcao != 8);
    return 0;
}

//FUNÇÕES DE MANIPULAÇÃO DE ARQUIVOS

void salvarDados(stAluno *alunos, int qtdAlunos, stDisciplina *disciplinas, int qtdDisciplinas, stMatricula *matriculas, int qtdMatriculas, stCompromisso *compromissos, int qtdCompromissos) {
    FILE *f;

    // 1. Salvar Alunos
    f = fopen("alunos.txt", "w"); // "w" sobrescreve o arquivo
    if (f == NULL) { printf("Erro ao salvar alunos.\n"); } 
    else {
        fprintf(f, "%d\n", qtdAlunos); // A primeira linha diz quantos alunos existem
        for (int i = 0; i < qtdAlunos; i++) {
            // Formato: RA (nova linha) Nome (nova linha) Email
            fprintf(f, "%d\n", alunos[i].ra);
            fprintf(f, "%s\n", alunos[i].nome);
            fprintf(f, "%s\n", alunos[i].email);
        }
        fclose(f);
    }

    // 2. Salvar Disciplinas
    f = fopen("disciplinas.txt", "w");
    if (f == NULL) { printf("Erro ao salvar disciplinas.\n"); }
    else {
        fprintf(f, "%d\n", qtdDisciplinas);
        for (int i = 0; i < qtdDisciplinas; i++) {
            fprintf(f, "%d\n", disciplinas[i].codigoDis);
            fprintf(f, "%s\n", disciplinas[i].disciplina);
        }
        fclose(f);
    }

    // 3. Salvar Matrículas
    f = fopen("matriculas.txt", "w");
    if (f == NULL) { printf("Erro ao salvar matriculas.\n"); }
    else {
        fprintf(f, "%d\n", qtdMatriculas);
        for (int i = 0; i < qtdMatriculas; i++) {
            fprintf(f, "%d\n", matriculas[i].ra);
            fprintf(f, "%d\n", matriculas[i].codigoDis);
        }
        fclose(f);
    }

    // 4. Salvar Compromissos
    f = fopen("compromissos.txt", "w");
    if (f == NULL) { printf("Erro ao salvar compromissos.\n"); }
    else {
        fprintf(f, "%d\n", qtdCompromissos);
        for (int i = 0; i < qtdCompromissos; i++) {
            // Salva RA, Data, Hora e Descrição
            fprintf(f, "%d\n", compromissos[i].aluno.ra); // Apenas o RA é suficiente para reconstruir o link depois, mas aqui salvamos os dados diretos
            fprintf(f, "%s\n", compromissos[i].aluno.nome); // Salvamos o nome para facilitar leitura manual, mas na carga buscaremos pelo RA se necessário
            fprintf(f, "%d %d %d\n", compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano);
            fprintf(f, "%d %d\n", compromissos[i].horario.hora, compromissos[i].horario.min);
            fprintf(f, "%s\n", compromissos[i].descricao);
        }
        fclose(f);
    }
    printf("\nDados salvos com sucesso!\n");
}

void carregarDados(stAluno *alunos, int *qtdAlunos, stDisciplina *disciplinas, int *qtdDisciplinas, stMatricula *matriculas, int *qtdMatriculas, stCompromisso *compromissos, int *qtdCompromissos) {
    FILE *f;

    // 1. Carregar Alunos
    f = fopen("alunos.txt", "r");
    if (f != NULL) {
        fscanf(f, "%d", qtdAlunos); // Lê a quantidade
        fgetc(f); // Consome o \n após o número
        for (int i = 0; i < *qtdAlunos; i++) {
            fscanf(f, "%d", &alunos[i].ra);
            fgetc(f); // Consome \n
            fgets(alunos[i].nome, sizeof(alunos[i].nome), f);
            alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0'; // Remove \n do fgets
            fgets(alunos[i].email, sizeof(alunos[i].email), f);
            alunos[i].email[strcspn(alunos[i].email, "\n")] = '\0';
        }
        fclose(f);
    } else {
        *qtdAlunos = 0; // Arquivo não existe, começa do zero
    }

    // 2. Carregar Disciplinas
    f = fopen("disciplinas.txt", "r");
    if (f != NULL) {
        fscanf(f, "%d", qtdDisciplinas);
        fgetc(f);
        for (int i = 0; i < *qtdDisciplinas; i++) {
            fscanf(f, "%d", &disciplinas[i].codigoDis);
            fgetc(f);
            fgets(disciplinas[i].disciplina, sizeof(disciplinas[i].disciplina), f);
            disciplinas[i].disciplina[strcspn(disciplinas[i].disciplina, "\n")] = '\0';
        }
        fclose(f);
    } else {
        *qtdDisciplinas = 0;
    }

    // 3. Carregar Matrículas
    f = fopen("matriculas.txt", "r");
    if (f != NULL) {
        fscanf(f, "%d", qtdMatriculas);
        for (int i = 0; i < *qtdMatriculas; i++) {
            fscanf(f, "%d", &matriculas[i].ra);
            fscanf(f, "%d", &matriculas[i].codigoDis);
        }
        fclose(f);
    } else {
        *qtdMatriculas = 0;
    }

    // 4. Carregar Compromissos
    f = fopen("compromissos.txt", "r");
    if (f != NULL) {
        fscanf(f, "%d", qtdCompromissos);
        fgetc(f);
        for (int i = 0; i < *qtdCompromissos; i++) {
            fscanf(f, "%d", &compromissos[i].aluno.ra);
            fgetc(f);
            fgets(compromissos[i].aluno.nome, sizeof(compromissos[i].aluno.nome), f); // Lê nome (mas confiaremos no RA para lógica)
            compromissos[i].aluno.nome[strcspn(compromissos[i].aluno.nome, "\n")] = '\0';
            
            fscanf(f, "%d %d %d", &compromissos[i].data.dia, &compromissos[i].data.mes, &compromissos[i].data.ano);
            fscanf(f, "%d %d", &compromissos[i].horario.hora, &compromissos[i].horario.min);
            fgetc(f); // Consome \n antes da string descrição
            
            fgets(compromissos[i].descricao, sizeof(compromissos[i].descricao), f);
            compromissos[i].descricao[strcspn(compromissos[i].descricao, "\n")] = '\0';
            
            // Opcional: Re-vincular dados completos do aluno usando o RA lido para garantir consistência
            // int idx = encontraAluno(alunos, *qtdAlunos, compromissos[i].aluno.ra);
            // if(idx != -1) compromissos[i].aluno = alunos[idx];
        }
        fclose(f);
    } else {
        *qtdCompromissos = 0;
    }
}
