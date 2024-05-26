#include <stdlib.h>
#include <stdio.h>
#ifndef manipulacaoPixels_h
#define manipulacaoPixels_h

FILE* abrirArquivo(char nomeArquivo[]);
void abrirMenuOpcoes();
int alocarValores(FILE *fp, struct Imagem *imagem, struct RGB ***pixels);
void gerarImagemCinza(struct Imagem *imagem, struct RGB **pixels);
void gerarImagemNegativa(struct Imagem *imagem, struct RGB **pixels);
FILE* aumentarBrilhoImagem();
FILE* diminuiBrilhoImagem();
void rotacionarImagem(struct Imagem *imagem, struct RGB **pixels);
FILE* envelhecerImagem();
void escreverNovaImagem(char nomeArquivo[], struct Imagem *imagem, struct RGB **pixels);

#endif