#include "Criatura.h"


Criatura::Criatura(
    string n,
    int v,
    int a
)
:
Entidad(n,v)
{

    ataque = a;

}


int Criatura::getAtaque()
{

    return ataque;

}
