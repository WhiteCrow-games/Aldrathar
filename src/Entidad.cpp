#include "Entidad.h"


Entidad::Entidad(string n, int v)
{

    nombre = n;

    vida = v;

}


string Entidad::getNombre()
{

    return nombre;

}


int Entidad::getVida()
{

    return vida;

}


void Entidad::recibirDanio(int dano)
{

    vida -= dano;


    if(vida < 0)
        vida = 0;


    cout << nombre 
         << " recibe "
         << dano
         << " daño\n";

}
