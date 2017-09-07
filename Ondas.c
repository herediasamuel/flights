///ALGORITMO ONDAS
/*
Algoritmo CaminoMasCortoX_Y
	constante
		N ← 100;	// N es la cantidad máxima de vértices que puede manejar el alg.
	tipo
		matrizAdy = arreglo[1..N][1..N] de entero;	// Tipo para matriz de adyacencia
		matrizOndas = arreglo[0..N-1] de conjuntos; 	// Tipo para almacenar las ondas 
		vectorVertices = arreglo[1..N] de entero; 	// Tipo para almacenar las marcas de los vértices 
		vertice = entero;			// Tipo para los vértices
	variable
		Ady : matrizAdy;			// Contendrá la matriz de adyacencia del grafo
		Ondas : matrizOndas;  	// Cada posición del arreglo tendrá un conjunto, este conj. contendrá los
				// vértices q pertenecen a la onda identificada por el índice d esa casilla
		MarcasVert : vectorVertices;  // Almacena la marca que recibe cada vértice al ser visitado en las ondas.
		Camino : arreglo[0..N-1] de vertice;	// Almacenará el camino buscado entre X y Y (en el caso d q exista).
		ExisteCam : logico;	
		X, Y : vertice;	
		n, i : entero;	
inicio 
	lecturas_iniciales(n, Ady)				// lee el número de vértices del grafo: n y lee los arcos
	leer( X, Y) 				// lee los vértices: origen X y destino Y 
	inicializar(marcasVert)				// cada casilla se inicializa con -1 
	Busqueda_hacia_adelante(X, Y, marcasVert, Ady, Ondas, i, ExisteCam)
	si (ExisteCam) entonces 			// Tiene sentido construir el camino
		Construccion_hacia_atras(X, Y, Ady, Ondas, i, Camino)
	 sino
		escribir(“No existe camino entre ”, X, “ y ”, Y)
	fsi
Fin  			// fin CaminoMasCortoX_Y //
*/
///BUSQUEDA HACIA ADELANTE
/*
procedimiento Busqueda_hacia_adelante( X, Y: vertice;  var MarcasVert : vectorVertices;  Ady: matrizAdy;
							var Ondas: matrizOndas; var i: entero;  var ExisteCam: logico)
inicio 
	variable
	w : vertice;
	Ondas[ 0 ] ← { X } 	// Inicializa colocando el vértice origen X en la onda 0, el epicentro
	marcar_vertices( Ondas[0], 0, MarcasVert ) 	// marca al vértice X como visitado con el valor 0
	Ondas[ 1] ← Conjunto_adyacentes_no_marcados( X, Ady, MarcasVert ) // Inicializa la onda 1, colocando los adyacentes de X
	i ← 1 					// Inicializa el índice de ondas en 1, que es la onda actual.
	si (Ondas[1] ≠ vacio) entonces		// verifica si existen vértices en la onda 1
		marcar_vertices( Ondas[1], 1, MarcasVert ) 	// marca los vértices de la onda 1 como visitados con el valor 1
		mientras ( Y no pertenece Ondas[ i ] y Ondas[ i ] ≠ vacio ) hace  // mientras no haya conseguido a Y y todavía queden adyacentes 
			Ondas[ i + 1] ← vacio
			para  cada vértice w pertenece Ondas[ i ] hacer
				Ondas[ i + 1] ← Ondas[ i + 1]  UNION Conjunto_adyacentes_no_marcados( w, Ady, MarcasVert )
				si (Ondas[ i + 1] ≠ vacio) entonces
					marcar_vertices( Ondas[ i + 1], i + 1, MarcasVert )
				fsi
			fpara
			i ← i + 1
		fmientras
	fsi

finProcedimiento  // fin procedimiento Busqueda_hacia_adelante //
*/
///CONSTRUCCION HACIA ATRAS
/*
procedimiento Construccion_hacia_atras( X, Y: vertice;  Ady: matrizAdy;  Ondas: matrizOndas;  i: entero;
								var Camino: arreglo[0..N-1] de vertice)
inicio 

	variable
		k : entero;

	Camino[ i ] ← Y 			// Coloca el vértice destino Y, en la posición de la onda i
	para k ← i [decrementando] hasta 1		// realiza el proceso de devolverse, construcción hacia atrás
		Camino[ k – 1] ← Adyacente_onda_anterior( Camino[ k ], Ady, Ondas)
	fpara
	escribir( “El camino más corto, en cantidad de arcos, entre ”, X , “ y ”, Y ,“ es: ” ) 	
	para k ← 0 [incrementando] hasta i		// Muestra los vértices del camino, en el orden correcto 
		escribir(Camino[ k ] )
	fpara

finProcedimiento  // fin procedimiento Construccion_hacia_atras //
*/

