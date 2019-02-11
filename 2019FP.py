if __name__ == '__main__':
    with open('arquivo.txt', 'r') as f:
        file = f.readlines()

    normais = 0
    quebradas = 0
    erros = 0
    linhaAtual =0
    arquivo = []
    for line in file:
        try:
            if(line[3] == '/' and line[6] == '/' and line[-2] == 'D'):#caso linha normal  (extra dentro do if) ->
                final = line[33:].split()
                
                strFinal = line[1:11] + ';' +  line[12:22] +';'+ line[23:33]
                strFinal = strFinal+ ';' + final[0] + ' ' + final[1]  + ' ' + final[2] + ';' + final[-3] + ';' + final[-2] + ';' + final[-1].rstrip('\n')
                
                arquivo.append(strFinal)
                normais +=1
                linhaAtual +=1

            #caso linhas quebradas
            elif(line[3] == '/' and line[6] == '/' and len(line) < 100):
                
                quebrada = line.split()
                
                linhaQuebrada = quebrada[0] + ';' + quebrada[1] + ';' + quebrada[2] + ';' + quebrada[3] + ' ' + quebrada[4]
                linhaAtual +=1
                
            elif(len(line) < 120 and line[2] == ' '):
                temp = line.lstrip()
                linhaQuebrada = linhaQuebrada.rstrip('\n') + temp
                linhaAtual +=1

            elif(len(line) > 120 and line[1] == " " and line[-2] == 'D'and "Saldo" not in line):
                temp = line.lstrip()
                temp = temp[:-3]
                t1 = temp[:40]
                t1 = t1.strip()
                t2 = temp[41:71]
                t2 = t2.strip()
                t3 = temp[71:]
                t3 = t3.strip()

                last = t1+ ';' + t2 + ';' + t3
                linhaQuebrada = linhaQuebrada.rstrip('\n') + last
                arquivo.append(linhaQuebrada)
                linhaAtual +=1

        except Exception as e:
            erros +=1
            linhaAtual +=1

    with open('arquivo.csv', 'w') as saida:
        for item in arquivo:
            item = item + '\n'
            saida.write(item)


    print('quebradas = ' + str(quebradas))
    print('normais = ' + str(normais))
    print('erros = ' + str(erros))
print('nro Linhas = ' + str(linhaAtual))
