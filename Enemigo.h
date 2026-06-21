#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <iostream>
using namespace std;

class Enemigo {
private:
    string nombre;
    int vida;
    int ataque;

public:
    Enemigo(string n, int v, int a);

    string getNombre();
    int getVida();
    int getAtaque();

    void atacar(string nombre_);
    void mostrarDatosMenu();
    void mostrarDatos();
    void name();
    void recibirDanio(int cantidad);
};

#endif
