#ifndef _Arcos_H_
#include <stdio.h>
///*** Marcos ***///
#define _Arcos_H_
#define TRUE 1
#define FALSE 0
#define max 100

///*** Tipo ***///
typedef struct{
	int v;
	int w;
	float Peso;
}Arco;
typedef struct{
	Arco Arc[max];
	int lon;
	int vert;
	
}Arcos;
///***Prototipos de funciones***///

void arcVacio(Arcos *A);
int arcsVac(Arcos A);
Arcos arcElim(Arcos A,Arco E);
int igual(Arco A,Arco E);
void ver(Arcos A);
void copiar(Arco *A, Arco E);
void copiarA(Arcos *A,Arcos E);
void vertA(Arcos *A);
Arcos inserArc(Arcos A, Arco E);
void extracion(int v[max],int w[max],Arcos A);
void inicio(int M[max][max]);
void verM(Arcos A,FILE *fy);
#endif



