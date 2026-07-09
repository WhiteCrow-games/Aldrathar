class Juego
{
private:

    vector<Humano> humanos;

    vector<Goblin> goblins;

    vector<Dragon> dragons;

    vector<Golem> golems;

    vector<Hipogrifo> hipogrifos;

    vector<Entidad*> teamHeroes;

    vector<Entidad*> teamEnemigo;

    Entidad* heroActual;

    Entidad* enemigoActual;

public:

    Juego();

    void iniciar();

    void menuPrincipal();

    void seleccionarHeroe();

    void seleccionarEnemigo();

    void combatir();

};
