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
/*
(modificar esta parte) // el puntero tiene q ser creado para  el primer slot de team
  Humano *heroActual = nullptr; //creacion de puntero
   int seleccio

   cin >> principal;

// condicional para poner todos Entidad

       switch(principal){
       case 1:
 //              heroActual = &humano1;
           break;
       case 2:
 //              heroActual = &humano2;
           break;
       }



           limpiarPantalla();
 (clase o vector teamEnemigo)objetivoActual = nullptr;
           cout << "tu personaje es: " << endl;
   if(heroActual != nullptr){
       heroActual->mostrarDatos();}
    else{
       cout<< "no valido" << endl;

       cin.get();
       cin.get();
    }
                limpiarPantalla();

           cout << "Selecciona tu oponente: " << endl;
   for(int i = 0; i < 2; i++){
           cout << i+1 << "  -------------------------------------\n" <<endl;
    goblin[i].mostrarDatosMenu();
}
   int b;
   cin >> b;
        switch(b){
        case 1:
            objetivoActual = &goblin[0];
        break;
        case 2:
            objetivoActual = &goblin[1];
        break;

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
            break;
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
*/
   return 0;
   }
