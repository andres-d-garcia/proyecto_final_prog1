#include <iostream>
#include <random>
#include <string>
using namespace std;

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

struct Monstruo{
    string name;
    int hp;
    int ataque;
    int defensa;
};

int numeroAleatorio(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

Monstruo crearMonstruoRandom(const string& nombre,
                             int hpMin, int hpMax,
                             int atkMin, int atkMax,
                             int defMin, int defMax) {
    Monstruo m;
    m.name = nombre;
    m.hp = numeroAleatorio(hpMin, hpMax);
    m.ataque = numeroAleatorio(atkMin, atkMax);
    m.defensa = numeroAleatorio(defMin, defMax);
    return m;
}

void mostrarEstado(const Monstruo& monstruo) {
    cout << monstruo.name << " - HP: " << monstruo.hp 
         << " | Ataque: " << monstruo.ataque 
         << " | Defensa: " << monstruo.defensa << endl;
}

int main() {
    // Ejemplo: monstruo con valores fijos
    mostrarEstado(Monstruo{"Monstruo", 100, 20, 10});

    // Ejemplo: monstruo con estadísticas aleatorias
    Monstruo aleatorio = crearMonstruoRandom("Goblin",
                                             50, 120,   // HP rango
                                             5, 25,      // Ataque rango
                                             0, 10);     // Defensa rango
    mostrarEstado(aleatorio);

    return 0;
}