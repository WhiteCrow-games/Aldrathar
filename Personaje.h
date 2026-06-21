#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <Entidad.h>
#include <iostream>
using namespace std;

class Personaje: public Entidad {
private:
	string apellido;
	string casa;
	int nivel;

public:
    Personaje(string n, int a, int v, int d,
    float p,int e, string ap, int lvl);

    string getApellido();
    string getCasa();
   int getLvl();

    void mostrarDatos();
    void atacar(string nombre_);
    void recibirDanio(int cantidad);
};

#endif
