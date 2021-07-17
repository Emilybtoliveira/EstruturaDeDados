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

int menu(){
    char opcao;

    limpa();

    printf("\nSISTEMA DE ESTOQUE\n");
           
    printf("\nOperações:\n1  Listar estoque\n2  Cadastrar produto novo\n3  Adicionar remessa de produto\n4  Remover produto\n5  Consultar produto\n6  Encerrar\n\n");
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

    printf("Digite o nome do produto: ");
    gets(novoProduto.nome);

    limpa();

    printf("Digite a marca do produto: ");
    gets(novoProduto.marca);

    limpa();    

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

    printf("Cadastrado com sucesso.\n");
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

void procura(ListaInicio *lista){
    No *auxiliar;
    char opcao;
    printf("Digite a opção pelo elemento que deseja procurar:\n");
    printf("1 Por codigo\n2 Por nome\n");
    scanf("%c", &opcao);

    if(lista->inicio == NULL){
        printf("A lista está vazia.");
        return;
    }    
    else{
        if(opcao == 49){
            int codigo;
            printf("Digite o código do produto procurado: ");
            scanf("%d", &codigo);

        }
        else if(opcao == 50){
            limpa();     

            char nome[50];
            printf("Digite o nome do produto procurado: ");
            gets(nome);

            limpa();     
        }
        else{
            printf("Opção invalida\n");
            return procura(lista);
        }       
    }
    
}

void main(){
    int operacao, loop = 1;
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
                //remessa de produto
                break;

            case 4:
                //retirar produto
                break;

            case 5:
                //consultar produto
                break;

            default:
                return;
        }
    }
    
}