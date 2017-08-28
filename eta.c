#include<stdio.h>
#include<stdlib.h>
#include<string.h>

double convert(char reais[13]){
    double brl = 0;
    int a=0;

    if(reais[0] > 47 && reais[0] < 58){
        brl = brl + ((float)reais[0] - 48.0) * 10000000;
    }

    if(reais[1] > 47 && reais[1] < 58){
        brl = brl + ((float)reais[1] - 48.0) * 1000000;
    }

    if(reais[3] > 47 && reais[3] < 58){
        brl = brl + ((float)reais[3] - 48.0) * 100000;
    }

    if(reais[4] > 47 && reais[4] < 58){
        brl = brl + ((float)reais[4] - 48.0) * 10000;
    }

    if(reais[5] > 47 && reais[5] < 58){
        brl = brl + ((float)reais[5] - 48.0) * 1000;
    }

    if(reais[7] > 47 && reais[7] < 58){
        brl = brl + ((float)reais[7] - 48.0) * 100;
    }

    if(reais[8] > 47 && reais[8] < 58){
        brl = brl + ((float)reais[8] - 48.0) * 10;
    }

    if(reais[9] > 47 && reais[9] < 58){
        brl = brl + ((float)reais[9] - 48.0) * 1;
    }

    if(reais[11] > 47 && reais[11] < 58){
        brl = brl + ((float)reais[11] - 48.0)/10;
    }

    if(reais[12] > 47 && reais[12] < 58){
        brl = brl + ((float)reais[12] - 48.0)/100;
    }
    return brl;
}


int cases(char *linha){

    if(linha[3] == '/' && linha[127] == ',' && strlen(linha) > 80){//LINHAS COMPLETAS
        return 1;
    }
    else if(linha[3] == '/' && strlen(linha) < 90){//linha com data, sem dados financeiros
        return 2;
    }
    else if(linha[3] == ' ' && strlen(linha) < 90){//LINHAS INUTEIS
        return 3;
    }
    else if(linha[3] == ' ' && linha[127] == ',' && strlen(linha) > 80){
        if(strstr(linha, "Saldo Atual:")!= NULL){
            return 6;
        }
        else if(strstr(linha, "Saldo Anterior:")!= NULL){
            return 6;
        }
        else if(strstr(linha, "Saldo do Mes:")!= NULL){
            return 6;
        }
        else if(strstr(linha, "Saldo Geral:")!= NULL){
            return 6;
        }
        else{
        return 4;
        }
    }
    else{ // TRATANDO CABEÇALHOS
        if(linha[127] == '-' && strlen(linha)> 90){
            return 5;
        }
    }
}

void solve1(char *linha, FILE *saida){// case 1: linhas completas

    int i;
    char lfinal[200], reais[13];
    double brl;

    //gerando a data
    for(i=0 ; i<11 ; i++){
        lfinal[i] = linha[i+1];
    }
    lfinal[10] = ';';

    //gerando o lançamento    
    for(i=0 ; i<11 ; i++){
        lfinal[i+11] = linha[i+12];
    }
    lfinal[21] = ';';

    // copiando contrapartida - 23 a 42
    for(i=0 ; i<21 ; i++){
        lfinal[i+22] = linha[i+23];
    }
    lfinal[42] = ';';

    // copiando complemento 45 a 76

    for(i=0 ; i<33 ; i++){
        lfinal[i+43] = linha[i+44];
    }
    lfinal[76] = ';';
    lfinal[77] = '\0';

    //JOGANDO PRIMEIRA PARTE NO ARQUIVO DE SAIDA!!!
    
    fprintf(saida, "%s", lfinal);
    printf("%s", lfinal);

    //DECISÃO ENTRE CREDITO E DEBITO;
    if(linha[91] == ','){//DEBITO
        for(i=0 ; i < 13 ; i++){
            reais[i] = linha[i+81];
        }
        brl = convert(reais);
        printf("D%.2lf", brl);
        fprintf(saida, "%.2lf;0;", brl);
        
    }
    else if(linha[109] == ','){//CREDITO
        for(i=0 ; i < 13 ; i++){
            reais[i] = linha[i+99]; 
        }
        brl = convert(reais);
        printf("C%.2lf", brl);
        fprintf(saida, "0;%.2lf;", brl);
    }
    for(i=0 ; i < 13 ; i++){//TOTAL
            reais[i] = linha[i+117];
        }
        brl = convert(reais);
        printf("T%.2lf\n", brl);
        fprintf(saida, "%.2lf\n", brl);
}

