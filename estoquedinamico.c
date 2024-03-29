#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ANO_ATUAL 21

typedef struct{
    int id;
    char nome[50];
    char marca[30];
    char validade[5];
    int qtd;
}Produto;

typedef struct no{
    Produto produto;
    struct no *prox;
}No;

typedef struct{
    No *inicio;
}ListaInicio;

void limpa(){
    fflush(stdin);
    __fpurge(stdin);
}

int validaData(char data[]){
    int i;
    for(i = 0; data[i] != '\0'; i++){
        if(data[i] < 47 || data[i] > 57){
            return 0;
        }
    }    
    if(i != 5){
        return 0;
    }
    else{
        int mes = (data[0]-48)*10 + (data[1]-48);
        int ano = (data[3]-48)*10 + (data[4]-48);

        if(mes >= 1 && mes <= 12){
            if(ano >= ANO_ATUAL){
                return 1;
            }
            else{
                printf("Esse ano já passou. ");
                return 0;
            }            
        }
        else{
            printf("Esse mês não existe. ");
            return 0;
        }        
    }
}

int validaNumeros(char valor[]){
    int i, convert_int = 0, tam = 0;

    for(i = 0; valor[i] != '\0'; i++){
        if(valor[i] < 48 || valor[i] > 57){
            return 0;
        }
        tam += 1;
    }

    tam -= 1;

    for(i = 0; valor[i] != '\0'; i++){

        convert_int += (valor[i]-48) * pow(10, tam);

        tam -= 1;
    }

    return convert_int;
}

void determinaPosicao(ListaInicio *lista, No *aInserir){
    int mes_val_aux, ano_val_aux, mes_val_ainserir, ano_val_ainserir;
    No *auxiliar  = lista->inicio;
    No *ultimoNo = 0;

    while(auxiliar != NULL){
        if(auxiliar->produto.id == aInserir->produto.id){
            
            while(auxiliar != NULL && auxiliar->produto.id == aInserir->produto.id){
                /* mes/ano_val_aux é a validade do nó auxiliar convertida para int*/
                mes_val_aux = (auxiliar->produto.validade[0] - 48)*10 + (auxiliar->produto.validade[1] - 48);
                ano_val_aux = (auxiliar->produto.validade[3] - 48)*10 + (auxiliar->produto.validade[4] - 48);
                /* mes/ano_val_ainserir é a validade do nó a inserir na lista convertida para int*/
                mes_val_ainserir = (aInserir->produto.validade[0] - 48)*10 + (aInserir->produto.validade[1] - 48);
                ano_val_ainserir = (aInserir->produto.validade[3] - 48)*10 + (aInserir->produto.validade[4] - 48);

                if(ano_val_aux < ano_val_ainserir){
                    /* o nó a ser inserido tem uma validade maior(pelo ano), logo deve vir abaixo do nó q ja esta na lista */
                    if(ultimoNo != 0){
                        ultimoNo->prox = auxiliar;
                    }
                    
                    aInserir->prox = auxiliar->prox;
                    auxiliar->prox = aInserir;

                    ultimoNo = auxiliar;
                    auxiliar = aInserir->prox;  
                }
                else if(ano_val_aux > ano_val_ainserir){
                    /* o nó a ser inserido tem uma validade menor(pelo ano), logo deve vir acima do nó q ja esta na lista */
                    if(ultimoNo == 0){
                        lista->inicio = aInserir;
                        aInserir->prox = auxiliar;
                    }
                    else{
                        ultimoNo->prox = aInserir; 
                        aInserir->prox = auxiliar;                        
                    }  
                    return;                                     
                }
                else{
                    /* anos iguais, deve se comparar o mes */
                    if(mes_val_aux < mes_val_ainserir){
                        /* o nó a ser inserido tem uma validade maior(pelo mes), logo deve vir abaixo do nó q ja esta na lista */
                        if(ultimoNo != 0){
                            ultimoNo->prox = auxiliar;
                        }
                        
                        aInserir->prox = auxiliar->prox;
                        auxiliar->prox = aInserir;

                        ultimoNo = auxiliar;
                        auxiliar = aInserir->prox;  
                    }
                    else if(mes_val_aux > mes_val_ainserir){
                        /* o nó a ser inserido tem uma validade menor(pelo mes), logo deve vir acima do nó q ja esta na lista */
                        if(ultimoNo == 0){
                            lista->inicio = aInserir;
                            aInserir->prox = auxiliar;
                        }
                        else{
                            ultimoNo->prox = aInserir; 
                            aInserir->prox = auxiliar;                        
                        }
                        return;
                    }
                    else{
                        if(ultimoNo != 0){
                            ultimoNo->prox = auxiliar;
                        }
                        
                        aInserir->prox = auxiliar->prox;
                        auxiliar->prox = aInserir;

                        ultimoNo = auxiliar;
                        auxiliar = aInserir->prox;
                    }
                    
                }
                              
            }

            return;            
        }

        ultimoNo = auxiliar;
        auxiliar = auxiliar->prox;
    }

}

