#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right){
    int n1 = mid-left + 1;
    int n2 = right - mid;

    vector<int> Left(n1); 
    vector<int> Right(n2);

    for (int i = 0; i < n1; i++)
        Left[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        Right[j] = arr[mid + 1 + j];


    int i = 0, j = 0;
    int k = left;
    while (i < n1 && j < n2){
        if (Left[i] <= Right[j]){
            arr[k++] = Left[i++];
        }
        else{
            arr[k++] = Right[j++];
        }
    }
    while (i < n1){
        arr[k++] = Left[i++];
    }
    while (j < n2){
        arr[k++] = Right[j++];
    }
}

void sort(vector<int>& arr, int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;
        sort(arr, left, mid);
        sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
void mergeSort(vector<int>& arr) {
    int arr_size = arr.size();
    
    if (arr_size <= 1) {
        return; 
    }
    
    sort(arr, 0, arr_size - 1);
}