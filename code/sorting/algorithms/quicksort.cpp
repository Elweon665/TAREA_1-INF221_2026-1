#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

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