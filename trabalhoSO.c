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

typedef struct STRUCT_MATRIZES{
	int tamanho_col;//representa coluna
	int tamanho_lin;//representa linha
    int **matriz;
}Struct_Matrizes;//typedef de struct para facilitar chamadas

Struct_Matrizes* Aloca_Struct(){
//funcao responsavel por alocar a struct de matriz na memoria
    Struct_Matrizes *struct_matriz = (Struct_Matrizes*)malloc(sizeof(struct STRUCT_MATRIZES));//aloca na memoria
    return struct_matriz;//retorna a struct
}

void Le_arquivo(FILE *Leitura, Struct_Matrizes *struct_matriz){
//Função responsavel por ler arquivo e montar matriz
	//Cria variaveis para ler do arquivo
	fscanf(Leitura,"%d",&struct_matriz->tamanho_lin);//le quantidade de linhas
	getc(Leitura);
	//pula o espaço
    fscanf(Leitura,"%d",&struct_matriz->tamanho_col);//le quantidade de colunas
    getc(Leitura);
	//pula o espaço
    struct_matriz->matriz=(int **)malloc(struct_matriz->tamanho_lin*sizeof(int*));//aloca matriz
    int valor = 0;
    for(int i = 0; i<struct_matriz->tamanho_lin;i++){
        struct_matriz->matriz[i]=(int *)malloc(struct_matriz->tamanho_col*sizeof(int));
        for(int j = 0; j<struct_matriz->tamanho_col;j++){
            fscanf(Leitura,"%d",&valor);
            getc(Leitura);//pula espaco
            struct_matriz->matriz[i][j] = valor;
        }
        getc(Leitura);//pula \n
    }   
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
        Struct_Matrizes *struct_matrizA = Aloca_Struct();//Aloca Struct para matriz A
        Struct_Matrizes *struct_matrizB = Aloca_Struct();//Aloca Struct para matriz B
        Le_arquivo(arquivo_Leitura, struct_matrizA);//Le o arquivo referente a matriz A e preenche a mesma
        fclose(arquivo_Leitura);//fecha o arquivo
        arquivo_Leitura = fopen(argv[2],"r");//abre o arquvio referente a matriz B
        if(arquivo_Leitura == NULL){//Caso erro ao abrir
            printf("\n%s não é um arquivo/caminho válido\n",argv[2]);
            return 0;//sai
        }
        Le_arquivo(arquivo_Leitura, struct_matrizB);//Le arquivo referente a matriz B e preenche a mesma
        fclose(arquivo_Leitura);//fecha arquvivo de leitura
    }
   
}