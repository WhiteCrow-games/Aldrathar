#include "Hipogrifo.h"

Hipogrifo::Hipogrifo(
    string n,
    string color,
    string vuelo,
    int v,
    int a,
    int d,
    int vel,
    float p,
    float al,
int i,
    float env,
    int e,
    int l,
    int mgi
)
: Entidad(n, a, v, d, vel, p, al, i,  e, l, mgi)
{
    colorPlumas = color;
    tipoVuelo = vuelo;
    envergadura = env;
}

string Hipogrifo::getColorPlumas() {
    return colorPlumas;
}

string Hipogrifo::getTipoVuelo() {
    return tipoVuelo;
}

float Hipogrifo::getEnvergadura() {
    return envergadura;
}
