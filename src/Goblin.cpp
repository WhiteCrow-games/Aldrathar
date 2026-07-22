#include "Goblin.h"


Goblin::Goblin(
    string n,		//nombre
	string e,	//especie <- criatura
	string r,	//region
    int v,		//vida
    int a

):Criatura(n,e,v,a){

region = r;
}
string Goblin:: getRegion(){
	return region;
}
