#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_SORTEIOS 5000
#define NUM_POR_SORTEIO 6

#define MIN_INTERVALO 1
#define MAX_INTERVALO 60

#define BOOL char
#define FALSE 0
#define TRUE 1

int sorteios[QTD_SORTEIOS][NUM_POR_SORTEIO];
int sorteioOrdenado[QTD_SORTEIOS * NUM_POR_SORTEIO];
int sorteioOrdenadoBackup[QTD_SORTEIOS * NUM_POR_SORTEIO];

int verifica_duplicidade(int numeros_sorteados[], int numero_atual, int tam) {
  for (int i = 0; i < tam; i++) {
    if (numeros_sorteados[i] == numero_atual) {
      return TRUE;
    }
  }
  return FALSE;
}

void bubbleSort(int array[], int tam) {
  int aux;
  int swap;

  do {
    swap = FALSE;
    for (int i = 0; i < tam - 1; i++) {
      if (array[i] > array[i + 1]) {
        aux = array[i];
        array[i] = array[i + 1];
        array[i + 1] = aux;
        swap = TRUE;
      }
    }
  } while (swap);
}

void gera_sorteios() {
  for (int i = 0; i < QTD_SORTEIOS; i++) {
    int numerosSorteados[NUM_POR_SORTEIO] = {0};
    for (int j = 0; j < NUM_POR_SORTEIO; j++) {
      int numero;
      do {
        numero = 1 + (rand() % MAX_INTERVALO);
      } while (verifica_duplicidade(numerosSorteados, numero, j));
      numerosSorteados[j] = numero;
      sorteios[i][j] = numero;
    }
    bubbleSort(sorteios[i], NUM_POR_SORTEIO);
  }
}

void imprime_sorteio() {
  FILE *text;
  text = fopen("output/output.txt", "w");

  for (int i = 0; i < QTD_SORTEIOS; i++) {
    printf("SORTEIO %02d: ", i + 1);
    fprintf(text, "SORTEIO %02d: ", i + 1);
    for (int j = 0; j < NUM_POR_SORTEIO; j++) {
      printf("%02d ", sorteios[i][j]);
      fprintf(text, "%02d ", sorteios[i][j]);
    }
    printf("\n");
    fprintf(text, "\n");
  }
  fclose(text);
}

int ordenacao_geral() {
  FILE *text;
  int i, j, indice;

  // Criando array com números sorteados
  for (int i = 0; i < QTD_SORTEIOS; i++) {
    for (int j = 0; j < NUM_POR_SORTEIO; j++) {
      sorteioOrdenado[indice] = sorteios[i][j];
      sorteioOrdenadoBackup[indice] = sorteios[i][j];
      indice++;
    }
  }

  // Export Array não ordenado
  text = fopen("output/no_ordening.txt", "w");
  for (int i = 0; i < QTD_SORTEIOS * NUM_POR_SORTEIO; i++) {
    fprintf(text, "%02d ", sorteioOrdenado[i]);
  }
  fclose(text);

  // Export Array ordenado
  text = fopen("output/ordening.txt", "w");
  for (i = 0; i < QTD_SORTEIOS * NUM_POR_SORTEIO; i++) {
    bubbleSort(sorteioOrdenado, QTD_SORTEIOS * NUM_POR_SORTEIO);
    fprintf(text, "%02d ", sorteioOrdenado[i]);
  }
  fclose(text);
}

void estatistica_par_e_impares() {
  int par = 0, impar = 0;
  double porP, porI = 0;

  FILE *text;

  // Verificando divisibilidade e contando impares e pares
  for (int i = 0; i < QTD_SORTEIOS * NUM_POR_SORTEIO; i++) {
    if (sorteioOrdenadoBackup[i] % 2 == 0) {
      par++;
    } else {
      impar++;
    }
  }

  porP = ((double)par / (QTD_SORTEIOS * NUM_POR_SORTEIO)) * 100;
  porI = ((double)impar / (QTD_SORTEIOS * NUM_POR_SORTEIO)) * 100;

  printf("\n\nPares: %d - %.2f %% \nImpares: %d - %.2f %%\n\n", par, porP,
         impar, porI);

  text = fopen("output/est_par-impar.txt", "w");
  fprintf(text, "\nPar: %d - %.2f %% \nImpar: %d - %.2f %%\n", par, porP, impar,
          porI);
  fclose(text);
}

void estatistica_repeticao() {
  int aux = 1;
  FILE *text;

  text = fopen("output/est_repretição.txt", "w");

  for (int i = 0; i < QTD_SORTEIOS * NUM_POR_SORTEIO; i++) {
    if (sorteioOrdenado[i] == sorteioOrdenado[i + 1]) {
      aux++;
    } else {
      printf("Número %02d = %d vezes.\n", sorteioOrdenado[i], aux);
      fprintf(text, "Número %02d = %d vezes.\n", sorteioOrdenado[i], aux);
      aux = 1;
    }
  }
  fclose(text);
}

void estatistica_duplas() { printf("15 Duplas mais populares:");}

int main() {
  setlocale(LC_ALL, "Portuguese_Brasil");
  srand(time(NULL));

  gera_sorteios();
  imprime_sorteio();
  ordenacao_geral();
  estatistica_par_e_impares();
  estatistica_repeticao();
  //estatistica_duplas();

  return 0;
}