void procura(ListaInicio *lista){    
    No *auxiliar;
    char opcao;    

    if(lista->inicio == NULL){
        printf("O estoque esta vazio, cadastre algo antes de consultar.\n");
        return;
    }        
    else{
        int encontrou = 0;
        limpa();
        printf("\nDigite a opcao pelo elemento que deseja procurar:\n");
        printf("1 Por codigo\n2 Por nome\n");
        scanf("%c", &opcao);

        if(opcao == 49){
            int codigo;
            printf("Digite o codigo do produto procurado: ");
            scanf("%d", &codigo);

            auxiliar = lista->inicio;
            while(auxiliar != NULL){                
                if(auxiliar->produto.id == codigo){   
                    if(encontrou == 0){
                        printf("Isso foi o que encontramos:\n");
                        encontrou = 1;
                    }
                    
                    printf("%d %s %s %s %d\n", auxiliar->produto.id, auxiliar->produto.nome, 
                                            auxiliar->produto.marca, auxiliar->produto.validade, auxiliar->produto.qtd);                   
                }
                auxiliar = auxiliar->prox;
            }
            if(encontrou == 0){
                printf("O produto solicitado nao existe.\n");
            }                    
        }
        else if(opcao == 50){                
            int compara;
            char nome[50];
            limpa();
            printf("Digite o nome do produto procurado: ");
            gets(nome);
            limpa();   

            auxiliar = lista->inicio;
            while(auxiliar != NULL){      
                compara = strcmp(auxiliar->produto.nome, nome);        
                if(compara == 0){
                    if(encontrou == 0){
                        printf("Isso foi o que encontramos:\n");
                        encontrou = 1; 
                    }                                   
                    printf("  %d %s %s %s %d\n", auxiliar->produto.id, auxiliar->produto.nome, 
                                            auxiliar->produto.marca, auxiliar->produto.validade, auxiliar->produto.qtd);
                }
                auxiliar = auxiliar->prox;
            } 
            if(encontrou == 0){
                printf("O produto solicitado nao existe.\n");
            }
        }
        else{
            printf("Opcao invalida\n");
            return procura(lista);
        }     
    }    
}

void retiraQtd(ListaInicio *lista){
    int qtd, id;
    No *auxiliar;
    No *ultimo = 0;

    auxiliar = lista->inicio;

    printf("\nDigite o codigo do produto que quer retirar: ");   
    scanf("%d", &id);
    

    while(auxiliar != NULL){ 
        if(auxiliar->produto.id == id){

          printf("Digite a quantidade a ser retirada: ");
          scanf("%d", &qtd);

            while((auxiliar->produto.id == id)&&(qtd != 0)){                     
                if((auxiliar->produto.qtd - qtd) > 0){
                    auxiliar->produto.qtd -= qtd;
                    qtd = 0;
                }                
                else{
                    
                    if((auxiliar->produto.qtd - qtd) < 0){
                        qtd -= auxiliar->produto.qtd;                            
                    }  

                    else if((auxiliar->produto.qtd - qtd) == 0){
                        qtd = 0;
                    }
                    /* Nos dois casos, é preciso excluir o elemento, visto que a sua quantidade se torna 0 */
                    if(ultimo != 0){
                        ultimo->prox = auxiliar->prox;
                        auxiliar = ultimo->prox;
                    }
                    else{
                        lista->inicio = auxiliar->prox; 
                        ultimo = lista->inicio;
                        auxiliar = auxiliar->prox;

                        if(auxiliar == NULL){
                            break;
                        }
                    }                        
                                        
                }  
            }

            if(qtd > 0){
                printf("Nao existe estoque suficiente para retirar, falta(ram) %d unidade(s).\n", qtd);
            }
            else{
                printf("Sucesso na retirada dos produtos.\n");
            }

            return;
        }        
        
        ultimo = auxiliar;
        auxiliar = auxiliar->prox;
    }   

    printf("Esse código não existe.\n"); 
    return retiraQtd(lista);
}

No *procuraEspecifico(ListaInicio *lista, int id){ 
    No *auxiliar;
    auxiliar = lista->inicio;       

    while(auxiliar != NULL){                
        if(auxiliar->produto.id == id){            
            return auxiliar;                                 
        }
        auxiliar = auxiliar->prox;
    } 
    return 0;  
}


