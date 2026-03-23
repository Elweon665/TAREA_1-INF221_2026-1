/*Fuentes de informacion:
-Welcome to Quick Sort in C++ https://codesignal.com/learn/courses/sorting-and-searching-algorithms-in-cpp/lessons/exploring-quick-sort-in-cpp
-C++ Program for Quick Sort https://www.geeksforgeeks.org/cpp/cpp-program-for-quicksort/
-How to generate a random number in C++? https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
*/


#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;
//-Welcome to Quick Sort in C++ https://codesignal.com/learn/courses/sorting-and-searching-algorithms-in-cpp/lessons/exploring-quick-sort-in-cpp
//-C++ Program for Quick Sort https://www.geeksforgeeks.org/cpp/cpp-program-for-quicksort/
//-How to generate a random number in C++? https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
//En todo el codigo se realizó una mezcla entre ambos codigos y el codigo de aleatoriedad, junto con algunas modificacioens.
int partition(vector<int> &vec, int low, int high) {

    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(low, high);
    int random_pivot_index = distrib(gen);

    swap(vec[low], vec[random_pivot_index]);

    int v = vec[low];
    int i = low;
    int j = high + 1;

    while (true){
        while (++i <= high && vec[i] < v){}
        
        while(vec[--j] > v){}

        if (i >= j){
            break;
        }
        swap(vec[i], vec[j]);
    }
    swap(vec[low], vec[j]);
    return j;
}

void quickSort(vector<int> &vec, int low, int high){
    int j;
    if(low < high){
        j = partition(vec, low, high);
        quickSort(vec, low, j - 1);
        quickSort(vec, j + 1, high);
    }
}

void quickSort(vector<int> &vec){
    if(!vec.empty()){
        quickSort(vec, 0, vec.size() - 1);
    }
}