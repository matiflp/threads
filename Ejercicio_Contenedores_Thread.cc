/*
 * Ejercicio_Contenedores_Thread.cc
 *
 *  Created on: 29/04/2019
 *      Author: Matias - Jesus
 */

#include <iostream>
#include <vector>
#include <pthread.h>
#include <cmath>
#include "Logs.h"
#include "MiClase.h"

using namespace std;

void *matrix_Function( void *ptr );

struct Datos
{
typename vector < vector<double> >::iterator filai;
typename vector < vector<double> >::iterator filad;
};

int main()
{
	 vector < vector<double> > vector1(20000, vector<double>(20000,0));//Crea el vector.
	 unsigned int cantThread = 0;
	 unsigned int n = 0;

	 //Carga de Estrucutura
	 cout << "Ingresar la cantidad de thread: ";
	 cin >> cantThread;

	 Datos datos_hilo[cantThread];
	 pthread_t thread[cantThread];
	 n = ceil((float)20000 / cantThread);
	 MiClase miclase;

	 // Intanciación de los iteradores
	 if(cantThread==0)
	 {
		 datos_hilo[0].filai = vector1.begin();
		 datos_hilo[0].filad = vector1.end();
		 matrix_Function(datos_hilo);
	 }

	 for(unsigned int i=0 ; i < cantThread ; i++)
	 {
		 datos_hilo[i].filai=(vector1.begin()+(n*i));
		 datos_hilo[i].filad=(vector1.begin()+(n*(i+1)));
		 if((n*(i+1)) > vector1.size())
		 {
			 datos_hilo[i].filad=((vector1.end()));
		 }
	 }

	 // Creacion de los hilos.
	 for(unsigned int i=0 ; i < cantThread ; i++)
	 {
		 if((pthread_create( &thread[i], NULL, &matrix_Function, (void*) (datos_hilo+i))))
		 {
			 printf("Thread creation failed: \n");
		 }
	 }

	 for(unsigned int i=0 ; i < cantThread ; i++)
	 {
		 pthread_join( thread[i], NULL);
	 }

	 LOGS( "termino con cant de hilos: "<< cantThread);

	 for(unsigned int i=0 ; i < cantThread ; i++)
	 {
	 	pthread_exit( thread+i);
	 }

	 return 0;
}

void *matrix_Function( void *ptr )
{
	Datos *datosh;
	datosh = (Datos*) ptr;
	typename std::vector<vector<double>>::iterator ifila = datosh[0].filai;
	for( ; ifila != datosh[0].filad; ifila++ )
	{
		typename std::vector<double>::iterator icol = ifila->begin();
		for(;icol != ifila->end() ;icol++)
		{
			// Se realiza la siguiente operacion sin sentido practico con el objetivo de observar
			// una sobrecarga en el procesador
			for(double i = 0 ; i<=1 ; i+=0.1){
			(*icol) =  (*icol) + pow(i,2) + sqrt(tan((89.99999999999999 * M_PI) / 180) * pow(222.015267415489562223,16) +
					  pow(115.78536785924458129,16)* exp(153.26545865822325658) *
					  log(pow(333.36259632145974,30) / pow(20.23569874521283,10)));
			}
		}
	}
}