void cadastraNovoProduto(ListaInicio *lista){
    printf("\nCADASTRO DE NOVO PRODUTO\n");
    int verificado = 0;
    char data[6];
    char codigo[50];
    char quantidade[6];

    No *novoNo;
    No *resposta;
    Produto novoProduto;
    novoNo = malloc(sizeof(No));

    if(novoNo == NULL){
        printf("Nao eh possivel cadastrar.\n");
        return;
    }
                                    
    //fazer tratamento de erro
    while(verificado == 0){
        limpa();
        printf("Digite o codigo do produto: "); 
        //gets(codigo);        
        scanf(" %s", codigo);
        verificado = validaNumeros(codigo);
        
        if (verificado == 0){
            printf("O codigo deve conter apenas numeros.\n");
        }        

        limpa();  
    }
    
    novoProduto.id = verificado;
    verificado = 0;

    resposta = procuraEspecifico(lista, novoProduto.id);

    if(resposta != 0){ //verificar se ja nao eh um codigo cadastrado
        strcpy(novoProduto.nome, resposta->produto.nome);
        strcpy(novoProduto.marca, resposta->produto.marca);
    }
    else{        
        printf("Digite o nome do produto: ");
        gets(novoProduto.nome);
        limpa();

        printf("Digite a marca do produto: ");
        gets(novoProduto.marca);
        limpa();  
    }  

    while(verificado == 0){
        printf("Digite a validade do produto (mes/ano, ex: 03/23): ");
        scanf(" %s", data);
        //gets(data);
        limpa();

        if(validaData(data) == 1){
            verificado = 1;
            strcpy(novoProduto.validade, data);           
        }
        else{
            printf("Data invalida.\n");
        }        
    }
    
    verificado = 0;

    while(verificado == 0){        
        printf("Digite a quantidade de unidades do produto: "); 
        scanf(" %s", quantidade);
        //gets(quantidade);        

        verificado = validaNumeros(quantidade);
        
        if (verificado == 0){
            printf("Isso nao eh um numero.\n");
        }

        limpa();  
    }    
    novoProduto.qtd = verificado;

    novoNo->produto = novoProduto;    
    if(lista->inicio == NULL){
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
    }
    else{
        if(resposta != 0){
            determinaPosicao(lista, novoNo);
        }
        else{
            No *auxiliar;
            auxiliar = lista->inicio;
            
            while(auxiliar->prox != NULL){        
                auxiliar = auxiliar->prox;
            }

            novoNo->prox = auxiliar->prox;
            auxiliar->prox = novoNo;

        }        
               
    }

    printf("Cadastrado com sucesso!\n");
    return;
}

void imprimeEstoque(ListaInicio *lista){
    No *atual;
    printf("\nESTOQUE ATUAL\n");
    if(lista->inicio == NULL){
        printf("Não ha estoque cadastrado.\n");
        return;
    }
    else{
        printf("\nCodigo\tNome\tMarca\tValidade\tQuantidade disponível\n");
        for(atual = lista->inicio; atual != NULL; atual = atual->prox){
            printf("%d\t%s\t%s\t%s\t%d\n",atual->produto.id, atual->produto.nome, atual->produto.marca, atual->produto.validade, atual->produto.qtd);
        }
        return;
    }   
}

void iniciaLista(ListaInicio *lista){
    lista->inicio = NULL;
}

int menu(){
    char opcao;

    limpa();

    printf("\nSISTEMA DE ESTOQUE\n");
           
    printf("\nOperações:\n1  Listar estoque\n2  Cadastrar produto novo\n3  Retirar produto\n4  Consultar produto\n5  Encerrar sistema\n\n");
    printf("Digite a opção desejada: ");
    scanf("%c", &opcao);

    limpa();
    
    if(opcao > 48 && opcao < 55){
        return (opcao-48);
    }
    else{
        printf("Opcao invalida\n\n");
        return menu();
    }    
    
}

int main(){
    int operacao, loop = 1, codigo;
    char yn;
    ListaInicio *estoque;
    estoque = malloc(sizeof(ListaInicio));
    iniciaLista(estoque);

    while (loop){
        operacao = menu();

        switch (operacao)
        {        
            case 1:
                //listar estoque
                imprimeEstoque(estoque);
                break;
            case 2:
                //novo produto
                cadastraNovoProduto(estoque);                
                break;
            
            case 3:
                //retirar produto
                if(estoque->inicio == NULL){
                    printf("O estoque esta vazio, cadastre algo antes de consultar.\n");
                    break;
                }
                else{
                  retiraQtd(estoque);
                }                         
                break;

            case 4:
                //consultar produto                
                procura(estoque); // nao retorna nada, apenas printa o valor encontrado
                break;

            default:
                printf("Deseja mesmo encerrar? y/n: ");
                scanf("%c", &yn);
                limpa();
                if(yn == 121 || yn == 89){
                    return 0;
                }   
        }
    }
    
}