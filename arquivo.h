#ifndef ARQUIVO_H
#define ARQUIVO_H

typedef struct STRUCT_MATRIZES{
	int tamanho_col;//representa coluna
	int tamanho_lin;//representa linha
    float **matriz;
}Struct_Matrizes;//typedef de struct para facilitar chamadas
Struct_Matrizes* Aloca_Struct();//função que aloca memoria para a struct
float** Cria_matriz(int linha, int coluna);//função que cria a matriz
void Mostra_matriz(Struct_Matrizes * struct_matrizes);//função que mostra a matriz
void Le_arquivo(FILE *Leitura, Struct_Matrizes *struct_matriz);//função que le o arquivo
void Mostra_vetor(float *p, int tamanho);//função para mostra o vetor
void Salva_arquivo(Struct_Matrizes *matc);//função para salvar a matriz resultante em um arquivo
#endif