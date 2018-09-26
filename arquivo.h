#ifndef ARQUIVO_H
#define ARQUIVO_H

typedef struct STRUCT_MATRIZES{
	int tamanho_col;//representa coluna
	int tamanho_lin;//representa linha
    int **matriz;
}Struct_Matrizes;//typedef de struct para facilitar chamadas
Struct_Matrizes* Aloca_Struct();//função que aloca memoria para a struct
int** Cria_matriz(int linha, int coluna);//função que cria a matriz
void Mostra_matriz(Struct_Matrizes * struct_matrizes);//função que mostra a matriz
void Le_arquivo(FILE *Leitura, Struct_Matrizes *struct_matriz);//função que le o arquivo

#endif