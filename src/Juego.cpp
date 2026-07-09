#include "Juego.h"

#include <iostream>

using namespace std;


Juego::Juego()
{

    heroActual = nullptr;
    enemigoActual = nullptr;

}
void Juego::iniciar()
{

    cout << "============================\n";
    cout << "       ALDRATHAR\n";
    cout << "============================\n";


    crearPersonajes();

    crearEquipos();


    cout << "Mundo preparado...\n";

}

void Juego::crearPersonajes()
{

    humanos.emplace_back(
        "Atheon",
        "Cristals",
        "Guerrero",
        99,
        200,
        67,
        40,
        64.6,
        64,
        175.1,
        35,
        26,
        10
    );


    humanos.emplace_back(
        "Roseline",
        "Kart",
        "Guerrero",
        152,
        200,
        20,
        67,
        46.8,
        64,
        169.9,
        48,
        16,
        10
    );


    goblins.emplace_back(
        "Maldito",
        "Goblin",
        99,
        31,
        45,
        5,
        78.6,
        1.23,
        41,
        16,
        5,
        10
    );


   goblins.emplace_back(
        "De Pantano",
        "Goblin",
        99,
        30,
        45,
        5,
        57.1,
        1.23,
        38,
        16,
        5,
        10
    );
    cout << "Personajes creados.\n";

}

void Juego::crearEquipos()
{

    teamHeroes.push_back(&humanos[0]);
    teamHeroes.push_back(&humanos[1]);


    teamEnemigos.push_back(&goblins[0]);
    teamEnemigos.push_back(&goblins[1]);


    cout << "Equipos preparados.\n";

}
