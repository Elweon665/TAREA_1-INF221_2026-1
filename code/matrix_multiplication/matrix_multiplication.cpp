#include <bits/stdc++.h>
#include <filesystem>
#include <chrono>
#include <sys/resource.h>
#include <functional>
#include "algorithms/matrix.h"
using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

void writeMatrixToFile(const vector<vector<int>>& matriz, const string& nombre_de_archivo){
    ofstream file(nombre_de_archivo);
    for(const auto& fila : matriz){
        for(int num : fila){
            file << num << " ";
        }
        file << "\n"; 
    }
}

int get_MemoryUsage(){
    struct rusage usage;
    int ret;
    ret = getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

vector<vector<int>> Leer_matriz(const string& filepath){
    cout << "dentro de leer matriz" << endl;
    ifstream file(filepath);
    cout<<"ifstream listo"<<endl;
    if(!file.is_open()){
        cerr << "Error al abrir el archivo: " << filepath << endl;
        exit(1);
    }

    fs::path pathObj(filepath);
    string filename = pathObj.filename().string(); 
    size_t pos = filename.find('_');
    int n = stoi(filename.substr(0, pos));
    vector<vector<int>> matriz(n, vector<int>(n));

    cout << "variables asignadas" << endl;
    cout << "Inicio del while" <<endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            file >> matriz[i][j];
        }
    }
    cout <<"fin de dicho while" << endl;
    return matriz;
}

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
                    cout << "dentro del for doble" << endl;
                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                            d_mat1[i][j] = matriz1[i][j];
                            d_mat2[i][j] = matriz2[i][j];
                        }
                    }

                    cout << "fuera del for doble" << endl;

                    Matrix M1(d_mat1);
                    Matrix M2(d_mat2);

                    Matrix M_result = M1.strassen(M2);

                    vector<vector<int>> result_int(n, vector<int>(n));
                    cout << "otro for doble" << endl;
                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                            result_int[i][j] = static_cast<int>(M_result.data[i][j]);
                        }
                    }

                    cout << "fuera for doble" << endl;

                    return result_int; 

                }, "Strassen", datasetName);
            }
        }
    }

    cout << "\n¡Resultados de matrices guardados exitosamente!" << endl;

    return 0;
}