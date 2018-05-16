/*
 * tetris.c
 *
 *  Created on: 14/4/2017
 *      Author: Carlos
 */

#include "tetris.h"

int figs[16][TAMANO_FIGURA][TAMANO_FIGURA]={
		//conjunto de figuras y sus diferentes rotaciones
		{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,0,1},
				{0,1,1,1},
		},
		{
				{0,0,0,0},
				{0,0,1,0},
				{0,0,1,0},
				{0,0,1,1},
		},
		{
				{0,0,0,0},
				{0,0,0,0},
				{0,1,1,1},
				{0,1,0,0},
		},
		{
				{0,0,0,0},
				{0,0,1,1},
				{0,0,0,1},
				{0,0,0,1},
		},
		{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,1,0},
				{0,1,1,1},
		},
		{
				{0,0,0,0},
				{0,0,1,0},
				{0,0,1,1},
				{0,0,1,0},
		},
		{
				{0,0,0,0},
				{0,0,0,0},
				{0,1,1,1},
				{0,0,1,0},
		},
		{
				{0,0,0,0},
				{0,0,0,1},
				{0,0,1,1},
				{0,0,0,1},
		},
		{
				{0,0,0,0},
				{0,0,1,0},
				{0,0,1,1},
				{0,0,0,1},
		},
		{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,1,1},
				{0,1,1,0},
		},
		{
				{0,0,0,0},
				{0,0,1,0},
				{0,0,1,1},
				{0,0,0,1},
		},
		{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,1,1},
				{0,1,1,0},
		},
		{
				{0,0,0,1},
				{0,0,0,1},
				{0,0,0,1},
				{0,0,0,1},
		},
		{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,1},
		},
		{
				{0,0,0,1},
				{0,0,0,1},
				{0,0,0,1},
				{0,0,0,1},
		},
		{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,1},
		},
};




void ReseteaMatriz(tipo_pantalla *p_pantalla) {
	//reseteamos la matriz principal
	int i, j = 0;

	for(i=0;i<MATRIZ_ANCHO;i++) {
		for(j=0;j<MATRIZ_ALTO;j++) {
			p_pantalla->matriz[i][j] = 0;
		}
	}
}

void ReseteaLadrillos(tipo_pantalla *p_ladrillos) {
	//ponemos la matriz de ladrillos a cero
	int i, j = 0;

	for(i=0;i<MATRIZ_ANCHO;i++) {
		for(j=0;j<MATRIZ_ALTO;j++) {
			p_ladrillos->matriz[i][j] = 0;
		}
	}
}

void ReseteaFigura(tipo_figura *p_figura) {
	//igualamos la matriz a la primera figura y inicializamos los valores
	int i,j = 0;
	for (i=0 ; i < TAMANO_FIGURA ; i++){
		for (j=0 ; j < TAMANO_FIGURA ; j++){
			p_figura->matriz[i][j] = figs[0][i][j];
		}
	}
	p_figura->x = 0;//posicion es la 0,4
	p_figura->y = 4;
	p_figura->n = 1;//figura1
	p_figura->f = 0;//rotacion 0
}

void ReseteaResultado(int *p_n){
	p_n = 0;
}


/*void nuevaFigura(tipo_figura *p_figura)
 * en este metodo cambiamos de una figura a otra
 * actualizando el valor n que marca en que figura
 * nos encontramos en cada momento
 * */
void nuevaFigura (tipo_figura *p_figura){
	int i,j = 0;
	p_figura->x = 0;
	p_figura->y = 4;
	switch (p_figura->n){
	case (1):
		for (i=0 ; i < TAMANO_FIGURA ; i++){
			for (j=0 ; j< TAMANO_FIGURA ; j++){
				p_figura->matriz[i][j] = figs[p_figura->n*4][i][j];
			}
		}
		p_figura->n++;
		break;
	case (2):
		for (i=0 ; i < TAMANO_FIGURA ; i++){
			for (j=0 ; j< TAMANO_FIGURA ; j++){
				p_figura->matriz[i][j] =  figs[p_figura->n*4][i][j];
			}
		}
		p_figura->n++;
		break;
	case (3):
		for (i=0 ; i < TAMANO_FIGURA ; i++){
			for (j=0 ; j< TAMANO_FIGURA ; j++){
				p_figura->matriz[i][j] =  figs[p_figura->n*4][i][j];
			}
		}
		p_figura->n++;
		break;
	case (4):
		for (i=0 ; i < TAMANO_FIGURA ; i++){
			for (j=0 ; j< TAMANO_FIGURA ; j++){
				p_figura->matriz[i][j] =  figs[0][i][j];
			}
		}
		p_figura->n=1;
		break;
	}

}


