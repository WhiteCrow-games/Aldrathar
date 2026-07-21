#include "Humano.h"


Humano::Humano(
    string n,	//nombre
    string p,	//+profesion
    int v,	//vida
    int a,	//ataque
    int x,	//fila
    int y,	//columna
    char s	//simbolo

):Entidad(n,v,a,x,y,s)
{
    profesion = p;
}
string Humano::getProfesion()
{
   return profesion;
}