#include <stdio.h>
#include "Conjunto.h"
#include "Arcos.h"

Arcos lecturas_iniciales();
void inicializar(int m[max]);
void marcar_vertices(Conjunto *Ondas,int n,int MV[max]);
int Adyacente_onda_anterior(int C,Arcos A,Conjunto Ondas);
Conjunto Conjunto_adyacentes_no_marcados(int X,Arcos A,int MV[max]);
void Construccion_hacia_atras(int X,int Y,Arcos A,Conjunto Ondas[max],int i,int Cam[max]);
void Busqueda_hacia_adelante(int X,int Y,int MarcasVert[max],Arcos A,Conjunto Ondas[max],int *i,int *ExisteCam);
int main()
{
		
		Arcos A;
		Conjunto matrizOndas[max]; 
		int marcasVert[max]; 
		int Camino[max];
		int ExisteCam;//logico	
		int X,Y,n,i;// vertice;	entero;	
		A=lecturas_iniciales();
		printf("Vertice Origen:\n");
		scanf("%d",&X);
		printf("Vertice Llegada:\n");
		scanf("%d",&Y);
		inicializar(marcasVert);
		Busqueda_hacia_adelante(X,Y,marcasVert,A,matrizOndas,&i,&ExisteCam);
		if(ExisteCam==TRUE)
		{
			Construccion_hacia_atras(X,Y,A,matrizOndas,i,Camino);
		}else{
			printf("No existe camino entre: %d y %d \n",X,Y);
		}
		
return 0;
}


Arcos lecturas_iniciales()		
{
	int i,j;
	Arcos A;
	arcVacio(&A);
	printf("Ingrese la Cantidad de Vertices\n");
	scanf("%d",&A.vert);
	printf("Ingrese la Cantidad de Arcos\n");
	scanf("%d",&A.lon);
	
	for(i=0;i<A.lon;i++)
	{
		printf("Ingrese v:\n");
		scanf("%d",&A.Arc[i].v);	
		printf("Ingrese w:\n");
		scanf("%d",&A.Arc[i].w);
		//printf("Ingrese Peso:\n");
		//scanf("%f",&A.Arc[i].Peso);
	}

	return(A);
}

void inicializar(int m[max])
{
	int i;
	
	for(i=0;i<max;i++)
	{
		m[i]=-1;
	}
}

void marcar_vertices(Conjunto *Ondas,int n,int MV[max])
{
	int i;
	i=Ondas->lon;
	if(i==0)
	{
		MV[Ondas->Con[0]]=n;
	}else{
		for(i=0;i<Ondas->lon;i++)
		{
			MV[Ondas->Con[i]]=n;
		}
	}
}
Conjunto Conjunto_adyacentes_no_marcados(int X,Arcos A,int MV[max])
{
	int i;
	Conjunto C;
	cVa(&C);
	//printf("Dentro de conjuntos Adyacentes\n");
	//ver(A);
	for(i=0;i<A.lon;i++)
	{
		
		if((A.Arc[i].v==X)&&(MV[A.Arc[i].w]==-1))
		{
			C=cIe(C,A.Arc[i].w);
		}else{
			if((A.Arc[i].w==X)&&(MV[A.Arc[i].v]==-1))
			{
				C=cIe(C,A.Arc[i].v);
			}
		}
	}
	return (C);
}

