#include <stdlib.h>
#include <stdio.h>
#ifndef manipulacaoPixels_h
#define manipulacaoPixels_h

FILE* abrirArquivo(char nomeArquivo[]);
int alocarValores(FILE *fp, struct Imagem *imagem, struct RGB ***pixels);
void gerarImagemCinza(struct Imagem *imagem, struct RGB **pixels);
void gerarImagemNegativa(struct Imagem *imagem, struct RGB **pixels);
void modificarBrilhoImagem(struct Imagem *imagem, struct RGB **pixels, float valorPercentual);
void rotacionarImagem(struct Imagem *imagem, struct RGB **pixels);
void envelhecerImagem(struct Imagem *imagem, struct RGB **pixels);
void escreverNovaImagem(char nomeArquivo[], struct Imagem *imagem, struct RGB **pixels);
void saturarImagemCinza(struct Imagem *imagem, struct RGB **pixels);

#endif