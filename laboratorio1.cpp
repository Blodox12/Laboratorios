#include <iostream>
#include <vector>
#include <string>

using namespace std;

void mostrarMenu() {
    cout << "\n--- MENU DEL JUEGO ---" << endl;
    cout << "1. Añadir jugador y puntuación" << endl;
    cout << "2. Ver puntuaciones" << endl;
    cout << "3. Eliminar jugador" << endl;
    cout << "4. Salir" << endl;
    cout << "Selecciona una opción: ";
}

void agregarJugador(vector<string>& nombres, vector<int>& puntuaciones) {
    string nombre;
    int puntuacion;
    string input;

    cout << "Nombre del jugador: ";
    getline(cin, nombre);

    cout << "Puntuación del jugador: ";
    while (true) {
        getline(cin, input);
        bool esValido = true;
        
 
        if (input.empty()) {
            esValido = false;
        } else {
            // Verificar que todos los caracteres sean dígitos (permitir números negativos)
            int inicio = 0;
            if (input[0] == '-') inicio = 1;
            
            for (int i = inicio; i < input.length(); i++) {
                if (!isdigit(input[i])) {
                    esValido = false;
                    break;
                }
            }
            
            // Verificar que no sea solo un signo negativo
            if (input == "-") esValido = false;
        }
        
        if (esValido) {
            puntuacion = stoi(input);
            break;
        } else {
            cout << "Error: Ingresa solo números. Intenta de nuevo: ";
        }
    }

    nombres.push_back(nombre);
    puntuaciones.push_back(puntuacion);

    cout << "Jugador añadido con éxito." << endl;
}

void listarPuntuaciones(const vector<string>& nombres, const vector<int>& puntuaciones) {
    if (nombres.empty()) {
        cout << "No hay puntuaciones registradas." << endl;
        return;
    }

    cout << "\n--- Tabla de puntuaciones ---" << endl;
    for (size_t i = 0; i < nombres.size(); ++i) {
        cout << i << ". " << nombres[i] << " - " << puntuaciones[i] << " puntos" << endl;
    }
}

void eliminarJugador(vector<string>& nombres, vector<int>& puntuaciones) {
    if (nombres.empty()) {
        cout << "No hay jugadores para eliminar." << endl;
        return;
    }

    listarPuntuaciones(nombres, puntuaciones);
    int indice;
    string input;
    cout << "Ingresa el índice del jugador que deseas eliminar: ";
    while (true) {
        getline(cin, input);
        bool esValido = true;
        
        // Verificar que no esté vacío
        if (input.empty()) {
            esValido = false;
        } else {
            // Verificar que todos los caracteres sean dígitos
            for (int i = 0; i < input.length(); i++) {
                if (!isdigit(input[i])) {
                    esValido = false;
                    break;
                }
            }
        }
        
        if (esValido) {
            indice = stoi(input);
            break;
        } else {
            cout << "Error: Ingresa solo números. Intenta de nuevo: ";
        }
    }

    if (indice >= 0 && indice < nombres.size()) {
        nombres.erase(nombres.begin() + indice);
        puntuaciones.erase(puntuaciones.begin() + indice);
        cout << "Jugador eliminado exitosamente." << endl;
    } else {
        cout << "Índice inválido." << endl;
    }
}

int main() {
    vector<string> nombres;
    vector<int> puntuaciones;
    int opcion;
    string input;

    do {
        mostrarMenu();
        while (true) {
            getline(cin, input);
            bool esValido = true;
            
            // Verificar que no esté vacío
            if (input.empty()) {
                esValido = false;
            } else {
                // Verificar que todos los caracteres sean dígitos
                for (int i = 0; i < input.length(); i++) {
                    if (!isdigit(input[i])) {
                        esValido = false;
                        break;
                    }
                }
            }
            
            if (esValido) {
                opcion = stoi(input);
                break;
            } else {
                cout << "Error: Ingresa solo números. Selecciona una opción: ";
            }
        }

        switch (opcion) {
            case 1:
                agregarJugador(nombres, puntuaciones);
                break;
            case 2:
                listarPuntuaciones(nombres, puntuaciones);
                break;
            case 3:
                eliminarJugador(nombres, puntuaciones);
                break;
            case 4:
                cout << "Saliendo del programa. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción inválida. Intenta de nuevo." << endl;
        }

    } while (opcion != 4);

    return 0;
}
