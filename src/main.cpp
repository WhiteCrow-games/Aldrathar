
#include "Goblin.h"
#include "Humano.h"
#include "Entidad.h"
#include "Dragon.h"
#include "Golem.h"

using namespace std;

        void limpiarPantalla(){
                system("clear");
}

        int main(){
//------------------------------------------------
	vector<Humano> humanos;

	humanos.emplace_back(
		"Atheon",	//n
		"Cristals",	//ap
		"Guerrero",	//pr
		136,		//v
		100,		//a
		67,		//d
		7,		//vel
		189.5,		//al
		58.7,		//peso
		35,		//edad
		26,		//nivel
		10		//magia
);
	humanos.emplace_back(
		"Rose",
		"Mor",
		"Guerrero",
		110,
		100,
		61,
		6,
		150.5,
		48.7,
		16,
		34,
		10
);
//-------------------------------------------
	vector <Goblin> goblins;

    		goblins.emplace_back(
			"Maldito",
			"Goblin",
			190,
			89,
			45,
			5,
			78.6,
			1.23,
			16,
			5,
			10
);
	       goblins.emplace_back(
			"de Pantano",
			"Goblin",
			170,
			100,
			45,
			5,
			57.1,
			1.23,
			16,
			5,
			10
);
//-------------------------------------------------------------------------------

vector<Dragon> dragons;

		dragons.emplace_back(
    			"Cronos",      // nombre
		  	"Fuego",       // elemento
   			"Ancestral",   // tipo
    			"Arena",       // subElemento
    			460,           // vida
    			400,           // ataque
   			500,           // defensa
    			86,            // velocidad
    			4000,          // peso
	 		4.8,           // altura
 			12.7,          // longitud
  			600,           // edad
    			36,            // nivel
			40		//magia
);
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
			1000,
			34,
			20	//magia
);
//  	golems.push_back("Golem","del hierro",);
//--------------------------------------------------------------------------------
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

	for(int i = 0; i < 7; i++){
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
    teamEnemigo.push_back( &humanos[0]);
    teamEnemigo.push_back(&humanos[1]);
    teamEnemigo.push_back(&goblins[0]);
    teamEnemigo.push_back(&goblins[1]);
    teamEnemigo.push_back(&dragons[0]);
    teamEnemigo.push_back(&dragons[1]);
    teamEnemigo.push_back(&golems[0]);

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
		objetivoActual = teamEnemigo[3];
        	break;
        case 4:
		objetivoActual = teamEnemigo[4];
                break;
        case 5:
		objetivoActual = teamEnemigo[5];
	        break;
	case 6:
		objetivoActual = teamEnemigo[6];
		break;
	case 7:
		objetivoActual = teamEnemigo[7];
		}
	limpiarPantalla();

cout << "\n------------Iniciar combate------------" << endl;
    int turno = 1;
        if(heroActual == nullptr || objetivoActual == nullptr){

             cout << "Seleccion invalida." << endl;
return 0;
      }

    while (heroActual->getVida() > 0 && objetivoActual->getVida() > 0) {
        cout << "\n---------------Turno " << turno <<  "----------------\n" << endl;
        heroActual->atacar(objetivoActual->getNombre());
        objetivoActual->recibirDanio(heroActual->getAtaque());

       if (objetivoActual->getVida() <= 0) {
           cout << objetivoActual->getNombre() << " ha sido derrotado." << endl;
            }
       objetivoActual->atacar(heroActual->getNombre());
       heroActual->recibirDanio(objetivoActual->getAtaque());

       if (heroActual->getVida() <= 0) {
            cout << heroActual->getNombre() << " ha sido derrotado." << endl;
            break;
        }

       cout << "Vida de " << heroActual->getNombre() << ": " << heroActual->getVida() << endl;

       cout << "Vida de " << objetivoActual->getNombre() << ": " << objetivoActual->getVida() << endl;

        turno++;
}
   return 0;
}
