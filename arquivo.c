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
int** Cria_matriz(int linha, int coluna){
    //aloca dinamicamente espaço para a matriz
    int** matriz = (int**)malloc(linha * sizeof(int*));
    for (int i = 0; i < linha; i++){ //percorre as linhas do vetor, para alocar as colunas
       matriz[i] = (int*) malloc(coluna * sizeof(int));
    }
    //e assim que criada a matriz, retorna os ponteiros para ela*/
    return(matriz);
}

void Mostra_vetor(int *p, int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("%i ",p[i]);
    }
    printf("\n");
}
//Função para mostrar a matriz
void Mostra_matriz(Struct_Matrizes * struct_matrizes){
    //para linhas
    for(int i = 0; i < struct_matrizes->tamanho_lin; i++){
        //para as colunas
        for(int j = 0; j < struct_matrizes->tamanho_col; j++){
            //mostra o elemento
            printf("%i ",struct_matrizes->matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Le_arquivo(FILE *Leitura, Struct_Matrizes *struct_matriz){
    //Função responsavel por ler arquivo e montar matriz
	//Cria variaveis para ler do arquivo
    int valor;
	fscanf(Leitura,"%d",&struct_matriz->tamanho_lin);//le quantidade de linhas
	getc(Leitura);
	//pula o espaço
    fscanf(Leitura,"%d",&struct_matriz->tamanho_col);//le quantidade de colunas
    getc(Leitura);
	//pula o espaço
    struct_matriz->matriz = Cria_matriz(struct_matriz->tamanho_lin,struct_matriz->tamanho_col);
    for(int i = 0; i<struct_matriz->tamanho_lin;i++){
        for(int j = 0; j<struct_matriz->tamanho_col;j++){
            if((!feof(Leitura))){
                fscanf(Leitura,"%i",&valor);
                struct_matriz->matriz[i][j] = valor;
                getc(Leitura);//pula espaco
            }
        }
    }
}
