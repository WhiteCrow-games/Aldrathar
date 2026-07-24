#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <Mapa.h>
#include "Entidad.h"
#include "Humano.h"
#include "Goblin.h"
using namespace std;

class Juego{

private:
	Mapa mapa;
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

    void limpiarPantalla();

    void crearPersonajes();

    void crearEquipos();

    void mostrarHeroes();

    void mostrarEnemigos();

    void seleccionarHeroe();

    void seleccionarEnemigo();

void initHeroe();
    void colocarHeroe();

void initEnemigo();
    void colocarEnemigo();

	void combatir();
};
#endif
