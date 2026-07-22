#include "Humano.h"


Humano::Humano(
    string n,	//nombre
    string p,	//+profesion
    int v,	//vida
    int a	//ataque
):Entidad(n,v,a)
{
    profesion = p;
}
string Humano::getProfesion()
{
   return profesion;
}

