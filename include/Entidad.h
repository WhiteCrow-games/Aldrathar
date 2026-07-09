#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <iostream>
#include <string>

using namespace std;


class Entidad
{

protected:

    string nombre;

    int vida;


public:

    Entidad(string n, int v);


    string getNombre();

    int getVida();


    void recibirDanio(int dano);

};


#endif
