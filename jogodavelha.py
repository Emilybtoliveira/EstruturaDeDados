import random

def mostraPosicoes():
    print("\nEstes são os números atribuidos a cada espaço:\n")
    contador = 1
    for y in range(3):
        for x in range(3):
            print (" %i "% contador, end="")
            contador += 1
        print("\n")

def exibeTabuleiro(tabuleiro):
    print("\n")
    for i in range (3):
        for j in range(3):            
            if(tabuleiro[i][j] == 'X'):
                print(" X ", end="")
            elif(tabuleiro[i][j] == 'O'):
                print(" O ", end="")
            else:
                print(" _ ", end="")            
        print("\n")


def vezMaquina(carac_maquina, tabuleiro):    
    validado = False

    while (not validado):
        maquina = random.randint(1,9)

        for i in range(3):
            for j in range(3):
                if(tabuleiro[i][j] == maquina):
                    tabuleiro[i][j] = carac_maquina
                    validado = True
                    return
        
        validado = False                    

def verificaVencedor(exes, os, carac_jog):
    if(exes == 3):
        if(carac_jog == 'X'):
            return 1 #jogador venceu
        else:
            return 2 #maquina venceu
    elif(os == 3):
        if(carac_jog == 'X'):
            return 2 #maquina venceu
        else:
            return 1 #jogador venceu
    else:
        return 0

def verificaEstado(tabuleiro, carac_jog):
    exes = 0
    os = 0

    #diag principal
    for i in range (3):
        if (tabuleiro[i][i] == 'X'):
            exes += 1
        elif(tabuleiro[i][i] == 'O'):
            os += 1

    res = verificaVencedor(exes, os,  carac_jog)
    if(res != 0):
        return res
    else:
        exes = 0
        os = 0
    
    #diag secundaria
    i = 0
    for j in range(2, -1, -1):               
        if (tabuleiro[i][j] == 'X'):
            exes += 1
        elif(tabuleiro[i][j] == 'O'):
            os += 1
        i += 1 

    res = verificaVencedor(exes, os,  carac_jog)
    if(res != 0):
        return res
    else:
        exes = 0
        os = 0

    #linhas
    for i in range(3):
        for j in range(3):
            if (tabuleiro[i][j] == 'X'):
                exes += 1
            elif(tabuleiro[i][j] == 'O'):
                os += 1
        res = verificaVencedor(exes, os,  carac_jog)
        if(res != 0):
            return res
        else:
            exes = 0
            os = 0

    #colunas
    for j in range(3):
        for i in range(3):
            if (tabuleiro[i][j] == 'X'):
                exes += 1
            elif(tabuleiro[i][j] == 'O'):
                os += 1
        res = verificaVencedor(exes, os,  carac_jog)
        if(res != 0):
            return res
        else:
            exes = 0
            os = 0

    #todas ocupadas = empate
    for i in range(3):
        for j in range(3):
            if (tabuleiro[i][j] == 'X'):
                exes += 1
            elif(tabuleiro[i][j] == 'O'):
                os += 1
    if(exes+os == 9):
        return 3 #deu velha(empate)
    
    #nada ocorreu
    return 0;

def printa(verificando):
    if(verificando == 1):
        print("Você venceu! Parabéns!\n")
            
    elif(verificando == 2):
        print("Eu ganhei, ha! Vamos de novo!\n")
        
    elif(verificando == 3):
        print("Err, deu velha.\n")            


def jogo(carac_jog):
    fim_de_jogo = False    
    tabuleiro = [[1,2,3], [4,5,6], [7,8,9]]
    print("\nVocê começa;)")
    exibeTabuleiro(tabuleiro)
    while(fim_de_jogo == False):           

        #Opoente    
        validado = False
        while(validado == False):
            try:
                jogador = int(input("Sua vez (escolha uma posição de 1-9): ")) 
                if(jogador > 9 or jogador < 1):
                    print("O valor deve ser entre 1 e 9.")
                    validado = False
                else:
                    sair_loop = False
                    for i in range(3):
                        for j in range(3):
                            if(tabuleiro[i][j] == jogador):  
                                tabuleiro[i][j] = carac_jog
                                validado = True
                                sair_loop = True
                                break
                        if(sair_loop == True):
                            break
                    if(sair_loop == False):
                        print("Essa posição já está ocupada. Escolha outra.")
                        validado = False
                                
            except ValueError:
                print("Isso não é um número, digite novamente.")

        exibeTabuleiro(tabuleiro)
        verificando = verificaEstado(tabuleiro, carac_jog)
        if verificando != 0:
            printa(verificando)
            break
        
        print("Minha vez")

        #Vez da máquina
        if(carac_jog == 'X'):
            carac_maquina = 'O'
        else:
            carac_maquina = 'X'
        
        vezMaquina(carac_maquina, tabuleiro)
        exibeTabuleiro(tabuleiro)
        verificando = verificaEstado(tabuleiro, carac_jog)
        if verificando != 0:
            printa(verificando)
            break                              
        


def menu():
    while(True):
        validado = False
        print("JOGO DA VELHA")    
        print("Escolha uma ação:\n1.Ver posições\n2.Iniciar jogo\n3.Sair")
        try:
            opcao = int(input())

            if(opcao > 3 or opcao < 1):
                print("Escolha entre 1 e 3.\n")
            else:
                print("Opção selecionada:%i" %opcao)
                if (opcao == 1):
                    mostraPosicoes()
                elif (opcao == 2):  
                    while(validado == False):                  
                        carac_jog = input("Escolha X ou O: ")
                        
                        if(carac_jog == 'X' or carac_jog == 'O'):
                            validado = True
                        else:
                            print("Deve-se escolher X ou O.\n")                            

                    jogo(carac_jog)
                else:
                    break
        except ValueError:
            print("Isso não é um número, digite novamente.\n")

menu()

