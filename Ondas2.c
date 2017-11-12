#include<math.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>


#define c 250.0 // velocidad
#define L 0.5 //Lado del tambor
#define dx L/N
#define r 0.1
#define N 101
/*
double *x = malloc(N*N*sizeof(double));
double *y = malloc(N*N*sizeof(double));
double *phi = malloc(N*N*sizeof(double));
double *phi_future= malloc(N*N*sizeof(double));
*/




int main(){
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



/*
// Liberar memoria del cubo de datos
// Si hay problemas con la ram, esto puede ser util
for(i=0;i<N;i++)
	{
		
		for (j = 0; j < N; ++j)
		{
			free(M[i][j]);
		}
		free(M[i]);
	}
	free(M);


// Liberar memoria
//	for(i=0;i<N;i++)
//	{
//		free(matriz[i]);
//	}
//free(matriz);
*/

fclose(Datos);
fclose(Salida);


return 0;

}
