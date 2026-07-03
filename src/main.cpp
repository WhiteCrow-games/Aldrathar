#include "Goblin.h"
#include "Humano.h"
#include "Entidad.h"
#include "Dragon.h"
#include "Golem.h"
#include "Hipogrifo.h"

using namespace std;

        void limpiarPantalla(){
                system("clear");
			}


	void combatir(Entidad* heroActual, Entidad* objetivoActual){
		cout << "\n------------Iniciar combate------------" << endl;
    int turno = 1;
        	if(heroActual == nullptr || objetivoActual == nullptr){
			cout << "Seleccion invalida." << endl;
return;
 }
		   while (heroActual->getVida() > 0 && objetivoActual->getVida() > 0){
        limpiarPantalla();
        cout << "\n---------------Turno " << turno <<  "----------------" << endl;

        heroActual->atacar(objetivoActual->getNombre());
        objetivoActual->recibirDanio(heroActual->getAtaque());

       if (objetivoActual->getVida() <= 0) {
           cout << objetivoActual->getNombre() << " ha muerto"  << endl;
            break;
}
       objetivoActual->atacar(heroActual->getNombre());
       heroActual->recibirDanio(objetivoActual->getAtaque());

	if (heroActual->getVida() <= 0) {
            cout << heroActual->getNombre() << " ha sido derrota" << endl;
            break;
        }

       cout << "\nVida de " << heroActual->getNombre() << ": " << heroActual->getVida() << endl;

       cout << "Vida de " << objetivoActual->getNombre() << ": " << objetivoActual->getVida() << endl;
cin.get();
cin.get();
        turno++;

}
cin.get();
}
        int main(){
//------------------------------------------------
	vector<Humano> humanos;
 //humanos.empace_back(nombre-apellido-profesion-	     v   -a   -d   -v  -al   -i   -p   -e  -lvl -m--
	humanos.emplace_back("Atheon","Cristals","Guerrero", 200, 100, 67, 40, 191.5, 64, 58.7, 35, 26, 10);
	humanos.emplace_back("Rose", "Mor", "Guerrero",	     200, 100, 61, 67, 150.5, 64, 46.8, 48, 16, 10);
//-------------------------------------------s
	vector <Goblin> goblins;

    		goblins.emplace_back("Maldito","Goblin",    190, 89,  45, 5, 78.6, 1.23, 41, 16, 5, 10);
	       goblins.emplace_back("de Pantano", "Goblin", 170, 100, 45, 5, 57.1, 1.23, 38, 16, 5, 10);
//-------------------------------------------------------------------------------

vector<Dragon> dragons;

		dragons.emplace_back(
    			"Cronos",      // nombre
		  	"Fuego",       // elemento
   			"Ancestral",   // tipo
    			"Arena",       // subElemento
    			460,           // vida
    			100,           // ataque
   			243,           // defensa
    			47,            // velocidad
    			4230,          // peso
	 		4.8,           // altura
			79,
 			12.7,          // longitud
  			713,           // edad
    			71,            // nivel
			55);
		  dragons.emplace_back(
			"Galla",	//nombre
			"Fuego",	//elemento
			"centenario",	//tip
			"Silencio",	//subtipo
			159, 		//vid
			59, 		//atak
			60, 		//def
			50, 		//vel
			97.5, 		//peso
			2.6, 		//altura
			57,
			5.2, 		// longitud
			140, 		//edad
			21,		//nivel
			40	        //magia
);
//---------------------------------------------------------------------------------
		vector <Golem> golems;
	golems.emplace_back(
			"Tierra",
			"Golem",
			"Piedra",
			"Ambar",
			200,
			64,
			300,
			20,
			1874,
 			2.58,
			20,
			1000,
			34,
			20	//magia
);
//  	golems.push_back("Golem","del hierro",);
//--------------------------------------------------------------------------------

vector<Hipogrifo> hipogrifos;

hipogrifos.emplace_back(
    "Aeris",      // nombre
    "Blanco",     // color de plumas
    "Planeador",  // tipo de vuelo
    280,          // vida
    140,          // ataque
    90,           // defensa
    75,           // velocidad
    620.0,        // peso
    2.4,          // altura
	69, // inteligencia
    6.8,          // envergadura
    45,           // edad
    18,           // nivel
    30            // magia
);


//-----------------------------------------------------------------------
   cout << "---------------Sistema de juego ------------\n" << endl;
   cout << "Lista Heroes: " << endl;
   cout << "\n Selecciona tu heroe: " << endl;

	vector <Entidad*> entidades;
	    entidades.push_back( &humanos[0]);
	    entidades.push_back(&humanos[1]);
	    entidades.push_back(&goblins[0]);
	    entidades.push_back(&goblins[1]);
	    entidades.push_back(&dragons[0]);
	    entidades.push_back(&dragons[1]);
	    entidades.push_back(&golems[0]);
      	    entidades.push_back(&hipogrifos[0]);

	for(int i = 0; i < entidades.size(); i++){
		cout << i+1  << ". "; entidades[i]->mostrarDatosMenu();}
	int slot1;
	cin >> slot1;

  Entidad *heroActual = nullptr; //creacion de puntero
	switch(slot1){
        case 1:
             heroActual = &humanos[0];
           break;
        case 2:
             heroActual  = &humanos[1];
           break;
        case 3:
                heroActual = &goblins[0];
           break;
        case 4:
	        heroActual = &goblins[1];
           break;
        case 5:
                heroActual = &dragons[0];
           break;
        case 6:
                heroActual = &dragons[1];
           break;
        case 7:
                heroActual = &golems[0];
           break;
	case 8:
		heroActual = &hipogrifos[0];
	   break;
}


           limpiarPantalla();

Entidad *objetivoActual = nullptr;

           cout << "tu personaje es: " << endl;
   if(heroActual != nullptr){
       heroActual->mostrarDatos();}
    else{
       cout<< "no valido" << endl;

       cin.get();
       cin.get();
    };
	vector <Entidad*> teamEnemigo;
    teamEnemigo.push_back(&humanos[0]);
    teamEnemigo.push_back(&humanos[1]);
    teamEnemigo.push_back(&goblins[0]);
    teamEnemigo.push_back(&goblins[1]);
    teamEnemigo.push_back(&dragons[0]);
    teamEnemigo.push_back(&dragons[1]);
    teamEnemigo.push_back(&golems[0]);
    teamEnemigo.push_back(&hipogrifos[0]);

           cout << "Selecciona tu oponente: " << endl;
   for(int i = 0; i < teamEnemigo.size(); i++){
         cout << i+1 <<  ". "; teamEnemigo[i]->mostrarDatos();
}
   int slot4;
   cin >> slot4;
        switch(slot4){

	case 1:
	 	objetivoActual = teamEnemigo[0];
        	break;
        case 2:
		objetivoActual = teamEnemigo[1];
		break;
        case 3:
		objetivoActual = teamEnemigo[2];
        	break;
        case 4:
		objetivoActual = teamEnemigo[3];
                break;
        case 5:
		objetivoActual = teamEnemigo[4];
	        break;
	case 6:
		objetivoActual = teamEnemigo[5];
		break;
	case 7:
		objetivoActual = teamEnemigo[6];
		break;
	case 8:
		objetivoActual = teamEnemigo[7];
		break;
}

	limpiarPantalla();

 	combatir(heroActual, objetivoActual);
limpiarPantalla();
cout << "Saliendo del juego..." << endl;
   return 0;
}
