#include <stdio.h>

int verificaInicio(char nome[]){
    int primeiro_carac = nome[0];

    if(primeiro_carac >= 65 && primeiro_carac <=90){
        return 1;
    }
    else{
        if(primeiro_carac == 10 || primeiro_carac == 0 ){
           printf("Nome inválido. Não pode ser vazio.\n"); 
        }
        else{
            printf("Nome inválido. Deve iniciar com letra maiúscula.\n");
        }       
        return 0; 
    }
}

int verificaIntegridade(char nome[]){
    int i, novo_inicio = 0;

    for (i = 1; nome[i] != '\0'; i++){
        if(novo_inicio == 1){
            if(nome[i]< 65 || nome[i] > 90){
                printf("O inicio de cada nome deve começar com letra maiúscula.\n");
                return 0;
            }
            novo_inicio = 0;
        }
        else if(nome[i]< 97 || nome[i] > 122){
            if(nome[i] == ' '){
                novo_inicio = 1;
            }   
            else{
                printf("O nome deve conter apenas letras minusculas (com exceção da primeira letra de cada nome).\n");
                return 0;                
            }         
        }
    }

    return 1;
}

void esvazia(char nome[]){
    int i = 0;

    while(nome[i] != '\0'){
        nome[i] = '\0';
        i += 1;
    }
    
    return;
}


int main(){
    char nome[50];
    int validado = 0;   

    while(validado == 0){
        printf("Digite um nome: ");
        gets(nome);
        //printf("%d\n", nome[0]);

        validado = verificaInicio(nome);
        
        if(validado == 1){
            validado = verificaIntegridade(nome);

            if(validado == 1){
                printf("Nome válido.\n");
                break;
            }  
        }
        
        esvazia(nome);               
    }
    
    return 0;
}