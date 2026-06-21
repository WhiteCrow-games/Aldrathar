#include "Enemigo.h"

Enemigo::Enemigo(string n, int v, int a) {
    nombre = n;
    vida = v;
    ataque = a;
}

string Enemigo::getNombre() {
    return nombre;
}

int Enemigo::getVida() {
    return vida;
}

int Enemigo::getAtaque() {
    return ataque;
}

void Enemigo::atacar(string nombre_) {
    cout << "\n-" << nombre << " ataca a "
         << nombre_ << endl;
}

void Enemigo::mostrarDatosMenu() {
    cout << nombre << endl;
    cout << "vida: " << vida << endl;
    cout << "ataque: " << ataque << endl;
}

void Enemigo::mostrarDatos() {
    cout << "\n" << nombre
         << " " << vida << endl;
}

void Enemigo::name() {
    cout << nombre << endl;
}

void Enemigo::recibirDanio(int cantidad) {
    vida -= cantidad;

    cout << nombre << " ha recibido "
         << cantidad << " pts de daño\n";

    if (vida <= 0) {
        vida = 0;
        cout << "\nVictoria!!!\n";
    }
}
