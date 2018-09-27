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

typedef struct VETOR{
    int *vet;
}Vetor;

Vetor *coluna;
Vetor *linha;
int controle_matA;
int controle_matB;

void Aloca_vetor(int *p, int tamanho){
    p = (int*)malloc(tamanho * sizeof(int));
}

Vetor* Aloca_vetor_struct(){
//funcao responsavel por alocar a struct de matriz na memoria
    Vetor *vetor = (Vetor*)malloc(sizeof(struct VETOR));//aloca na memoria
    return vetor;//retorna a struct
}

void preenche_matrizA(){
    for(int i = 0; i < struct_matrizA->tamanho_lin; i++){
        coluna->vet[i] = struct_matrizA->matriz[i][controle_matA];
    }
}

void preenche_matrizB(){
    for(int i = 0; i < struct_matrizB->tamanho_col; i++){
        linha->vet[i] = struct_matrizB->matriz[controle_matB][i];
    }
}

void *Multiplica_celulas(void *param){
    Aloca_vetor(coluna->vet,struct_matrizA->tamanho_lin);
    Aloca_vetor(linha->vet,struct_matrizB->tamanho_col);
    preenche_matrizA();
    preenche_matrizB();
    controle_matB++;
    if(controle_matB == struct_matrizB->tamanho_lin){
        controle_matB = 0;
        controle_matA++;
    }
    int soma = 0;
    for(int i = 0; i < struct_matrizB->tamanho_col; i++){
        soma += linha->vet[i] * coluna->vet[i];
        printf("%d\t",soma);
    }printf("\n");
    soma =0;
    pthread_exit(0);
}

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
        Le_arquivo(arquivo_Leitura, struct_matrizA);//Le o arquivo referente a matriz A e preenche a mesma
        fclose(arquivo_Leitura);//fecha o arquivo
        arquivo_Leitura = fopen(argv[2],"r");//abre o arquvio referente a matriz B
        if(arquivo_Leitura == NULL){//Caso erro ao abrir
            printf("\n%s não é um arquivo/caminho válido\n",argv[2]);
            return 0;//sai
        }
        Mostra_matriz(struct_matrizA);
        Le_arquivo(arquivo_Leitura, struct_matrizB);//Le arquivo referente a matriz B e preenche a mesma
        fclose(arquivo_Leitura);//fecha arquvivo de leitura
        Mostra_matriz(struct_matrizB);
        coluna= Aloca_vetor_struct();
        linha= Aloca_vetor_struct();
        
        
        /*
            threads
        */
        /*variável para guardar a quantidade de elementos dos vetores de atributos e ids
        de threads*/
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
             if(pthread_join(idthreads[i],NULL) != 0){
                 printf("Erro na execução da thread: %i\n", i);
                 exit(1);
             }
        }
    }
    else if(argc == 1){
        printf("Falta passar os dois arquivos de matrizes como parametro\n");
    }
    return 0;
}
