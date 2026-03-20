#include <bits/stdc++.h>
#include <filesystem>
#include <chrono>
#include <sys/resource.h>
#include <functional>
#include "algorithms/sorting.h"
using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

void writeArrayToFile(const vector<int>& arr, const string& nombre_de_archivo){
    ofstream file(nombre_de_archivo);
    for(int num : arr){
        file << num << "\n";
    }
}

int get_MemoryUsage(){
    struct rusage usage;
    int ret;
    ret = getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

vector<int> Leer_arreglo(const string& filename){
    cout << "dentro de ller arreglo" << endl;
    ifstream file(filename);
    cout<<"ifstream listo"<<endl;
    if(!file.is_open()){
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }
    vector<int> arreglo;
    int num;
    string linea;
    cout << "variables asignadas" << endl;
    cout << "Inicio del while" <<endl;
    while (file >> num){
        arreglo.push_back(num);
    }
    cout <<"fin de dicho while" << endl;
    return arreglo;
}

void realizar_mediciones(function<void(vector<int>&)> sortAlgorithm, vector<int> arr, const string& algoName, const string& datasetName){
    int memoria_inicial = get_MemoryUsage();
    auto start = std::chrono::high_resolution_clock::now();
    sortAlgorithm(arr);
    auto stop = std::chrono::high_resolution_clock::now();

    int memoria_actual = get_MemoryUsage();
    int memoria_usada = memoria_actual - memoria_inicial;

    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    fs::create_directories("data/measurements");
    string outFilename = "data/measurements/resultados_generales.txt";
    ofstream outFile(outFilename, ios::app);

    if(outFile.is_open()) {
        outFile << "Dataset: " << datasetName << "\n";
        outFile << "Algoritmo: " << algoName << "\n";
        outFile << "Tiempo (ms): " << duracion.count() << "\n";
        outFile << "Memoria utilizada (KB): " << memoria_usada << "\n";
        outFile << "-----------------------------------\n";
        outFile.close();
    } else {
        cerr << "Error al abrir archivo de salida para " << algoName << endl;
    }
    fs::create_directories("data/array_output");
    string sortedFilename = "data/array_output/" + algoName + "_" + datasetName + "_sorted.txt";
    writeArrayToFile(arr, sortedFilename);
}

int main(){
    string directorio_entrada = "data/array_input";

    fs::create_directories("data/measurements");
    ofstream limpiarArchivo("data/measurements/resultados_generales.txt", ios::trunc);
    limpiarArchivo.close();
    
    cout << "hola" << endl;
    for (const auto& entry : fs::directory_iterator(directorio_entrada)){
        if (entry.is_regular_file()){
            cout <<"dentro del if" <<endl;
            string filepath = entry.path().string(); 
            string filename = entry.path().filename().string(); 
            string datasetName = entry.path().stem().string();
            cout << "strings asignados" << endl;
            vector<int> original_arr = Leer_arreglo(filepath);
            cout << "vector asignado" << endl;
            cout << "  -> Ejecutando MergeSort..." << endl;
            realizar_mediciones([&](vector<int>& a) { mergeSort(a); }, original_arr, "MergeSort", datasetName);

            cout << "  -> Ejecutando QuickSort..." << endl;
            realizar_mediciones([&](vector<int>& a) { quickSort(a); }, original_arr, "QuickSort", datasetName);

            cout << "  -> Ejecutando std::sort..." << endl;
            realizar_mediciones([&](vector<int>& a) { std::sort(a.begin(), a.end()); }, original_arr, "Sort", datasetName);
        }

    }

    cout << "Resultados guardados!" << endl;

    return 0;

}