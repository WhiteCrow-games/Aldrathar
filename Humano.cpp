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
int l) : Entidad(n, a, v, d, vel, p, e, l){
   apellido = ap;
   altura = al;
   prof = pr;
}

        string Humano ::getApellido(){
        return apellido;}

        float Humano::getAltura() {
        return altura; }

        string Humano::getProf(){
        return prof; }
