#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char nome[50];
    char marca[30];
    int validade;
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
                                                //lembrar de liberar espaços dos nós provisorios
void procura(ListaInicio *lista){    
    No *auxiliar;
    char opcao;    

    if(lista->inicio == NULL){
        printf("O estoque está vazio, cadastre algo antes de consultar.\n");
        return;
    }        
    else{
        int encontrou = 0;
        limpa();
        printf("\nDigite a opção pelo elemento que deseja procurar:\n");
        printf("1 Por codigo\n2 Por nome\n");
        scanf("%c", &opcao);

        if(opcao == 49){
            int codigo;
            printf("Digite o código do produto procurado: ");
            scanf("%d", &codigo);

            auxiliar = lista->inicio;
            while(auxiliar != NULL){                
                if(auxiliar->produto.id == codigo){   
                    if(encontrou == 0){
                        printf("Isso foi o que encontramos:\n");
                        encontrou = 1;
                    }
                    
                    printf("%d %s %s %d %d\n", auxiliar->produto.id, auxiliar->produto.nome, 
                                            auxiliar->produto.marca, auxiliar->produto.validade, auxiliar->produto.qtd);                   
                }
                auxiliar = auxiliar->prox;
            }
            if(encontrou == 0){
                printf("O produto solicitado não existe.\n");
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
                    printf("  %d %s %s %d %d\n", auxiliar->produto.id, auxiliar->produto.nome, 
                                            auxiliar->produto.marca, auxiliar->produto.validade, auxiliar->produto.qtd);
                }
                auxiliar = auxiliar->prox;
            } 
            if(encontrou == 0){
                printf("O produto solicitado não existe.\n");
            }
        }
        else{
            printf("Opção invalida\n");
            return procura(lista);
        }       
    }
    
}

No *procuraEspecifico(ListaInicio *lista, int elemento, int flip){ //elemento é sempre o ID
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
            printf("Não existe estoque suficiente para retirar, falta(ram) %d unidade(s).\n", qtd);
        }
        else{
            printf("Sucesso na retirada dos produtos.\n");
        }   
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
    No *novoNo;
    Produto novoProduto;
    novoNo = malloc(sizeof(No));

    if(novoNo == NULL){
        printf("Não eh possível cadastrar.\n");
        return;
    }
                                    
    //fazer tratamento de erro
    
    printf("Digite o código do produto: "); 
    scanf("%d", &novoProduto.id);
    limpa();

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

    printf("Digite a validade do produto (diamesano, sem espaços ou caracteres): ");
    scanf("%d", &novoProduto.validade);

    printf("Digite a quantidade de unidades do produto: ");
    scanf("%d", &novoProduto.qtd);

    //printf("%d %s %s %d %d\n", novoProduto.id, novoProduto.nome, novoProduto.marca, novoProduto.validade, novoProduto.qtd);
    
    novoNo->produto = novoProduto;
    
    if(lista->inicio == NULL){
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
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
        printf("\nCódigo\tNome\tMarca\tValidade\tQuantidade disponível\n");
        for(atual = lista->inicio; atual != NULL; atual = atual->prox){
            printf("%d\t%s\t%s\t%d\t%d\n",atual->produto.id, atual->produto.nome, atual->produto.marca, atual->produto.validade, atual->produto.qtd);
        }
        return;
    }   

}


void main(){
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
                    printf("O estoque está vazio, cadastre algo antes de consultar.\n");
                    break;
                }
                else{
                    printf("\nDigite o código do produto que quer retirar: ");   
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
                    return;
                }   
        }
    }
    
}