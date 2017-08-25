#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int classificador(char linha[]){
    if(strlen(linha) > 100 && linha[127] == ',' && linha[3] == '/'){ // case 1: quando é uma linha completa
        return 1;
    }
    else if(strlen(linha) < 100 && linha[3] == '/'){ //case 2: onde a linha tem data e quebra de linha
        return 2;
    }
    else if(linha[3] == ' ' && linha[127] == ',' && strlen(linha) > 100){ // case 3: onde a linha tem dados financeiros e houve uma quebra de linha acima)
        return 3;
    }
    else if(strlen(linha) < 100 && linha[3] == ' '){ // case 4: linha inútil
        return 4;
    }
    else{
        return 0;
    }


    //if(linha[3] == '/' && linha)

}

int main(){
    FILE *entrada = fopen("arquivo2.txt", "r");
    FILE *saida = fopen("saida.txt", "w");
    if(entrada == NULL){
        printf("Erro ao abrir o arquivo.\nO nome do arquivo deve ser 'arquivo.txt'");
        exit(1);
    }
    char linha[133], final[300];
    int contlinha = 0, tipo = 0, a=0, b=0;

    while(!feof(entrada)){
        contlinha++;
        fgets(linha, 200, entrada);
        tipo = classificador(linha);
    switch(tipo){
        case 0:
            printf("linha: %d, case 0\n", contlinha);
            break;
        case 1: // quando a linha possui todos os dados necessários

            a=0;
            b=0;

            for(a=0 ; a<11 ; a++){// data
                final[a] = linha[a+1];
            }
            final[10] = ';';
            for(a=0 ; a<10 ; a++){//lançamento
                final[a+11] = linha[a+12];
            }
            final[21] = ';'; // continua a partir do 22

            for(a=0 ; a < 14 ; a++){//debito
                final[a+22] = linha[a+80];
            }
            final[36] = ';';

            for(a=0 ; a< 14 ; a++){//credito
                final[a+37] = linha[a+98];
            }
            final[51] = ';'; // valor final
            for(a=0 ; a < 14 ; a++){
                final[a+52] = linha[a+116];
            }
            final[66] = ';';
            final[67] = '\0';

            printf("linha: %d, case 1 : %s inserido\n", contlinha, final);
            break;
        case 2:
            printf("linha: %d, case 2\n", contlinha);
            break;
        case 3:
            printf("linha: %d, case 3\n", contlinha);
            break;
        case 4:
            printf("linha: %d, case 4\n", contlinha);
            break;
    }


    }
    return 0;
}
