///    ***** Proyecto Computacional 2011 *****
///                    FACYT
///          Realizado por: Samuel Heredia
// // // // // // // // // // // // // // // // // // //
///   Fecha de Ultima revision:10/07/11
///   Nombre: Proyecto.c
// // // // // // // // // // // // // // // // // // //  
///   Nota: Este Programa incluye Tipos de Datos Abstractos estos son:
///         Arcos.c Arcos.h Conjunto.c Conjunto.h
///*** Librerias ***///
#include <stdio.h>
#include <string.h>
///*** TDA ***///
#include "Arcos.h"
#include "Conjunto.h"
///*** Marcos ***///
#define M 50
///*** Estructuras ***///
		typedef struct 
		{
			char nombre[M];
			char codigo;	
		}cuerposcelestes;
			
		typedef struct
		{
			char a[M];
			char b[M];
			float anios_luz;
			float combustible;
         }conexiones;
		
		typedef struct
		 {
			char nombre[M];
			char nombre1[M];
		 }agujerosn;
			
		typedef struct 
		{
			char nombre[M];
			char nombre1[M];
			float combustible;
		}viajesposibles;

/// *** Cabecera de Funciones y Procedimientos *** ///
// // // Funciones que retornan un Entero // // //
int ComConex(Arcos A);		
int iguality(int A,Conjunto W);
int forma_circuito(Arcos Amin);
int buscarComConVer(int A,Conjunto C[max]);
int observacion(char a[M],cuerposcelestes Na[M],int n);	 
int salida(viajesposibles V,cuerposcelestes C[M],int m);
int llegada(viajesposibles V,cuerposcelestes C[M],int m);
int Adyacente_onda_anterior(int C,Arcos A,Conjunto Ondas,Conjunto W,float *Suma);
// // // Procedimientos // // //
void interfaz ();
void agregar_agujeros(conexiones X[M],agujerosn A[M],int n,int a);	
void inicializa(Arcos A,Conjunto C[max]);
void vertices(int n, int V[max],int aux[max],int m);
void vectorG(int v[max],int w[max],int g[max],int n);
void inicializar(int m[max]);
void marcar_vertices(Conjunto *Ondas,int n,int MV[max]);
void Construccion_hacia_atras(int X,int Y,Arcos A,Conjunto Ondas[max],int i,int Cam[max],Conjunto *C,float *Sum);
void Busqueda_hacia_adelante(int X,int Y,int MarcasVert[max],Arcos A,Conjunto Ondas[max],int *i,int *ExisteCam);
void Kruskal(Arcos A,FILE *fy);
void Ondas(Arcos A,int X,int Y,float combustible,cuerposcelestes Cu[M],FILE *fy);
void mapa(cuerposcelestes Na[M],int n,FILE *fy);
void carga(agujerosn A[M],conexiones X[M],cuerposcelestes C[M],viajesposibles V[M],
cuerposcelestes Na[M],conexiones Nc[M],int *longitud,int *ncuerpos,int *agujeros,int *nviajes,int *n,int *m,FILE *fp,FILE *fy);
Conjunto Conjunto_adyacentes_no_marcados(int X,Arcos A,int MV[max]);
// // // Funciones que retornan Estructuras // // //
Arcos llenar_arcos(conexiones X[M],cuerposcelestes C[M],viajesposibles V[M],Arcos Ar,int a,int t);		
Arco extraer_etiqueta_arco_min_costo(Arcos AuxA);	

