#include "Criatura.h"


Criatura::Criatura(
    string n,
	string e,
    int v,
    int a,
int x,
int y,
char s
):Entidad(n,v,a,x,y,s){
 especie = e;
}


string getEspecie(){
    return especie;
}
