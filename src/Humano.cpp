#include "Humano.h"


Humano::Humano(
    string n,
    int v,
    string p
)
:
Entidad(n,v)
{

    profesion = p;

}


string Humano::getProfesion()
{

    return profesion;

}
