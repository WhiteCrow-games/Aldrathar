#include "Criatura.h"


Criatura::Criatura(
    string n,
	string e,
    int v,
    int a
):Entidad(n,v,a){
 especie = e;
}


string Criatura::getEspecie(){
    return especie;
}
