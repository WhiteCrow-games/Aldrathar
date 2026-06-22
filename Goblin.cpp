#include "Goblin.h"
Goblin::Goblin(
    string t,
    string n,
    int v,
    int a,
    int d,
    int vel,
    float p,
    float al,
    int e,
    int l
)
: Entidad(n, a, v, d, vel, p, e, l)
{
    tipo = t;
    altura = al;
}

string Goblin::getTipo() {
    return tipo;
}

float Goblin::getAltura() {
    return altura;
}
