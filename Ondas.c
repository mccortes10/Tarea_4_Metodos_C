#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//Ec. de Onda en 1D (guitarra) extremos fijos

#define pi 3.1416
void tambor();

int main(){
FILE *in;
FILE*solucion1 = fopen("Ondaextfijos.txt","w");
FILE*solucion2 = fopen("Ondaperturbada.txt","w");
float L = 0.64; // Longitud de la cuerda
float c = 250.0; // velocidad
int N = 129;
float r = 0.9;
float dx = 0.005;
float dt = r*(dx/c);
float n = (1.0/dt);
float x;
float t;

printf("%f\n", dt);

in = fopen("cond_ini_cuerda.dat","r"); // Abre el arcivo 
float**phi = malloc(N*sizeof(float*)); // Crea espacio en la memoria de la matriz
int i,j,k;
for (k=0;k<N;k++){
	phi[k]=malloc((int)(n)*sizeof(float));
			}
for(i=0;i<N;i++){
	fscanf(in,"%f %f\n", &x, &phi[i][0]);
	//phi[i][1]=phi[i][0];// Replicar para 2do tiempo 
			} 

// Primer paso
for (i = 1; i < N-1; ++i)
			{
				phi[i][1] = phi[i][0] + pow(r,2)/2.0*( phi[i-1][0] - 2*phi[i][0] + phi[i+1][0] );
			}			
			phi[0][1] = 0.0;
			phi[N-1][1] = 0.0;

for(j=1;j<n-1;j++)
{
	for(i=1;i<N-1;i++){
		phi[i][j+1]=(r*r)*(phi[i+1][j]-(2*phi[i][j])+phi[i-1][j])+(2*phi[i][j])-phi[i][j-1];
			}
	phi[0][j+1]=0.0;
	phi[N-1][j+1] =0.0;
	for(i=0;i<N;i++){
		fprintf(solucion1,"%f ",phi[i][j-1]);
			}
	fprintf(solucion1,"\n");	
}	
	fclose(solucion1);		


	// --------------------------------------------------
	// --------------------------------------------------
	// --------------------------------------------------
	// --------------------------------------------------
	// --------------------------------------------------

////Ec. de Onda en 1D (guitarra) perturbada

float**phi1 = malloc(N*sizeof(float*)); // Crea espacio en la memoria de la matriz
for (k=0;k<N;k++){
	phi1[k]=malloc((int)(n)*sizeof(float));
			}
for(i=0;i<N;i++){
	//fscanf(in,"%f %f\n", &x, &phi1[i][0]);
	phi1[i][0] = 0;// Replicar para 2do tiempo 
	phi1[i][1] = 0;// Replicar para 2do tiempo 
	} 
	t = dt;
	phi1[0][1] = 0.0;
	phi1[N-1][1] = sin((2*pi/L)*t);

// Primer paso
//for (i = 1; i < N-1; ++i)
//	{
//		phi1[i][1] = phi1[i][0] + pow(r,2)/2.0*( phi1[i-1][0] - 2*phi1[i][0] + phi1[i+1][0] );
//	}			
//	phi1[0][1] = 0.0;
//	phi1[N-1][1] = 0.0;

for(j=1;j<n-1;j++)
{
	t = t + dt;
	for(i=1;i<N-1;i++){
		phi1[i][j+1]=(r*r)*(phi1[i+1][j]-(2*phi1[i][j])+phi1[i-1][j])+(2*phi1[i][j])-phi1[i][j-1];
			}
	phi1[0][j+1]=0.0;
	phi1[N-1][j+1] = sin((2*pi/L)*t);

	for(i=0;i<N;i++){
		fprintf(solucion2,"%f ",phi1[i][j-1]);
			}
	fprintf(solucion2,"\n");	
}	
	fclose(solucion2);		

tambor();// LLAMA LA FUNCION QUE EJECUTA LA SOLUCION DEL TAMBOR

	return 0;

}

// TAMBOR

void tambor(){

float c = 250.0; // velocidad
float L = 0.5; //Lado del tambor
int N = 101;
float dx = L/N;
float r = 0.1;

float dt=dx*r/c;

int n = (int) 1.0/dt/1000; // Correr todos los pasos de tiempo tarda mucho. en la animacion toma un segundo cada iteracion. Se ejecuta solo la milésima parte donde es evidente el comportamiento de la onda en 2D
//printf("Delta de tiempo %f\nPasos de tiempo %d\n", dt,n);
//printf("Tiempo total %f s\n", (float) n*dt);

int i,j,k;
FILE *Datos = fopen("cond_ini_tambor.dat","r");
FILE *Salida = fopen("tambor.dat","w");


// Ejemplo de crear un cubo de datos
float ***M=malloc(n*sizeof(float**));
for(k=0;k<n;k++)
	{
		M[k] = malloc(N*sizeof(float*));
		for (j = 0; j < N; ++j)
		{
			M[k][j] = malloc(N*sizeof(float));
		}

	}

//Cargar condicones iniciales
char linea[1000];
char *split;




for(i=0;i<N;i++){
	fgets(linea,1000,Datos); // Leer maximo 1000 caracteres en cada linea de datos	
	split = strtok(linea," ");
	for(j=0;j<N;j++){
		M[0][i][j] = atof(split);
		split = strtok(NULL," ");		
		}	
	}





for(i=0;i<N;i++){
	for(j=0;j<N;j++){
		fprintf(Salida, "%f ",M[0][i][j]); // escribir archivo de salida
		M[1][i][j]= M[0][i][j]; // Replica la primera matriz de condicines iniciales 
	}
	fprintf(Salida, "\n");

} 



for(k=1;k<n-1;k++){

	for(j=1;j<N-1;j++){
		for(i=1;i<N-1;i++){
			M[k+1][i][j]=(r*r)*(M[k][i+1][j] - (4*M[k][i][j]) + M[k][i-1][j] + M[k][i][j+1] + M[k][i][j-1]) + 2*M[k][i][j] - M[k-1][i][j];
		}
	}

//Condiciones de frontera

for(i=0;i<N-1;i++){
	M[k+1][i][0]=0.0;
	M[k+1][0][i]=0.0;
	M[k+1][N-1][i]=0.0;
	M[k+1][i][N-1]=0.0;
	}
//Imprime en la matriz de salida (solucion)	
for(i=0;i<N;i++){
	for(j=0;j<N;j++){
		fprintf(Salida, "%f ",M[k+1][i][j]); // escribir archivo de salida
	}
	fprintf(Salida, "\n");

	} 
}


fclose(Datos);
fclose(Salida);






}

