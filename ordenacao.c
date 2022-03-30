#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#define VETOR_TAM 100000
#define ARQVETOR_TAM 12

#define ARQ_DIR "instancias-num"

typedef int vetor[VETOR_TAM];
typedef char arqvetor[ARQVETOR_TAM][256];

void insertion_sort(vetor vet, int tam);
void selection_sort(vetor vet, int tam);
void merge_sort(vetor vet, vetor auxvet, int ini, int fim);
void quick_sort(vetor vet, int p, int r);
void quick_sort_tradicional(vetor vet, int p, int r );

void gera_random_vetor(vetor vet, int tam, int min, int max);

long long get_ms();

int le_amostras_vet(char *arq, vetor vet, int *tam);
void imprime_amostras_vet(vetor vet, int tam);

void carrega_arqnome(char *arqnome, int i, int vettam);
void carrega_arqnome_vet(arqvetor arqvet, int *cont);
void lista_arqnome_vet(arqvetor arqvet, int tam);
void carrega_arqpath(char *path, char *arqnome, char *basedir);

void menu();
void menu_ordenamento();

int main() {
	vetor vet;
	vetor auxvet;
	
	int tam;
	int min, max;
	long long ms1, ms2;

	arqvetor arqvet;
	int arqvet_tam;
	int leu;

	char op = '1';
	char op2 = '0';
	int arqnum = 0;

	char path[256];

	carrega_arqnome_vet(arqvet, &arqvet_tam);
	do {
		menu();
		printf("\nInforme a opcao: ");

		fflush(stdin);
		fflush(stdout);
		op = getchar();

		switch (op) {
			case '1':
				printf("\nInforme a quantidade de elementos: ");
				scanf("%d", &tam);
				printf("Informe o valor minimo: ");
				scanf("%d", &min);
				printf("Informe o valor maximo: ");
				scanf("%d", &max);

				gera_random_vetor(vet, tam, min, max);

				printf("\nVetor gerado com sucesso!");
				break;
			case '2':
				lista_arqnome_vet(arqvet, arqvet_tam);
				printf("\nInforme o numero do arquivo de amostra: ");
				scanf("%d", &arqnum);

				if (arqnum < 1 || arqnum > arqvet_tam) {
					printf("\nVoce digitou um numero do arquivo que nao consta na lista acima.");
				} else {
					carrega_arqpath(path, arqvet[arqnum - 1], ARQ_DIR);
					leu = le_amostras_vet(path, vet, &tam);
					if (leu) {
						printf("\nAmostras carregadas com sucesso!");
					} else {
						printf("\nFalha na leitura do arquivo: %s", path);
					}
				}
				break;
			case '3':
				imprime_amostras_vet(vet, tam);
				break;
			case '4':
				menu_ordenamento();
				printf("\nInforme a opcao: ");

				fflush(stdin);
				fflush(stdout);
				op2 = getchar();

				switch (op2) {
					case '1':
						ms1 = get_ms();
						insertion_sort(vet, tam);
						ms2 = get_ms();
						printf("\nVetor ordenado com sucesso em: %lldms", (ms2 - ms1));
						break;
					case '2':
						ms1 = get_ms();
						selection_sort(vet, tam);
						ms2 = get_ms();
						printf("\nVetor ordenado com sucesso em: %lldms", (ms2 - ms1));
						break;
					case '3':
						ms1 = get_ms();
						merge_sort(vet, auxvet, 0, tam);
						ms2 = get_ms();
						printf("\nVetor ordenado com sucesso em: %lldms", (ms2 - ms1));
						break;
					case '4':
						ms1 = get_ms();
						quick_sort(vet, 0, tam-1);
						ms2 = get_ms();
						printf("\nVetor ordenado com sucesso em: %lldms", (ms2 - ms1));
						break;
					case '5':
						ms1 = get_ms();
						quick_sort_tradicional(vet, 0, tam-1);
						ms2 = get_ms();
						printf("\nVetor ordenado com sucesso em: %lldms", (ms2 - ms1));
						break;
					case '6':
						break;
					default:
						printf("\nOpcao invalida!");
				}

				if (op2 != '6')	{
					printf("\nTecle enter para continuar...");
					fflush(stdin);
					fflush(stdout);
					getc(stdin);
				}
				break;
			case '0':
				printf("\nTecle enter para sair...\n");
				break;
			default:
				printf("\nOpcao invalida!");
		}

		if (op != '0' && op != '4') {
			if (op != '0')
				printf("\nTecle enter para continuar...");
			fflush(stdin);
			fflush(stdout);
			getc(stdin);
		}

	} while (op != '0');

	return 0;
}

void menu() {
	printf("\n|*********** MENU ************|");
	printf("\n|                             |");
	printf("\n|  (1) Gera vetor randomico   |");
	printf("\n|  (2) Carregar amostras      |");
	printf("\n|  (3) Listar                 |");
	printf("\n|  (4) Ordenar                |");
	printf("\n|  (0) Sair                   |");
	printf("\n|                             |");
	printf("\n|*****************************|\n");
}

void menu_ordenamento() {
	printf("\n|********* ORDENAMENTO *********|");
	printf("\n|                               |");
	printf("\n|  (1) Insertion sort           |");
	printf("\n|  (2) Selection sort           |");
	printf("\n|  (3) Merge sort               |");
	printf("\n|  (4) Quick sort               |");
	printf("\n|  (5) Quick sort tradicional   |");
	printf("\n|  (6) Voltar                   |");
	printf("\n|                               |");
	printf("\n|*******************************|\n");
}

