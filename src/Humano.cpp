#include "Entidad.h"
#include "Humano.h"

Humano::Humano(
string n,
string ap,
string pr,
int a,
int v,
int d,
int vel,
float p,
float al,
int e,
int l,
int mgi) : Entidad(n, a, v, d, vel, p, al, e, l, mgi){
   apellido = ap;
   prof = pr;
}


        string Humano ::getApellido(){
        return apellido;
}

        string Humano::getProf(){
        return prof;
}
