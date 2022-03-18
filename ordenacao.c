#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define VETOR_TAM 100000
#define ARQVETOR_TAM 12

#define ARQ_DIR "instancias-num"

typedef int vetor[ VETOR_TAM ];
typedef char arqvetor[ ARQVETOR_TAM ][ 256 ];

void insertion_sort( vetor vet, int tam );
void selection_sort( vetor vet, int tam );

int le_amostras_vet( char* arq, vetor vet, int* tam );
void imprime_amostras_vet( vetor vet, int tam );

void carrega_arqnome( char* arqnome, int i, int vettam );
void carrega_arqnome_vet( arqvetor arqvet, int* cont );
void lista_arqnome_vet( arqvetor arqvet, int tam );
void carrega_arqpath( char* path, char* arqnome, char* basedir );

void menu();

int main() {
	vetor vet;	
	int tam;
	
	arqvetor arqvet;
	int arqvet_tam;
	int leu;
	
	int op = 1;
	int arqnum = 0;
	
	char path[ 256 ];
	
	carrega_arqnome_vet( arqvet, &arqvet_tam );
	do {
		fflush( stdin );
		
		menu();
		printf( "Informe o metodo de selecao: " );
		scanf( "%d", &op );				
		
		switch( op ) {
			case 1:
			case 2:
				lista_arqnome_vet( arqvet, arqvet_tam );				
				printf( "\nInforme o numero do arquivo de amostra: " );
				scanf( "%d", &arqnum );
				
				printf( "\n" );
				
				if ( arqnum < 1 || arqnum >= arqvet_tam ) {
					printf( "\nVoce digitou um número do arquivo que não consta na lista acima." );
					getc( stdin );
				} else {				
					carrega_arqpath( path, arqvet[ arqnum-1 ], ARQ_DIR );
					leu = le_amostras_vet( path, vet, &tam );
					if ( !leu ) {
						printf( "\nFalha na leitura do arquivo: %s", path );
						getc( stdin );
					}
					
					imprime_amostras_vet( vet, tam );
				}				
					
			    break;
		}
	} while( op != 0 );
		
	
	return 0;
}

void menu() {
	printf( "\n|******** MENU ********|" );
	printf( "\n|                      |" );
	printf( "\n|  (1) Selection sort  |" );
	printf( "\n|  (2) Insertion sort  |" );
	printf( "\n|  (0) Sair            |" );
	printf( "\n|                      |" );
	printf( "\n|**********************|\n\n" );		
}


void carrega_arqpath( char* path, char* arqnome, char* basedir ) {
	strcpy( path, basedir );
	strcat( path, "/" );
	strcat( path, arqnome );
}

void lista_arqnome_vet( arqvetor arqvet, int tam ) {	
	int i;
	
	printf( "\n| *** Lista de arquivos *** |\n\n" );
	for( i = 0; i < tam; i++ )
		printf( " (%d) %s\n", (i+1), arqvet[ i ] );
	printf( "\n" );
}

void carrega_arqnome_vet( arqvetor arqvet, int* cont ) {
	int i, j; 
		
	*cont = 0;
	for( i = 1; i <= 4; i++ )
		for( j = 1000; j <= 100000; j*=10 )
			carrega_arqnome( arqvet[ (*cont)++ ], i, j );			
}

void carrega_arqnome( char* arqnome, int i, int vettam ) {
	sprintf( arqnome, "%s%d%s%d%s", "num.", vettam, ".", i, ".in" );	
}

int le_amostras_vet( char* arqnome, vetor vet, int* tam ) {
	int i;
	FILE* arq;
	char linha[ 10 ];
	
	arq = fopen( arqnome, "r" );
	if ( arq == NULL )
		return 0;		
		
	fgets( linha, sizeof( linha ), arq );
	*tam = atoi( linha );
	
	for( i = 0; i < *tam; i++ ) {
		fgets( linha, sizeof( linha ), arq );
		vet[ i ] = atoi( linha );
	}
	
	fclose( arq );
	
	return 1;
}

void imprime_amostras_vet( vetor vet, int tam ) {
	int i;
	
	printf( "Vetor=\n" );
	for( i = 0; i < tam; i++ ) {
		printf( "%7d", vet[ i ] ); 
		if ( (i+1) % 10 == 0 )
			printf( "\n" );
	}
	printf( "\n" );
}

void insertion_sort( vetor vet, int tam ) {
	int i, j, aux;
	
	for( i = 1; i < tam; i++ ) {
		aux = vet[ i ];
		j = i-1;
		while ( j >= 0 && aux < vet[ j ] ) {
			vet[ j+1 ] = vet[ j ];
			j--;
		}
		vet[ i ] = aux;
	}
}

void selection_sort( vetor vet, int tam ) {
	int i, j, aux, min_i;
	
	for( i = 0; i < tam-1; i++ ) {
		min_i = i;
		for( j = i+1; j < tam; j++ )
			if ( vet[ i ] > vet[ j ] ) 
				min_i = j;
		if ( min_i != i ) {
			aux = vet[ i ];
			vet[ i ] = vet[ min_i ];
			vet[ min_i ] = aux;
		}
	}
}