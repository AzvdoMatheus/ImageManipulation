#include "manipulacaoPixels.c"
#include <stdio.h>
#include <string.h>

void abrirMenuOpcoes();

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
                // Lógica para envelhecimento da imagem
                break;

            // rotacionar 90 graus
            case 4:
                rotacionarImagem(&imagem, pixels);
                printf("\n|------------------------------------------|\n");
                printf("|Imagem rotacionada 90 graus com sucesso|\n");
                printf("|------------------------------------------|\n");
                break;

            case 5: {
                int sub_op;
                do {
                    printf("\n\n========== Opcoes imagens cinzas ==========\n\n");
                    printf("1- Gerar imagem negativa\n");
                    printf("2- Aumentar o brilho\n");
                    printf("3- Diminuir o brilho\n");
                    printf("4- Retornar ao menu principal\n");
                    printf("Insira a opcao desejada: ");
                    scanf("%d", &sub_op);

                    switch (sub_op) {
                        case 1:
                            gerarImagemNegativa(&imagem, pixels);
                            printf("\n|--------------------------------|\n");
                            printf("|Imagem negativa gerada com sucesso|\n");
                            printf("|----------------------------------|\n");
                            break;

                        // aumentar brilho
                        case 2:
                            // Lógica para aumentar o brilho
                            break;

                        // diminuir brilho
                        case 3:
                            // Lógica para diminuir o brilho
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
                } while (sub_op != 4);
                break;
            }

            case 6:
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
