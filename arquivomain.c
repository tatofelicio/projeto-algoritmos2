#include "structs_prototipos.h"

int main(){

    setlocale(LC_ALL, "Portuguese");
    
    //inicialização das variáveis
    int qtdAlunos = 0, qtdDisciplinas = 0, qtdMatriculas = 0, qtdCompromissos = 0;
    int tamanhoIncial = 10;
    
    //alocação de memória dos vetores
    stAluno *alunos = (stAluno *)malloc(tamanhoIncial * sizeof(stAluno));
    stDisciplina *disciplinas = (stDisciplina *)malloc(tamanhoIncial * sizeof(stDisciplina));
    stMatricula *matriculas = (stMatricula *)malloc(tamanhoIncial * sizeof(stMatricula));
    stCompromisso *compromissos = (stCompromisso *)malloc(tamanhoIncial * sizeof(stCompromisso));

    menu(alunos, &qtdAlunos,
    disciplinas, &qtdDisciplinas,
    matriculas, &qtdMatriculas,
    compromissos, &qtdCompromissos);

    free(alunos);
    free(disciplinas);
    free(matriculas);
    free(compromissos);

return 0;
}