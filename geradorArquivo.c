#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void main(int argc, char const *argv[]){
    if(argc == 4 && argv[1] != NULL && argv[2] != NULL && argv[3] != NULL){
        char caminho[100]; strcpy(caminho,argv[1]);
        int tamanho_linha = atoi(argv[2]);
        int tamanho_coluna = atoi(argv[3]);
        FILE *arquivo = fopen(caminho,"w");
        if(arquivo != NULL){
            for(int i = 0; i < tamanho_linha; i++){
                for(int j = 0; j < tamanho_coluna; j++){
                    fprintf(file,"%f")
                }
            }
        }

    }else{
        printf("É necessário passar o tamanho de linha, de coluna e o caminho/nome do arquivo de matriz!\n");
        printf("A ordem correta do parametro é caminho/nome,linha e por fim coluna\n");
    }
}