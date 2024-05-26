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
void abrirMenuOpcoes();
int alocarValores(FILE *fp, struct Imagem *imagem, struct RGB ***pixels);
void escreverNovaImagem(char nomeArquivo[], struct Imagem *imagem, struct RGB **pixels);
void gerarImagemCinza(struct Imagem *imagem, struct RGB **pixels);
void gerarImagemNegativa(struct Imagem *imagem, struct RGB **pixels);
void rotacionarImagem(struct Imagem *imagem, struct RGB **pixels);

void abrirMenuOpcoes() {
    int op;
    char nomeArquivo[30];
    struct Imagem imagem;
    struct RGB **pixels = NULL;

    do {
        printf("\n\n========== Menu opcoes ==========\n\n");
        printf("1- Inserir nova imagem\n");
        printf("2- Gerar uma imagem tons de cinza\n");
        printf("3- Imagem colorida - envelhecimento da imagem\n");
        printf("4- Rotacionar a imagem colorida – 90º\n");
        printf("5- Acessar menu de imagens cinzas\n");
        printf("6- Sair\n");
        printf("Insira a opcao desejada: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
            printf("Insira o caminho do arquivo (deve estar em .ppm): ");
            scanf("%s", nomeArquivo);
            FILE *fp = abrirArquivo(nomeArquivo);
            if (fp == NULL) {
                printf("\n|-----------------------|\n");
                printf("|Erro ao abrir o arquivo|\n");
                printf("|-----------------------|\n");
                break;
            }
            if (alocarValores(fp, &imagem, &pixels) != 0) {
                fclose(fp);
                printf("\n|----------------------|\n");
                printf("|Erro ao alocar valores|\n");
                printf("|----------------------|\n");
                break;
            }
            fclose(fp);
            printf("\n|----------------------------|\n");
            printf("|Imagem carregada com sucesso|\n");
            printf("|----------------------------|\n");
            break;

        case 2:
            gerarImagemCinza(&imagem, pixels);
            printf("\n|------------------------------------------|\n");
            printf("|Imagem em tons de cinza gerada com sucesso|\n");
            printf("|------------------------------------------|\n");
            break;

        // envelhecer imagem
        case 3:

            break;

        //rotacionar 90 graus
        //inverter valores de x com y
        case 4:
            rotacionarImagem(&imagem, pixels);
            printf("\n|------------------------------------------|\n");
            printf("|Imagem rotacionada 90 graus com sucesso|\n");
            printf("|------------------------------------------|\n");
            break;

        case 5:
            op = 0;
            do { 
                printf("\n\n========== Opcoes imagens cinzas ==========\n\n");
                printf("\n1- Gerar imagem negativa\n");
                printf("2- Aumentar o brilho\n");
                printf("3- Diminuir o brilho\n");
                printf("4- Retornar ao menu principal\n");
                printf("Insira a opcao desejada: ");
                scanf("%d", &op);

                switch (op) {
                    case 1:
                        gerarImagemNegativa(&imagem, pixels);
                        printf("\n|--------------------------------|\n");
                        printf("|Imagem negativa gerada com sucesso|\n");
                        printf("|----------------------------------|\n");
                        break;

                // aumentar brilho
                    case 2:

                        break;

                // diminuir brilho
                    case 3:

                        break;

                    case 4:
                        printf("\n|----------------------------|\n");
                        printf("|Retornando ao menu principal|\n");
                        printf("|----------------------------|\n");
                        break;

                    default:
                        printf("\n|-------------------------------|\n");
                        printf("|Opção inválida. Tente novamente|\n");
                        printf("|-------------------------------|\n");
                        break;
                }
            } while (op != 4);

        case 6:
            printf("\n|-------------------|\n");
            printf("|Fechando o programa|\n");
            printf("|-------------------|\n");
            break;

        default:
            printf("\n|-------------------------------|\n");
            printf("|Opção inválida. Tente novamente|\n");
            printf("|-------------------------------|\n");
            break;
        }
    } while (op != 5);
}

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