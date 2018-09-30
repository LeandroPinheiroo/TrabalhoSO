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

Struct_Matrizes* Aloca_Struct(){
//funcao responsavel por alocar a struct de matriz na memoria
    Struct_Matrizes *struct_matriz = (Struct_Matrizes*)malloc(sizeof(struct STRUCT_MATRIZES));//aloca na memoria
    return struct_matriz;//retorna a struct
}
//Função para criar matriz de acordo com o valores para linha e coluna passado por parametro
float** Cria_matriz(int linha, int coluna){
    //aloca dinamicamente espaço para a matriz
    float** matriz = (float**)malloc(linha * sizeof(float*));
    for (int i = 0; i < linha; i++){ //percorre as linhas do vetor, para alocar as colunas
       matriz[i] = (float*) malloc(coluna * sizeof(float));
    }
    //e assim que criada a matriz, retorna os ponteiros para ela*/
    return(matriz);
}

void Mostra_vetor(float *p, int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("%f ",p[i]);
    }
    printf("\n");
}
//Função para mostrar a matriz
void Mostra_matriz(Struct_Matrizes * struct_matrizes){
    //mostra as linhas
    printf("%i\n",struct_matrizes->tamanho_lin);
    printf("%i\n",struct_matrizes->tamanho_col);
    //primeiro for para linhas
    for(int i = 0; i < struct_matrizes->tamanho_lin; i++){
        //segundo para as colunas
        for(int j = 0; j < struct_matrizes->tamanho_col; j++){
            //mostra o elemento
            printf("%f ",struct_matrizes->matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Le_arquivo(FILE *Leitura, Struct_Matrizes *struct_matriz){
    //Função responsavel por ler arquivo e montar matriz
	//Cria variaveis para ler do arquivo
    float valor;
	fscanf(Leitura,"%i",&struct_matriz->tamanho_lin);//le quantidade de linhas
	getc(Leitura);
	//pula o espaço
    fscanf(Leitura,"%i",&struct_matriz->tamanho_col);//le quantidade de colunas
    getc(Leitura);
	//pula o espaço
    //aloca a matriz com tamanho de linhas e colunas lidas anteriormente
    struct_matriz->matriz = Cria_matriz(struct_matriz->tamanho_lin,struct_matriz->tamanho_col);
    for(int i = 0; i<struct_matriz->tamanho_lin;i++){
        for(int j = 0; j<struct_matriz->tamanho_col;j++){
            //agora le todos os numeros da matriz
            //verificando se ainda não está no final do arquivo, para não ler o vazio
            if((!feof(Leitura))){
                //le o valor
                fscanf(Leitura,"%f",&valor);
                //salva na matriz
                struct_matriz->matriz[i][j] = valor;
                getc(Leitura);//pula espaco
            }
        }
    }
}
//função para salvar o arquivo da matriz C
void Salva_arquivo(Struct_Matrizes *matc){
    //abre o arquivo em modo de leitura
    FILE* arquivo = fopen("resultado.txt","w");
    //verifica se não houve erro na leitura
    if(arquivo != NULL){
        //salva a linha e a coluna no arquivo
        fprintf(arquivo,"%i\n",matc->tamanho_lin);
        fprintf(arquivo,"%i\n",matc->tamanho_col);
        //senão houve, salva a matriz no arquivo
        for(int i = 0; i < matc->tamanho_lin; i++){
            for(int j = 0; j < matc->tamanho_col; j++){
                fprintf(arquivo,"%f ",matc->matriz[i][j]);
            }
            fprintf(arquivo,"\n");
        }
        //fecha o arquivo no final do salvamento
        fclose(arquivo);
    }
    //se houve erro, mostra mensagem para avisar alguma irregularidade no arquivo
    else{
        printf("Caminho irregular passado para o arquivo!\n");
    }
}
