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
    int l,
    int mgi
)
: Entidad(n, a, v, d, vel, p, al, e, l, mgi)
{
    tipo = t;

}

string Goblin::getTipo() {
    return tipo;
}

