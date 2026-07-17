#ifndef MAPA_H
#define MAPA_H

class Mapa {
	private:
	  int filas;
	  int columnas;
	  char mapa[20][40];

	public:
	  Mapa();
     void dibujar();
	void colocarElemento(int fila, int columna, char simbolo);
	void pared(char simbolo);
};
#endif
