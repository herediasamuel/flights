#include<stdio.h>
//#include<string.h>
#include "Conjunto.h"

///Vacia el conjunto///
void cVa(Conjunto *A)
{
	A->lon=0;
}
///Consulta si el conjunto es Vacio///
int cEv(Conjunto A)
{
	if (A.lon==0)
	{
		return(TRUE);
	}else{
		return(FALSE);
	}
}
///Verifica si un elemento pertenece al conjunto///
int cPe(Conjunto A,int E)
{
	int i,m;
	m=A.lon;
	if(m==0)
	{
		return(FALSE);
	}else{
		for(i=0;i<m;i++)
		{
			if(A.Con[i]==E)
			{
				return(TRUE);
			}
		}
	}
	return(FALSE);
}
///Inserta un Elemento al conjunto///
Conjunto cIe(Conjunto A, int E)
{
	int i;
	i=A.lon;
	A.Con[i]=E;
	A.lon=A.lon+1;
	return(A);
}
///Elimina un elemento del Conjunto///
Conjunto cEe(Conjunto A,int E)
{
	int i,m;
	i=0;
	m=200;//se le asigna un valor fuera del rango del Conjunto
	while((i<A.lon)&&(m==200))
	{
		if(A.Con[i]==E)
		{
			m=i;
			for(i=m;i<A.lon;i++)
			{
				A.Con[i]=A.Con[i+1];
			}
		}
	}
	return (A);
}
///PARA MOSTRAR POR PANTALLA LOS CONJUNTOS CON SUS ELEMENTOS
void verC(Conjunto A)
{
	int i;
	if(A.lon==0)
	{
		printf("VACIO\n");
	}else{
		printf("(");
		for(i=0;i<A.lon;i++)
		{
			printf("%d ",A.Con[i]);
			
			//printf("COnjunto: %d ",A.Con[i]);
		}
		//printf("LON:%d",A.lon);
		printf(")");
		printf("\n");
	}
}
///PERMITE UNIR ELEMENTOS A UN CONJUNTO AL MISMO TIEMPO QUE VALIDA QUE NO SE REPITAN
Conjunto Union(Conjunto A,Conjunto E)
{
	Conjunto Aux;
	int i,n,m;
	n=A.lon;
	m=E.lon;
	cVa(&Aux);
	if(n==0)
	{
		for(i=0;i<m;i++)
		{
			Aux=cIe(Aux,E.Con[i]);
		}
	}else{
		for(i=0;i<n;i++)
		{
			Aux=cIe(Aux,A.Con[i]);
		}
		for(i=0;i<m;i++)
		{
			
			if(Aux.Con[i]!=E.Con[i])
			{
				Aux=cIe(Aux,E.Con[i]);
			}
		}
	}
	return(Aux);
}
	
