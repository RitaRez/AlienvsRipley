#ifndef GRAFO_H
#define GRAFO_H
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include "fila.h"
#include "kbhit.h"
#include "visual.h"
#define MAX_LEN 128
#define TAMN 10
#define TAMG 100 
#define saida 99
int **G;
int **criaGrafo();
void insereGrafo(int grafo);
int *vetorDistancias(int **m, int ini);
int Busca(int ripley, int *dist);
int BuscaFoge(int ripley, int alien);
int CaminhoAlienLinear(int alien, Fila *f);
int PercorreLinear(int *dist, int ripley, int alien);
int CaminhoAlienAleatorio();
int PercorreAleatorio(int *dist, int ripley, int alien);
int AlienInteligente(int ripley, int alien);
int PercorreInteligente(int *dist, int ripley, int alien);
#endif