/*void colocar(tipo_tetris *p_tetris):
 * este metodo se llama cuando la figura se choca
 * con los ladrillos y hay que colocarla en ellos.
 * ESte llama a otro metodo que añade la figura
 *
 * Comprueva que no haya ninguna fila con todas las
 * columnas ocupadas y si lo hay llama a un metodo
 * que lo rompe
 * */
void colocar (tipo_tetris *p_tetris){
	anadir(p_tetris);
	int i,j,cuenta = 0;
	for (j = 0; j< MATRIZ_ALTO ; j++){
		if (p_tetris->ladrillos.matriz[0][j] == 1){
			cuenta ++;
		}
	}
	if(cuenta == 7){//si la primera fila esta llena la ponemos entera a 0
		for (j = 0; j< MATRIZ_ALTO ; j++){
			p_tetris->ladrillos.matriz[0][j] = 0;
		}
	}
	cuenta = 0;
	for (i = 1; i< MATRIZ_ANCHO ; i ++){
		for (j = 0; j< MATRIZ_ALTO ; j++){
			if (p_tetris->ladrillos.matriz[i][j] == 1){
					cuenta ++;
			}
		}
		if (cuenta == 7){//si hay alguna fila entera a 0 llamamos al metodo que
			//la destruye
			romper(&p_tetris->ladrillos , i);
			p_tetris->n++;
		}
		cuenta=0;
	}
	nuevaFigura(&p_tetris->figura);//necesitamos una nueva figura

}


/*void añadir(tipo_tetris *p_tetris):
 * metodo encargado de añadir la figura actual
 * a la matriz de ladrillos
 * */
void anadir(tipo_tetris *p_tetris){
	int i, j = 0;

		for(i=0;i<TAMANO_FIGURA;i++) {
			for(j=0;j<TAMANO_FIGURA;j++) {
				if (( (p_tetris->figura.x-3+i >= 0) && (p_tetris->figura.x-3+i < MATRIZ_ANCHO) ) &&
						( (p_tetris->figura.y-3+j >= 0) && (p_tetris->figura.y-3+j < MATRIZ_ALTO) )){
					if (p_tetris->figura.matriz[i][j]==1){
						p_tetris->ladrillos.matriz[p_tetris->figura.x-3+i][p_tetris->figura.y-3+j] =p_tetris->figura.matriz[i][j];
					}

				}

			}
		}
}


/*void romper(tipo_pantalla *p_ladrillos, int h):
 * metodo que se encarga de destruir una fila entera
 * pasada como parametro
 * */
void romper(tipo_pantalla *p_ladrillos , int h){
	int i,j = 0;
	for (i=h ; i > 0 ; i--){//ponemos todas las filas superiores en una posicion debajo
		//asi nos aseguramos de que se rompe correctamente la fila
		for (j=0 ; j < TAMANO_FIGURA ; j++){
			p_ladrillos->matriz[i][j] =  p_ladrillos->matriz[i-1][j];
		}
	}
	for (j = 0; j< MATRIZ_ALTO ; j++){//la fila 0 se pone a 0
		p_ladrillos->matriz[0][j] = 0;
	}
}


void PintaMensajeInicialPantalla (tipo_pantalla *p_pantalla, tipo_pantalla *p_pantalla_inicial) {
	//pinta el mensaje inicial
	int i,j = 0;
	for(i=0;i<MATRIZ_ANCHO;i++) {
			for(j=0;j<MATRIZ_ALTO;j++) {
				p_pantalla->matriz[i][j] = p_pantalla_inicial->matriz[i][j];
			}
	    }
}

void PintaPantallaPorTerminal  (tipo_pantalla *p_pantalla) {
	//metodo que pinta la pantalla en el terminal
	int i, j=0;
	puts("[PANTALLA]\n");
	for(i=0;i<MATRIZ_ALTO;i++) {
		for(j=0;j<MATRIZ_ANCHO;j++) {
			printf("%d",p_pantalla->matriz[j][i]);
		}
		printf("\n");
	}
}

void PintaLadrillos(tipo_pantalla *p_ladrillos, tipo_pantalla *p_pantalla) {
	//metoodo que pinta los ladrillos en la matriz de pantalla
	int i, j = 0;
	for(i=0;i<MATRIZ_ANCHO;i++) {
		for(j=0;j<MATRIZ_ALTO;j++) {
			p_pantalla->matriz[i][j] = p_ladrillos->matriz[i][j];
		}
    }
}