/// ***** CUERPO PRINCIPAL DEL ALGORITMO ***** ///
int main ()
{
	// // *** vARIABLES *** // //
	FILE *fp,*fy;
	int longitud,ncuerpos,agujeros,nviajes,i,n,m,turno,x,y;
	cuerposcelestes C[M],Na[M];			//Cuerpos celestes y No agujeros(Na)
	conexiones X[M],Nc[M];				//Conexiones y No agujeros Negros
	agujerosn A[M];						//Almacena el mapa entre agujeros negros
	viajesposibles V[M]; 				//ALmacena la consulta de viajes por Archivo
	Arcos Ar;
	arcVacio(&Ar);

	fp = fopen("archivos.in","r");
	
	if(fp==NULL)
	{
		
		printf("Archivo <archivos.in> no abrio");
		return 1;
		
	}else
	{
		fy = fopen("archivos.out","w");	
		carga(A,X,C,V,Na,Nc,&longitud,&ncuerpos,&agujeros,&nviajes,&n,&m,fp,fy);
		fclose (fp);
	}
	interfaz();
	mapa(Na,n,fy);
	arcVacio(&Ar);
	Ar.vert=n;
	Ar.lon=m;
	turno=1;
	Ar=llenar_arcos(Nc,Na,V,Ar,agujeros,turno);
	Kruskal(Ar,fy);
	Ar.vert=longitud;
	Ar.lon=ncuerpos;
	turno=0;
	agregar_agujeros(X,A,ncuerpos,agujeros);
	Ar=llenar_arcos(X,C,V,Ar,agujeros,turno);
	for(i=0;i<nviajes;i++)
	{
		x=salida(V[i],C,ncuerpos);
		y=llegada(V[i],C,ncuerpos);
		Ondas(Ar,x,y,V[i].combustible,C,fy);
	}
	fclose (fy);
	return 0;


}
void mapa(cuerposcelestes Na[M],int n,FILE *fy)
{
	int i;
	printf("Mapa de interconexión satelital\n");
	fprintf(fy,"Mapa de interconexión satelital\n");
	for(i=0;i<n;i++)
	{
		printf("%d %s\n",i+1,Na[i].nombre);
		fprintf(fy,"%d %s\n",i+1,Na[i].nombre);
	}
}
int salida(viajesposibles V,cuerposcelestes C[M],int m)
{
	int i;
	for(i=0;i<m;i++)
	{
		if(strcmp(V.nombre,C[i].nombre)==FALSE)
		{
			return(i+1);
		}
	}
	printf("La salida del Viaje esta fuera del mapa interespacial");
	return 1;
}
int llegada(viajesposibles V,cuerposcelestes C[M],int m)
{
	int i;
	for(i=0;i<m;i++)
	{
		if(strcmp(V.nombre1,C[i].nombre)==FALSE)
		{
			return(i+1);
		}
	}
	printf("El sitio de Destino del Viaje esta fuera del mapa interespacial");
	return 1;
}
void agregar_agujeros(conexiones X[M],agujerosn A[M],int n,int a)
{
	int i,j;
	j=0;
	for(i=n;i<(n+a);i++)
	{
		strcpy(X[i].a,A[j].nombre);
		strcpy(X[i].b,A[j].nombre1);
		X[i].combustible=0.0;
		j=j+1;
	}
}
Arcos llenar_arcos(conexiones X[M],cuerposcelestes C[M],viajesposibles V[M],Arcos Ar,int a,int t)
{
	Arcos Aux;
	Arco J;
	int i,j,h;
	arcVacio(&Aux);	
	for(i=0;i<Ar.lon+a;i++)
	{
		for(j=0;j<Ar.vert;j++)
		{
	         
			if(strcmp(X[i].a,C[j].nombre)==FALSE)
			{
				for(h=0;h<Ar.vert;h++)
				{
					if(strcmp(X[i].b,C[h].nombre)==FALSE)
					{
						J.v=j+1;
						J.w=h+1;
						if(t==0)
						{
							J.Peso=X[i].combustible;
						}else{
							J.Peso=X[i].anios_luz;
						}
						Aux=inserArc(Aux,J);
					}
				}
			}
		}
	}
	if(t==0)
	{
		Aux.vert=Ar.vert;
		Aux.lon=Ar.lon+a;
	}
	return(Aux);
	
}
	
int observacion(char a[M],cuerposcelestes Na[M],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(strcmp(a,Na[i].nombre)==FALSE)
		{
			return(TRUE);
		}
	}
	return(FALSE);
}
	
