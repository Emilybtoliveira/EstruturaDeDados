""" One possible improvement for Bubble Sort would be to add a flag variable
and a test that determines if an exchange was made during the current iteration. 
If no exchange was made, then the list is sorted and so the algorithm can stop early. 
This makes the best case performance become O(n) (because if the list is already sorted, 
then no iterations will take place on the first pass, and the sort will stop right there).
Modify the Bubble Sort implementation to add this flag and test. Compare the modified 
implementation on a range of inputs to determine if it does or does not improve performance 
in practice. """

def bubbleSortWFlag(array, size):
    print("\n->Ordenando o array usando uma flag\n")
    loops = 0
    for i in range(0,  (size-1)):
        flag = 0

        for j in range(0, (size-1)):
            print("\t{}".format(array))

            if array[j] > array[j +1]:
                aux = array[j]
                array[j] = array[j+1]
                array[j+1] = aux
                flag += 1            
            
            loops += 1       
        
        if not flag:
            print("\n  Ordenação completa após {} loops".format(loops))
            return
        
    print("\n  Ordenação completa após {} loops".format(loops))

def bubbleSort(array, size):
    print("\n->Ordenando o array sem usar flag\n")
    loops = 0
    for i in range(0,  (size-1)):
        for j in range(0, (size-1)):
            print("\t{}".format(array))
            if array[j] > array[j +1]:
                aux = array[j]
                array[j] = array[j+1]
                array[j+1] = aux
            loops += 1
        
        
    print("\n  Ordenação completa após {} loops".format(loops))

def setArray():
    print("Forneça um array no formato: \n \t[x, y, z, ...]")
    str_arr = input()
    array = []

    numero = ''

    for i in str_arr:
        if (i >= '0' and i <= '9'):
            numero += i
        if (i == ',' or i ==']'):  
            array.append(int(numero)) 
            numero = ''
    while(True):
        confirma = input("Esse foi o array fornecido => {}. Deseja confirmar? S/N ".format(array))

        if confirma == 'N' or confirma == 'n':
            return setArray()
        elif confirma == 'S' or confirma == 's':
            array_copy = array.copy()
            bubbleSortWFlag(array, len(array))        
            bubbleSort(array_copy, len(array_copy))
            break
    

setArray()