void carrega_arqpath(char *path, char *arqnome, char *basedir) {
	strcpy(path, basedir);
	strcat(path, "/");
	strcat(path, arqnome);
}

void lista_arqnome_vet(arqvetor arqvet, int tam) {
	int i;

	printf("\n| *** Lista de arquivos *** |\n\n");
	for (i = 0; i < tam; i++)
		printf(" (%d) %s\n", (i + 1), arqvet[i]);
	printf("\n");
}

void carrega_arqnome_vet(arqvetor arqvet, int *cont) {
	int i, j;

	*cont = 0;
	for (i = 1; i <= 4; i++)
		for (j = 1000; j <= 100000; j *= 10)
			carrega_arqnome(arqvet[(*cont)++], i, j);
}

void carrega_arqnome(char *arqnome, int i, int vettam) {
	sprintf(arqnome, "%s%d%s%d%s", "num.", vettam, ".", i, ".in");
}

int le_amostras_vet(char *arqnome, vetor vet, int *tam) {
	int i;
	FILE *arq;
	char linha[10];

	arq = fopen(arqnome, "r");
	if (arq == NULL)
		return 0;

	fgets(linha, sizeof(linha), arq);
	*tam = atoi(linha);

	for (i = 0; i < *tam; i++) {
		fgets(linha, sizeof(linha), arq);
		vet[i] = atoi(linha);
	}

	fclose(arq);

	return 1;
}

void imprime_amostras_vet(vetor vet, int tam) {
	int i;

	printf("\nVetor=\n");
	for (i = 0; i < tam; i++)
	{
		printf("%11d", vet[i]);
		if ((i + 1) % 7 == 0)
			printf("\n");
	}
	printf("\n");
}

void gera_random_vetor(vetor vet, int tam, int min, int max) {
	int i;
	for (int i = 0; i < tam; i++)
		vet[i] = min + (rand() % (max - min + 1));
}

void insertion_sort(vetor vet, int tam) {
	int i, j, aux;

	for (i = 1; i < tam; i++)
	{
		aux = vet[i];
		j = i - 1;
		while (j >= 0 && aux < vet[j])
		{
			vet[j + 1] = vet[j];
			j--;
		}
		vet[j + 1] = aux;
	}
}

void selection_sort(vetor vet, int tam) {
	int i, j, aux, min_i;

	for (i = 0; i < tam - 1; i++)
	{
		min_i = i;
		for (j = i + 1; j < tam; j++)
			if (vet[j] < vet[min_i])
				min_i = j;
		if (min_i != i)
		{
			aux = vet[i];
			vet[i] = vet[min_i];
			vet[min_i] = aux;
		}
	}
}

void merge(vetor vet, vetor auxvet, int inicio, int meio, int fim ) {
	int i = inicio;
	int j = meio;
	
	int k = inicio;
	
	while ( i < meio && j < fim ) {
		if ( vet[i] < vet[j] ) {
			auxvet[k++] = vet[i++];
		} else {
			auxvet[k++] = vet[j++];
		}
	}
	
	while ( i < meio )
		auxvet[ k++ ] = vet[ i++ ];
	
	while( j < fim )
		auxvet[ k++ ] = vet[ j++ ];
	
	for( k = inicio; k < fim; k++ )
		vet[ k ] = auxvet[ k ];	
}

void merge_sort(vetor vet, vetor auxvet, int ini, int fim ) {
	int meio;
	if ( ini < fim-1 ) {
		meio = ( ini + fim ) / 2;
		merge_sort( vet, auxvet, ini, meio );
		merge_sort( vet, auxvet, meio, fim );
		merge( vet, auxvet, ini, meio, fim );
	}
}


int particiona_tradicional(vetor vet, int p, int r ) {
	int pivor = vet[ r ];
	int i = p-1;
	int j, aux;
	for( j = p; j < r; j++ ) {
		if( vet[j] <= pivor ){
			i++;
			aux = vet[ i ];
			vet[ i ] = vet[ j ];
			vet[ j ] = aux;
		}
	}
	vet[ r ] = vet[ i+1 ];
	vet[ i+1 ] = pivor;			
	return i+1;		
}

void quick_sort_tradicional(vetor vet, int p, int r ) {
	int pivo;
	if ( p < r ) {
		pivo = particiona_tradicional( vet, p, r );
		quick_sort( vet, p, pivo-1 );
		quick_sort( vet, pivo+1, r );
	}
}

int particiona(vetor vet, int p, int r ) {
	int pivor = vet[p];
	int a = p+1;
	int b = r;
	int aux;
	while( 1 ) {
		if ( a < r )
			while( vet[a] <= pivor && a < r )
				a++;
		if ( b > 0 )
			while( vet[b] > pivor && b > 0 )
				b--;
		
		if ( vet[a] == vet[b] ) {
			a++;			
		} else if ( a <= b ) {
			aux = vet[a];
			vet[a] = vet[b];
			vet[b] = aux;
		} else {
			vet[p] = vet[ b ];
			vet[b] = pivor;
			return b;
		}
	}
}

void quick_sort(vetor vet, int p, int r ) {
	int pivo;
	if ( p < r ) {
		pivo = particiona( vet, p, r );
		quick_sort( vet, p, pivo-1 );
		quick_sort( vet, pivo+1, r );
	}
}

long long get_ms() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (((long long)(t.tv_sec) * 1000)) + (t.tv_usec / 1000);
}