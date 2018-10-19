if __name__ == '__main__':
    with open('arquivo2.txt', 'r') as f:
        file = f.readlines()

    normais = 0
    quebradas = 0
    erros = 0
    linhaAtual =0
    arquivo = []
    for line in file:
        try:
            if(line[2] == '/' and line[5] == '/' and line[-3] == 'D'):#caso linha normal
                final = line[33:].split()
                
                strFinal = line[0:10] + ';' +  line[11:21] +';'+ line[22:32]
                strFinal = strFinal+ ';' + final[0] + ' ' + final[1]  + ' ' + final[2] + ';' + final[-3] + ';' + final[-2] + ';' + final[-1].rstrip('\n')

                arquivo.append(strFinal)
                normais +=1
                linhaAtual +=1

            #caso linhas quebradas
            elif(line[2] == '/' and line[5] == '/' and line[-3] == '-'):
                quebrada = line.split()
                linhaQuebrada = quebrada[0] + ';' + quebrada[1] + ';' + quebrada[2] + ' ' + quebrada[3] + ' ' + quebrada[4]
                linhaAtual +=1

            elif(line[0] == '0'):
                linhaQuebrada = linhaQuebrada.rstrip('\n') + ';' + line.rstrip('\n')
                linhaAtual +=1
                
            elif(line[0] == 'D' and line[1] == ' '):
                quebradas+=1
                linhaQuebrada = linhaQuebrada + ';' + line.rstrip
                arquivo.append(linhaQuebrada)
                linhaAtual +=1
                


        except Exception as e:
            erros +=1
            linhaAtual +=1

    with open('arquivoSaida.txt', 'w') as saida:
        for item in arquivo:
            item = item + '\n'
            saida.write(item)


    print('quebradas = ' + str(quebradas))
    print('normais = ' + str(normais))
    print('erros = ' + str(erros))
    print('nro Linhas = ' + str(linhaAtual))
