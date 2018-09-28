//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////1
//
//Nome:		Leandro Souza Pinheiro 
//Nome:		João Paulo de Souza
//
//4º Periodo	Sistema Operacional
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"
#include <pthread.h>

Struct_Matrizes *struct_matrizA;
Struct_Matrizes *struct_matrizB;
Struct_Matrizes *struct_matrizC;

//controle da matriz A, controla a coluna que ela lê, as linhas são controladas pelo laço
int controle_matA_linha = 0;
//controle da matriz B, controla a linha que ela lê, as colunas são controladas pelo laço
int controle_matB_coluna = 0;

//controles da matriz c, para preenche-la, o controle de linha e coluna;
int c_matrizc_linha = 0;
int c_matrizc_coluna = 0;

//variavel que armazena as somas


int* Vetor_matrizA(){
    int *vetor = (int*)malloc(struct_matrizA->tamanho_col * sizeof(int));
    return vetor;
}

int* Vetor_matrizB(){
    int *vetor = (int*)malloc(struct_matrizB->tamanho_lin * sizeof(int));
    return vetor;
}

void preenche_vetorMatrizA(int *v){
    for(int i = 0; i < struct_matrizA->tamanho_col; i++){
        v[i] = struct_matrizA->matriz[controle_matA_linha][i];
    }
}

void preenche_vetorMatrizB(int *v){
    for(int j = 0; j < struct_matrizB->tamanho_lin; j++){
        v[j] = struct_matrizB->matriz[j][controle_matB_coluna];
    }
}

//função de multiplicar as celulas que cada thread vai executar uma vez
void *Multiplica_celulas(void *param){
    //zera a soma, para somar os valores da linha e coluna
    int soma; soma = 0;
    //cria os vetores que vao receber uma linha e uma coluna das matrizes A e B
    int *vetorA = Vetor_matrizA();
    int *vetorB = Vetor_matrizB();
    //preenche os dois vetores com a linha e coluna respectiva
    preenche_vetorMatrizA(vetorA);
    //Mostra_vetor(vetorA,struct_matrizA->tamanho_col);
    preenche_vetorMatrizB(vetorB);
    //Mostra_vetor(vetorB,struct_matrizB->tamanho_lin);
    //printf("\n");
    //realiza a soma de acordo com os indices dos vetores
    for(int i = 0; i < struct_matrizA->tamanho_col; i++){
        soma += vetorA[i] * vetorB[i];
    }
    //salva o valor na matriz, entretanto tem de controlar o indice da coluna e da linha
    struct_matrizC->matriz[c_matrizc_linha][c_matrizc_coluna] = soma;
    c_matrizc_coluna++;
    //verifica se ja está no final da coluna da matriz c
    if(c_matrizc_coluna == struct_matrizC->tamanho_col){
        //se chegou ao final, zera a coluna e incrementa a linha
        c_matrizc_coluna = 0;
        c_matrizc_linha++;
    }
    //incrementa a coluna para preencher o vetor
    controle_matB_coluna++;
    //verifica se o ja chegou ao final da coluna da matriz B
    if(controle_matB_coluna == struct_matrizB->tamanho_col){
        //zera a variavel que controla a coluna
        controle_matB_coluna = 0;
        //e soma mais um a linha
        controle_matA_linha++;
    }
    //libera os dois vetores
    free(vetorA);
    free(vetorB);
    pthread_exit(0);
}
//função para dar free em tudo e zerar as variaveis
void limpa_tudo(){
    free(struct_matrizA);
    free(struct_matrizB);
    free(struct_matrizC);
    controle_matA_linha = 0;
    controle_matB_coluna = 0;
    c_matrizc_coluna = 0;
    c_matrizc_linha = 0;
}
//função principal
int main(int argc, char const *argv[]){
   FILE *arquivo_Leitura;//Cria ponteiro para abrir arquivos de entrada
   if(argc == 3){//Verifica a quantidade de argumentos passados
        arquivo_Leitura = fopen(argv[1],"r");
        //Abre o arquivo 1
        if(arquivo_Leitura == NULL){
            printf("\n%s não é um arquivo/caminho válido\n",argv[1]);
            return 0;//sai
        }//Caso o Arquivo não exista
        struct_matrizA = Aloca_Struct();//Aloca Struct para matriz A
        struct_matrizB = Aloca_Struct();//Aloca Struct para matriz B
        struct_matrizC = Aloca_Struct();//Aloca Struct para matriz C
        Le_arquivo(arquivo_Leitura, struct_matrizA);//Le o arquivo referente a matriz A e preenche a mesma
        fclose(arquivo_Leitura);//fecha o arquivo
        arquivo_Leitura = fopen(argv[2],"r");//abre o arquvio referente a matriz B
        if(arquivo_Leitura == NULL){//Caso erro ao abrir
            printf("\n%s não é um arquivo/caminho válido\n",argv[2]);
            return 0;//sai
        }
        Mostra_matriz(struct_matrizA);//mostra a matriz A
        Le_arquivo(arquivo_Leitura, struct_matrizB);//Le arquivo referente a matriz B e preenche a mesma
        fclose(arquivo_Leitura);//fecha arquvivo de leitura
        Mostra_matriz(struct_matrizB);//mostra a matriz B
        /*
            threads
        */
        /*variável para guardar a quantidade de elementos dos vetores de atributos e ids
        de threads*/
        //cria a matriz C
        struct_matrizC->matriz = Cria_matriz(struct_matrizA->tamanho_lin,struct_matrizB->tamanho_col);
        //pega o tamanho da linha da matriz c, que é o mesmo da linha de A
        struct_matrizC->tamanho_lin = struct_matrizA->tamanho_lin;
        //pega o tamanho da coluna da matriz c, que é o mesmo da coluna de B
        struct_matrizC->tamanho_col = struct_matrizB->tamanho_col;
        //variavel tamanho, multiplica a linha da matriz A com a coluna da B para encontra o tamanho
        //da nova matriz
        int tamanho = struct_matrizA->tamanho_lin * struct_matrizB->tamanho_col;
        /*cria o vetor de atributos das threads*/
        pthread_attr_t atributothreads[tamanho];
        /*e cria o vetor de ids das threads*/
        pthread_t idthreads[tamanho];
        /*inicializa o vetor dos atributos das threads com default*/
        for(int i = 0; i < tamanho; i++){
            pthread_attr_init(&atributothreads[i]);
        }
        /*cria as threads*/
        for(int i = 0; i < tamanho; i++){
            pthread_create(&idthreads[i],&atributothreads[i],Multiplica_celulas, (void *)NULL);
        }
        /*threads em execução, aguardando elas terminarem suas execuções*/
        for(int i = 0; i < tamanho; i++){
            //em caso da thread der erro na execução, aborta a aplicação
             if(pthread_join(idthreads[i],NULL) != 0){
                 printf("Erro na execução da thread: %i\n", i);
                 exit(1);
             }
        }
        //mostra a matriz C
        Mostra_matriz(struct_matrizC);
        //limpa todos os ponteiros e zera as variaveis
        limpa_tudo();
    }
    //em caso de argumentos faltando por parametro, mostra mensagem de erro
    else if(argc == 1){
        printf("Falta passar os dois arquivos de matrizes como parametro\n");
    }
    limpa_tudo();
    return 0;
}
