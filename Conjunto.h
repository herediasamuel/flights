#ifndef _Conjunto_H_

///*** Marcos ***///
#define _Conjunto_H_
#define TRUE 1
#define FALSE 0
#define max 100

///*** Tipo ***///
typedef struct{
	int Con[max];
	int lon;
	
}Conjunto;

///***Prototipos de funciones***///

void cVa(Conjunto *A);
int cEv(Conjunto A);
Conjunto cIe(Conjunto A, int E);
Conjunto cEe(Conjunto A,int E);
int cPe(Conjunto A,int E);
void verC(Conjunto A);
Conjunto Union(Conjunto A,Conjunto E);

#endif


