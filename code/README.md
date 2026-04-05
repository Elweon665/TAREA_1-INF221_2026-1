# Documentación

## Entrega

"Más allá de la notación asintótica: Análisis experimental de algoritmos de ordenamiento y multiplicación de matrices." Nombre: Vicente Carvajal Helqui Rol: 202273572-4 

En esta entrega se estudia el comportamiento de los algoritmos tanto de ordenamiento de arreglos, así como los que permiten multiplicar matrices. 

Ejecución del codigo: Diríjase a la carpeta de interés (sorting o matrix_multoplication) y dentro de ella escriba: "make run". 

En caso de querer graficar, diríjase a la carpeta "scripts" y ejecute plot_generator.py con Python 3.10 o posterior. 

## Multiplicación de matrices 
En esta entrega se consideran dos algoritmos de este tipo, los cuales son: Naive y Strassen. 

Tal y como dice el documento de la entrega, son algoritmos conocidos y que han sido documentados en varias partes (Sobre todo en internet) Por lo que se implementaron y adaptaron implementaciones conocidas de ambos algoritmos 

A continuación, se documentarán el propósito de las funciones de cada código: 


strassen.cpp: 

valitadateDimensions: Verifica que las dimensiones de las matrices son cuadradas y por ende validas 

validateMultiplication: Verifica que las matrices se puedan multiplicar 

validateSquarePowerofTwo: Revisa que la matriz sea cuadrada 

operator+: Realiza la operación de suma cuando es necesaria 

operator-: Realiza la operación de resta cuando es necesaria 

operator*: Realiza la operación de multiplicación de 2 valores 

operator>>: Realiza la operación de shiteo 

toStringWithPresision: convierte el resultado de una multiplicación a string para poder ser escrito en el texto que contiene el resultado de la multiplicación de la matriz 

params: Función que define parte de las reglas para dividir la matriz, es como un diccionario de coordenadas, un mapa. 

fromQuaters: Función que realiza la división de las matrices en submatrices en base a las reglas definidas por la función params 

strassen: Función principal, encargado de realizar la multiplicación mediante este algoritmo llamando a las funciones respectivas según el paso a realizar. 

Funciones de naive.cpp: 

naive: Función principal, este se encarga de ejecutar el algoritmo como tal, sin mucha más ciencia. 
### Programa principal 
matrix_multiplication.cpp es el programa principal. 

Funciones de matrix_multiplication.cpp: 

writeMatrixToFile: Función que se encarga finalmente de escribir la matriz resultante en el archivo de salida 

get_MemoryUsage: Se encarga de medir el uso de la memoria RAM durante la ejecución de los archivos 

Leer_Matriz: Lee las matrices de entrada y hace la conversión respectiva del .txt original para que se pueda realizar la multiplicación de las matrices posteriormente. 

realizar_mediciones: Realiza las mediciones respectivas de tiempo y memoria llamando a las funciones respectivas, además de mandar a ejecutar los algoritmos de multiplicación de matrices, además de escribir el resultado de las mediciones en un archivo de texto llamado "resultados_generales.txt" dentro de la carpeta "measurements" 

main: Función principal, encargado de recibir las matrices de entrada, verificarlas, y posteriormente mandar a ejecutar los algoritmos respectivos. 

### Scripts 
matrix_generator.py: Programa encargado de crear los archivos de entrada que quedan guardados en matrix_input. 

plot_generator.py: Script encargado de tomar los datos escritos en "resultados_generales.txt" y genera los gráficos que representan los resultados generales. 
## Ordenamiento de arreglo unidimensional 

Algoritmos: MergeSort, QuickSort, std::sort. 

Al igual que en el caso de las matrices, estos algoritmos son conocidos y se ha decidido colocar implementaciones externas de estos mismos, a excepción de sort.cpp donde este viene con el código ya escrito por defecto en esta entrega. 

A continuación, se documentarán el uso de las funciones de cada programa: 

mergesort.cpp 

merge: Esta función se encarga de realizar la división en sublistas de los arreglos, como lo propone parte del algoritmo 

sort: Se encarga de forma recursiva de ordenar el arreglo en base a las subdivisiones realizadas anteriormente 

mergeSort: Función principal, se encarga de ejecutar el algoritmo llamando a las funciones como tal. 


quicksort.cpp:  

partition: Se encarga de realizar las particiones en base a un pivote seleccionado de forma aleatoria y realizar los intercambios necesarios a través del uso de la recursión. 

void quickSort(vector<int> &vec, int low, int high):  

Parte del algoritmo, llama a la función de partición y de forma recursiva llama a sí misma a medida que se va realizando el ordenamiento en base a los pivotes aleatorios. 

void quickSort(vector<int> &vec): Recibe el arreglo y si no está vacío comienza con la ejecución del algoritmo Quicksort. 

sort.cpp: 

sortArray: Recibe el arreglo y ejecuta la función estándar llamada "sort". 

### Programa principal 
sorting.cpp es el programa principal. 

writeArraysToFile: Función que se encarga finalmente de escribir el arreglo resultante en el archivo de salida 

get_MemoryUsage: Se encarga de medir el uso de la memoria RAM durante la ejecución de los archivos 

Leer_arreglo: Lee los arreglos de entrada y hace la conversión respectiva del .txt original para que se pueda realizar el ordenamiento de arreglos posteriormente. 

realizar_mediciones: Realiza las mediciones respectivas de tiempo y memoria llamando a las funciones respectivas, además de mandar a ejecutar los algoritmos de ordenamiento de arreglos, además de escribir el resultado de las mediciones en un archivo de texto llamado "resultados_generales.txt" dentro de la carpeta "measurements" 

 
main: Función principal, encargado de recibir los arreglos de entrada, verificarlas, y posteriormente mandar a ejecutar los algoritmos respectivos. 
### Scripts 
array_generator.py: Programa encargado de crear los archivos de entrada que quedan guardados en array_input. 

plot_generator.py: Script encargado de tomar los datos escritos en "resultados_generales.txt" y genera los gráficos que representan los resultados generales. 