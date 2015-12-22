#include <stdio.h>
#include <math.h>
#include <time.h>

/************************************************/
/*	Perceptron monocapa de 1 neurona	*/
/*	Para funciones linealmente		*/
/*	separables. Robert A. Vazeux 2015	*/
/************************************************/

#define RAND_MAX 		3276700000	// maximo valor aleatorio
#define MAX_ETAPAS		100		// numero de etapas de aprendizaje (generacion)
#define MAX_MUESTRAS		4		// numero de muestras
#define TASA_APRENDIZAJE	0.6		// velocidad a la que aprende la red 

/* Estructura del perceptron (neurona de dos entradas) */
typedef struct {

	float w0;		// Peso sináptico 1
	float w1;		// Peso sináptico 2
	float u;		// umbral (grado de inhibición)

} perceptron_t;

/* Estructura de una muestra */
typedef struct {

	unsigned char x0;	// Entrada 1
	unsigned char x1;	// Entrada 2
	unsigned char s;	// Salida esperada

} muestra_t;

void init_muestrasOR(muestra_t *);
void init_muestrasAND(muestra_t *);
void init_perceptron(void);
void aprender(muestra_t *);
float sigmoide(float x);
float transf(float x);
float error(float a, float b);
float randomFloat();

perceptron_t neurona;


int main() {

	muestra_t muestras[MAX_MUESTRAS];	// set de muestras
	init_muestrasAND(muestras);		// Inicializa el set de muestras
	init_perceptron();			// Inicializamos la neurona con pesos aleatorios
	aprender(muestras);

	return 0;

}

/* Inicializamos las muestras para el caso OR */
void init_muestrasOR(muestra_t * muestras) {

	muestras[0].x0	= 0;
	muestras[0].x1	= 0;
	muestras[0].s	= muestras[0].x0 | muestras[0].x1;	

	muestras[1].x0	= 0;
	muestras[1].x1	= 1;
	muestras[1].s	= muestras[1].x0 | muestras[1].x1;

	muestras[2].x0	= 1;
	muestras[2].x1	= 0;
	muestras[2].s	= muestras[2].x0 | muestras[2].x1;

	muestras[3].x0	= 1;
	muestras[3].x1	= 1;
	muestras[3].s	= muestras[3].x0 | muestras[3].x1;

}

/* Inicializamos las muestras para el caso AND */
void init_muestrasAND(muestra_t * muestras) {

	muestras[0].x0	= 0;
	muestras[0].x1	= 0;
	muestras[0].s	= muestras[0].x0 & muestras[0].x1;	

	muestras[1].x0	= 0;
	muestras[1].x1	= 1;
	muestras[1].s	= muestras[1].x0 & muestras[1].x1;

	muestras[2].x0	= 1;
	muestras[2].x1	= 0;
	muestras[2].s	= muestras[2].x0 & muestras[2].x1;

	muestras[3].x0	= 1;
	muestras[3].x1	= 1;
	muestras[3].s	= muestras[3].x0 & muestras[3].x1;

}

void init_perceptron(void) {

	srand(time(NULL));

	neurona.w0 	= randomFloat();
	neurona.w1 	= randomFloat();
	neurona.u	= randomFloat();

	printf("Pesos: w0 = %f, w1 = %f, u = %f \n",neurona.w0, neurona.w1, neurona.u);

}

void aprender(muestra_t * muestras) {

	int e;		// Etapa
	int m;		// Muestra
	float y;	// Salida

	for(e = 0; e < MAX_ETAPAS; e++) {
		
		printf("[ETAPA %d]\n", e+1);
		for(m = 0; m < MAX_MUESTRAS; m++) {
			
			y = sigmoide(muestras[m].x0 * neurona.w0 + muestras[m].x1 * neurona.w1 - neurona.u);
			//BACK PROPAGATION (regla de aprendizaje)
			neurona.w0 += TASA_APRENDIZAJE * error(y, muestras[m].s) * muestras[m].x0;
			neurona.w1 += TASA_APRENDIZAJE * error(y, muestras[m].s) * muestras[m].x1;
			neurona.u  += -TASA_APRENDIZAJE * error(y, muestras[m].s);
			printf("\t[MUESTRA %d] y = %f s = %d \n", m+1, y, muestras[m].s);
		}
	}

}


/* Función sigmoide como función de transferencia (analogica), se podría usar la función signo o la de Heaviside en su lugar (discretas) */
float sigmoide(float x){

	return (1 / (1 + exp((double) -x )));
}

float error(float a, float b) {
	
	return (b - a);
}

/* Devuelve un random float entre 0 y 1 */
float randomFloat() 
{
    return (float)(rand()) / RAND_MAX;
}
