#include "Juego.h"

#include <iostream>

using namespace std;


Juego::Juego(){
    heroActual = nullptr;
    enemigoActual = nullptr;
	}//juego();

	void Juego::limpiarPantalla(){
	system("cls");
	system("clear");
	}//limpiarPantalla();

	void Juego::iniciar(){
cout << "\033[36m";
    cout << "=========================================\n";
    cout << "🐉		ALDRATHAR		🐉\n";
    cout << "=========================================\n";
cout << "\033[0m";
		crearPersonajes();
		crearEquipos();
mapa.colocarElemento(3, 5, '#'); //elemento independiente.
seleccionarHeroe();
limpiarPantalla();
heroActual->mostrarDatos();
seleccionarEnemigo();
	limpiarPantalla();
	heroActual->mostrarDatos();
	enemigoActual->mostrarDatos();
	cout << "Creando mapa...\n";
cin.get();
cin.get();

	while(heroActual->getVida()<=0){
	mapa.pared('#');
	colocarHeroe();
	colocarEnemigo();
	mapa.dibujar();
cout << "enter para salir...\n";
cin.get();
cin.get();
	}//while
}//iniciar

void Juego::crearPersonajes(){

    humanos.emplace_back(
        "Criss  Atheon",//nombre
        "Guerrero",	//profecion
        200,		//vida
	46		//ataque
	);


    humanos.emplace_back(
        "Roseline Karh",//nombre
	"Mago",		//profecion
        200,		//vida
	45 		//ataque
	);


    goblins.emplace_back(
        "Goblin",	//nombre
	"Guerrero",	//especie
        "Invernalia",	//region
	99,		//vida
        31		//ataque
);


   goblins.emplace_back(
        "Goblin",	//nombre
        "amarillo",	//especie
	"Dunaz del sol",//region
	99,		//vida
        30		//ataque
    	);
} //crearPersonaje();

	void Juego::crearEquipos(){ //creacion de equipo

    teamHeroes.push_back(&humanos[0]); //teamHeroes[0]
    teamHeroes.push_back(&humanos[1]); //teamHeroes[1]


    teamEnemigos.push_back(&goblins[0]); //teamEnemigos[0]
    teamEnemigos.push_back(&goblins[1]); //teamEnemigos[1]
	} // crearEquipos


void Juego::mostrarHeroes(){
	cout << "============================================\n";
	cout << "             Heroes\n";
	cout << "============================================\n";
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

void Juego::seleccionarHeroe() {

    int opcion;

    mostrarHeroes();

    cout << "\nSelecciona tu héroe: ";
    cin >> opcion;


    if (opcion >= 1 && opcion <= teamHeroes.size()) {
        heroActual = teamHeroes[opcion - 1];
    } else {
        cout << "Opción inválida.\n";
    }
}//seleccionHeroe();

void Juego::seleccionarEnemigo(){
	int option;
	mostrarEnemigos();
	cout << "\nSelecciona oponente: ";
	cin >> option;
	if (option>=1 && option <=teamEnemigos.size()){
	  enemigoActual = teamEnemigos[option -1];
	}else{
	cout << "option inválidad.\n";
	}

}//seleccionarEnemigo();

	void Juego::colocarHeroe(){
    heroActual->setX(4);
    heroActual->setY(8);
    heroActual-> setSimbolo('@');

	mapa.colocarElemento(
	heroActual->getX(),
	heroActual->getY(),
	heroActual->getSimbolo()
    );
}// colocarHeroe(){x, y, getFila(),getColumna, getSimbolo);

	void Juego::colocarEnemigo(){
	enemigoActual->setX(16);
	enemigoActual->setY(36);
	enemigoActual->setSimbolo('&');

	mapa.colocarElemento(
	enemigoActual->getX(),
	enemigoActual->getY(),
	enemigoActual->getSimbolo()
	};
} // colocarEnemigo
