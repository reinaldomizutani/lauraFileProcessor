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
    char c = 'a', data[11], lancamento[11],linha[200], intermed[100];
    int cont = 0, a=0;
    entrada = fopen("arquivo2.txt", "r");
    saida = fopen("saida.txt", "w");
    fprintf(saida, "\n\n");

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
    if(linha[3] == '/'){
        for(int a = 1 ; a < 11 ; a++){
            data[a-1] = linha[a];
        }
        data[10] = '\0';
        for(int a = 12 ; a < 22 ; a++){
            lancamento[a-12] = linha[a];
        }
        lancamento[10] = '\0';
    }

    // -----------------------------------------------
    // Linhas intermediárias (que não começam com data)
    // -----------------------------------------------

    else if(linha[3] == 20){
        c = 'a';
        while(c != '\n'){
            c = linha[a];
            a = a + 1;
            cont = cont + 1;
            printf("a: %d\ncont: %d", a, cont)
        }
        // caso em que a linha não possui dados de operações de débito, crédito ou saldo total.
        if(cont < 90){
            cont = 0;
            a = 0;
            while(linha[cont] == 20){
            cont = cont + 1;
            }
            while(c != '\n'){
                c = linha[cont];
                intermed[a] = c;
                a++;
                cont++;
        }
        // Caso onde há resultados financeiros a serem trabalhados
        }/*
        else if (cont > 90){

        }


*/
    }


    fprintf(saida, "%s;%s;%s\n", data, lancamento, intermed);
    printf("%s\n", intermed);
    }
    
    fclose(entrada);
    fclose(saida);
    return 0;
}