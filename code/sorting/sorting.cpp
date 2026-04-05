/*Fuentes de informacion:
-C++ Files and Streams https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
-How to Measure Memory Usage in C++ https://mrswolf.github.io/memory-usage-cpp/
-Using getline() with the file input in C++ https://stackoverflow.com/questions/20739453/using-getline-with-file-input-in-c
-Getline en C++ - Ejemplo con función getline() https://www.freecodecamp.org/espanol/news/getline-en-c-ejemplo-con-funcion-getline/
-getrusage(2) — Linux manual page https://man7.org/linux/man-pages/man2/getrusage.2.html
-Ideas de gemini www.gemini.google.com
-The /proc Filesystem https://www.kernel.org/doc/html/latest/filesystems/proc.html
-std::filesystem::path https://en.cppreference.com/w/cpp/filesystem/path.html*/


#include <bits/stdc++.h>
#include <filesystem>
#include <chrono>
#include <sys/resource.h>
#include <functional>
#include "algorithms/sorting.h"
using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;


//C++ Files and Streams https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
//Ciertas ideas del codigo fueron tomados de aqui
void writeArrayToFile(const vector<int>& arr, const string& nombre_de_archivo){
    ofstream file(nombre_de_archivo);
    for(int num : arr){
        file << num << "\n";
    }
}

//Ideas de gemini
//The /proc Filesystem
//Se combinaronambas ideas para crear la funcion
//Difiere del calculo de memoria en matrices, pues por alguna razón este codigo funciona mejor para el caso de los arreglos.
int get_MemoryUsage(){
    ifstream status("/proc/self/status");
    string line;
    while (getline(status, line)) {
        if (line.rfind("VmRSS:", 0) == 0) {
            istringstream iss(line);
            string key;
            long value;
            string unit;
            iss >> key >> value >> unit; 
            return value;
        }
    }
    return 0;
}

//-C++ Files and Streams
//Using getline() with the file input in C++
//Se cominaron ambas fuentes ppara la funcion.
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
    while (file >> num){
        arreglo.push_back(num);
    }
    return arreglo;
}


//-C++ Files and Streams
//Using getline() with the file input in C++
//Ideas de Gemini

void realizar_mediciones(function<void(vector<int>&)> sortAlgorithm, vector<int> arr, const string& algoName, const string& datasetName){
    long memoria_inicial = get_MemoryUsage();
    long memoria_peak = memoria_inicial;

    auto start = high_resolution_clock::now();
    sortAlgorithm(arr);
    long memoria_post = get_MemoryUsage();
    auto stop = high_resolution_clock::now();

    long memoria_usada = max(0L, memoria_post - memoria_inicial);

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

//-C++ Files and Streams
//Using getline() with the file input in C++
//Ideas de Gemini
//std::filesystem::path
int main(){
    string directorio_entrada = "data/array_input";

    fs::create_directories("data/measurements");
    ofstream limpiarArchivo("data/measurements/resultados_generales.txt", ios::trunc);
    limpiarArchivo.close();
    
    cout << "hola" << endl;
    for (const auto& entry : fs::directory_iterator(directorio_entrada)){
        if (entry.is_regular_file()){
            string filepath = entry.path().string(); 
            string filename = entry.path().filename().string(); 
            string datasetName = entry.path().stem().string();
            vector<int> original_arr = Leer_arreglo(filepath);

            cout << "  -> Ejecutando QuickSort..." << endl;
            realizar_mediciones([&](vector<int>& a) { quickSort(a); }, original_arr, "QuickSort", datasetName);

            cout << "  -> Ejecutando std::sort..." << endl;
            realizar_mediciones([&](vector<int>& a) { std::sort(a.begin(), a.end()); }, original_arr, "Sort", datasetName);

            cout << "  -> Ejecutando MergeSort..." << endl;
            realizar_mediciones([&](vector<int>& a) { mergeSort(a); }, original_arr, "MergeSort", datasetName);
        }

    }

    cout << "Resultados guardados!" << endl;
    cout << "Generando graficos..." << endl;
    system("cd scripts && python3 plot_generator.py");

    return 0;

}