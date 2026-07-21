#include "Goblin.h"


Goblin::Goblin(
    string n,		//nombre
	string e,	//especie <- criatura
	string r,	//region
    int v,		//vida
    int a,		//ataque
	int x,		//fila
	int y,		//columna
	char s		//simbolo

):Criatura(n,e,v,a,x,y,s){

region = r;
}
string Goblin:: getRegion(){
	return region;
}
