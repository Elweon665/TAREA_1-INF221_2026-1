# Documentación

## Entrega

"Más allá de la notación asintótica: Análisis experimental de algoritmos de ordenamiento y multiplicación de matrices." Nombre: Vicente Carvajal Helqui Rol: 202273572-4

En esta entrega se estudia el comportamiento de los algoritmos tanto de ordenamiento de arreglos así como los que permiten multiplicar matrices.

Ejecucion del codigo: Dirijase a la carpeta de interes (aorting o matrix_multoplication) y dentro de ella escriba: "make run".

En caso de querer graficar, dirig¿jase a la carpeta "scripts" y ejecute plot_generator.py con Python 3.10 o posterior.

## Multiplicación de matrices

En esta entrega se consideran dos algoritmos de este tipo, los cuales son: Naive y Strassen.

Tal y como dice el documento de la entrega, son algoritmos conocidos y que han sido documentados en varias partes (Sobre todo en internet) Por lo que se implementaron y adaptaron implementaciones conocidas de ambos algoritmos

A continuacion, se documentaran el proposito de las funciones de cada codigo:

strassen.cpp:

valitadateDimensions: Verifica que las dimensiones de las matrices son cuadradas y por ende validas

validateMultiplication: Verifica que las matrices se puedan multiplicar

validateSquarePowerofTwo: Revisa que la matriz sea cuadrada

operator+: Realiza la operacion de suma cuando es necesaria

operator-: Realiza la operacion de resta cuando es necesaria

operator*: Realiza la operacion de multiplicacion de 2 valores

operator>>: Realiza la operacion de shiteo

toStringWithPresision: convierte el resultado de una multiplicacion a string para poder ser escrito en el texto que contiene el resultado de la multiplicacion de la matriz

params: Funcion que define parte de las reglas para dividir la matriz, es como un diccionario de coordenadas, un mapa.

fromQuaters: Funcion que realiza la division de las matrices en submatrices en bae a las reglas definidas por la funcion params

strassen: Funcion principal, encargado de realizar la multiplicacion mediante este algoritmo llamando a las funciones respectivas según el paso a realizar.

Funciones de naive.cpp:

naive: Funcion principal, este se encaarga de ejecutar el algoritmo como tal, sin mucha más ciencia.

### Programa principal

matrix_multiplication.cpp es el programa principal.

Funciones de matrix_multiplication.cpp:

writeMatrixToFile: Funcion que se encarga finalmente de escribir la matriz resultante en el archivo de salida

get_MemoryUsage: Se encarga de medir el uso de la memoria RAM durante la ejecucion de los archivos

Leer_Matriz: Lee las matrices de entrada y hace la conversion respectiva del .txt original para que se puueda realizar la multiplicacion de las matrices posteriormente.

realizar_mediciones: Realiza las mediciones respectivas de tiempo y memoria llamando a las funciones respectivas, además de mandar a ejecutar los algoritmos de multiplicacion de matrices, además de escribir el resultado de las mediciones en un archivo de texto llamado "resultados_generales.txt" dentro de la carpeta "measurements"

main: Funcion principal, encargado de recibir las matrices de entrada, verificarlas, y posteriormente mandar a ejecutar los algoritmos respectivos.

### Scripts

matrix_generator.py: Programa encargado de crear los archivos de entrada que quedan guardados en matrix_input.

plot_generator.py: Script encargador de tomar los datos escritos en "resultados_generales.txt" y genera los graficos que representan los resultados generales.

## Ordenamiento de arreglo unidimensional

Algoritmos: MergeSort, QuickSort, std::sort.

Al igual que en el caso de las matrices, estos algoritmos son conocidos y se ha decidido colocar implementaciones externas de estos mismos, a excepcion de sort.cpp donde este viene con el codigo ya escrito por defecto en esta entrega.

A continuacion, se documentaran el uso de las funciones de cada programa:

mergesort.cpp

merge: Esta funcion se encarga de realizar la division en sublistas de los arreglos, como lo popone parte del algoritmo

sort: Se encarga de forma recursiva de  ordenar el arreglo en base a las subdivisiones realizadas anteriormente

mergeSort: Funcion principal, se encarga de ejecuatar el algoritmo llamando a las funciones como tal.

quicksort.cpp: 

partition: Se encarga de realizar las particiones en base a un pivote seleccionado de forma aleatoria y realizar los intercambios necesarios a traves del uso de la recursion.

void quickSort(vector<int> &vec, int low, int high): 
Parte del algoritmo, llama a la funcion de particion y de forma recursivase llama a si misma a medida que se va realizando el ordenamiento en base a los pivotes aleatorios.

void quickSort(vector<int> &vec): Recibe el arreglo y si no esta vacio comienza con la ejecucion del algoritmo quicksort.

sort.cpp:

sortArray: Recibe el arreglo y ejecuta la funcion estandar llamada "sort".

### Programa principal

sorting.cpp es el programa principal.

writeArraysToFile: Funcion que se encarga finalmente de escribir el arreglo resultante en el archivo de salida

get_MemoryUsage: Se encarga de medir el uso de la memoria RAM durante la ejecucion de los archivos

Leer_arreglo: Lee los arreglos de entrada y hace la conversion respectiva del .txt original para que se puueda realizar e ordenamiento de arreglos posteriormente.

realizar_mediciones: Realiza las mediciones respectivas de tiempo y memoria llamando a las funciones respectivas, además de mandar a ejecutar los algoritmos de ordenamiento de arreglos, además de escribir el resultado de las mediciones en un archivo de texto llamado "resultados_generales.txt" dentro de la carpeta "measurements"

main: Funcion principal, encargado de recibir los arreglos de entrada, verificarlas, y posteriormente mandar a ejecutar los algoritmos respectivos.

### Scripts

array_generator.py: Programa encargado de crear los archivos de entrada que quedan guardados en array_input.

plot_generator.py: Script encargador de tomar los datos escritos en "resultados_generales.txt" y genera los graficos que representan los resultados generales.