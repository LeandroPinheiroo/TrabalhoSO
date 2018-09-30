#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void main(int argc, char const *argv[]){
    if(argc == 2 && argv[1] != NULL){
        srand(time(NULL));
        char caminho[100]; strcpy(caminho,argv[1]);
        int tamanho_linha = rand() % 6 + 1;
        int tamanho_coluna = rand() % 6 + 1;
        float valor;
        FILE *arquivo = fopen(caminho,"w");
        if(arquivo != NULL){ 
            fprintf(arquivo,"%i\n",tamanho_linha);
            fprintf(arquivo,"%i\n",tamanho_coluna);
            for(int i = 0; i < tamanho_linha; i++){
                for(int j = 0; j < tamanho_coluna; j++){
                    valor = (float)(rand() % 100 + 1) / (rand() % 10 + 1);
                    fprintf(arquivo,"%f ",valor);
                }
                fprintf(arquivo,"\n");
            }
        }

    }else{
        printf("É necessário passar o caminho/nome do arquivo de matriz!\n");
    }
}