#include "Juego.h"

#include <iostream>

using namespace std;


Juego::Juego(){
    heroActual = nullptr;
    enemigoActual = nullptr;
}

void Juego::iniciar(){
    cout << "============================\n";
    cout << "       ALDRATHAR\n";
    cout << "============================\n";

	crearPersonajes();
	 //VS
	crearEquipos();


    cout << "Mundo preparado...\n";
mapa.colocarElemento(3, 5, '&');
mapa.dibujar();
mostrarHeroes();
}

void Juego::crearPersonajes()
{

    humanos.emplace_back(
        "Cristals",	//nombre
        "Guerrero",	//profecion
        200		//vida
	);


    humanos.emplace_back(
        "Roseline",	//nombre
	"Mago",		//profecion
        200		//vida
	);


    goblins.emplace_back(
        "Goblin 1",	//nombre
        99,		//vida
        31		//ataque
 	);


   goblins.emplace_back(
        "Goblin 2",	//nombre
        99,		//vida
        30		//ataque
    	);
}

	void Juego::crearEquipos(){ //creacion de equipo

    teamHeroes.push_back(&humanos[0]); //teamHeroes[0]
    teamHeroes.push_back(&humanos[1]); //teamHeroes[1]


    teamEnemigos.push_back(&goblins[0]); //teamEnemigos[0]
    teamEnemigos.push_back(&goblins[1]); //teamEnemigos[1]
	} // crearEquipos


void Juego::mostrarHeroes(){
		cout << "============================\n";
                cout << "           Heroes\n";
                cout << "============================\n";
	for(int i = 0; i < teamHeroes.size(); i++){
	cout << i+1 <<". ";
	teamHeroes[i]->mostrarDatos();
	}

} //mostrarHeroes

void Juego::mostrarEnemigos(){
	for(int i = 0; i < teamEnemigos.size(); i++){
                cout << i+1 << " .";
	teamEnemigos[i]->mostrarDatos();
        }
} // mostrarEnemigos


/**
*Creacion de formula
*de seleccion de personaje
*/

void Juego::seleccionarHeroe(){}
/**	int opcion;
cout << "Selecciona tu Heroe:/n" << endl;
	cin >> opcion;
if ( opcion >= 1 // continue..

} //seleccionHeroe
*/
void Juego::seleccionarEnemigo(){}