int pertenece(int Y,Conjunto C)
{
	int i;
	for(i=0;i<C.lon;i++)
	{
		if(Y==C.Con[i])
		{
			//printf("retorne verdad");
			return(TRUE);
		}
	}
	//printf("retorne Falso\n");
	return(FALSE);
}
void Busqueda_hacia_adelante(int X,int Y,int MarcasVert[max],Arcos A,Conjunto Ondas[max],int *i,int *ExisteCam)
{
	//printf("1\n");
	int w,j,h;
	Conjunto O;
	cVa(&Ondas[0]);
	cVa(&Ondas[1]);
	Ondas[0]=cIe(Ondas[0],X);
	//verC(Ondas[0]);
	//printf("\n\n2\n");
	marcar_vertices(&Ondas[0],0,MarcasVert);

	//printf("3\n");
	Ondas[1]=Conjunto_adyacentes_no_marcados(X,A,MarcasVert);
	//verC(Ondas[1]);
	*i=1;
		//printf("4\n");
	if(Ondas[1].lon != 0)
	{
			//printf("5\n");
			marcar_vertices(&Ondas[1],1,MarcasVert);
			//printf("%d %d",MarcasVert[2],MarcasVert[3]);
			//printf("\n6\n");
			//printf("El Y es:%d",Y);
			//verC(Ondas[*i]);
			
			while((pertenece(Y,Ondas[*i])==FALSE) && Ondas[*i].lon != 0)
			{
				cVa(&Ondas[*i+1]);
				//printf("7\n");
				for(j=0;j<Ondas[*i].lon;j++)
				{
					w=Ondas[*i].Con[j];
					//printf("Dentro del ciclo %d\n",w);
					O=Conjunto_adyacentes_no_marcados(w,A,MarcasVert);
					//verC(O);
					Ondas[*i+1]=Union(Ondas[*i+1],O);
					//printf("8\n");
					//verC(Ondas[*i+1]);
					if(Ondas[*i+1].lon != 0)
					{
						marcar_vertices(&Ondas[*i+1],*i+1,MarcasVert);
					}
					//for(h=0;h<4;h++)
					//{
						//printf("%d",MarcasVert[h]);
					//}
						
				}
				//*i++;
				*i=*i+1;
			}
			if(pertenece(Y,Ondas[*i])==TRUE)
			{
					*ExisteCam=TRUE;
			}else{
					*ExisteCam=FALSE;
			}
	}
}
int Adyacente_onda_anterior(int C,Arcos A,Conjunto Ondas)
{
	int i,j;
	
	for(i=0;i<A.lon;i++)
	{
		if(A.Arc[i].v==C)
		{
			for(j=0;j<Ondas.lon;j++)
			{
				if(A.Arc[i].w==Ondas.Con[j])
				{
					return(Ondas.Con[j]);
				}
			}
		}
	}
	for(i=0;i<A.lon;i++)
	{
		if(A.Arc[i].w==C)
		{
			for(j=0;j<Ondas.lon;j++)
			{
				if(A.Arc[i].v==Ondas.Con[j])
				{
					return(Ondas.Con[j]);
				}
			}
		}
	}
}

void Construccion_hacia_atras(int X,int Y,Arcos A,Conjunto Ondas[max],int i,int Cam[max])
{
	int k;
	Cam[i]=Y;
	printf("\n dentro de cam i es :%d\n",i);
	for(k = i;k >= 0 ;k--)
	{		
		Cam[k-1]=Adyacente_onda_anterior(Cam[k],A,Ondas[k-1]);
	}
	printf("El Camino mas Corto en Cantidad de Arcos entre %d y %d es:",X,Y);
		printf("SALIDA <---> ");
	for(k = 0;k <= i ;k++)
	{
		printf("%d <---> ",Cam[k]);
	}

	printf("LLEGADA");
	printf("\n");
}

				
				
