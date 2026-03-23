/* Fuentes de informacion:
-Header Files in C++ https://www.geeksforgeeks.org/cpp/header-files-in-c-c-with-examples/*/
#ifndef SORTING_H
#define SORTING_H

#include <vector>
//https://www.geeksforgeeks.org/cpp/header-files-in-c-c-with-examples/
//En base a lo mostrado en la pagina, se hizo esta parte del codigo tomando en cuenta que son funciones void.
void mergeSort(std::vector<int>& arr);
void quickSort(std::vector<int>& vec, int l, int u); 
void quickSort(std::vector<int>& vec);
void sortArray(std::vector<int>& arr);

#endif