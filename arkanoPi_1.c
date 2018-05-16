
#include "arkanoPi_1.h"
#include "fsm.h"


static /*volatile*/ tipo_juego juego;

//------------------------------------------------------
// FUNCIONES DE ACCION
//------------------------------------------------------
enum fsm_state {
	WAIT_START=0,
	WAIT_PUSH=1,
	WAIT_END=2,
};
int columna=0;
int debounceTime=DEBOUNCE_TIME;
static tmr_t* tmrt;
static tmr_t* tmrp;

int col[7] = {0,1,2,3,4,7,23};

volatile int flags = 0;

void delay_until (unsigned int next) {
	unsigned int now = millis();

	if (next > now) {
		delay (next - now);
	}
}
int CompruebaTeclaPulsada (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_TECLA);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaTeclaRotar (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_ROTAR);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaTeclaPelota (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_PELOTA);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaTeclaRaquetaIzquierda (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_RAQUETA_IZQUIERDA);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaTeclaRaquetaDerecha (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_RAQUETA_DERECHA);
	piUnlock (FLAGS_KEY);

	return result;
}
int CompruebaFinalJuego (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_FINAL_JUEGO);
	piUnlock (FLAGS_KEY);

	return result;
}


/* void InicializaJuego (fsm_t *fsm): funcion encargada de llevar a cabo
 la oportuna inicializaci髇 de toda variable o estructura de datos
 que resulte necesaria para el desarrollo del juego.*/
void InicializaJuego (fsm_t *fsm) {
	piLock (FLAGS_KEY);
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	piLock (STD_IO_BUFFER_KEY);
	ActualizaPantallaTetris(&juego.tetris);
	PintaPantallaPorTerminal(&juego.tetris.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);

}

/* void MueveRaquetaIzquierda (fsm_t *fsm):metodo encargado
 * de mover las figuras a la izquierda si es posible */
void MueveRaquetaIzquierda (fsm_t *fsm) {

	piLock (FLAGS_KEY);
	flags &= ~FLAG_RAQUETA_IZQUIERDA;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	int i,j = 0;
	for (i=0 ; i < TAMANO_FIGURA ; i++){
		for (j=0 ; j < TAMANO_FIGURA ; j++){
		if (((juego.tetris.ladrillos.matriz[juego.tetris.figura.x-3+i-1][juego.tetris.figura.y-3+j] == 1) && (juego.tetris.figura.matriz[i][j] == 1))|| ((juego.tetris.figura.y-3+j-1<0)  && (juego.tetris.figura.matriz[i][j] == 1))) {
			printf("no puedes moverte");
			//si alguna posicion se sale fuera del mapa o se choca contra los ladrillos
			//no deja moverse
			return;
		}
		}
	}
	juego.tetris.figura.y--;//movemos la figura
	piLock (STD_IO_BUFFER_KEY);
	ActualizaPantallaTetris(&juego.tetris);//actualizamos
	PintaPantallaPorTerminal(&juego.tetris.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);
}

/* void MueveRaquetaIzquierda (fsm_t *fsm):metodo encargado
 * de mover las figuras a la derecha si es posible */
void MueveRaquetaDerecha (fsm_t *fsm) {
	piLock (FLAGS_KEY);
	flags &= ~FLAG_RAQUETA_DERECHA;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	int i,j = 0;
	for (i=0 ; i < TAMANO_FIGURA ; i++){
		for (j=0 ; j < TAMANO_FIGURA ; j++){
		if (((juego.tetris.ladrillos.matriz[juego.tetris.figura.x-3+i+1][juego.tetris.figura.y-3+j] == 1) && (juego.tetris.figura.matriz[i][j] == 1))|| ((juego.tetris.figura.y-3+j+1>6) && (juego.tetris.figura.matriz[i][j] == 1))) {
			printf("no puedes moverte");
			//si alguna posicion se sale fuera del mapa o se choca contra los ladrillos
			//no deja moverse
			return;
		}
		}
	}
	juego.tetris.figura.y++;//movemos la figura
	piLock (STD_IO_BUFFER_KEY);
	ActualizaPantallaTetris(&juego.tetris);//actualizamos
	PintaPantallaPorTerminal(&juego.tetris.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);
}

/* void MovimientoPelota (fsm_t *fsm): funcion encargada
 * de mover la figura hacia abajo si se puede
 * se debe asegurar que no se choque contra nada
 * de los ladrillos.*/
