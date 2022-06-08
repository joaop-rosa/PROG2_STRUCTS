#include <stdio.h>
#include <string.h>

typedef struct ficha_aluno FICHA_ALUNO;
struct ficha_aluno{
    char nome[50];
    int matricula;
    float nota;
};


int escreverArquivo(FICHA_ALUNO aluno){
    //SALVA NO ARQUIVO AS INFORMACOES
    FILE *arquivo;
    arquivo = fopen("teste.bin", "ab+") ;
    if ( arquivo == NULL ) {
        return 0;
    } else {
        fwrite(&aluno,sizeof(FICHA_ALUNO), 1, arquivo);
        fclose(arquivo);
        return 1;
    }

}

void lerArquivo(){
    FILE *arquivo ;
    struct ficha_aluno structLida;
    int endFileControl;
    arquivo = fopen("teste.bin", "rb") ;
    if ( arquivo == NULL ) {
        printf( "Nao foi possivel abrir arquivo." ) ;
    } else {
        while (!feof(arquivo)) {
            endFileControl = fread(&structLida, sizeof(FICHA_ALUNO), 1, arquivo);
            if (endFileControl != 0) {
                printf("Matricula: %d\n", structLida.matricula);
                printf("Nome: %s\n", structLida.nome);
                printf("Nota Final: %0.2f\n", structLida.nota);
                printf("------------------------------\n");
            }
        }
    }
    fclose(arquivo) ;

}
void lerMatriculaEspecifica(int matriculaConsulta){
    FILE *arquivo ;
    struct ficha_aluno structLida;
    int endFileControl;
    int controle = 0;
    arquivo = fopen("teste.bin", "rb") ;
    if ( arquivo == NULL ) {
        printf( "Nao foi possivel abrir arquivo." ) ;
    } else {
        while (!feof(arquivo)) {
            endFileControl = fread(&structLida, sizeof(FICHA_ALUNO), 1, arquivo);
            if (endFileControl != 0) {
                if(matriculaConsulta == structLida.matricula){
                    printf("Matricula: %d\n", structLida.matricula);
                    printf("Nome: %s\n", structLida.nome);
                    printf("Nota Final: %0.2f\n", structLida.nota);
                    controle = 1;
                }
            }
        }
        fclose(arquivo) ;
    }
    if(controle != 1){
        printf( "Matricula nao encontrada" ) ;
    }
}

void estatisticas(){
    FILE *arquivo ;
    struct ficha_aluno structLida;
    int endFileControl;
    int quantidadeAlunos = 0;
    float mediaNotas = 0;
    char alunoMaiorNota[50];
    char alunoMenorNota[50];
    float maiorNota,menorNota;

    arquivo = fopen("teste.bin", "rb") ;
    if ( arquivo == NULL ) {
        printf( "Nao foi possivel abrir arquivo." ) ;
    } else {
        while (!feof(arquivo)) {
            endFileControl = fread(&structLida, sizeof(FICHA_ALUNO), 1, arquivo);
            if (endFileControl != 0) {
                quantidadeAlunos++;
                mediaNotas += structLida.nota;
                if(quantidadeAlunos == 1){
                    strcpy(alunoMaiorNota,structLida.nome);
                    strcpy(alunoMenorNota,structLida.nome);
                    maiorNota = structLida.nota;
                    menorNota = structLida.nota;
                } else{
                    if(structLida.nota > maiorNota){
                        strcpy(alunoMaiorNota,structLida.nome);
                        maiorNota = structLida.nota;
                    }
                    if(structLida.nota < menorNota){
                        strcpy(alunoMenorNota,structLida.nome);
                        menorNota = structLida.nota;
                    }
                }
            }
        }
    }
    mediaNotas /= (float)quantidadeAlunos;
    printf("Quantidade de alunos: %d\n", quantidadeAlunos);
    printf("Media da turma: %0.2f\n", mediaNotas);
    printf("Aluno com maior nota: %s\n", alunoMaiorNota);
    printf("Aluno com menor nota: %s\n", alunoMenorNota);
    fclose(arquivo) ;

}

int main() {
    int matricula;
    int resp;
    struct ficha_aluno aluno;
    printf("BEM-VINDO...\n");
    do {
        printf("1 - Apresentar todo conteudo do arquivo\n");
        printf("2 - Apresentar conteudo de um registro\n");
        printf("3 - Cadastrar um registro\n");
        printf("4 - Estatisticas da Turma\n");
        printf("5 - Fechar o programa\n");
        printf("SELECIONE A OPCAO QUE DESEJA:\n");
        scanf("%d",&resp);
        getchar();
        switch (resp) {
            case 1:
                printf("MOSTRAR REGISTROS:\n\n");
                lerArquivo();
                break;
            case 2:
                printf("SELECIONAR REGISTRO:\n\n");
                printf("Informe a matricula que deseja consultar:\n");
                scanf("%d",&matricula);
                getchar();
                lerMatriculaEspecifica(matricula);
                break;
            case 3:
                printf("CADASTRO DE REGISTROS:\n\n");

                printf("Informe a matricula do aluno:\n");
                scanf("%d",&aluno.matricula);
                getchar();

                printf("Informe o nome do aluno:\n");
                fgets(aluno.nome,50,stdin);
                aluno.nome[strlen(aluno.nome)-1] = '\0';

                fflush(stdin);
                printf("Informe a nota final do aluno:\n");
                scanf("%f",&aluno.nota);
                getchar();

                int confirmacao = escreverArquivo(aluno);
                if(confirmacao == 1){
                    printf("CADASTRADO COM SUCESSO\n");
                }else{
                    printf("ERRO NO CADASTRO! TENTE NOVAMENTE\n");
                }
                break;
            case 4:
                printf("ESTATISTICAS\n\n");
                estatisticas();
                break;
            case 5:
                printf("FECHAR PROGRAMA\n");
                break;
            default:
                printf("ENTRADA INVALIDA\n");
                break;
        }
        printf("\n");
        printf("----------------------------------------------------\n");
    }while(resp != 5);
}
