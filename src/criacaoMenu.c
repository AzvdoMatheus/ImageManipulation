#include "manipulacaoPixels.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirMenuOpcoes();

void abrirMenuOpcoes() {
    int op;
    int qtdImagensCinza = 0;
    float valorPercentual;
    char nomeArquivo[30];
    struct Imagem imagem;
    struct RGB **pixels = NULL;
    int imagemCarregada = 0;

    do {
        printf("\n\n========== Menu opcoes ==========\n\n");
        printf("1- Inserir nova imagem\n");
        printf("2- Gerar uma imagem tons de cinza\n");
        printf("3- Imagem colorida - envelhecimento da imagem\n");
        printf("4- Rotacionar a imagem colorida – 90º\n");
        printf("5- Acessar menu de imagens cinzas\n");
        printf("6- Sair\n");
        printf("\nInsira a opcao desejada: ");
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
                imagemCarregada = 1;
                printf("\n|----------------------------|\n");
                printf("|Imagem carregada com sucesso|\n");
                printf("|----------------------------|\n");
                break;

            case 2:
                if (!imagemCarregada) {
                    printf("\n|-------------------------|\n");
                    printf("|Nenhuma imagem carregada.|\n");
                    printf("|-------------------------|\n");
                    break;
                }
                gerarImagemCinza(&imagem, pixels);
                qtdImagensCinza++;
                printf("\n|------------------------------------------|\n");
                printf("|Imagem em tons de cinza gerada com sucesso|\n");
                printf("|------------------------------------------|\n");
                break;

            case 3:
                if (!imagemCarregada) {
                    printf("\n|------------------------|\n");
                    printf("|Nenhuma imagem carregada|\n");
                    printf("|------------------------|\n");
                    break;
                }
                envelhecerImagem(&imagem, pixels);
                printf("\n|-------------------------------------|\n");
                printf("|Imagem envelhecida gerada com sucesso|\n");
                printf("|-------------------------------------|\n");
                break;

            case 4:
                if (!imagemCarregada) {
                    printf("\n|------------------------|\n");
                    printf("|Nenhuma imagem carregada|\n");
                    printf("|------------------------|\n");
                    break;
                }
                rotacionarImagem(&imagem, pixels);
                printf("\n|----------------------------------------------|\n");
                printf("|Imagem rotacionada 90 graus gerada com sucesso|\n");
                printf("|----------------------------------------------|\n");
                break;

            case 5: {
                if (!imagemCarregada) {
                    printf("\n|------------------------|\n");
                    printf("|Nenhuma imagem carregada|\n");
                    printf("|------------------------|\n");
                    break;
                }
                int sub_op;
                do {
                    printf("\n\n========== Opcoes imagens cinzas ==========\n\n");
                    printf("1- Gerar imagem negativa\n");
                    printf("2- Modificar brilho da imagem\n");
                    printf("3- Retornar ao menu principal\n");
                    printf("\nInsira a opcao desejada: ");
                    scanf("%d", &sub_op);

                    switch (sub_op) {
                        case 1:
                            gerarImagemNegativa(&imagem, pixels);
                            printf("\n|----------------------------------|\n");
                            printf("|Imagem negativa gerada com sucesso|\n");
                            printf("|----------------------------------|\n");
                            break;

                        case 2:
                            printf("Indique qual a porcentagem de brilho deseja modificar(0 - 100): ");
                            scanf("%f", &valorPercentual);
                            if (valorPercentual < 0 || valorPercentual > 100) {
                                printf("\n|--------------------------------|\n");
                                printf("|Valor inválido. Tente novamente.|\n");
                                printf("|--------------------------------|\n");
                                break;
                            }
                            modificarBrilhoImagem(&imagem, pixels, valorPercentual);
                            printf("\n|----------------------------|\n");
                            printf("|Brilho modificado com sucesso|\n");
                            printf("|----------------------------|\n");
                            break;

                        case 3:
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
                } while (sub_op != 3);
                break;
            }

            case 6:
                if (pixels != NULL) {
                    for (int i = 0; i < imagem.linha; i++) {
                        free(pixels[i]);
                    }
                    free(pixels);
                }
                printf("\n|-------------------|\n");
                printf("|Fechando o programa|\n");
                printf("|-------------------|\n\n");
                exit(0);

            default:
                printf("\n|-------------------------------|\n");
                printf("|Opção inválida. Tente novamente|\n");
                printf("|-------------------------------|\n");
                break;
        }
    } while (op != 6);
}
