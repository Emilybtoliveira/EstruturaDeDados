# Por:  - Emily Brito de Oliveira
#       - Felipe Ferreira Vasconcelos
#       - Taígo Ítalo de Moraes Pedrosa 
# Testado com Python 3.8.2 em Ubuntu (Repl.it)

import os

def debug(tree):
	pass

def addNodeOption(tree, fathers):
	if(len(tree.keys()) <= 1):
		os.system("clear")
		print("--------------- Adicionar Nó na Árvore ---------------")
		print("\033[1m\n     Como a árvore está vazia, este é o nó raiz.\n\033[0m")
		father = "root"
	else:
		flag = True
		while(flag):
			os.system("clear")
			print("--------------- Adicionar Nó na Árvore ---------------")
			father = input("Digite o id do nó pai: ")

			if(father in tree.keys()):
				flag = False
			else:
				os.system("clear")
				print("\033[91m\033[1mO id \"%s\" não existe.\033[0m" % (father))
				input("Pressione Enter para continuar...")
		
	flag = True
	while(flag):
		os.system("clear")
		print("--------------- Adicionar Nó na Árvore ---------------")
		print("Digite o id do nó pai:",father)
		node = input("Digite o id do novo nó: ")

		if(node not in tree.keys()):
			flag = False
		else:
			os.system("clear")
			print("\033[91m\033[1mO id \"%s\" já está na árvore.\033[0m" % (father))
			input("Pressione Enter para continuar...")
	
	tree[father].append(node)
	tree[node] = []
	fathers[node] = father
	input("\nPressione Enter para continuar...")

def removeNode(tree, node):
	children = tree[node]
	for child in children:
		removeNode(tree, child)
	del tree[node]

def removeNodeOption(tree, fathers):
	if(len(tree.keys()) <= 1):
		os.system("clear")
		print("---------------- Remover Nó da Árvore ----------------")
		print("\033[91m\033[1mA árvore está vazia.\033[0m")
		input("Pressione Enter para continuar...")
		return

	flag = True
	while(flag):
		os.system("clear")
		print("---------------- Remover Nó da Árvore ----------------")
		print("\033[91m\033[1m\n     ATENÇÃO, ESTA AÇÃO REMOVERÁ O NÓ ESCOLHIDO E\n     TODOS OS SEUS NÓS FILHOS. ESTA AÇÃO NÃO PODE-\n     RÁ SER DESFEITA.\033[0m\n")

		option = input("Digite o id do nó: ")

		if(option in tree.keys()):
			removeNode(tree, option)
			tree[fathers[option]].remove(option)
			flag = False
		else:
			#invalid option (did not return...)
			os.system("clear")
			print("\033[91m\033[1mO id \"%s\" não existe.\033[0m" % (option))
			input("Pressione Enter para continuar...")

	input("Pressione Enter para continuar...")

def traverse(tree, node):
	children = tree[node]
	for child in children:
		traverse(tree, child)
	print(node, end=", " if node != tree["root"][0] else ".\n")

def traverseOption(tree):
	os.system("clear")
	print("------------ Percurso Postordem da Árvore ------------\n")
	traverse(tree, tree["root"][0])
	input("\nPressione Enter para continuar...")
	
def menu():
	option = 0
	while(True):
		os.system("clear")
		print("------------- Postorder em Árvore N-aria -------------")
		print("    1 - Adicionar nó na árvore")
		print("    2 - Remover nó da árvore")
		print("    3 - Percorrer postorder")
		print("    0 - Finalizar Execução")
		option = input("\nDigite a opção desejada: ")
		
		try:
			option = int(option)
			if(option >= -1 and option <= 7):
				return option
		except:
			#invalid option (did not return...)
			os.system("clear")
			print("\033[91m\033[1mOpção \"%s\" é inválida.\033[0m" % (option))
			input("Pressione Enter para continuar...")

def main():
	tree = {}
	fathers = {}
	tree["root"] = []

	option = menu()	
	while(option):
		if(option == 1):
			addNodeOption(tree, fathers)
		elif(option == 2):
			removeNodeOption(tree, fathers)
		elif(option == 3):
			traverseOption(tree)
		option = menu()
	os.system("clear")
	print("----------------- Execução Finalizada ----------------")

main()

'''
Para a árvore:
	  a
	 / \
	b   c
   /|\	
  d e f

Ctrl+C, Ctrl+V:
1
a

1
a
b

1
a
c

1
b
d

1
b
e

1
b
f

3

'''


"""
debug

1
4

1
4
5

1
4
1

1
1
3

1
1
2

1
5
8

3
"""