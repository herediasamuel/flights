#include<stdio.h>
#include<string.h>
#include "Arcos.h"
///Inicializa las variables de los Arcos con cero es Decir Vacio 
void arcVacio(Arcos *A)
{
	A->lon=0;
	A->vert=0;
}
///Verifica si un conjunto de arcos esta vacio
int arcsVac(Arcos A)
{
	if (A.lon==0)
	{
		return(TRUE);
	}else{
		return(FALSE);
	}
}
/// Verifica la igualdad entre dos arcos
int igual(Arco A,Arco E)
{
	if(((A.v==E.v)&&(A.w==E.w))||((A.v==E.w)&&(A.w==E.v)))
	{
		return(TRUE);
	}else{
		return(FALSE);
	}
}
///Esta funcion Evalua la Cantidad de vertices depues de Agregar un Arco
void vertA(Arcos *A)
{
	int ver[30],i,j,x,suma;
	suma=0;
	for(i=0;i<30;i++)
	{
		ver[i]=0;
	}
	for(i=0;i<A->lon;i++)
	{
		j=A->Arc[i].v;
		x=A->Arc[i].w;
		ver[j-1]=1;
		ver[x-1]=1;
	}
	for(i=0;i<20;i++)
	{
		suma=ver[i]+suma;
	}
	A->vert=suma;
}
///Inserta un Arco al Conjunto de Arcos	
Arcos inserArc(Arcos A, Arco E)
{
	int i;
	i=A.lon;
	A.Arc[i].v=E.v;
	A.Arc[i].w=E.w;
	A.Arc[i].Peso=E.Peso;
	A.lon=A.lon+1;
	vertA(&A);
	return (A);
}
///Elimina un Arco del conjunto de Arcos
Arcos arcElim(Arcos A,Arco E)
{
	int i,m;
	i=0;
	for(i=0;i<A.lon;i++)
	{
		if(igual(A.Arc[i],E)==TRUE)
		{
			m=i;
		}
	}
	for(i=m;i<A.lon-1;i++)
	{
		A.Arc[i].v=A.Arc[i+1].v;
		A.Arc[i].w=A.Arc[i+1].w;
		A.Arc[i].Peso=A.Arc[i+1].Peso;	
	}
	A.lon=A.lon-1;
	return(A);
}
///Mostrar por Pantalla Los Arcos del Grafo			
void ver(Arcos A)
{
	int i;
	if(A.lon==0)
	{
		printf("Conjunto de Arcos Vacio\n");
	}else{
		
			for(i=0;i<A.lon;i++)
			{
				printf(" |%d| -----%0.2f---- |%d|\n",A.Arc[i].v,A.Arc[i].Peso,A.Arc[i].w);
			}
			printf("LON:%d  VERT:%d\n",A.lon,A.vert);
	}
}
///Copia la informacion de una Arco a otro, Sobrescribiendo la informacionde a quel sobre quien se copie
void copiar(Arco *A, Arco E)
{
	A->v=E.v;
	A->w=E.w;
	A->Peso=E.Peso;
}
///Copia la informacion unos Arcos a otros, Sobrescribiendo la informacionde a quel sobre quien se copia
void copiarA(Arcos *A,Arcos E)
{
	int i,n;
	n=E.lon;
	for(i=0;i<n;i++)
	{
		copiar(&A->Arc[i],E.Arc[i]);
	}
	A->vert=E.vert;
	A->lon=E.lon;
}
///Extrae los conjuntos de los vertices tanto de llegada como de salida
void extracion(int v[max],int w[max],Arcos A)
{
	int i;
	for(i=0;i<A.lon;i++)
	{
		v[i]=A.Arc[i].v;
		w[i]=A.Arc[i].w;
	}
}
///inicializa la matriz de verM en 0
void inicio(int M[max][max])
{
	int i,j;
	for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			M[i][j]=0;
		}
	}
}
///SE observan los Arcos desde una matriz
void verM(Arcos A,FILE *fy)
{
	int matriz[max][max];
	int j,i;
	inicio(matriz);

		for(j=0;j<A.lon;j++)
		{
			matriz[A.Arc[j].v][A.Arc[j].w]=1;
			matriz[A.Arc[j].w][A.Arc[j].v]=1;
		}
		for(i=1;i<A.vert+1;i++)
		{
			for(j=1;j<A.vert+1;j++)
			{
				printf("%d ",matriz[i][j]);
				fprintf(fy,"%d ",matriz[i][j]);
			}
			printf("\n");
			fprintf(fy,"\n");
		}
}
