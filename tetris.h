/*
 * tetris.h
 *
 *  Created on: 14/4/2017
 *      Author: Carlos
 */

#ifndef TETRIS_H_
#define TETRIS_H_

#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h>

#define MATRIZ_ANCHO 	10
#define MATRIZ_ALTO 	7
#define TAMANO_FIGURA   4
#define NUMERO_FIGURA   7


typedef struct {
	int matriz[MATRIZ_ANCHO][MATRIZ_ALTO];
} tipo_pantalla;

typedef struct {
	int matriz[ TAMANO_FIGURA][ TAMANO_FIGURA];
	int x;
	int y;
	int n;
	int f;
	/*fig f1;
	fig f2;
	fig f3;
	fig f4;
	fig f5;
	fig f6;
	fig f7;*/
} tipo_figura;

typedef struct {
	int matriz1[TAMANO_FIGURA][TAMANO_FIGURA];
	int matriz2[TAMANO_FIGURA][TAMANO_FIGURA];
	int matriz3[TAMANO_FIGURA][TAMANO_FIGURA];
	int matriz4[TAMANO_FIGURA][TAMANO_FIGURA];
}fig;

typedef struct {
  tipo_pantalla ladrillos;
  tipo_pantalla pantalla;
  tipo_figura figura;
  int n;

} tipo_tetris;

void ReseteaMatriz(tipo_pantalla *p_pantalla);
void ReseteaLadrillos(tipo_pantalla *p_ladrillos);
void ReseteaFigura(tipo_figura *p_figura) ;
void nuevaFigura (tipo_figura *p_figura);
void colocar (tipo_tetris *p_tetris);
void anadir(tipo_tetris *p_tetris);
void romper(tipo_pantalla *p_ladrillos , int h);
int rotarTetris (tipo_tetris *p_tetris);
void ReseteaResultado(int *p_n);
void PintaMensajeInicialPantalla (tipo_pantalla *p_pantalla, tipo_pantalla *p_pantalla_inicial);
void PintaPantallaPorTerminal  (tipo_pantalla *p_pantalla);
void PintaLadrillos(tipo_pantalla *p_ladrillos, tipo_pantalla *p_pantalla);
void PintaFigura(tipo_figura *p_figura, tipo_pantalla *p_pantalla);
void ActualizaPantallaTetris(tipo_tetris* p_tetris) ;
void InicializaTetris(tipo_tetris *p_tetris);
void Rotar(tipo_tetris *p_tetris);
#endif /* TETRIS_H_ */