void carga(agujerosn A[M],conexiones X[M],cuerposcelestes C[M],viajesposibles V[M],
cuerposcelestes Na[M],conexiones Nc[M],int *longitud,int *ncuerpos,int *agujeros,int *nviajes,int *n,int *m,FILE *fp,FILE *fy)
{
	int i,j,k,l,pos;
	pos=0;
	*n=0;
	*m=0;	
		fscanf(fp,"%d",longitud);	
		for(i=0;i<*longitud;i++)
		{
			fscanf(fp,"%s %c",C[i].nombre,&C[i].codigo);
			if(C[i].codigo != 'A')
			{
				strcpy(Na[*n].nombre,C[i].nombre);
				Na[*n].codigo=C[i].codigo;
				*n+=1;
			}
			///printf("%s %c\n",C[i].nombre,C[i].codigo);	
		}
			fscanf(fp,"%d",ncuerpos);
			///printf("%d\n",*ncuerpos);
			for(j=0;j<*ncuerpos;j++)
			{	
				fscanf(fp,"%s %s",X[j].a,X[j].b);
				///printf("%s %s\n",X[j].a,X[j].b);
				fscanf(fp,"%f %f",&X[j].anios_luz,&X[j].combustible);
				///printf("%f %f\n",X[j].anios_luz,X[j].combustible);	
				if((observacion(X[j].a,Na,*n)==TRUE)&&(observacion(X[j].b,Na,*n)==TRUE))
				{
					strcpy(Nc[*m].a,X[j].a);
					strcpy(Nc[*m].b,X[j].b);
					Nc[*m].anios_luz=X[j].anios_luz;
					Nc[*m].combustible=X[j].combustible;
					*m+=1;
				}	 
			
			}	
				fscanf(fp,"%d",agujeros);
				///printf("%d \n",*agujeros);
			
			for(k=0;k<*agujeros;k++)
			 {
				 fscanf(fp,"%s %s",A[k].nombre,A[k].nombre1);
				/// printf("%s %s\n",A[k].nombre,A[k].nombre1);
			 }
			 
				fscanf(fp,"%d",nviajes);
				/// printf("%d\n",*nviajes);		 
			for(l=0;l<*nviajes;l++)
			{
				fscanf(fp,"%s %s %f",V[l].nombre,V[l].nombre1,&V[l].combustible);
				///printf("%s %s %.2f\n",V[l].nombre,V[l].nombre1,V[l].combustible);
			}

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
	int w,j;
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
int iguality(int A,Conjunto W)
{
	int j;

		for(j=0;j<W.lon;j++)
		{
			if(A==W.Con[j])
			{
		
				return(TRUE);
			}
		}

	return(FALSE);
}
int Adyacente_onda_anterior(int C,Arcos A,Conjunto Ondas,Conjunto W,float *Suma)
{
	int i,j;
	
		for(i=0;i<A.lon;i++)
		{
				if(((A.Arc[i].v==C)||(A.Arc[i].w==C))&&((iguality(A.Arc[i].v,W)==FALSE)&&(iguality(A.Arc[i].w,W)==FALSE)))
				{
					for(j=0;j<Ondas.lon;j++)
					{
						if(A.Arc[i].w==Ondas.Con[j])
						{
							*Suma=*Suma+A.Arc[i].Peso;
							return(Ondas.Con[j]);
						}
						else{
							if(A.Arc[i].v==Ondas.Con[j])
							{
								*Suma=*Suma+A.Arc[i].Peso;
								return(Ondas.Con[j]);
							}
					
						}
					}
				}
		}
	
}

void Construccion_hacia_atras(int X,int Y,Arcos A,Conjunto Ondas[max],int i,int Cam[max],Conjunto *C,float *Sum)
{
	int k;
	float S=0;
	Cam[i]=Y;
	for(k = i;k >= 0 ;k--)
	{		
		Cam[k-1]=Adyacente_onda_anterior(Cam[k],A,Ondas[k-1],*C,&S);
	}
	*Sum=S;
	*C=cIe(*C,Cam[i-1]);
}

				
				
int ComConex(Arcos A)
{
	int i,j;
	int n;
	int p;
	Conjunto C[max];
    ///Arcos A;
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
		///printf("la cantidad de componentes conexas son:%d\n",p);
	return (p);
}
void Kruskal(Arcos A,FILE *fy)
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
	verM(Amin,fy);
	printf("Costo Total del Camino: %0.2f",CT);
}
void Ondas(Arcos A,int X,int Y,float combustible,cuerposcelestes Cu[M],FILE *fy)
{
		Conjunto matrizOndas[max];
		Conjunto C; 
		float Total=0;
		float limite=9999999;
		int marcasVert[max]; 
		int Camino[max],Aux[max];
		int ExisteCam;//logico	
		int i,j,z;// vertice;	entero;	
		cVa(&C);
		inicializar(marcasVert);
		Busqueda_hacia_adelante(X,Y,marcasVert,A,matrizOndas,&i,&ExisteCam);
		if(ExisteCam==TRUE)
		{
			for(j=0;j<matrizOndas[i-1].lon;j++)
			{
						Construccion_hacia_atras(X,Y,A,matrizOndas,i,Camino,&C,&Total);
						if(Camino[0]==X)
						{
							if(Total<limite)
							{
								for(z=0;z<i+1;z++)
								{
									Aux[z]=Camino[z];
								}
								limite=Total;
							}
						}		
			}
				
			
		}else{
			printf("No existe camino entre: %d y %d \n",X,Y);
		}
		printf("\nPlan de Viaje entre: %s %s \n",Cu[X-1].nombre,Cu[Y-1].nombre);
		fprintf(fy,"\nPlan de Viaje entre: %s %s \n",Cu[X-1].nombre,Cu[Y-1].nombre);
		for(z=0;z<i+1;z++)
		{
			printf("%s",Cu[Aux[z]-1].nombre);
			fprintf(fy,"%s",Cu[Aux[z]-1].nombre);
			if(z!=i)
			{
				printf("-");
				fprintf(fy,"-");
			}
		}
		printf("\n");
		if(limite>combustible)
		{
			printf("El combustible inicial no es suficiente");
			fprintf(fy,"\nEl combustible inicial no es suficiente\n");
		}
}
