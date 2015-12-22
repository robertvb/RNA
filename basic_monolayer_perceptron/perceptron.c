#include <stdio.h>
#include <math.h>

/************************************************/
/*	Perceptron monocapa de 1 neurona	*/
/*	Para funciones linealmente		*/
/*	separables. Robert A. Vazeux 2015	*/
/************************************************/

#define MAX_ETAPAS		10
#define MAX_MUESTRAS		4
#define TASA_APRENDIZAJE	10
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

void init_muestras(muestra_t *);
void init_perceptron(void);
void aprender(muestra_t *);
float sigmoide(float x);
float transf(float x);
float error(float a, float b);

perceptron_t neurona;


int main() {

	muestra_t muestras[MAX_MUESTRAS];	// set de muestras
	init_muestras(muestras);		// Inicializa el set de muestras
	init_perceptron();			// Inicializamos la neurona
	aprender(muestras);

	return 0;

}

/* Inicializamos las muestras para el caso OR */
void init_muestras(muestra_t * muestras) {

	muestras[0].x0	= 0;
	muestras[0].x1	= 0;
	muestras[0].s	= 0;	

	muestras[1].x0	= 0;
	muestras[1].x1	= 1;
	muestras[1].s	= 1;

	muestras[2].x0	= 1;
	muestras[2].x1	= 0;
	muestras[2].s	= 1;

	muestras[3].x0	= 1;
	muestras[3].x1	= 1;
	muestras[3].s	= 1;

}

void init_perceptron(void) {

	neurona.w0 	= 0;
	neurona.w1 	= 0;
	neurona.u	= 0;

}

void aprender(muestra_t * muestras) {

	int e;		// Etapa
	int m;		// Muestra
	float y;	// Salida

	for(e = 0; e < MAX_ETAPAS; e++) {
		
		printf("[ETAPA %d]\n", e+1);
		for(m = 0; m < MAX_MUESTRAS; m++) {
			
			y = sigmoide(muestras[m].x0 * neurona.w0 + muestras[m].x1 * neurona.w1 - neurona.u);
			neurona.w0 += TASA_APRENDIZAJE * error(y, muestras[m].s) * muestras[m].x0;
			neurona.w1 += TASA_APRENDIZAJE * error(y, muestras[m].s) * muestras[m].x1;
			neurona.u  += -TASA_APRENDIZAJE * error(y, muestras[m].s);
			printf("\t[MUESTRA %d] y = %f s = %d \n", m+1, y, muestras[m].s);
		}
	}

}


/* Función sigmoide como función de transferencia, se podría usar la función signo o la de Heaviside en su lugar */
float sigmoide(float x){

	return (1 / (1 + exp((double) -x )));
}

float error(float a, float b) {
	
	return (b - a);
}

