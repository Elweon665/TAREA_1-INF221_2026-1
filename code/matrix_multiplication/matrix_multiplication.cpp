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
#include "algorithms/matrix.h"
using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

//C++ Files and Streams https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
//Ciertas ideas del codigo fueron tomados de aqui
void writeMatrixToFile(const vector<vector<int>>& matriz, const string& nombre_de_archivo){
    ofstream file(nombre_de_archivo);
    for(const auto& fila : matriz){
        for(int num : fila){
            file << num << " ";
        }
        file << "\n"; 
    }
}
//How to Measure Memory Usage in C++
//getrusage(2) — Linux manual page
//Ideas de gemini
int get_MemoryUsage(){
    struct rusage usage;
    int ret;
    ret = getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

//-C++ Files and Streams
//Using getline() with the file input in C++
//Se cominaron ambas fuentes ppara la funcion.
vector<vector<int>> Leer_matriz(const string& filepath){
    ifstream file(filepath);
    if(!file.is_open()){
        cerr << "Error al abrir el archivo: " << filepath << endl;
        exit(1);
    }

    fs::path pathObj(filepath);
    string filename = pathObj.filename().string(); 
    size_t pos = filename.find('_');
    int n = stoi(filename.substr(0, pos));
    vector<vector<int>> matriz(n, vector<int>(n));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            file >> matriz[i][j];
        }
    }
    return matriz;
}

//-C++ Files and Streams
//Using getline() with the file input in C++
//Ideas de Gemini

void realizar_mediciones(function<vector<vector<int>>()> matrixAlgorithm, const string& algoName, const string& datasetName){
    int memoria_inicial = get_MemoryUsage();
    auto start = std::chrono::high_resolution_clock::now();
    vector<vector<int>> resultado = matrixAlgorithm();
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
    fs::create_directories("data/matrix_output");
    string sortedFilename = "data/matrix_output/" + algoName + "_" + datasetName + "_result.txt";
    writeMatrixToFile(resultado, sortedFilename);
}

//-C++ Files and Streams
//Using getline() with the file input in C++
//Ideas de Gemini
//std::filesystem::path

int main(){
    string directorio_entrada = "data/matrix_input";

    fs::create_directories("data/measurements");
    ofstream limpiarArchivo("data/measurements/resultados_matrices.txt", ios::trunc);
    limpiarArchivo.close();
    
    cout << "Iniciando proceso de multiplicacion de matrices..." << endl;
    
    for (const auto& entry : fs::directory_iterator(directorio_entrada)){
        if (entry.is_regular_file()){
            string filepath1 = entry.path().string(); 
            string filename1 = entry.path().filename().string(); 
            
            if (filename1.find("_1.txt") != string::npos) {
            
                string filepath2 = filepath1;
                filepath2.replace(filepath2.find("_1.txt"), 6, "_2.txt");
                
                if (!fs::exists(filepath2)) {
                    cerr << "Advertencia: No se encontró la pareja para " << filename1 << endl;
                    continue; 
                }
                
                string datasetName = entry.path().stem().string(); 
                datasetName = datasetName.substr(0, datasetName.length() - 2);

                cout << "\nProcesando par: " << datasetName << endl;

                vector<vector<int>> matriz1 = Leer_matriz(filepath1);
                vector<vector<int>> matriz2 = Leer_matriz(filepath2);

                cout << "  -> Ejecutando Algoritmo Naive (Tradicional)..." << endl;
                realizar_mediciones([&]() { return naive(matriz1, matriz2); }, "Naive", datasetName);

                cout << "  -> Ejecutando Algoritmo Strassen..." << endl;
                realizar_mediciones([&]() { 
                    int n = matriz1.size();
                    vector<vector<double>> d_mat1(n, vector<double>(n));
                    vector<vector<double>> d_mat2(n, vector<double>(n));
                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                            d_mat1[i][j] = matriz1[i][j];
                            d_mat2[i][j] = matriz2[i][j];
                        }
                    }

                    Matrix M1(d_mat1);
                    Matrix M2(d_mat2);

                    Matrix M_result = M1.strassen(M2);

                    vector<vector<int>> result_int(n, vector<int>(n));
                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                            result_int[i][j] = static_cast<int>(M_result.data[i][j]);
                        }
                    }

                    return result_int; 

                }, "Strassen", datasetName);
            }
        }
    }

    cout << "\n¡Resultados de matrices guardados exitosamente!" << endl;
    cout << "Generando graficos..." << endl;
    system("cd scripts && python3 plot_generator.py");

    return 0;
}