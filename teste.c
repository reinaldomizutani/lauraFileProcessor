#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
TO DO:
- linhas repetidas de data - existem mais linhas de data do que linhas de lançamento
*/


    // -----------------------------------------------
    // main e declaração de variáveis
    // -----------------------------------------------
int main(){
    FILE *entrada;
    FILE *saida;
    char data[11], lancamento[11],linha[200], intermed[200], dados[200], final[600], aux[15], aux2[15];
    int cont = 0, a=0, b=0, debito=0, credito=0;
    entrada = fopen("arquivo2.txt", "r");
    saida = fopen("saida.txt", "w");

    // -----------------------------------------------
    // verificação para abertura do arquivo
    // -----------------------------------------------
    if(entrada == NULL){
        printf("Erro ao abrir o arquivo.\nO nome do arquivo deve ser 'arquivo.txt'");
        exit(1);
    }

    // -----------------------------------------------
    // Main loop do programa
    // -----------------------------------------------
    while(!feof(entrada)){
        fgets(linha, 200, entrada);

        // -----------------------------------------------
        // CONSTRUTOR DE DATA E LANÇAMENTO: se a linha possui uma data (linha[3]=='/'), copia os caracteres para a variável char data
        // -----------------------------------------------

        if(linha[3] == '/'){ // precisa verificar esse if (ele ta separando todas as linhas que tem data, mas nao finaliza se a linha tem todos os dados)
            for(int a = 1 ; a < 11 ; a++){
                data[a-1] = linha[a];
            }
            data[10] = '\0';
            for(int a = 12 ; a < 22 ; a++){
                lancamento[a-12] = linha[a];
            }
            lancamento[10] = '\0';
            a=0;
            for(a = 0 ; a < 10 ; a++){//concatenando na variavel final
                final[a] = data[a];
            }
            
            final[10] = ';';
            for(a = 11 ; a < 21 ; a++){
                final[a] = lancamento[a-11];
            }
            final[21] = ';';

            for(a=22 ; a<42 ; a++){
                final[a] = linha[a];
            }

            final[42] = ';';

            while(linha[a] != '\n'){
                final[a] = linha[a];
                a++;
            }
            final[72] = '\n';
            final[73] = '\0';
            

            if(strlen(linha) > 80){
                //SEGUNDA PARTE PARA LINHAS COMPLETAS!!
                // para DEBITO
                if(linha[109] == ','){
                    a=0;
                    cont=111;
                    while(aux[a-1] != ' '){
                        aux[a] = linha[cont];
                        a++;
                        cont--;
                    }
                    aux[a] = '\0';
                    final[72] = ';';

                    b = strlen(aux);
                    for(a=0 ; a < b+3 ; a++){
                        final[a+73] = aux[b-1];
                        b--;
                    }
                    printf("%s\n", final);
                }
            }
            else if(strlen(linha)<80){

            }
        }
    }
    
    
    fclose(entrada);
    fclose(saida);
    return 0;
}
