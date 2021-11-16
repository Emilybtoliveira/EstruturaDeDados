#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define HASHTABLE_LENGTH 1000

void pause(void){
	printf("\nPressione Enter para continuar... ");
	char pause[300];
	fgets(pause, 300, stdin);
}

void clearStdin(void){
    fflush(stdin);
}


/* COMEÇO DA DLL */
struct Data{
	char key[250];
	char name[200];
	char address[400];
};

struct Node{
	struct Node* next;
	struct Node* prev;
	struct Data* data;
};

struct List{
	struct Node* head;
	struct Node* tail;
	int length;
};

//Add element to the end of the list
int append(struct List** list, struct Data* new_data){
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = new_data;

    node->next = NULL;

	if ((*list)->length == 0) {
        (*list)->tail = node;
        (*list)->head = node;
		(*list)->length = 1;
        return (*list)->length;
    }

	(*list)->tail->next = node;
    node->prev = (*list)->tail;
	(*list)->tail = node;

	(*list)->length = (*list)->length + 1;
    return (*list)->length;
}

//Get element on the position p
struct Data* getIndex(struct List** list, int p){
	int len = (*list)->length;

	int n = 0;

	struct Node* node;
	if((len/2) > p){ /*começar de head*/
		int i = 0;
		node = (*list)->head;
		while (i < p) {
			node = node->next;
			i++;
			n++;
		}
	} else { /*começar de tail*/
		int i = len-1;
		node = (*list)->tail;
		while (i > p) {
			node = node->prev;
			i--;
			n++;
		}	
	}

	return node->data;
}

struct Data* deleteByKey(struct List** list, char* key){
	int len = (*list)->length;
	struct Node* node;

	int i = 0;

	node = (*list)->head;
	char* nodeKey;
	while (node != NULL) {
		nodeKey = node->data->key;
		if(!strcmp(key,nodeKey)){
			break;
		}
		node = node->next;
		i++;
	}

	if(node != NULL && !strcmp(key,nodeKey)){
		//nó correto
		if(node->prev != NULL){
			(node->prev)->next = node->next;
		}
		if(NULL != node->next){
			(node->next)->prev = node->prev;
		}
		
		if(i == 0){
			(*list)->head = node->next;
		}

		if(i == len-1){
			(*list)->tail = node->prev;
		}

		struct Data* data = (struct Data*) malloc(sizeof(struct Data));
		(*list)->length = (*list)->length - 1;
		memcpy(data, &(node->data), sizeof(struct Data));
		free(node);
		return data;
	} 
	
	return NULL;
}
/* FIM DA DLL */


