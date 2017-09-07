///Algoritmo de Kruskal
/*procedimiento Alg_Kruskal(Ady: matrizAdy;  A: conjunto_etiquetas_de_arco;  n: entero;
				var Amin: conjunto_etiquetas_de_arco)
		// Ady: matrizAdy  Contiene la matriz de adyacencia del grafo G
		// A, Amin: conjunto_etiquetas_de_arco  Almacenan etiquetas ai de los arcos del grafo
		// n: entero  es el número de vértices de la corrida (n menor igual N)
inicio 
	variable
		i: entero;	// i es contador del número de arcos añadidos al subgrafo actual Ti 
		CT: real;	// CT es el costo del subgrafo expandido Ti 
		AuxA: conjunto_etiquetas_de_arco;	// AuxA es variable auxiliar, contiene inicialmente las etiquetas de A 
		ei: etiqueta_de_arco;	// Almacenará la etiqueta ai del arco que se esté procesando
	Amin ← vacio;	// inicializa el conj. de etiquetas de los arcos de Ti en vacío 
				// (el subgrafo expandido Ti comienza con sólo los vértices)
	CT ← 0;	// el costo de Ti se inicializa en 0 
	AuxA ← A;	// se colocan las etiquetas de los arcos del grafo G en una variable auxiliar 
	i ← 0;	// el contador de número de arcos añadidos a Ti se inicializa en 0 
	mientras (i < n – 1) hacer	// mientras no se haya formado el árbol expandido mínimo 
		ei ← extraer_etiqueta_arco_min_costo(AuxA – Amin);
		si Negacion( forma_circuito_al_añadir(ei, Amin, Ady) ) entonces  // verificar que no se vaya a formar circuito al añadir ei
			Amin ← Amin union {ei};
			CT ← CT + C(ei);
			i ← i + 1;
		sino  // si se forma un circuito al añadir ei a los arcos de Amin (arcos del subgrafo Ti)  
			AuxA ← AuxA – {ei};
		fsi
	fmientras
	escribir(“El conjunto de arcos de Tmin es: ”, Amin , “ con un costo de ”, CT)
finProcedimiento  // fin procedimiento Alg_Kruskal //
*/
#include <stdio.h>
#include "Conjunto.h"
#include "Arcos.h"
#define N 100

Arcos lecturas_iniciales();
Arco extraer_etiqueta_arco_min_costo(Arcos AuxA);
void inicializa(Arcos A,Conjunto C[max]);
int buscarComConVer(int A,Conjunto C[max]);
void verc(Conjunto C[max]);
int forma_circuito(Arcos Amin);
void vertices(int n, int V[max],int aux[max],int m);
void vectorG(int v[max],int w[max],int g[max],int n);
void inicializar(int m[max]);
void marcar_vertices(Conjunto *Ondas,int n,int MV[max]);
Conjunto Adyacente_onda_anterior(Conjunto C,Arcos A,Conjunto Ondas);
Conjunto Conjunto_adyacentes_no_marcados(int X,Arcos A,int MV[max]);
void Construccion_hacia_atras(int X,int Y,Arcos A,Conjunto Ondas[max],int i,Conjunto Cam[max]);
void Busqueda_hacia_adelante(int X,int Y,int MarcasVert[max],Arcos A,Conjunto Ondas[max],int *i,int *ExisteCam);
int ComConex(Arcos A);
void Kruskal(Arcos A);
void Ondas(Arcos A);

