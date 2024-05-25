#include <stdio.h>
#include <stdlib.h>

struct RGB {
  int R;
  int G;
  int B;
};

struct Imagem {
  int linha;
  int coluna;
  int valorMaximo;
};

int main(void) {

  FILE *fp;
  fp = fopen("./images.ppm", "r");

  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  struct Imagem imagem;
  if (fscanf(fp, "%d %d", &imagem.coluna, &imagem.linha) != 2) {
    printf("Erro ao ler as dimensões da imagem.\n");
    fclose(fp);
    return 1;
  }

  if (fscanf(fp, "%d", &imagem.valorMaximo) != 1) {
    printf("Erro ao ler o valor máximo da cor.\n");
    fclose(fp);
    return 1;
  }

  struct RGB **pixels = malloc(imagem.linha * sizeof(struct RGB *));
  if (pixels == NULL) {
    printf("Erro de alocação de memória.\n");
    fclose(fp);
    return 1;
  }

  for (int i = 0; i < imagem.linha; i++) {
    pixels[i] = malloc(imagem.coluna * sizeof(struct RGB));
    if (pixels[i] == NULL) {
      printf("Erro de alocação de memória.\n");
      for (int k = 0; k < i; k++) {
        free(pixels[k]);
      }
      free(pixels);
      fclose(fp);
      return 1;
    }
    for (int j = 0; j < imagem.coluna; j++) {
      if (fscanf(fp, "%d", &pixels[i][j].R) != 1 || fscanf(fp, "%d", &pixels[i][j].G) != 1 || fscanf(fp, "%d", &pixels[i][j].B) != 1) {
        printf("Erro ao ler os pixels da imagem.\n");
        for (int k = 0; k <= i; k++) {
          free(pixels[k]);
        }
        free(pixels);
        fclose(fp);
        return 1;
      }
    }
  }

  printf("Pixel na posição (0,0): R=%d, G=%d, B=%d\n", pixels[100][100].R, pixels[100][100].G, pixels[100][100].B);

  for(int i = 0; i < imagem.linha; i++) {
    for(int j = 0; j< imagem.coluna; j++) {
      pixels[i][j].R *= 2;
      pixels[i][j].G *= 2;
      pixels[i][j].B *= 2;
    }
  }

  for (int i = 0; i < imagem.linha; i++) {
    for (int j = 0; j < imagem.coluna; j++) {
        printf("(%d, %d, %d)\t", pixels[i][j].R, pixels[i][j].G, pixels[i][j].B);
    }
    printf("\n");
  }

  printf("Pixel na posição (0,0): R=%d, G=%d, B=%d\n", pixels[100][100].R, pixels[100][100].G, pixels[100][100].B);
  
  for (int i = 0; i < imagem.linha; i++) {
    free(pixels[i]);
  }
  free(pixels);

  fclose(fp);
  return 0;
}