void MovimientoPelota (fsm_t *fsm) {
	// A completar por el alumno...
	piLock (FLAGS_KEY);
	flags &= ~FLAG_PELOTA;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	if(juego.tetris.figura.x == 9){//si esta en la ultima fila se choca contra el suelo
		printf("no puedes moverte");
		colocar(&juego.tetris);//colocamos
		digitalWrite(24,(juego.tetris.figura.n-1) & 0x01);//sacamos por los pines de figura la figura nueva
		digitalWrite(25,(juego.tetris.figura.n-1) & 0x02);
	}
	int i,j = 0;
	for (i=0 ; i < TAMANO_FIGURA ; i++){
		for (j=0 ; j < TAMANO_FIGURA ; j++){
		if ((juego.tetris.ladrillos.matriz[juego.tetris.figura.x-3+i+1][juego.tetris.figura.y-3+j] == 1) && (juego.tetris.figura.matriz[i][j] == 1)) {
			//si nos chocamos contra los ladrillos
			printf("no puedes moverte");
			colocar(&juego.tetris);//colocamos la figura
			digitalWrite(24,(juego.tetris.figura.n-1) & 0x01);//sacamos por los pines de figura la figura nueva
			digitalWrite(25,(juego.tetris.figura.n-1) & 0x02);
			for (i = 1; i< TAMANO_FIGURA ; i ++){
				for (j = 0; j< TAMANO_FIGURA ; j++){
					if((juego.tetris.figura.matriz[i][j] == 1)&&(juego.tetris.ladrillos.matriz[juego.tetris.figura.x-3+i][juego.tetris.figura.y-3+j] == 1)){
						piLock (FLAGS_KEY);// si la nueva figura no entra llamamos a final juego
						flags |= FLAG_FINAL_JUEGO;
						piUnlock (FLAGS_KEY);
					}

				}
			}
			}
		}
	}
	juego.tetris.figura.x++;//bajamos la figura
	piLock (STD_IO_BUFFER_KEY);
	ActualizaPantallaTetris(&juego.tetris);//actualizamos
	PintaPantallaPorTerminal(&juego.tetris.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);
}


/*void rotar (fsm_t *fsm):
 * Metodo que se encarga de rotar las figuras cuando
 * se indica */
void rotar (fsm_t *fsm){
	piLock (FLAGS_KEY);
	flags &= ~FLAG_ROTAR;
	piUnlock (FLAGS_KEY);
	int r = rotarTetris(&juego.tetris);//metodo que realmente rota
	piLock (STD_IO_BUFFER_KEY);
	if (r == 0){//si es cero se puede rotar y se actualza pantalla
		printf("roto");
		ActualizaPantallaTetris(&juego.tetris);
		PintaPantallaPorTerminal(&juego.tetris.pantalla);
	}else{
		printf("no roto");//si no no se rota
	}
	piUnlock (STD_IO_BUFFER_KEY);

}

/* void FinalJuego (fsm_t *fsm): funci贸n encargada de mostrar en la ventana de
* terminal los mensajes necesarios para informar acerca del resultado del juego.*/
void FinalJuego (fsm_t *fsm) {
	// A completar por el alumno...
	piLock (FLAGS_KEY);
	flags &= ~FLAG_FINAL_JUEGO;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	piLock (STD_IO_BUFFER_KEY);
	printf("PERDISTE: %d PUNTOS", juego.tetris.n);
	piUnlock (STD_IO_BUFFER_KEY);
}