int main()
{
	Arcos A;
	A=lecturas_iniciales();
	Kruskal(A);
	Ondas(A);
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
		printf("Ingrese Peso:\n");
		scanf("%f",&A.Arc[i].Peso);
	}

	return(A);
}
int forma_circuito(Arcos Amin)
{
	int m,n,p;
	m=Amin.lon;
	n=Amin.vert;
	p=ComConex(Amin);
	if((m-n+p)==0)
	{
		return(FALSE);
	}else{
		return(TRUE);
	}
}
Arco extraer_etiqueta_arco_min_costo(Arcos AuxA)
{
	int i,et;
	float Cm=99999;
	
	for(i=0;i<AuxA.lon;i++)
	{
		if(AuxA.Arc[i].Peso<Cm)
		{
			Cm=AuxA.Arc[i].Peso;
			et=i;
		}
	}
	
	return(AuxA.Arc[et]);
}
int buscarComConVer(int A,Conjunto C[max])
{
	int i=0;
	int bool;
	bool=FALSE;
	while(bool==FALSE)
	{
		bool=cPe(C[i],A);
		i++;
	}
		return(i);
}
void verc(Conjunto C[max])
{
	int i,j;
	for(i=0;i<3;i++)
	{
		printf("\n");
		printf("Longitud:%d\n",C[i].lon);
		for(j=0;j<C[i].lon;j++)
		{
			printf("%d\n",C[i].Con[j]);
		}
	}
}		
void vertices(int n, int V[max],int aux[max],int m)
{
	int i,j,x;
	n=2*n;

	for(i=0;i<m;i++)
	{
		for(j=i+1;j<m;j++)
		{
			while(V[i]==V[j])
			{
				for(x=j;x<n-1;x++)
				{
					V[x]=V[x+1];
					V[n]=0;
				}
			
			}
		}
	}
	
}
void vectorG(int v[max],int w[max],int g[max],int n)
{
	int i,j;
	j=0;
	for(i=0;i<n;i++)
	{
		g[i]=v[i];
	}
	for(i=n;i<2*n;i++)
	{
		g[i]=w[j];
		j++;
	}
}
void burbuja(int g[max],int n)
{
	int i,j,aux;
	n=2*n;
			for(i=1;i<n;i++)
			{
				for(j=0;j<n-1;j++)
				{
					if(g[j]>g[j+1])
					{
						aux=g[j];
						g[j]=g[j+1];
						g[j+1]=aux;
					}
				}
			}
}
		
	
void inicializa(Arcos A,Conjunto C[max])
{
		int n,i;
		int vector[max],v[max],w[max],g[max];
		n=A.vert;
		extracion(v,w,A);
		vectorG(v,w,g,A.lon);
		burbuja(g,A.lon);
		vertices(A.lon,g,vector,n);
		for(i=0;i<n;i++)
		{
			C[i].lon=1;
			C[i].Con[0]=g[i];
		}
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
			return(TRUE);
		}
	}
	return(FALSE);
}
void Busqueda_hacia_adelante(int X,int Y,int MarcasVert[max],Arcos A,Conjunto Ondas[max],int *i,int *ExisteCam)
{
	int w,j,h;
	Conjunto O;
	cVa(&Ondas[0]);
	cVa(&Ondas[1]);
	Ondas[0]=cIe(Ondas[0],X);
	marcar_vertices(&Ondas[0],0,MarcasVert);
	Ondas[1]=Conjunto_adyacentes_no_marcados(X,A,MarcasVert);
	*i=1;
	if(Ondas[1].lon != 0)
	{
			marcar_vertices(&Ondas[1],1,MarcasVert);
			while((pertenece(Y,Ondas[*i])==FALSE) && Ondas[*i].lon != 0)
			{
				cVa(&Ondas[*i+1]);
				for(j=0;j<Ondas[*i].lon;j++)
				{
					w=Ondas[*i].Con[j];
					O=Conjunto_adyacentes_no_marcados(w,A,MarcasVert);
					Ondas[*i+1]=Union(Ondas[*i+1],O);
					if(Ondas[*i+1].lon != 0)
					{
						marcar_vertices(&Ondas[*i+1],*i+1,MarcasVert);
					}					
				}
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
Conjunto Adyacente_onda_anterior(Conjunto C,Arcos A,Conjunto Ondas)
{
	int i,j;
	Conjunto Aux;
	cVa(&Aux);
	ver(A);
	for(i=0;i<A.lon;i++)
	{
		for(j=0;j<C.lon;j++)
		{
			if(A.Arc[i].v==C.Con[j])
			{
				//printf("Entre en si");
				Aux=cIe(Aux,A.Arc[i].w);
				//verC(Aux);
			}else{
				//printf("Entre en sino");
				if(A.Arc[i].w==C.Con[j])
				{
					Aux=cIe(Aux,A.Arc[i].v);
					//verC(Aux);
				}
			}
			
		}
	}
	/*for(i=0;i<A.lon;i++)
	{
		for(j=0;j<C.lon;j++)
		{
				if(A.Arc[i].w==C.Con[j])
				{
					Aux=cIe(Aux,A.Arc[i].v);
					verC(Aux);
				}
			}
	}*/

	return (Aux);
}

void Construccion_hacia_atras(int X,int Y,Arcos A,Conjunto Ondas[max],int i,Conjunto Cam[max])
{
	int k;
	Cam[i]=cIe(Cam[i],Y);
	//printf("\n dentro de cam i es :%d\n",i);
	for(k = i;k >= 0 ;k--)
	{		
		Cam[k-1]=Adyacente_onda_anterior(Cam[k],A,Ondas[k-1]);
	}
	//printf("El Camino mas Corto en Cantidad de Arcos entre %d y %d es:",X,Y);
		//printf("SALIDA <---> ");
	//for(k = 0;k <= i ;k++)
	//{
		//printf(" ");
		//verC(Cam[k]);
	//}
	//verC(Cam);
	//printf("LLEGADA");
	//printf("\n");
}

				
				
int ComConex(Arcos A)
{
	int i,j,d,f;
	int n,x;
	int p;
	Conjunto C[max];
    ///Arcos A;
	Arco arc;
	n=0;
	///arcVacio(&A);
	///A=lecturas_iniciales();
	inicializa(A,C);
	p=A.vert;
			while(n<A.lon)
			{
				i=buscarComConVer(A.Arc[n].v,C);
				j=buscarComConVer(A.Arc[n].w,C);
				if(i!=j)
				{
					C[i-1]=Union(C[i-1],C[j-1]);
					cVa(&C[j-1]);
					p=p-1;
				}
					
				n++;
			}
		//printf("la cantidad de componentes conexas son:%d\n",p);
	return (p);
}
void Kruskal(Arcos A)
{
		int i;
	float CT;
	Arcos Amin,AuxA;
	///Arcos A;
	Arco ei;
	CT=0;
	i=0;
	///arcVacio(&A);
	arcVacio(&Amin);
	arcVacio(&AuxA);
	///A=lecturas_iniciales();
	copiarA(&AuxA,A);
	while(i<(A.vert-1))
	{
		ei=extraer_etiqueta_arco_min_costo(AuxA);
		Amin=inserArc(Amin,ei);
		if(forma_circuito(Amin)==FALSE)
		{
			CT=CT+ei.Peso;
			AuxA=arcElim(AuxA,ei);
			i=i+1;
		}else{
			AuxA=arcElim(AuxA,ei);
			Amin=arcElim(Amin,ei);
		}
	}
	printf("El camino total es: \n\n");
	ver(Amin);
	printf("Costo Total del Camino: %0.2f",CT);
}
void Ondas(Arcos A)
{
		//Arcos A;
		Conjunto matrizOndas[max]; 
		int marcasVert[max],k; 
		Conjunto Camino[max];
		int ExisteCam;//logico	
		int X,Y,n,i;// vertice;	entero;	
		//A=lecturas_iniciales();
		printf("Vertice Origen:\n");
		scanf("%d",&X);
		printf("Vertice Llegada:\n");
		scanf("%d",&Y);
		inicializar(marcasVert);
		Busqueda_hacia_adelante(X,Y,marcasVert,A,matrizOndas,&i,&ExisteCam);
			for(k = 0;k <= i ;k++)
	{
		printf(" ");
		verC(matrizOndas[k]);
	}
		if(ExisteCam==TRUE)
		{
			Construccion_hacia_atras(X,Y,A,matrizOndas,i,Camino);
		}else{
			printf("No existe camino entre: %d y %d \n",X,Y);
		}
}
