#ifndef JUEGO_H
#define JUEGO_H

#include <vector>

#include "Entidad.h"
#include "Humano.h"
#include "Goblin.h"

class Juego
{
private:

    // Personajes del juego
    std::vector<Humano> humanos;
    std::vector<Goblin> goblins;

    // Equipos
    std::vector<Entidad*> teamHeroes;
    std::vector<Entidad*> teamEnemigos;

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
