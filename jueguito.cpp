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

// Limpia la pantalla después de `segundos` segundos.
// Esta versión no usa hilos ni librerías adicionales: bloquea el hilo
// actual durante la espera (usa el comando del sistema `timeout`/`sleep`).
// Nota: en Windows se usa `timeout`, en Unix `sleep`.
void limpiarDespues(int segundos, bool /*async*/ = false) {
  if (segundos <= 0) {
    limpiarPantalla();
    return;
  }

#ifdef _WIN32
  std::string cmd = "timeout /t " + std::to_string(segundos) + " >nul";
#else
  std::string cmd = "sleep " + std::to_string(segundos) + " > /dev/null";
#endif
  system(cmd.c_str());
  limpiarPantalla();
}

struct Heroe{
  string name;
  int hp;
  int ataque;
  int defensa;
};

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

// Función para aplicar daño: resta (ataque - defensa) a `hp` (mínimo 0)
int aplicarDanio(int& hp, int ataque, int defensa) {
  int danio = ataque - defensa;
  if (danio < 0) danio = 1;
  if (danio == 1){
    cout << "El ataque no pudo penetrar la defensa." << endl;
  }
  hp -= danio;
  if (hp < 0) hp = 0; 
  cout << "-" << danio << " puntos de vida!" << endl;
  return 0;
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

void mostrarEstado(const Heroe& h) {
  cout << h.name << " - HP: " << h.hp 
     << " | Ataque: " << h.ataque 
     << " | Defensa: " << h.defensa << endl;
}

int main() {
  limpiarPantalla();
  cout << "¡Bienvenido al jueguito de combate!" << endl;
  // Crear héroe y monstruo
  Heroe heroe{"Heroe", 120, 25, 8};
  Monstruo monstruo = crearMonstruoRandom("Goblin", 50, 120, 5, 25, 0, 10);

  cout << "-- Estado inicial -----------------" << endl;
  mostrarEstado(heroe);
  mostrarEstado(monstruo);
  cout << "-----------------------------------" << endl;

  // Bucle de combate simple
  while (monstruo.hp > 0 && heroe.hp > 0) {
    cout << "\nElige una accion: (1) Atacar  (2) Huir : " ;
    int opcion = 0;
    if (!(cin >> opcion)) {
      cout << "Entrada inválida. Saliendo." << endl;
      break;
    }

    if (opcion == 1) {
      // Héroe ataca
      cout << "Atacas al monstruo!" << endl;
      aplicarDanio(monstruo.hp, heroe.ataque, monstruo.defensa);
      limpiarDespues(5);
      mostrarEstado(heroe);
      mostrarEstado(monstruo);
      if (monstruo.hp <= 0) {
        cout << "Has derrotado al monstruo!" << endl;
        break;
      }

      // Monstruo contraataca
      cout << "El monstruo contraataca!" << endl;
      aplicarDanio(heroe.hp, monstruo.ataque, heroe.defensa);
      limpiarDespues(5);
      mostrarEstado(heroe);
      mostrarEstado(monstruo);
      if (heroe.hp <= 0) {
        cout << "Has sido derrotado!" << endl;
        break;
      }

    } else if (opcion == 2) {
      cout << "Huyes del combate, tu vida no se ha recuperado..." << endl;
      break;
    } else {
      cout << "Opción no válida." << endl;
    }
  }

  return 0;
}