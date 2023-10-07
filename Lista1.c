#include <stdio.h>
#include <stdlib.h>

#define MAX_NOME 100
#define MAX_GENERO 50
#define MAX_LOCAL 50
#define MAX_ALBUNS 100

typedef struct {
  char nome[MAX_NOME];
  char genero[MAX_GENERO];
  char local[MAX_LOCAL];
  char *albuns[MAX_ALBUNS];
} Artista;

int main() {
  // Declaração de variáveis
  Artista *lista;
  int tam = 0;
  char opcao;

  // Leitura do arquivo
  lista = ler_artistas("artistas.txt", &tam);

  // Menu interativo
  do {
    printf("\n\n=== Menu ===\n");
    printf("1. Inserir artista\n");
    printf("2. Remover artista\n");
    printf("3. Editar artista\n");
    printf("4. Buscar artista\n");
    printf("5. Buscar álbum\n");
    printf("0. Sair\n");
    printf("\nEscolha uma opção: ");
    scanf(" %c", &opcao);

    switch (opcao) {
      case '1':
        inserir_artista(lista, &tam);
        break;
      case '2':
        remover_artista(lista, &tam);
        break;
      case '3':
        editar_artista(lista, &tam);
        break;
      case '4':
        buscar_artista(lista, &tam);
        break;
      case '5':
        buscar_album(lista, &tam);
        break;
      case '0':
        break;
      default:
        printf("Opção inválida.\n");
        break;
    }
  } while (opcao != '0');

  // Escrita do arquivo
  escrever_artistas("artistas.txt", lista, tam);

  // Liberação da memória
  for (int i = 0; i < tam; i++) {
    free(lista[i].albuns);
  }
  free(lista);

  return 0;
}

// Leitura do arquivo
Artista *ler_artistas(const char *nome_arquivo, int *tam) {
  // Declaração de variáveis
  Artista *lista;
  FILE *arq;
  int i = 0;

  // Abertura do arquivo
  arq = fopen(nome_arquivo, "r");
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
  }

  // Alocação da memória
  lista = (Artista *)malloc(sizeof(Artista));
  if (lista == NULL) {
    printf("Erro ao alocar memória.\n");
    exit(1);
  }

  // Leitura dos registros
  while (!feof(arq)) {
    // Leitura do nome
    fgets(lista[i].nome, MAX_NOME, arq);
    lista[i].nome[strcspn(lista[i].nome, "\n")] = '\0';

    // Leitura do gênero
    fgets(lista[i].genero, MAX_GENERO, arq);
    lista[i].genero[strcspn(lista[i].genero, "\n")] = '\0';

    // Leitura do local
    fgets(lista[i].local, MAX_LOCAL, arq);
    lista[i].local[strcspn(lista[i].local, "\n")] = '\0';

    // Leitura dos álbuns
    lista[i].albuns = (char **)malloc(sizeof(char *) * MAX_ALBUNS);
    for (int j = 0; j < MAX_ALBUNS; j++) {
      fgets(lista[i].albuns[j], MAX_NOME, arq);
      lista[i].albuns[j][strcspn(lista[i].albuns[j], "\n")] = '\0';
    }

