#ifndef JUEGO_H
#define JUEGO_H

#include <vector>

#include "Entidad.h"
#include "Humano.h"
#include "Goblin.h"
using namespace std;

class Juego
{
private:

    // Personajes del juego
    vector<Humano> humanos;
    vector<Goblin> goblins;

    // Equipos
    vector<Entidad*> teamHeroes;
    vector<Entidad*> teamEnemigos;

    // Selección actual
    Entidad* heroActual;
    Entidad* enemigoActual;

public:

    Juego();

    void iniciar();

private:

    void crearPersonajes();

    void crearEquipos();

    void mostrarHeroes();

    void mostrarEnemigos();

    void seleccionarHeroe();

    void seleccionarEnemigo();

    void combatir();
};

#endif
