#include <iostream>
#include <random>
#include <vector>

using namespace std;

//Función para generar numeros aleatorios
int numeroAleatorio(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
//Función para elegir un numero valido
int elegirNumero(const vector<bool>& posibles) {

    vector<int> disponibles;

    for(int i = 0; i < 20; i++) {
        if(posibles[i]) {
            disponibles.push_back(i + 1);
        }
    }

    int indice = numeroAleatorio(0, disponibles.size() - 1);

    return disponibles[indice];
}

//Función principal
int main() {

    int simulaciones;
    cin >> simulaciones;

    int ganadasJ1 = 0;
    int ganadasJ2 = 0;

    int totalCartas = 0;
    int totalTurnos = 0;

    for(int partida = 0; partida < simulaciones; partida++) {

        // Números secretos
        int secretoJ1 = numeroAleatorio(1, 20);
        int secretoJ2 = numeroAleatorio(1, 20);

        // Posibles números
        vector<bool> posiblesJ1(20, true);
        vector<bool> posiblesJ2(20, true);

        bool bloqueoJ1 = false;
        bool bloqueoJ2 = false;

        int cartasEspeciales = 0;
        int turnos = 0;

        int jugadorActual = 1;

        bool ganador = false;
        // PARTIDA

        while(!ganador) {

            turnos++;

            // ======================================
            // TURNO JUGADOR 1
            // ======================================

            if(jugadorActual == 1) {

                if(bloqueoJ1) {
                    bloqueoJ1 = false;
                    jugadorActual = 2;
                    continue;
                }

                int carta = numeroAleatorio(1, 6);

                cartasEspeciales++;

                // ---------- PARIDAD ----------
                if(carta == 1) {

                    if(secretoJ2 % 2 == 0) {
                        for(int i = 0; i < 20; i++) {
                            if((i + 1) % 2 != 0)
                                posiblesJ1[i] = false;
                        }
                    }
                    else {
                        for(int i = 0; i < 20; i++) {
                            if((i + 1) % 2 == 0)
                                posiblesJ1[i] = false;
                        }
                    }
                }

                // ---------- MAYOR/MENOR ----------
                else if(carta == 2) {

                    if(secretoJ2 > 10) {
                        for(int i = 0; i < 10; i++)
                            posiblesJ1[i] = false;
                    }
                    else {
                        for(int i = 10; i < 20; i++)
                            posiblesJ1[i] = false;
                    }
                }

                // ---------- RANGO 1-5 ----------
                else if(carta == 3) {

                    if(secretoJ2 >= 1 && secretoJ2 <= 5) {

                        for(int i = 5; i < 20; i++)
                            posiblesJ1[i] = false;
                    }
                    else {

                        for(int i = 0; i < 5; i++)
                            posiblesJ1[i] = false;
                    }
                }

                // ---------- RANGO 15-20 ----------
                else if(carta == 4) {

                    if(secretoJ2 >= 15 && secretoJ2 <= 20) {

                        for(int i = 0; i < 14; i++)
                            posiblesJ1[i] = false;
                    }
                    else {

                        for(int i = 14; i < 20; i++)
                            posiblesJ1[i] = false;
                    }
                }

                // ---------- BLOQUEO ----------
                else if(carta == 5) {

                    bloqueoJ2 = true;
                }

                // ---------- COMODÍN ----------
                else if(carta == 6) {
                    // No ocurre nada
                }
                // INTENTO DE ADIVINANZA
                int intento = elegirNumero(posiblesJ1);
                if(intento == secretoJ2) {
                    ganadasJ1++;
                    ganador = true;
                }
                else {

                    posiblesJ1[intento - 1] = false;
                }

                jugadorActual = 2;
            }
            
            // TURNO JUGADOR 2

            else {

                if(bloqueoJ2) {
                    bloqueoJ2 = false;
                    jugadorActual = 1;
                    continue;
                }

                int carta = numeroAleatorio(1, 6);

                cartasEspeciales++;

                // ---------- PARIDAD ----------
                if(carta == 1) {

                    if(secretoJ1 % 2 == 0) {
                        for(int i = 0; i < 20; i++) {
                            if((i + 1) % 2 != 0)
                                posiblesJ2[i] = false;
                        }
                    }
                    else {
                        for(int i = 0; i < 20; i++) {
                            if((i + 1) % 2 == 0)
                                posiblesJ2[i] = false;
                        }
                    }
                }

                // ---------- MAYOR/MENOR ----------
                else if(carta == 2) {

                    if(secretoJ1 > 10) {
                        for(int i = 0; i < 10; i++)
                            posiblesJ2[i] = false;
                    }
                    else {
                        for(int i = 10; i < 20; i++)
                            posiblesJ2[i] = false;
                    }
                }

                // ---------- RANGO 1-5 ----------
                else if(carta == 3) {

                    if(secretoJ1 >= 1 && secretoJ1 <= 5) {

                        for(int i = 5; i < 20; i++)
                            posiblesJ2[i] = false;
                    }
                    else {

                        for(int i = 0; i < 5; i++)
                            posiblesJ2[i] = false;
                    }
                }

                // ---------- RANGO 15-20 ----------
                else if(carta == 4) {

                    if(secretoJ1 >= 15 && secretoJ1 <= 20) {

                        for(int i = 0; i < 14; i++)
                            posiblesJ2[i] = false;
                    }
                    else {

                        for(int i = 14; i < 20; i++)
                            posiblesJ2[i] = false;
                    }
                }

                // ---------- BLOQUEO ----------
                else if(carta == 5) {

                    bloqueoJ1 = true;
                }

                // ---------- COMODÍN ----------
                else if(carta == 6) {
                    // No ocurre nada
                }

                // ======================================
                // INTENTO
                // ======================================

                int intento = elegirNumero(posiblesJ2);

                if(intento == secretoJ1) {

                    ganadasJ2++;
                    ganador = true;
                }
                else {

                    posiblesJ2[intento - 1] = false;
                }

                jugadorActual = 1;
            }
        }

        totalCartas += cartasEspeciales;
        totalTurnos += turnos;
    }


// RESULTADOS

    double probJ1 = (double)ganadasJ1 / simulaciones;
    double probJ2 = (double)ganadasJ2 / simulaciones;
    double promedioCartas = (double)totalCartas / simulaciones;
    double promedioTurnos = (double)totalTurnos / simulaciones;

    cout << "\n========== RESULTADOS ==========\n";

    cout << "Simulaciones: " << simulaciones << endl;

    cout << "\nVictorias Jugador 1: " << ganadasJ1 << endl;
    cout << "Victorias Jugador 2: " << ganadasJ2 << endl;

    cout << "\nProbabilidad victoria J1: " << probJ1 << endl;
    cout << "Probabilidad victoria J2: " << probJ2 << endl;

    cout << "\nPromedio cartas especiales: "
         << promedioCartas << endl;

    cout << "Promedio turnos: "
         << promedioTurnos << endl;

    return 0;
}