void PintaFigura(tipo_figura *p_figura, tipo_pantalla *p_pantalla) {
	//metodo encargado de pintar la matrizx de figura correctamente en la matriz de pantlla
	int i, j = 0;

	for(i=0;i<TAMANO_FIGURA;i++) {
		for(j=0;j<TAMANO_FIGURA;j++) {
			if (( (p_figura->x-3+i >= 0) && (p_figura->x-3+i < MATRIZ_ANCHO) ) &&
					( (p_figura->y-3+j >= 0) && (p_figura->y-3+j < MATRIZ_ALTO) )){
				if (p_figura->matriz[i][j]==1){
					p_pantalla->matriz[p_figura->x-3+i][p_figura->y-3+j] = p_figura->matriz[i][j];
				}


			}

		}
	}
}

void ActualizaPantallaTetris(tipo_tetris* p_tetris) {

	ReseteaMatriz((tipo_pantalla*)(&(p_tetris->pantalla)));
	//pintamos antes los ladrillos que la figura
	PintaLadrillos(&(p_tetris->ladrillos), &(p_tetris->pantalla));
	PintaFigura(&(p_tetris->figura), &(p_tetris->pantalla));

}

void InicializaTetris(tipo_tetris *p_tetris) {

	static tipo_pantalla mensaje_inicial = { {
			//mensaje inicial
			{0,0,0,0,0,0,0},
			{0,0,0,1,0,0,0},
			{1,1,0,1,1,0,0},
			{1,1,0,0,1,1,0},
			{0,0,0,0,0,1,1},
			{0,0,0,0,0,1,1},
			{1,1,0,0,1,1,0},
			{1,1,0,1,1,0,0},
			{0,0,0,1,0,0,0},
			{0,0,0,0,0,0,0},
	} };
	ReseteaMatriz((tipo_pantalla*)(&(p_tetris->pantalla)));
	//reseteamos todo correctamente
	ReseteaLadrillos((tipo_pantalla*)(&(p_tetris->ladrillos)));
	ReseteaFigura((tipo_figura*)(&(p_tetris->figura)));
	ReseteaResultado(&p_tetris->n);

	PintaMensajeInicialPantalla(&p_tetris->pantalla, &mensaje_inicial);
}


/*int rotarTetris (tipo_tetris *p_tetris)
 * metodo que devuelve un 1 si no se puede rotar
 * y un 0 si se puede rotar correctamente
 * para comprobar si puede rotar el proceso consiste
 * en comprovar que ninguna parte de la figura se superpone
 * con los ladrillos ni se sale de la pantalla
 * */
int rotarTetris (tipo_tetris *p_tetris){
	int matriz_aux [TAMANO_FIGURA][TAMANO_FIGURA] ={
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
	};
	int i,j=0;
	//cambiamos de figura
	if (p_tetris->figura.f == 3){
		p_tetris->figura.f = 0;
	}else{
		p_tetris->figura.f++;
	}
	for(i=0;i<TAMANO_FIGURA;i++) {//ponemos en la matriz aux la nueva figura
		for(j=0;j<TAMANO_FIGURA;j++) {
			matriz_aux[i][j] = figs[((p_tetris->figura.n-1)*4) +p_tetris->figura.f][i][j];
		}
	}
	for(i=0;i<TAMANO_FIGURA;i++) {
		for(j=0;j<TAMANO_FIGURA;j++) {
			if (((p_tetris->ladrillos.matriz[p_tetris->figura.x-3+i][p_tetris->figura.y-3+j] == 1) && (matriz_aux[i][j] == 1)) || ((matriz_aux[i][j] == 1) && (p_tetris->figura.x +3 -i < 0)) ||((matriz_aux[i][j] == 1) && (p_tetris->figura.x +3 -i > 10)) || ((matriz_aux[i][j] == 1) && (p_tetris->figura.y +3 -j < 0)) ||((matriz_aux[i][j] == 1) && (p_tetris->figura.y +3 -j > 7)) ) {
				if (p_tetris->figura.f == 0){//si no se puede rotar volvemos a la figura anterior y devolvemos 1
					p_tetris->figura.f = 3;
				}else{
					p_tetris->figura.f--;
				}
				return 1;
			}
		}
	}

	for(i=0;i<TAMANO_FIGURA;i++) {//si se puede ponemos la nueva figura rotada y devolvemos un 0
		for(j=0;j<TAMANO_FIGURA;j++) {
			p_tetris->figura.matriz[i][j] = figs[((p_tetris->figura.n-1)*4) +p_tetris->figura.f][i][j];
		}
	}
	return 0;

}

