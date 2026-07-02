#include "Golem.h"

Golem::Golem (
	string ele,
	    string n,
	string m,
	string c,
	    int v,
	    int a,
	    int d,
	    int vel,
	    float p,
      	    float al,
		int i,
	    int e,
	    int l,
	    int mgi
)
: Entidad(n, a, v, d, vel, p, al, i, e, l, mgi)
{
    elemento = ele;
    material = m;
    cristal = c;
}

string Golem::getElemento() {
    return elemento;
}
string Golem::getMaterial() {
	return material;
}
string Golem::getCristal() {
	return cristal;
}