void solve2(char *linha, FILE *saida, char *aux){// // case 2: linha com data, sem dados financeiros

    int i, j;
    char lfinal[200];

    //gerando a data
    for(i=0 ; i<11 ; i++){
        lfinal[i] = linha[i+1];
    }
    lfinal[10] = ';';

    //gerando o lançamento    
    for(i=0 ; i<11 ; i++){
        lfinal[i+11] = linha[i+12];
    }
    lfinal[21] = ';';

    // copiando contrapartida - 23 a 42
    for(i=0 ; i<21 ; i++){
        lfinal[i+22] = linha[i+23];
    }
    lfinal[42] = ';';

    // copiando complemento 45 a 76

    for(i=0 ; i<33 ; i++){
        lfinal[i+43] = linha[i+44];
    }
    lfinal[76] = '\0';
    i=0;
    while(lfinal[i] != '\n'){
        aux[i] = lfinal[i];
        i++;
    }
    aux[72] = '\0';
}

void solve3(char *linha, FILE *saida, char *aux){// case 3: Linhas inuteis
    int i=0;
    char lfinal[200];

    // copiando complemento 45 a 76
    while(linha[i] != '\n'){
        lfinal[i] = linha[i+53];
        i++;
        }
    strcat(aux, lfinal);
}

void solve4(char *linha, FILE *saida, char *aux){// case 4: continuação, sem dados finaiceiros

    int i=0;
    char lfinal[200], reais[13];
    double brl;

    aux[strlen(aux) - 6] = '\0';

    // copiando complemento 45 a 76
    for(i=0 ; i<20 ; i++){        
        lfinal[i] = linha[i+44];
    }
    lfinal[i] = ';';
    lfinal[i+1] = '\0';
    strcat(aux, lfinal);

    //JOGANDO PRIMEIRA PARTE NO ARQUIVO DE SAIDA!!!
    fprintf(saida, "%s", aux);
    printf("%s", aux);

    //DECISÃO ENTRE CREDITO E DEBITO;
    if(linha[91] == ','){//DEBITO
        for(i=0 ; i < 13 ; i++){
            reais[i] = linha[i+81];
        }
        brl = convert(reais);
        printf("D%.2lf", brl);
        fprintf(saida, "%.2lf;0;", brl);
        
    }
    else if(linha[109] == ','){//CREDITO
        for(i=0 ; i < 13 ; i++){
            reais[i] = linha[i+99]; 
        }
        brl = convert(reais);
        printf("C%.2lf", brl);
        fprintf(saida, "0;%.2lf;", brl);
    }
    for(i=0 ; i < 13 ; i++){//TOTAL
            reais[i] = linha[i+117];
        }
        brl = convert(reais);
        printf("T%.2lf\n", brl);
        fprintf(saida, "%.2lf\n", brl);
        aux[0] = '\0';
}


int main(){
    FILE *entrada = fopen("arquivo.txt", "r");
    FILE *saida = fopen("saida.csv", "w");

    char linha[200], aux[200];
    int a = 0, b=0;
    //criando o primeiro arquivo pré-processado com menos lixo
    while(!feof(entrada)){
        fgets(linha, 200, entrada);
        a = cases(linha);


        switch(a){
            case 1:
                solve1(linha, saida);
                break;
            case 2:
                solve2(linha, saida, aux);
                break;
            case 3:
                solve3(linha, saida, aux);
                break;
            case 4:
                solve4(linha, saida, aux);
                break;
            default:
            printf("cabecalho");
        }

    }
    fclose(entrada);
    fclose(saida);
    return 0;
}