/*void ReseteaJuego (void): funci贸n encargada de llevar a cabo la
* reinicializaci贸n de cuantas variables o estructuras resulten
* necesarias para dar comienzo a una nueva partida.*/
void ReseteaJuego (fsm_t *fsm) {
	piLock (FLAGS_KEY);
	flags &= ~FLAG_FINAL_JUEGO;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	InicializaTetris(&juego.tetris);
	piLock (STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(&juego.tetris.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);
	digitalWrite(24,(juego.tetris.figura.n-1) & 0x01);//enviamos la primera figura a la otra raspberry
	digitalWrite(25,(juego.tetris.figura.n-1)& 0x02);

}

//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------

/* int systemSetup (void): procedimiento de configuracion del sistema.
* configura el uso de posibles librerias ,
* configurar las interrupciones externas asociadas a los pines GPIO,
* configurar las interrupciones peri贸dicas y sus correspondientes temporizadores,
* crear, si fuese necesario, los threads adicionales que pueda requerir el sistema*/
int systemSetup (void) {

	wiringPiSetupGpio();
	//ponemos a 0 la variable flags
	piLock (FLAGS_KEY);
	flags = 0;
	piUnlock (FLAGS_KEY);
	//iniciamos los timers
	tmrt = tmr_new (refrescar);
	tmrp = tmr_new (flagPelota);
	tmr_startms (tmrt, 1);
	tmr_startms (tmrp, 1000);
	//filas
	pinMode(0,OUTPUT);
	pinMode(1,OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(7,OUTPUT);
	pinMode(23,OUTPUT);
	//columnas
	pinMode(22,OUTPUT);
	pinMode(18,OUTPUT);
	pinMode(17,OUTPUT);
	pinMode(14,OUTPUT);
	pinMode(24,OUTPUT);
	pinMode(25,OUTPUT);
	//botones
	pinMode (GPIO_BUTTONDER, INPUT);
	pinMode (GPIO_BUTTONIZQ, INPUT);
	wiringPiISR (GPIO_BUTTONDER, INT_EDGE_FALLING, boton_izquierda);
	wiringPiISR (GPIO_BUTTONIZQ, INT_EDGE_FALLING, boton_derecha);
	wiringPiISR (GPIO_BUTTONROTAR, INT_EDGE_FALLING, boton_rotar);

	return 1;

}

/*static void flagPelota (union sigval value)
 * aqui se activa el flag del snake cada segundo
 */
static void flagPelota (union sigval value){
	piLock (FLAGS_KEY);
	flags |=FLAG_PELOTA;//flag que activa el movimiento pelota
	piUnlock (FLAGS_KEY);
	tmr_startms (tmrp, 500);
}
void boton_izquierda(void){
	if (millis () < debounceTime) {
	debounceTime = millis () + DEBOUNCE_TIME ;
	return;
	}
	piLock (FLAGS_KEY);
	flags |=FLAG_RAQUETA_IZQUIERDA;
	flags |= FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	while (digitalRead (GPIO_BUTTONIZQ) == HIGH) {
	delay (1) ;
	}
	debounceTime = millis () + DEBOUNCE_TIME ;

}
void boton_derecha(void){
	if (millis () < debounceTime) {
		debounceTime = millis () + DEBOUNCE_TIME ;
		return;
	}
	piLock (FLAGS_KEY);
	flags |=FLAG_RAQUETA_DERECHA;
	flags |= FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	while (digitalRead (GPIO_BUTTONDER) == HIGH) {
		delay (1) ;
	}
	debounceTime = millis () + DEBOUNCE_TIME ;

}

void boton_rotar(void){
	if (millis () < debounceTime) {
		debounceTime = millis () + DEBOUNCE_TIME ;
		return;
	}
	piLock (FLAGS_KEY);
	flags |=FLAG_ROTAR;
	piUnlock (FLAGS_KEY);
	while (digitalRead (GPIO_BUTTONDER) == HIGH) {
		delay (1) ;
	}
	debounceTime = millis () + DEBOUNCE_TIME ;
}




static void  refrescar(union sigval value){


	int i;
	int c= 9 - (columna%10);

	for(i=0;i<7;i++){
		if(juego.tetris.pantalla.matriz[c][i] == 1){
			digitalWrite(col[i], LOW);
		}else{
			digitalWrite(col[i], HIGH);
		}
	}
	//col
	digitalWrite(14,c & 0x01);
	digitalWrite(17,c & 0x02);
	digitalWrite(18,c & 0x04);
	digitalWrite(22,c & 0x08);
	tmr_startms (tmrt, 1);
	columna++;
}

int main () {
	unsigned int next;

	fsm_trans_t tabla_juego[] = {
			{ WAIT_START,   CompruebaTeclaPulsada,  WAIT_PUSH, InicializaJuego},
			{ WAIT_PUSH,   CompruebaTeclaRaquetaIzquierda,  WAIT_PUSH, MueveRaquetaIzquierda},
			{ WAIT_PUSH,   CompruebaTeclaPelota,  WAIT_PUSH, MovimientoPelota},
			{ WAIT_PUSH,   CompruebaTeclaRaquetaDerecha,  WAIT_PUSH, MueveRaquetaDerecha },
			{ WAIT_PUSH,   CompruebaTeclaRotar,  WAIT_PUSH, rotar },
			{ WAIT_PUSH,   CompruebaFinalJuego,  WAIT_END, FinalJuego},
			{ WAIT_END,   CompruebaTeclaPulsada,  WAIT_START, ReseteaJuego},
			{ -1, NULL, -1, NULL },
	};


	fsm_t* juego_fsm = fsm_new (WAIT_START, tabla_juego, NULL);
	// Configuracion e inicializacion del sistema

	systemSetup();
	ReseteaJuego(juego_fsm);
	/*fsm_setup (juego_fsm);*/

	next = millis();
	while (1) {
		fsm_fire (juego_fsm);
		next += CLK_MS;
		delay_until (next);
	}

	fsm_destroy (juego_fsm);


}
