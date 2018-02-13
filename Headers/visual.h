#ifndef VISUAL_H
#define VISUAL_H
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include "grafo.h"
#include "kbhit.h"
#define MAX_LEN 128
#define TAMN 10
#define TAMG 100 
#define saida 99

void print_image(FILE *fptr, WINDOW *w);
int impressao(WINDOW *w, char *filename);
char **Mapa(int *dist, int ripley, int alien);
void PrintMapa(char **map);
void PrintMinigame(char **map);
int MainAlien (int grafoEscolhido, int modoAlien);
int mainJanelaMenu();
int mainJanelaMenuAlien(int escolhido);
int mainJanelaMenuNostromos(int escolhido);
int mainJanelaMenuRepeticao(int batata);
int mainJanelaMenuGameMode();
int prologue();
int creditos();
int Minigame(int ripley, int grafo, int dificuldade);
#endif