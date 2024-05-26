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
    escreverNovaImagem("imagem_cinza.ppm", imagem, pixels);
}

void gerarImagemNegativa(struct Imagem *imagem, struct RGB **pixels) { 
    for (int i = 0; i < imagem->linha; i++) {
        for (int j = 0; j < imagem->coluna; j++) {
            pixels[i][j].R = imagem->valorMaximo - pixels[i][j].R;
            pixels[i][j].G = imagem->valorMaximo - pixels[i][j].G;
            pixels[i][j].B = imagem->valorMaximo - pixels[i][j].B;
        }
    }
    escreverNovaImagem("imagem_negativa.ppm", imagem, pixels);
}

// 1.3
void aumentarBrihoImagem(struct Imagem *imagem, struct RGB **pixels) {

}

void diminuirBrilhoImagem(struct Imagem *imagem, struct RGB **pixels) {
    
}

void envelhecerImagem(struct Imagem *imagem, struct RGB **pixels) {
    
}

void rotacionarImagem(struct Imagem *imagem, struct RGB **pixels) {
    FILE *fp_novo = fopen("imagem_rotacionada.ppm", "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    fprintf(fp_novo, "P3\n");
    fprintf(fp_novo, "%d %d\n", imagem->linha, imagem->coluna);  
    fprintf(fp_novo, "%d\n", imagem->valorMaximo);

    for (int i = 0; i < imagem->coluna; i++) {
        for (int j = imagem->linha - 1; j >= 0; j--) {
            fprintf(fp_novo, "%d %d %d ", pixels[j][i].R, pixels[j][i].G, pixels[j][i].B);
        }
        fprintf(fp_novo, "\n");
    }
    fclose(fp_novo);
}