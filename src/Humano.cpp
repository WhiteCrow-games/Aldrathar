#include "Humano.h"


Humano::Humano(
    string n,
    string p,
	int v
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
