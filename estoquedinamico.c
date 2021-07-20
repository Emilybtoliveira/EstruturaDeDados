#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void posicionaElemento(No *inicio_procura, No *posElem, char validadeElem[], int idElem){
    No *auxiliar;
    No *provisorio;
    int compara;
    char validadeAtual[5];

    auxiliar = inicio_procura;
    
    while(auxiliar->produto.id == idElem){         
        strcpy(validadeAtual, auxiliar->produto.validade);

        compara = strcmp(&validadeAtual[3], &validadeElem[3]); //compara o primeiro digito do ano
               
        if(compara > 0){ //validadeatual é maior, logo validadeelem deve vir antes dele
            continue;
        }
        else if(compara < 0){
            provisorio = auxiliar->prox;
            auxiliar->prox = posElem;
            posElem->prox = provisorio;
            return;            
        }
        
        auxiliar = auxiliar->prox;
    }
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
        return 1;
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
                                                //lembrar de liberar espaços dos nós provisorios
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

No *procuraEspecifico(ListaInicio *lista, int elemento, int flip){ 
    /*o valor elemento é sempre o ID do elemento procurado*/
    /* flip = 0 é a operação de remover;
       flip = 1 é procurar a posição de um elemento*/

    int qtd, falta = 0;
    No *auxiliar;
    No *ultimo = 0;
    auxiliar = lista->inicio;       

    while(auxiliar != NULL){                
        if(auxiliar->produto.id == elemento){
            if(flip == 0){
                return auxiliar; 
            }       
            else{ 
                if(falta == 0){
                    printf("Digite a quantidade a ser retirada: ");
                    scanf("%d", &qtd);
                } 
                if((auxiliar->produto.qtd - qtd) > 0){
                    auxiliar->produto.qtd -= qtd;
                    return 0;
                }
                else{
                    if((auxiliar->produto.qtd - qtd) < 0){
                        qtd -= auxiliar->produto.qtd;
                        falta = 1;
                    }                    

                    if(ultimo != 0){
                        ultimo->prox = auxiliar->prox;
                    }
                    else{
                        lista->inicio = auxiliar->prox;
                    }

                    if((auxiliar->produto.qtd - qtd) == 0){
                        return 0; 
                    }                    
                }

            }                     
        }
        ultimo = auxiliar;
        auxiliar = auxiliar->prox;
    }

    if(flip == 1){
        if(qtd > 0){
            printf("Nao existe estoque suficiente para retirar, falta(ram) %d unidade(s).\n", qtd);
        }
        else{
            printf("Sucesso na retirada dos produtos.\n");
        }   
    }
    else{
        return 0;
    }    
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

void iniciaLista(ListaInicio *lista){
    lista->inicio = NULL;
}

void cadastraNovoProduto(ListaInicio *lista){
    printf("\nCADASTRO DE NOVO PRODUTO\n");
    int verificado = 0;
    char data[6];
    char codigo[50];
    char quantidade[6];

    No *novoNo;
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
        gets(codigo);        

        verificado = validaNumeros(codigo);
        
        if (verificado == 0){
            printf("O codigo deve conter apenas numeros.\n");
        }        

        limpa();  
    }
    
    novoProduto.id = verificado;
    verificado = 0;

    No *resposta = procuraEspecifico(lista, novoProduto.id, 0);

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
        //scanf("%c", data);
        gets(data);
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
        gets(quantidade);        

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
            posicionaElemento(resposta, novoNo, novoProduto.validade, novoProduto.id);            
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
                    printf("\nDigite o codigo do produto que quer retirar: ");   
                    scanf("%d", &codigo);  
                    procuraEspecifico(estoque, codigo, 1); 
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