/* COMEÇO DA HASH */
int generateHash(char *str){
	long hash = 5381;
	int c;

	while ((c = *str++)){
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return (((hash % HASHTABLE_LENGTH) + HASHTABLE_LENGTH) % HASHTABLE_LENGTH);
}

bool insertAgainMenu(void){
	system("clear");
	printf("ID já existente, deseja alterar dados?\n(S) ou (N): ");
	char opcao[200];
	fgets(opcao, 200, stdin);
	opcao[strcspn(opcao, "\n")] = 0;
	//S -> 115, 83
	//N -> 110, 78
	if(strlen(opcao) == 1){
		if(opcao[0] == 115 || opcao[0] == 83){
			system("clear");
			return 1;

		} else if (opcao[0] == 110 || opcao[0] == 78){
			system("clear");
			return 0;
		}
	}

	system("clear");
	printf("Opção \"%s\" é invalida\n", opcao);
	pause();
	return insertAgainMenu();
}

int insert(struct Data** data, struct List* HashTable [HASHTABLE_LENGTH]){
	int hash = generateHash((*data)->key);
	struct List* list = (struct List*) HashTable[hash];

	struct Node* node = list->head;
	while (node != NULL) {
		if(!strcmp((*data)->key,node->data->key)){
			if(insertAgainMenu()){
				node->data = *data;
				return list->length;
			} else {
				return -1;
			}
		}
		node = node->next;
	}

	int len = append((struct List**) &HashTable[hash], (*data));
	return len;
}

struct Data* get(char* key, struct List* HashTable[HASHTABLE_LENGTH]){
	int hash = generateHash(key);
	struct List* list = (struct List*) HashTable[hash];

	struct Node* node = list->head;
	char* nodeKey;
	while (node != NULL) {
		nodeKey = node->data->key;
		if(!strcmp(key,nodeKey)){
			break;
		}
		node = node->next;
	}

	if(node != NULL && !strcmp(key,nodeKey)){
		return node->data;
	} else {
		return NULL;
	}
}

struct Data* del(char* key, struct List* HashTable[HASHTABLE_LENGTH]){
	int hash = generateHash(key);
	struct List* list = (struct List*) HashTable[hash];

	return deleteByKey(&list,key);
}


/* FIM DA HASH */

/* COMEÇO DE IMPRESSÃO NA TELA */
void printListKeys(struct Node* head){
	struct Node* node = head;
	if(node != NULL){
		printf("%s", node->data->key);
    	node = node->next;
	}
    while (node != NULL) {
        printf(", %s", node->data->key);
		node = node->next;
    }
}

void printData(struct Data* data){
	if(data != NULL){
		printf("{\"%s\":\n	Nome    : \"%s\",\n 	Endereço: \"%s\"\n}\n", data->key, data->name, data->address);
	} else {
		printf("{NULL}\n Não há dados relacionados a chave informada.");
		printf("\n");
	}
}

void printByName(char* name, struct List* HashTable[HASHTABLE_LENGTH]){
	int i = 0;

	for (i = 0; i < HASHTABLE_LENGTH; i++){
		struct List* list = (struct List*) HashTable[i];
		if(list->length > 0){
			struct Node* node = list->head;
			char* nodeName;
			while (node != NULL) {
				nodeName = node->data->name;
				if(!strcmp(name,nodeName)){
					printData(node->data);
					printf("\n");
				}
				node = node->next;
			}

		}
	}
}
/* FIM DE IMPRESSÃO NA TELA */

bool deleteAllMenu(bool isAll){
	system("clear");
	printf("Remover %selementos da lista é uma ação irreversível.\n", (isAll) ? "todos os " : "");
	printf("TEM CERTEZA QUE DESEJA PROSSEGUIR?\n(S) ou (N): ");
	char opcao[200];
	fgets(opcao, 200, stdin);
	opcao[strcspn(opcao, "\n")] = 0;
	//S -> 115, 83
	//N -> 110, 78
	if(strlen(opcao) == 1){
		if(opcao[0] == 115 || opcao[0] == 83){
			system("clear");
			return 1;

		} else if (opcao[0] == 110 || opcao[0] == 78){
			system("clear");
			return 0;
		}
	}

	system("clear");
	printf("Opção \"%s\" é invalida\n", opcao);
	pause();
	return deleteAllMenu(isAll);
}

int menu(){
	char opcao[200];
	system("clear");

	clearStdin();

  	printf("Dicionário - Folha de Pagamento\n");
	printf("	1 - Cadastrar/Alterar funcionário\n");
	printf("	2 - Consultar por ID\n");
	printf("	3 - Consultar por Nome\n");
	printf("	4 - Remover por ID\n");
	printf("	5 - Remover todos\n");
	printf("	6 - Imprimir chaves\n");
	printf("	0 - Finalizar\n");
  	printf("\nDigite a opção desejada: ");
  	fgets(opcao, 200, stdin);
	opcao[strcspn(opcao, "\n")] = 0;

    clearStdin();
    
    if(strlen(opcao) == 1 && opcao[0] >= 48 && opcao[0] <= 54){
		system("clear");
        return (opcao[0]-48);
    } else{
		system("clear");
        printf("Opção \"%s\" é invalida\n\n", opcao);
		pause();
        return menu();
    }
}

int main(void) {
	struct Data* data;
	struct List* HashTable[HASHTABLE_LENGTH];
    int i;
    
	for (i = 0; i < HASHTABLE_LENGTH; i++){
		struct List* newList = (struct List*) malloc(sizeof(struct List));
		newList->length = 0;
		newList->head = NULL;
		newList->tail = NULL;
		HashTable[i] = newList;
	}

	int action = menu();
    while(action != 0){
        /*Cadastra*/
		if(action == 1){
			char id[250+1], name[200+1], address[400+1];
			data = (struct Data*) malloc(sizeof(struct Data));

			printf("Digite o ID dx funcionárix: ");
			fgets(id, 250, stdin);
			id[strcspn(id, "\n")] = 0;

			printf("Digite o nome dx funcionárix: ");
			fgets(name, 200, stdin);
			name[strcspn(name, "\n")] = 0;

			printf("Digite o endereço dx funcionárix: ");
			fgets(address, 400, stdin);
			address[strcspn(address, "\n")] = 0;

			strcpy(data->key, id);
			strcpy(data->name, name);
			strcpy(data->address, address);

			int len = insert(&data, HashTable);

			if(len >= 0){
            	printf("\nCadastrado com sucesso.\n");
			} else {
				printf("\nNão foram feitas alterações.\n");
			}
			pause();
		}
		
        /*Procura ID*/
		if(action == 2){
			char id[250+1];
			printf("Informe o ID dx funcionárix: ");
			fgets(id, 250, stdin);
			id[strcspn(id, "\n")] = 0;

			struct Data* data = get(id, HashTable);

			system("clear");
			printData(data);
			pause();
		}

		/*Procura Nome*/
		if(action == 3){
			char name[250+1];
			printf("Informe o Nome (exato) dx funcionárix: ");
			fgets(name, 250, stdin);
			name[strcspn(name, "\n")] = 0;

			system("clear");
			printByName(name, HashTable);
			pause();
		}

        /*Remove ID*/
		if(action == 4){
			char id[250+1];
			printf("Informe o ID dx funcionárix: ");
			fgets(id, 250, stdin);
			id[strcspn(id, "\n")] = 0;

			system("clear");
			if(deleteAllMenu(false)){
				struct Data* data = del(id, HashTable);
				printf("Removido com sucesso.\n");
			} else {
				printf("\nNão foram feitas alterações.\n");
			}

			pause();
		}

		/*Remove todos*/
        if(action == 5){
			system("clear");
			if(deleteAllMenu(false)){
            	int i;
				for (i = 0; i < HASHTABLE_LENGTH; i++){
					struct List* list = (struct List*) HashTable[i];
					if(list->length > 0){
						struct Node* node = list->head;
						while (node->next != NULL) {
							node = node->next;
							free(node->prev->data);
							free(node->prev);
						}
						free(node->data);
						free(node);

						list->length = 0;
						list->head = NULL;
						list->tail = NULL;
					}
				}
				printf("Removido(s) com sucesso.\n");
			} else {
				printf("\nNão foram feitas alterações.\n");
			}

			pause();
        }

        /*Lista chaves*/
        if(action == 6){
            bool hasPrinted = false;
            int i;
			printf("[");
			for (i = 0; i < HASHTABLE_LENGTH; i++){
				struct List* list = (struct List*) HashTable[i];
				if(list->length > 0){
					hasPrinted = true;
					printListKeys(list->head);
					printf(", ");
				}
			}

			printf("%s]\n", (hasPrinted) ? "\b\b" : " ");
			
			pause();
        }

		action = menu();
	}
	printf("---> Execução Finalizada <---");
}