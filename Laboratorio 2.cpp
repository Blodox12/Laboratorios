#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Función para verificar si un número es primo
bool esPrimo(int num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

// Función para generar la serie de números triangulares
vector<int> generarTriangulares() {
    vector<int> triangulares;
    for (int n = 1; n <= 10; n++) {
        triangulares.push_back(n * (n + 1) / 2);
    }
    return triangulares;
}

// Función para generar los primeros 10 números primos
vector<int> generarPrimos() {
    vector<int> primos;
    int num = 2;
    while (primos.size() < 10) {
        if (esPrimo(num)) {
            primos.push_back(num);
        }
        num++;
    }
    return primos;
}

// Función para generar la secuencia de Fibonacci
vector<int> generarFibonacci() {
    vector<int> fibonacci = {0, 1};
    for (int i = 2; i < 10; i++) {
        fibonacci.push_back(fibonacci[i-1] + fibonacci[i-2]);
    }
    return fibonacci;
}

// Función para encontrar los valores incorrectos en una fila
vector<int> encontrarIncorrectos(vector<int>& fila, vector<int>& serieCorrecta) {
    vector<int> incorrectos;
    for (int i = 0; i < 10; i++) {
        if (fila[i] != serieCorrecta[i]) {
            incorrectos.push_back(fila[i]);
        }
    }
    return incorrectos;
}

// Función para contar errores en una fila
int contarErrores(vector<int>& fila, vector<int>& serieCorrecta) {
    int errores = 0;
    for (int i = 0; i < 10; i++) {
        if (fila[i] != serieCorrecta[i]) {
            errores++;
        }
    }
    return errores;
}

// Función para validar una fila contra su serie correcta
bool validarFila(vector<int>& fila, vector<int>& serieCorrecta, string nombreSerie) {
    int errores = contarErrores(fila, serieCorrecta);
    
    if (errores == 1) {
        cout << "  ✓ Fila registrada correctamente." << endl;
        return true;
    } else if (errores == 0) {
        cout << "  ❌ Error: Debe tener exactamente 1 valor modificado." << endl;
        return false;
    } else {
        cout << "  ❌ Error: Debe tener exactamente 1 valor modificado." << endl;
        return false;
    }
}

int main() {
    cout << "=== DECODIFICADOR DE MATRIZ SECRETA ===" << endl;
    cout << "Este programa detecta valores incorrectos en una matriz de 3x10." << endl;
    cout << "Cada fila debe seguir una serie matematica especifica:" << endl;
    cout << "- Fila 1: Numeros triangulares (1, 3, 6, 10, 15, 21, 28, 36, 45, 55)" << endl;
    cout << "- Fila 2: Numeros primos (2, 3, 5, 7, 11, 13, 17, 19, 23, 29)" << endl;
    cout << "- Fila 3: Secuencia Fibonacci (0, 1, 1, 2, 3, 5, 8, 13, 21, 34)" << endl;
    cout << endl;
    cout << "⚠️  IMPORTANTE: Cada fila DEBE tener exactamente 1 valor modificado." << endl;
    cout << "   Esto es necesario para generar el código secreto." << endl;
    cout << endl;
    cout << "FORMATO DE ENTRADA:" << endl;
    cout << "Ingrese 10 numeros separados por espacios en cada fila." << endl;
    cout << "Ejemplo: 1 3 6 10 15 21 7 36 45 55 (donde 7 reemplaza a 28)" << endl;
    cout << "========================================================" << endl << endl;
    
    // Declarar la matriz
    vector<vector<int>> matriz(3, vector<int>(10));
    
    // Generar las series correctas antes de solicitar datos
    vector<int> triangulares = generarTriangulares();
    vector<int> primos = generarPrimos();
    vector<int> fibonacci = generarFibonacci();
    
    // Nombres y series para cada fila
    vector<string> nombresSeries = {"Números Triangulares", "Números Primos", "Secuencia de Fibonacci"};
    vector<vector<int>> seriesCorrectas = {triangulares, primos, fibonacci};
    
    // Solicitar datos al usuario con validación por sucesión
    for (int fila = 0; fila < 3; fila++) {
        bool filaCompleta = false;
        
        cout << "=== FILA " << (fila + 1) << ": " << nombresSeries[fila] << " ===" << endl;
        cout << "Serie correcta: ";
        for (int i = 0; i < seriesCorrectas[fila].size(); i++) {
            cout << seriesCorrectas[fila][i];
            if (i < seriesCorrectas[fila].size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "⚠️  OBLIGATORIO: Debe modificar exactamente 1 valor de la serie." << endl;
        
        // Mostrar ejemplo específico para cada fila
        if (fila == 0) {
            cout << "Ejemplo: 1, 3, 6, 10, 15, 21, 7, 36, 45, 55 (cambiar 28 por 7)" << endl;
        } else if (fila == 1) {
            cout << "Ejemplo: 2, 3, 5, 7, 20, 13, 17, 19, 23, 29 (cambiar 11 por 20)" << endl;
        } else {
            cout << "Ejemplo: 0, 1, 1, 2, 3, 5, 8, 13, 19, 34 (cambiar 21 por 19)" << endl;
        }
        
        while (!filaCompleta) {
            cout << endl << "Ingrese 10 números de " << nombresSeries[fila] << ": ";
            
            string linea;
            getline(cin, linea);
            
            // Si la línea está vacía (primera iteración después de cin), intentar de nuevo
            if (linea.empty()) {
                continue;
            }
            
            // Convertir la línea en un vector de enteros
            vector<int> numerosIngresados;
            string numero = "";
            
            // Procesar cada caracter de la línea
            for (char c : linea) {
                if (c == ' ' || c == '\t') {
                    if (!numero.empty()) {
                        try {
                            numerosIngresados.push_back(stoi(numero));
                            numero = "";
                        } catch (const exception& e) {
                            numerosIngresados.clear();
                            break;
                        }
                    }
                } else if (isdigit(c) || c == '-') {
                    numero += c;
                } else {
                    // Caracter inválido
                    numerosIngresados.clear();
                    break;
                }
            }
            
            // Agregar el último número si existe
            if (!numero.empty() && !numerosIngresados.empty()) {
                try {
                    numerosIngresados.push_back(stoi(numero));
                } catch (const exception& e) {
                    numerosIngresados.clear();
                }
            }
            
            // Validar que se ingresaron exactamente 10 números
            if (numerosIngresados.size() == 10) {
                // Validar que la fila corresponde a la serie correcta
                if (validarFila(numerosIngresados, seriesCorrectas[fila], nombresSeries[fila])) {
                    // Copiar los números válidos a la matriz
                    for (int col = 0; col < 10; col++) {
                        matriz[fila][col] = numerosIngresados[col];
                    }
                    filaCompleta = true;
                } else {
                    cout << "  Intente nuevamente con la serie correcta." << endl;
                }
            } else {
                cout << "  ❌ Error: Debe ingresar exactamente 10 números." << endl;
                cout << "     Usted ingresó " << numerosIngresados.size() << " números." << endl;
                cout << "     Intente nuevamente." << endl;
            }
        }
        cout << endl;
    }
    
    // Encontrar los valores incorrectos
    vector<int> codigosIncorrectos;
    
    // Analizar todas las filas silenciosamente
    vector<int> erroresFila1 = encontrarIncorrectos(matriz[0], triangulares);
    codigosIncorrectos.push_back(erroresFila1[0]);
    
    vector<int> erroresFila2 = encontrarIncorrectos(matriz[1], primos);
    codigosIncorrectos.push_back(erroresFila2[0]);
    
    vector<int> erroresFila3 = encontrarIncorrectos(matriz[2], fibonacci);
    codigosIncorrectos.push_back(erroresFila3[0]);
    
    // Mostrar el código secreto
    cout << endl << "=== CÓDIGO SECRETO DESCIFRADO ===" << endl;
    cout << "Código: ";
    for (int i = 0; i < codigosIncorrectos.size(); i++) {
        cout << codigosIncorrectos[i];
        if (i < codigosIncorrectos.size() - 1) cout << "-";
    }
    cout << endl;
    
    return 0;
}