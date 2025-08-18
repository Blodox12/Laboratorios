#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Reserva {
    string nombre_usuario;
    string documento;
    string id_equipo;
    string fecha_hora;
};

struct Equipo {
    string id_equipo;
    int capacidad;
    queue<Reserva> lista_espera; // Cola de espera para este equipo
};

vector<Equipo> equipos;
vector<Reserva> reservas;

// ------------------- Funciones auxiliares -------------------

void mostrarDisponibilidad() {
    cout << "\n--- Disponibilidad de Equipos ---\n";
    for (const auto &eq : equipos) {
        cout << "Equipo: " << eq.id_equipo 
             << " | Capacidad disponible: " << eq.capacidad 
             << " | En lista de espera: " << eq.lista_espera.size() << endl;
    }
}

void mostrarReservas() {
    cout << "\n--- Reservas Confirmadas ---\n";
    if (reservas.empty()) {
        cout << "No hay reservas confirmadas.\n";
        return;
    }
    for (const auto &r : reservas) {
        cout << "Usuario: " << r.nombre_usuario 
             << " | Documento: " << r.documento 
             << " | Equipo: " << r.id_equipo 
             << " | Fecha/Hora: " << r.fecha_hora << endl;
    }
}

void buscarReserva() {
    string dato;
    cout << "Ingrese nombre o documento para buscar: ";
    cin >> dato;
    bool encontrado = false;
    for (const auto &r : reservas) {
        if (r.nombre_usuario == dato || r.documento == dato) {
            cout << "Reserva encontrada -> Usuario: " << r.nombre_usuario
                 << ", Documento: " << r.documento
                 << ", Equipo: " << r.id_equipo
                 << ", Fecha/Hora: " << r.fecha_hora << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No existe la reserva.\n";
}

void registrarReserva() {
    Reserva nueva;
    cout << "Nombre usuario: ";
    cin >> nueva.nombre_usuario;
    cout << "Documento: ";
    cin >> nueva.documento;

    cout << "\n--- Equipos disponibles ---\n";
    for (const auto &eq : equipos) {
        cout << "ID: " << eq.id_equipo 
             << " | Capacidad disponible: " << eq.capacidad << endl;
    }
    cout << "Ingrese el ID EXACTO del equipo que desea reservar: ";
    cin >> nueva.id_equipo;

    cout << "Fecha/Hora (formato DD/MM/AAAA-HH:MM): ";
    cin >> nueva.fecha_hora;

    // Verificar duplicado
    for (const auto &r : reservas) {
        if (r.documento == nueva.documento && r.id_equipo == nueva.id_equipo) {
            cout << "Error: Ya existe una reserva para este usuario y equipo.\n";
            return;
        }
    }

    // Buscar equipo
    for (auto &eq : equipos) {
        if (eq.id_equipo == nueva.id_equipo) {
            if (eq.capacidad > 0) {
                eq.capacidad--;
                reservas.push_back(nueva);
                cout << "Reserva confirmada.\n";
            } else {
                char opcion;
                cout << "No hay capacidad. ¿Desea entrar en lista de espera? (s/n): ";
                cin >> opcion;
                if (opcion == 's' || opcion == 'S') {
                    eq.lista_espera.push(nueva);
                    cout << "Agregado a lista de espera.\n";
                } else {
                    cout << "Reserva cancelada.\n";
                }
            }
            return;
        }
    }
    cout << "Equipo no encontrado.\n";
}


void cancelarReserva() {
    string dato;
    cout << "Ingrese nombre o documento de la reserva a cancelar: ";
    cin >> dato;

    for (size_t i = 0; i < reservas.size(); i++) {
        if (reservas[i].nombre_usuario == dato || reservas[i].documento == dato) {
            string id_equipo = reservas[i].id_equipo;

            // Eliminar reserva
            reservas.erase(reservas.begin() + i);
            cout << "Reserva cancelada.\n";

            // Buscar equipo y liberar capacidad
            for (auto &eq : equipos) {
                if (eq.id_equipo == id_equipo) {
                    eq.capacidad++;

                    // Si hay lista de espera
                    if (!eq.lista_espera.empty()) {
                        Reserva turno = eq.lista_espera.front();
                        eq.lista_espera.pop();
                        eq.capacidad--; 
                        reservas.push_back(turno);
                        cout << "Se asignó el turno al usuario en espera: " 
                             << turno.nombre_usuario << endl;
                    }
                    return;
                }
            }
        }
    }
    cout << "No se encontró la reserva.\n";
}

// ------------------- Programa principal -------------------

int main() {
    // Inicializamos equipos de ejemplo
    equipos.push_back({"Bicicleta", 2});
    equipos.push_back({"BalonFutbol", 1});
    equipos.push_back({"Raqueta", 3});

    int opcion;
    while (true) {
        cout << "\n==== Sistema de Reservas de Equipos ====\n";
        cout << "1. Registrar una reserva\n";
        cout << "2. Buscar reserva por usuario\n";
        cout << "3. Mostrar todas las reservas\n";
        cout << "4. Mostrar disponibilidad de equipos\n";
        cout << "5. Cancelar una reserva\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarReserva(); break;
            case 2: buscarReserva(); break;
            case 3: mostrarReservas(); break;
            case 4: mostrarDisponibilidad(); break;
            case 5: cancelarReserva(); break;
            case 6: cout << "Saliendo...\n"; return 0;
            default: cout << "Opcion invalida.\n";
        }
    }
}
