'''Fuentes de informacion:
-Graph Plotting in Python | Set 1 https://www.geeksforgeeks.org/python/graph-plotting-in-python-set-1/
-Pyplot tutorial https://matplotlib.org/stable/tutorials/pyplot.html
-Python RegEx https://www.w3schools.com/python/python_regex.asp
-Reading a File in Python https://www.geeksforgeeks.org/python/how-to-read-from-a-file-in-python/
-Ideas de Gemini www.gemini.google.com
'''

import os
import re
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

entrada = "../data/measurements/resultados_generales.txt"
salida = "../data/plots"

#Reading a File in Python
#Python RegEx
#Ideas de Gemini
def extraer_datos(archivo):
    datos = []
    registro_actual = {}
    
    with open(archivo, 'r', encoding='utf-8') as f:
        for linea in f:
            linea = linea.strip()
            
            if linea.startswith("-----------------------------------"):
                if registro_actual:
                    datos.append(registro_actual)
                    registro_actual = {}
            elif linea.startswith('Dataset:'):
                nombre_dataset = linea.split('Dataset:')[1].strip()
                registro_actual['Dataset'] = nombre_dataset
                
                match_size = re.search(r'^(\d+)', nombre_dataset)
                registro_actual['Size'] = int(match_size.group(1)) if match_size else 0

                match_tipo = re.search(r'^\d+_([a-zA-Z]+)_', nombre_dataset)
                registro_actual['Tipo'] = match_tipo.group(1) if match_tipo else 'desconocido'
                
            elif linea.startswith('Algoritmo:'):
                registro_actual['Algoritmo'] = linea.split('Algoritmo:')[1].strip()
            elif linea.startswith('Tiempo (ms):'):
                registro_actual['Tiempo_ms'] = float(linea.split('Tiempo (ms):')[1].strip())
            elif linea.startswith('Memoria utilizada (KB):'):
                registro_actual['Memoria_KB'] = float(linea.split('Memoria utilizada (KB):')[1].strip())
 
        if registro_actual:
            datos.append(registro_actual)
            
    return pd.DataFrame(datos)

#Graph Plotting in Python | Set 1
#Pyplot tutorial
#Ideas de Gemini
def generar_graficos():
    os.makedirs(salida, exist_ok=True)
    df = extraer_datos(entrada)
    
    df_grouped = df.groupby(['Size', 'Tipo', 'Algoritmo'])[['Tiempo_ms', 'Memoria_KB']].mean().reset_index()
    tipos = df_grouped['Tipo'].unique()
    algoritmos = df_grouped['Algoritmo'].unique()
    
    tamaños = [0, 10, 1000, 100000, 10000000]
    tiempos = [0, 1000, 2000, 3000, 4000, 5000, 6000]
    for tipo in tipos:
        df_tipo = df_grouped[df_grouped['Tipo'] == tipo]
        # --- Gráfico Tiempo ---
        plt.figure(figsize=(10, 6))
        for algo in algoritmos:
            subset = df_tipo[df_tipo['Algoritmo'] == algo].sort_values('Size')
            if not subset.empty:
                plt.plot(subset['Size'], subset['Tiempo_ms'], marker='o', linewidth=2, label=algo)

        plt.title(f"Tiempo de Ejecución — Arreglo {tipo.capitalize()}")
        plt.xlabel("Tamaño de Arreglo (N)")
        plt.ylabel("Tiempo promedio (ms)")
        plt.xticks(tamaños)
        plt.yticks(tiempos)
        plt.xscale('log')
        #plt.yscale('log')
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.legend()
        plt.tight_layout()
        path = os.path.join(salida, f'tiempo_{tipo}.png')
        plt.savefig(path, dpi=300)
        print(f"Guardado: {path}")
        plt.close()

        if tipo == "aleatorio":
            memorias = [0, 400, 800, 1200, 1600,2000, 2400, 2800, 3200, 3400]
        else:
            memorias = [0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200]
        # --- Gráfico Memoria ---
        plt.figure(figsize=(10, 6))
        for algo in algoritmos:
            subset = df_tipo[df_tipo['Algoritmo'] == algo].sort_values('Size')
            if not subset.empty:
                plt.plot(subset['Size'], subset['Memoria_KB'], marker='s', linewidth=2, linestyle='-.', label=algo)

        plt.title(f"Consumo de Memoria — Arreglo {tipo.capitalize()}")
        plt.xlabel("Tamaño de Arreglo (N)")
        plt.ylabel("Memoria Promedio Utilizada (KB)")
        plt.xticks(tamaños)
        plt.yticks(memorias)
        plt.xscale('log')
        #plt.yscale('log')
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.legend()
        plt.tight_layout()
        path = os.path.join(salida, f'memoria_{tipo}.png')
        plt.savefig(path, dpi=300)
        print(f"Guardado: {path}")
        plt.close()

if __name__ == "__main__":
    generar_graficos()