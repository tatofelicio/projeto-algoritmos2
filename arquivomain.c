#include <stdio.h>
#include <stdlib.h> // Essencial para free()
#include "structs_prototipos.h" // Onde estão as structs e todos os protótipos

// Define um tamanho inicial para os vetores dinâmicos
#define TAM_INICIAL 5

int main() {
    
    // --- 1. CONTROLE DE QUANTIDADE DE ITENS ---
    // Contadores para saber quantos itens CADASTRADOS temos
    int qtdAlunos = 0;
    int qtdDisciplinas = 0;
    int qtdMatriculas = 0;
    int qtdCompromissos = 0;

    // --- 2. CONTROLE DE CAPACIDADE DOS VETORES ---
    // Contadores para saber o TAMANHO MÁXIMO ATUAL dos vetores
    int tamAlunos = TAM_INICIAL;
    int tamDisciplinas = TAM_INICIAL;
    int tamMatriculas = TAM_INICIAL;
    int tamCompromissos = TAM_INICIAL;

    // --- 3. INICIALIZAÇÃO DOS VETORES DINÂMICOS ---
    // Chama as funções de alocação que você criou
    stAluno *alunos = criaVetorAlunos(tamAlunos);
    stDisciplina *disciplinas = criaVetorDisciplinas(tamDisciplinas);
    stMatricula *matriculas = criaVetorMatriculas(tamMatriculas);
    stCompromisso *compromissos = criaVetorCompromissos(tamCompromissos);

    int opcao;

    // --- 4. LOOP PRINCIPAL DO MENU ---
    do {
        // Chama a função de menu que você criou
        opcao = menu(); 

        // --- 5. EXECUÇÃO DAS FUNÇÕES ---
        switch (opcao) {
            case 1: // Cadastrar Aluno
                // Verifica se o vetor de alunos está cheio
                if (qtdAlunos == tamAlunos) {
                    printf("Vetor de alunos cheio. Realocando...\n");
                    // Dobra o tamanho e chama a função de realocação
                    tamAlunos *= 2; 
                    alunos = realocaVetorAlunos(alunos, tamAlunos);
                }
                // Chama a função de cadastro
                cadastraAluno(alunos, qtdAlunos);
                qtdAlunos++; // Incrementa o contador de alunos
                break;

            case 2: // Cadastrar Disciplina
                if (qtdDisciplinas == tamDisciplinas) {
                    printf("Vetor de disciplinas cheio. Realocando...\n");
                    tamDisciplinas *= 2;
                    disciplinas = realocaVetorDisciplinas(disciplinas, tamDisciplinas);
                }
                cadastraDisciplina(disciplinas, qtdDisciplinas);
                qtdDisciplinas++;
                break;

            case 3: // Cadastrar Matrícula
                if (qtdMatriculas == tamMatriculas) {
                    printf("Vetor de matrículas cheio. Realocando...\n");
                    tamMatriculas *= 2;
                    matriculas = realocaVetorMatriculas(matriculas, tamMatriculas);
                }
                // Passa todos os dados necessários para a função
                cadastraMatricula(matriculas, qtdMatriculas, alunos, qtdAlunos, disciplinas, qtdDisciplinas);
                qtdMatriculas++;
                break;

            case 4: // Cadastrar Compromisso
                if (qtdCompromissos == tamCompromissos) {
                    printf("Vetor de compromissos cheio. Realocando...\n");
                    tamCompromissos *= 2;
                    compromissos = realocaVetorCompromissos(compromissos, tamCompromissos);
                }
                // Passa o ENDEREÇO do contador, pois a sua função já incrementa ele
                cadastraCompromisso(compromissos, &qtdCompromissos, alunos, qtdAlunos);
                // Não precisamos de "qtdCompromissos++" aqui, pois sua função já faz isso.
                break;

            case 5: // Imprimir Relatório de Compromissos
                printf("Função 'Imprimir Relatório de Compromissos' ainda não implementada.\n");
                // Aqui você chamaria a sua função de impressão de compromissos
                // ex: imprimeCompromissos(compromissos, qtdCompromissos, alunos, qtdAlunos);
                break;

            case 6: // Imprimir Relatório de um aluno
                printf("Função 'Imprimir Relatório de um aluno' ainda não implementada.\n");
                // ex: imprimeRelatorioAluno(alunos, qtdAlunos, matriculas, qtdMatriculas, disciplinas, qtdDisciplinas);
                break;

            case 7: // Imprimir dados de todos os alunos
                printf("Função 'Imprimir dados de todos os alunos' ainda não implementada.\n");
                // ex: imprimeTodosAlunos(alunos, qtdAlunos);
                break;

            case 8: // Sair
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida! Por favor, tente novamente.\n");
                break;
        }
        
        printf("\nPressione Enter para continuar...");
        getchar(); // Pausa para o usuário ler a saída
        getchar(); // Limpa o buffer do Enter
        
        // Limpa a tela (opcional, mas ajuda na organização)
        // system("clear"); // Para Linux/Mac
        // system("cls");   // Para Windows

    } while (opcao != 8);

    // --- 6. LIBERAÇÃO DE MEMÓRIA ---
    // Libera toda a memória alocada antes de fechar o programa
    printf("Liberando memória...\n");
    free(alunos);
    free(disciplinas);
    free(matriculas);
    free(compromissos);

    printf("Programa encerrado.\n");
    
    return 0; // Fim do programa
}