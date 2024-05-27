#include <stdio.h>
#include <stdlib.h>

struct Imagem {
    int linha;
    int coluna;
    unsigned int valorMaximo;
};

struct RGB {
    unsigned int R;
    unsigned int G;
    unsigned int B;
};

FILE *abrirArquivo(char nomeArquivo[]);
int alocarValores(FILE *fp, struct Imagem *imagem, struct RGB ***pixels);
void escreverNovaImagem(char nomeArquivo[], struct Imagem *imagem, struct RGB **pixels);
void gerarImagemCinza(struct Imagem *imagem, struct RGB **pixels);
void gerarImagemNegativa(struct Imagem *imagem, struct RGB **pixels);
void rotacionarImagem(struct Imagem *imagem, struct RGB **pixels);
void modificarBrilhoImagem(struct Imagem *imagem, struct RGB **pixels, float valorPercentual);
void envelhecerImagem(struct Imagem *imagem, struct RGB **pixels);

FILE *abrirArquivo(char nomeArquivo[]) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }
    return fp;
}

void escreverNovaImagem(char nomeArquivo[], struct Imagem *imagem, struct RGB **pixels) {
    FILE *fp_novo = fopen(nomeArquivo, "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    fprintf(fp_novo, "P3\n");
    fprintf(fp_novo, "%d %d\n", imagem->coluna, imagem->linha);
    fprintf(fp_novo, "%d\n", imagem->valorMaximo);

    for (int i = 0; i < imagem->linha; i++) {
        for (int j = 0; j < imagem->coluna; j++) {
            fprintf(fp_novo, "%d %d %d ", pixels[i][j].R, pixels[i][j].G, pixels[i][j].B);
        }
        fprintf(fp_novo, "\n");
    }
    fclose(fp_novo);
}

int alocarValores(FILE *fp, struct Imagem *imagem, struct RGB ***pixels) {
    char formato[3];
    if (fscanf(fp, "%s", formato) != 1 || strcmp(formato, "P3") != 0) {
        printf("Formato de arquivo inválido ou erro ao ler o formato.\n");
        return 1;
    }

    if (fscanf(fp, "%d %d", &imagem->coluna, &imagem->linha) != 2) {
        printf("Erro ao ler as dimensões da imagem.\n");
        return 1;
    }

    if (fscanf(fp, "%d", &imagem->valorMaximo) != 1) {
        printf("Erro ao ler o valor máximo da cor.\n");
        return 1;
    }

    *pixels = (struct RGB **)malloc(imagem->linha * sizeof(struct RGB *));
    if (*pixels == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    for (int i = 0; i < imagem->linha; i++) {
        (*pixels)[i] = (struct RGB *)malloc(imagem->coluna * sizeof(struct RGB));
        if ((*pixels)[i] == NULL) {
            printf("Erro de alocação de memória.\n");
            for (int k = 0; k < i; k++) {
                free((*pixels)[k]);
            }
            free(*pixels);
            return 1;
        }
        for (int j = 0; j < imagem->coluna; j++) {
            if (fscanf(fp, "%d %d %d", &((*pixels)[i][j].R), &((*pixels)[i][j].G), &((*pixels)[i][j].B)) != 3) {
                printf("Erro ao ler os pixels da imagem.\n");
                for (int k = 0; k < i; k++) {
                    free((*pixels)[k]);
                }
                free(*pixels);
                return 1;
            }
        }
    }
    return 0;
}

void gerarImagemCinza(struct Imagem *imagem, struct RGB **pixels) {
    for (int i = 0; i < imagem->linha; i++) {
        for (int j = 0; j < imagem->coluna; j++) {
            int cinza = (int)((pixels[i][j].R * 0.30) + (pixels[i][j].G * 0.59) + (pixels[i][j].B * 0.11));
            pixels[i][j].R = cinza;
            pixels[i][j].G = cinza;
            pixels[i][j].B = cinza;
        }
    }
    escreverNovaImagem("./imagens_geradas/imagem_cinza.ppm", imagem, pixels);
}

void gerarImagemNegativa(struct Imagem *imagem, struct RGB **pixels) { 
    for (int i = 0; i < imagem->linha; i++) {
        for (int j = 0; j < imagem->coluna; j++) {
            pixels[i][j].R = imagem->valorMaximo - pixels[i][j].R;
            pixels[i][j].G = imagem->valorMaximo - pixels[i][j].G;
            pixels[i][j].B = imagem->valorMaximo - pixels[i][j].B;
        }
    }
    escreverNovaImagem("./imagens_geradas/imagem_negativa.ppm", imagem, pixels);
}

void modificarBrilhoImagem(struct Imagem *imagem, struct RGB **pixels, float valorPercentual) {
    for (int i = 0; i < imagem->linha; i++) {
        for (int j = 0; j < imagem->coluna; j++) {
            int novoR = (int)(pixels[i][j].R / (100 / valorPercentual));
            int novoG = (int)(pixels[i][j].G / (100 / valorPercentual));
            int novoB = (int)(pixels[i][j].B / (100 / valorPercentual));

            pixels[i][j].R = novoR > 255 ? 255 : (novoR < 0 ? 0 : novoR);
            pixels[i][j].G = novoG > 255 ? 255 : (novoG < 0 ? 0 : novoG);
            pixels[i][j].B = novoB > 255 ? 255 : (novoB < 0 ? 0 : novoB);
        }
    }
    escreverNovaImagem("./imagens_geradas/imagemBrilhoModificado.ppm", imagem, pixels);
}

void envelhecerImagem(struct Imagem *imagem, struct RGB **pixels) {
    for (int i = 0; i < imagem->linha; i++) {
        for (int j = 0; j < imagem->coluna; j++) {
            pixels[i][j].R = pixels[i][j].R > 20 ? pixels[i][j].R * 0.63 : 0;
            pixels[i][j].G = pixels[i][j].G > 20 ? pixels[i][j].G * 0.38 : 0;
            pixels[i][j].B = pixels[i][j].B > 20 ? pixels[i][j].B * 0 : 0;
        }
    }
    escreverNovaImagem("./imagens_geradas/imagemEnvelhecida.ppm", imagem, pixels);
}

void rotacionarImagem(struct Imagem *imagem, struct RGB **pixels) {
    struct Imagem novaImagem;
    novaImagem.linha = imagem->coluna;
    novaImagem.coluna = imagem->linha;
    novaImagem.valorMaximo = imagem->valorMaximo;

    struct RGB **pixelsRotacionados = (struct RGB **)malloc(novaImagem.linha * sizeof(struct RGB *));
    for (int i = 0; i < novaImagem.linha; i++) {
        pixelsRotacionados[i] = (struct RGB *)malloc(novaImagem.coluna * sizeof(struct RGB));
    }

    for (int i = 0; i < imagem->linha; i++) {
        for (int j = 0; j < imagem->coluna; j++) {
            pixelsRotacionados[j][imagem->linha - 1 - i] = pixels[i][j];
        }
    }
    escreverNovaImagem("./imagens_geradas/imagem_rotacionada.ppm", &novaImagem, pixelsRotacionados);

    for (int i = 0; i < novaImagem.linha; i++) {
        free(pixelsRotacionados[i]);
    }
    free(pixelsRotacionados);
}
