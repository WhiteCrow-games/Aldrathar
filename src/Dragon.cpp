#include "Dragon.h"
Dragon :: Dragon(

    string n,
	    string ele,
	    string t,
	    string sub,
    int v,
    int a,
    int d,
    int vel,
    float p,
    float al,
	int i,
	    float log,
    int e,
    int l,
    int mgi
)
: Entidad (n, a, v, d, vel, p, al, i, e, l, mgi)
{
    elemento = ele;
    tipo = t;
    subElemento = sub;
    longitud = log;
}
string Dragon :: getElemento(){
	return elemento;
	}
string Dragon::getTipo() {
    return tipo;
}
string Dragon :: getSub(){
	return subElemento;
	}
float Dragon::getLongitud(){
	return longitud;
	}

