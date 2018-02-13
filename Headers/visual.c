#include "visual.h"

void print_image(FILE *fptr, WINDOW *w){

    /*Função auxiliar da função Impressão*/

    char read_string[MAX_LEN];
    int i;
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL){
    	wprintw(w, "%s",read_string);
    }}
int impressao(WINDOW *w, char *filename){

    //Função Que imprime as ASCII Arts

    FILE *fptr = NULL;
 
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
 
    print_image(fptr, w);
 
    fclose(fptr);} 
char **Mapa(int *dist, int ripley, int alien) {

    //Função que transforma o grafo em uma matriz

    int vertices = 9;
    char **map = (char **) malloc((TAMN*3 + 2) * sizeof(char *));
    for (int i = 0; i < (TAMN*3 + 2); ++i) {
        map[i] = (char *) malloc((TAMN*3 + 2) * sizeof(char));
    }
    system("clear");
    int c = 1;
    int a = 1;

    for(int i = TAMN*3+1; i >= 0; i--) {
        for(int j = 0; j < TAMN*3+2; j++) {
            if(i == 0 || i == TAMN*3+1) {
                map[i][j] = 'X';
            } else if(j == 0 || j == TAMN*3+1) {
                 map[i][j] = 'X';
            }
        }
    }

    for(int i = TAMN-1; i >= 0; i--) {
        for(int j = 0; j < TAMN; j++) {
            vertices = j * TAMN + i;
            if(dist[vertices] != -1) {
                map[0+a][0+c] = ' ';
                map[0+a][1+c] = ' ';
                map[0+a][2+c] = ' ';
                map[1+a][0+c] = ' ';
                map[1+a][1+c] = ' ';
                map[1+a][2+c] = ' ';
                map[2+a][0+c] = ' ';
                map[2+a][1+c] = ' ';
                map[2+a][2+c] = ' ';
            } else if(dist[vertices] == -1) {
                map[0+a][0+c] = 'X';
                map[0+a][1+c] = 'X';
                map[0+a][2+c] = 'X';
                map[1+a][0+c] = 'X';
                map[1+a][1+c] = 'X';
                map[1+a][2+c] = 'X';
                map[2+a][0+c] = 'X';
                map[2+a][1+c] = 'X';
                map[2+a][2+c] = 'X';
            }
            
            if(vertices == alien) {
                map[a+1][c+1] = 'A';
            } else if(vertices == ripley) {
                map[a+1][c+1] = 'R';
            } else if(vertices == saida) {
                map[a+1][c+1] = 'S';
            }
            
            c += 3; 
            vertices++;
        }
        c = 1;
        a = a+3;
    }
    return map;}//
void PrintMapa(char **map) {

    //Imprime o Mapa 

    WINDOW *w;
    int ch;

    initscr();
    w = newwin(60,170,1,22);
    int x=0, y=0;
    for (int i = TAMN*3 + 1; i >= 0; --i) {
        for (int j = 0; j < TAMN*3+2; ++j) {
                mvwprintw(w,x+5,y+68, "%c%c",map[i][j],map[i][j]);
                x += 1;
            }
        y += 2;
        x = 0;
    }

    wrefresh(w);
    sleep(1);
    delwin(w);
    endwin();}
void PrintMinigame(char **map) {

    //Imprime o minigame

    WINDOW *w;
    int ch, width = 7;

    initscr();
    w = newwin(60,170,1,22);
    int x=0, y=0;
    for (int i = TAMN*3 + 1; i >= 0; --i) {
        for (int j = 0; j < TAMN*3+2; ++j) {
                mvwprintw(w,x+5,y+68, "%c%c",map[i][j],map[i][j]);   
                x += 1;
            }
        y += 2;
        x = 0;
    }

    wrefresh(w);} 
int MainAlien (int grafoEscolhido, int modoAlien){
    srand(time(NULL));
     
    insereGrafo(grafoEscolhido);
    int *dist = vetorDistancias(G, saida); //Caminho que Ripley irá seguir
    int res;
    switch(modoAlien){
        case 1:
            res = PercorreLinear(dist, 0, 9); //Alien linear
            break;
        case 2:
            res = PercorreAleatorio(dist, 0, 9); //Alien spawna aleatoriamente
            break;
        case 3:
            res = PercorreInteligente(dist, 0, 9); //Alien Inteligente
            break;
    }
 	return res;}
int mainJanelaMenu() {

    //Imprime e Faz a interface entre o usuario e o programa no menu principal

    WINDOW *w;
    int ch, i = 0, e = 0,d = 0;
    
    initscr();
    w = newwin( 60, 170, 1, 22 );
    wmove(w, 2, 1);
    impressao(w, "Ascii_ART/image.txt");
    wrefresh( w );
    noecho();
    keypad( w, TRUE );
    curs_set( 0 );
    mvwprintw( w, 17, 2, ">");

    while(( ch = wgetch(w)) != '\n'){ 
            switch( ch ) {
                case KEY_UP:
                            i--;
                            i = ( i<0 ) ? 3 : i;
                            e = 0;
                            d = 0; 
                            break;
                case KEY_DOWN:
                            i++;
                            i = ( i>3 ) ? 0 : i;
                            e = 0;
                            d = 0; 
                            break;
                case KEY_LEFT:
                            e++;
                            break;
                case KEY_RIGHT:
                            d++;
                            break;
            }
            if(e == 3 && d == 1){
                delwin(w);
                endwin();
                return 4;
            } else if (i == 0){ 
                 mvwprintw( w, 24, 2, " ");
                 mvwprintw( w, 40, 2, " "); 
                 mvwprintw( w, 32, 2, " ");
                 mvwprintw( w, 17, 2, ">");
            }
            else if(i == 1){
                 mvwprintw( w, 17, 2, " ");
                 mvwprintw( w, 40, 2, " "); 
                 mvwprintw( w, 32, 2, " ");
                 mvwprintw( w, 24, 2, ">");
            }
            else if(i == 2){
                 mvwprintw( w, 17, 2, " ");
                 mvwprintw( w, 40, 2, " "); 
                 mvwprintw( w, 24, 2, " ");
                 mvwprintw( w, 32, 2, ">");
            }
            else if(i == 3){
                 mvwprintw( w, 32, 2, " ");
                 mvwprintw( w, 24, 2, " ");
                 mvwprintw( w, 17, 2, " ");
                 mvwprintw( w, 40, 2, ">");
            }
    }


 	delwin(w);
    endwin();
	return i;}
int mainJanelaMenuAlien(int escolhido) {

    //Imprime e Faz a interface entre o usuario e o programa no menu de escolha do Alien

    WINDOW *w;
    int ch, i = 0;
    
    initscr();
    w = newwin( 60, 170, 1, 22 );
    impressao(w, "Ascii_ART/image1.txt");   
    wrefresh( w );
    noecho();
    keypad( w, TRUE );
    curs_set( 0 );
    mvwprintw( w, 14, 2, ">"); 

    if(escolhido == 0){
        mvwprintw( w, 14, 60, "<");
        mvwprintw( w, 13, 61, "<");
        mvwprintw( w, 15, 61, "<");
    }
    else if(escolhido == 1){
        mvwprintw( w, 23, 80, "<");
        mvwprintw( w, 22, 81, "<");
        mvwprintw( w, 24, 81, "<");
    }
    else if(escolhido == 2){
        mvwprintw( w, 31, 60, "<");
        mvwprintw( w, 30, 61, "<");
        mvwprintw( w, 32, 61, "<");
    } 

    while(( ch = wgetch(w)) != '\n'){ 
            switch( ch ) {
                case KEY_UP:
                            i--;
                            i = ( i<0 ) ? 2 : i;
                            break;
                case KEY_DOWN:
                            i++;
                            i = ( i>2 ) ? 0 : i;
                            break;

            }
            if (i == 0){ 
                 mvwprintw( w, 23, 2, " "); 
                 mvwprintw( w, 31, 2, " ");
                 mvwprintw( w, 14, 2, ">");
            }
            else if(i == 1){
                 mvwprintw( w, 14, 2, " "); 
                 mvwprintw( w, 31, 2, " ");
                 mvwprintw( w, 23, 2, ">");
            }
            else if(i == 2){
                 mvwprintw( w, 14, 2, " ");
                 mvwprintw( w, 23, 2, " ");
                 mvwprintw( w, 31, 2, ">");
            }
        }


 	delwin(w);
    endwin();
	return i;}
int mainJanelaMenuNostromos(int escolhido) {

    //Imprime e Faz a interface entre o usuario e o programa no menu de escolha da nostromo

    WINDOW *w;
    int ch, i = 0;
    
    initscr();
    w = newwin( 60, 170, 1, 22 );
    impressao(w, "Ascii_ART/image4.txt");
    wrefresh( w );
 
    noecho();
    keypad( w, TRUE );
    curs_set( 0 );

    mvwprintw( w, 15, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    mvwprintw( w, 16, 90, "XX                                          XXXXXX            XX");
    mvwprintw( w, 17, 90, "XX                                          XXXXXX  AA        XX");
    mvwprintw( w, 18, 90, "XX                                          XXXXXX            XX");
    mvwprintw( w, 19, 90, "XX      XXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXXXXXX            XX");
    mvwprintw( w, 20, 90, "XX  RR  XXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXXXXXX            XX");
    mvwprintw( w, 21, 90, "XX      XXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXXXXXX            XX");
    mvwprintw( w, 22, 90, "XX                                          XXXXXXXXXXXX      XX");
    mvwprintw( w, 23, 90, "XX                                          XXXXXXXXXXXX      XX");
    mvwprintw( w, 24, 90, "XX                                          XXXXXXXXXXXX      XX");
    mvwprintw( w, 25, 90, "XXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXX            XXXXXX      XX");
    mvwprintw( w, 26, 90, "XXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXX            XXXXXX      XX");
    mvwprintw( w, 27, 90, "XXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXX            XXXXXX      XX");
    mvwprintw( w, 28, 90, "XXXXXXXX      XXXXXX      XXXXXX                              XX");
    mvwprintw( w, 29, 90, "XXXXXXXX      XXXXXX      XXXXXX                              XX");
    mvwprintw( w, 30, 90, "XXXXXXXX      XXXXXX      XXXXXX                              XX");
    mvwprintw( w, 31, 90, "XX            XXXXXX      XXXXXX      XXXXXXXXXXXXXXXXXXXXXXXXXX");
    mvwprintw( w, 32, 90, "XX            XXXXXX      XXXXXX      XXXXXXXXXXXXXXXXXXXXXXXXXX");
    mvwprintw( w, 33, 90, "XX            XXXXXX      XXXXXX      XXXXXXXXXXXXXXXXXXXXXXXXXX");
    mvwprintw( w, 34, 90, "XX      XXXXXXXXXXXX      XXXXXX                              XX");
    mvwprintw( w, 35, 90, "XX      XXXXXXXXXXXX      XXXXXX                              XX");
    mvwprintw( w, 36, 90, "XX      XXXXXXXXXXXX      XXXXXX                              XX");
    mvwprintw( w, 37, 90, "XX            XXXXXX                  XXXXXXXXXXXXXXXXXX      XX");
    mvwprintw( w, 38, 90, "XX            XXXXXX                  XXXXXXXXXXXXXXXXXX      XX");
    mvwprintw( w, 39, 90, "XX            XXXXXX                  XXXXXXXXXXXXXXXXXX      XX");
    mvwprintw( w, 40, 90, "XX            XXXXXXXXXXXXXXXXXX                  XXXXXX      XX");
    mvwprintw( w, 41, 90, "XX            XXXXXXXXXXXXXXXXXX                  XXXXXX      XX");
    mvwprintw( w, 42, 90, "XX            XXXXXXXXXXXXXXXXXX                  XXXXXX      XX");
    mvwprintw( w, 43, 90, "XXXXXXXX                              XXXXXXXXXXXXXXXXXX      XX");
    mvwprintw( w, 44, 90, "XXXXXXXX                              XXXXXXXXXXXXXXXXXX  SS  XX");
    mvwprintw( w, 45, 90, "XXXXXXXX                              XXXXXXXXXXXXXXXXXX      XX");
    mvwprintw( w, 46, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

    mvwprintw( w, 15, 2, ">");

    if(escolhido == 0){
        mvwprintw( w, 15, 50, "<");
        mvwprintw( w, 16, 51, "<");
        mvwprintw( w, 14, 51, "<");
    }
    else if(escolhido == 1){
        mvwprintw( w, 24, 50, "<");
        mvwprintw( w, 23, 51, "<");
        mvwprintw( w, 25, 51, "<");
    }
    else if(escolhido == 2){
        mvwprintw( w, 34, 50, "<");
        mvwprintw( w, 35, 51, "<");
        mvwprintw( w, 33, 51, "<");
    }
    else if(escolhido == 3){
        mvwprintw( w, 44, 50, "<");
        mvwprintw( w, 43, 51, "<");
        mvwprintw( w, 45, 51, "<");
    }

    while(( ch = wgetch(w)) != '\n'){ 
            switch( ch ) {
                case KEY_UP:
                            i--;
                            i = ( i<0 ) ? 3 : i;
                            break;
                case KEY_DOWN:
                            i++;
                            i = ( i>3 ) ? 0 : i;
                            break;
            }
            if (i == 0){ 
                mvwprintw( w, 15, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 16, 90, "XX                                          XXXXXX            XX");
                mvwprintw( w, 17, 90, "XX                                          XXXXXX  AA        XX");
                mvwprintw( w, 18, 90, "XX                                          XXXXXX            XX");
                mvwprintw( w, 19, 90, "XX      XXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXXXXXX            XX");
                mvwprintw( w, 20, 90, "XX  RR  XXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXXXXXX            XX");
                mvwprintw( w, 21, 90, "XX      XXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXXXXXX            XX");
                mvwprintw( w, 22, 90, "XX                                          XXXXXXXXXXXX      XX");
                mvwprintw( w, 23, 90, "XX                                          XXXXXXXXXXXX      XX");
                mvwprintw( w, 24, 90, "XX                                          XXXXXXXXXXXX      XX");
                mvwprintw( w, 25, 90, "XXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXX            XXXXXX      XX");
                mvwprintw( w, 26, 90, "XXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXX            XXXXXX      XX");
                mvwprintw( w, 27, 90, "XXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXX            XXXXXX      XX");
                mvwprintw( w, 28, 90, "XXXXXXXX      XXXXXX      XXXXXX                              XX");
                mvwprintw( w, 29, 90, "XXXXXXXX      XXXXXX      XXXXXX                              XX");
                mvwprintw( w, 30, 90, "XXXXXXXX      XXXXXX      XXXXXX                              XX");
                mvwprintw( w, 31, 90, "XX            XXXXXX      XXXXXX      XXXXXXXXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 32, 90, "XX            XXXXXX      XXXXXX      XXXXXXXXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 33, 90, "XX            XXXXXX      XXXXXX      XXXXXXXXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 34, 90, "XX      XXXXXXXXXXXX      XXXXXX                              XX");
                mvwprintw( w, 35, 90, "XX      XXXXXXXXXXXX      XXXXXX                              XX");
                mvwprintw( w, 36, 90, "XX      XXXXXXXXXXXX      XXXXXX                              XX");
                mvwprintw( w, 37, 90, "XX            XXXXXX                  XXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 38, 90, "XX            XXXXXX                  XXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 39, 90, "XX            XXXXXX                  XXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 40, 90, "XX            XXXXXXXXXXXXXXXXXX                  XXXXXX      XX");
                mvwprintw( w, 41, 90, "XX            XXXXXXXXXXXXXXXXXX                  XXXXXX      XX");
                mvwprintw( w, 42, 90, "XX            XXXXXXXXXXXXXXXXXX                  XXXXXX      XX");
                mvwprintw( w, 43, 90, "XXXXXXXX                              XXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 44, 90, "XXXXXXXX                              XXXXXXXXXXXXXXXXXX  SS  XX");
                mvwprintw( w, 45, 90, "XXXXXXXX                              XXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 46, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");          
                mvwprintw( w, 24, 2, " ");
                mvwprintw( w, 44, 2, " "); 
                mvwprintw( w, 34, 2, " ");
                mvwprintw( w, 15, 2, ">");
            }
            else if(i == 1){

                mvwprintw( w, 15, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 16, 90, "XX                                                            XX");
                mvwprintw( w, 17, 90, "XX                                                            XX");
                mvwprintw( w, 18, 90, "XX                                                            XX");
                mvwprintw( w, 19, 90, "XX                                                            XX");
                mvwprintw( w, 20, 90, "XX  RR                                                    AA  XX");
                mvwprintw( w, 21, 90, "XX                                                            XX");
                mvwprintw( w, 22, 90, "XX                                                            XX");
                mvwprintw( w, 23, 90, "XX                                                            XX");
                mvwprintw( w, 24, 90, "XX                                                            XX");
                mvwprintw( w, 25, 90, "XX                                                            XX");
                mvwprintw( w, 26, 90, "XX                                                            XX");
                mvwprintw( w, 27, 90, "XX                                                            XX");
                mvwprintw( w, 28, 90, "XX                                                            XX");
                mvwprintw( w, 29, 90, "XX                                                            XX");
                mvwprintw( w, 30, 90, "XX                                                            XX");
                mvwprintw( w, 31, 90, "XX                                                            XX");
                mvwprintw( w, 32, 90, "XX                                                            XX");
                mvwprintw( w, 33, 90, "XX                                                            XX");
                mvwprintw( w, 34, 90, "XX                                                            XX");
                mvwprintw( w, 35, 90, "XX                                                            XX");
                mvwprintw( w, 36, 90, "XX                                                            XX");
                mvwprintw( w, 37, 90, "XX                                                            XX");
                mvwprintw( w, 38, 90, "XX                                                            XX");
                mvwprintw( w, 39, 90, "XX                                                            XX");
                mvwprintw( w, 40, 90, "XX                                                            XX");
                mvwprintw( w, 41, 90, "XX                                                            XX");
                mvwprintw( w, 42, 90, "XX                                                            XX");
                mvwprintw( w, 43, 90, "XX                                                            XX");
                mvwprintw( w, 44, 90, "XX                                                        SS  XX");
                mvwprintw( w, 45, 90, "XX                                                            XX");
                mvwprintw( w, 46, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 15, 2, " ");
                mvwprintw( w, 44, 2, " "); 
                mvwprintw( w, 34, 2, " ");
                mvwprintw( w, 24, 2, ">");
            }
            else if(i == 2){
                mvwprintw( w, 15, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 16, 90, "XX                        XXXXXXXXXXXX                        XX");
                mvwprintw( w, 17, 90, "XX                        XXXXXXXXXXXX              AA        XX");
                mvwprintw( w, 18, 90, "XX                        XXXXXXXXXXXX                        XX");
                mvwprintw( w, 19, 90, "XX      XXXXXXXXXXXX            XXXXXX      XXXXXXXXXXXX      XX");
                mvwprintw( w, 20, 90, "XX  RR  XXXXXXXXXXXX            XXXXXX      XXXXXXXXXXXX      XX");
                mvwprintw( w, 21, 90, "XX      XXXXXXXXXXXX            XXXXXX      XXXXXXXXXXXX      XX");
                mvwprintw( w, 22, 90, "XX                                                            XX");
                mvwprintw( w, 23, 90, "XX                                                            XX");
                mvwprintw( w, 24, 90, "XX                                                            XX");
                mvwprintw( w, 25, 90, "XXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 26, 90, "XXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 27, 90, "XXXXXXXXXXXXXXXXXXXX      XXXXXXXXXXXX      XXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 28, 90, "XXXXXXXX                        XXXXXX            XXXXXXXXXXXXXX");
                mvwprintw( w, 29, 90, "XXXXXXXX                        XXXXXX            XXXXXXXXXXXXXX");
                mvwprintw( w, 30, 90, "XXXXXXXX                        XXXXXX            XXXXXXXXXXXXXX");
                mvwprintw( w, 31, 90, "XXXXXXXX      XXXXXXXXXXXX      XXXXXX                        XX");
                mvwprintw( w, 32, 90, "XXXXXXXX      XXXXXXXXXXXX      XXXXXX                        XX");
                mvwprintw( w, 33, 90, "XXXXXXXX      XXXXXXXXXXXX      XXXXXX                        XX");
                mvwprintw( w, 34, 90, "XXXXXXXX      XXXXXX            XXXXXX      XXXXXXXXXXXX      XX");
                mvwprintw( w, 35, 90, "XXXXXXXX      XXXXXX            XXXXXX      XXXXXXXXXXXX      XX");
                mvwprintw( w, 36, 90, "XXXXXXXX      XXXXXX            XXXXXX      XXXXXXXXXXXX      XX");
                mvwprintw( w, 37, 90, "XXXXXXXX      XXXXXX                              XXXXXX      XX");
                mvwprintw( w, 38, 90, "XXXXXXXX      XXXXXX                              XXXXXX      XX");
                mvwprintw( w, 39, 90, "XXXXXXXX      XXXXXX                              XXXXXX      XX");
                mvwprintw( w, 40, 90, "XXXXXXXX                  XXXXXXXXXXXXXXXXXX      XXXXXX      XX");
                mvwprintw( w, 41, 90, "XXXXXXXX                  XXXXXXXXXXXXXXXXXX      XXXXXX      XX");
                mvwprintw( w, 42, 90, "XXXXXXXX                  XXXXXXXXXXXXXXXXXX      XXXXXX      XX");
                mvwprintw( w, 43, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                  XXXXXX      XX");
                mvwprintw( w, 44, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                  XXXXXX  SS  XX");
                mvwprintw( w, 45, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                  XXXXXX      XX");
                mvwprintw( w, 46, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 15, 2, " ");
                mvwprintw( w, 44, 2, " "); 
                mvwprintw( w, 24, 2, " ");
                mvwprintw( w, 34, 2, ">");
            }
            else if(i == 3){
                mvwprintw( w, 15, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");   
                mvwprintw( w, 16, 90, "XX      XXXXXXXXXXXX            XXXXXX                        XX");
                mvwprintw( w, 17, 90, "XX      XXXXXXXXXXXX            XXXXXX                        XX");
                mvwprintw( w, 18, 90, "XX      XXXXXXXXXXXX            XXXXXX                        XX");
                mvwprintw( w, 19, 90, "XX      XXXXXX                              XXXXXXXXXXXX      XX");
                mvwprintw( w, 20, 90, "XX  RR  XXXXXX                              XXXXXXXXXXXX  AA  XX");
                mvwprintw( w, 21, 90, "XX      XXXXXX                              XXXXXXXXXXXX      XX");
                mvwprintw( w, 22, 90, "XX                  XXXXXX                                    XX");
                mvwprintw( w, 23, 90, "XX                  XXXXXX                                    XX");
                mvwprintw( w, 24, 90, "XX                  XXXXXX                                    XX");
                mvwprintw( w, 25, 90, "XXXXXXXXXXXXXX      XXXXXX      XXXXXXXXXXXXXXXXXX      XXXXXXXX");
                mvwprintw( w, 26, 90, "XXXXXXXXXXXXXX      XXXXXX      XXXXXXXXXXXXXXXXXX      XXXXXXXX");
                mvwprintw( w, 27, 90, "XXXXXXXXXXXXXX      XXXXXX      XXXXXXXXXXXXXXXXXX      XXXXXXXX");
                mvwprintw( w, 28, 90, "XX                              XXXXXXXXXXXX            XXXXXXXX");
                mvwprintw( w, 29, 90, "XX                              XXXXXXXXXXXX            XXXXXXXX");
                mvwprintw( w, 30, 90, "XX                              XXXXXXXXXXXX            XXXXXXXX");
                mvwprintw( w, 31, 90, "XX            XXXXXXXXXXXX            XXXXXX      XXXXXXXXXXXXXX");
                mvwprintw( w, 32, 90, "XX            XXXXXXXXXXXX            XXXXXX      XXXXXXXXXXXXXX");
                mvwprintw( w, 33, 90, "XX            XXXXXXXXXXXX            XXXXXX      XXXXXXXXXXXXXX");
                mvwprintw( w, 34, 90, "XX                                    XXXXXX                  XX");
                mvwprintw( w, 35, 90, "XX                                    XXXXXX                  XX");
                mvwprintw( w, 36, 90, "XX                                    XXXXXX                  XX");
                mvwprintw( w, 37, 90, "XX      XXXXXX      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 38, 90, "XX      XXXXXX      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 39, 90, "XX      XXXXXX      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 40, 90, "XX      XXXXXX                  XXXXXXXXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 41, 90, "XX      XXXXXX                  XXXXXXXXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 42, 90, "XX      XXXXXX                  XXXXXXXXXXXXXXXXXXXXXXXX      XX");
                mvwprintw( w, 43, 90, "XX      XXXXXXXXXXXXXXXXXX                                    XX");
                mvwprintw( w, 44, 90, "XX      XXXXXXXXXXXXXXXXXX                                SS  XX");
                mvwprintw( w, 45, 90, "XX      XXXXXXXXXXXXXXXXXX                                    XX");
                mvwprintw( w, 46, 90, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                mvwprintw( w, 34, 2, " ");
                mvwprintw( w, 24, 2, " ");
                mvwprintw( w, 15, 2, " ");
                mvwprintw( w, 44, 2, ">");
            }

    }

 	delwin(w);
    endwin();
	return i;}
int mainJanelaMenuRepeticao(int batata) {

    //Imprime e Faz a interface entre o usuario e o programa no menu de escolha DA OPCAO DE CONTINUAR OU RESETAR O JOGO

    WINDOW *w;
    int ch, i = 0;
    
    initscr();
    w = newwin(60,170,1,22);
    wmove(w, 2, 1);
    if(batata == 1)
        impressao(w, "Ascii_ART/gameover.txt");
    else if(batata == 0)
        impressao(w, "Ascii_ART/youwin.txt"); 

    wrefresh(w);
    noecho();
    keypad( w, TRUE );
    curs_set(0);
     
    mvwprintw( w, 13, 2, ">"); 
    while(( ch = wgetch(w)) != '\n'){ 

            switch( ch ) {
                case KEY_UP:
                            i--;
                            i = ( i<0 ) ? 1 : i;
                            break;
                case KEY_DOWN:
                            i++;
                            i = ( i>1 ) ? 0 : i;
                            break;
            }

            if (i == 0){ 
                mvwprintw( w, 21, 2, " ");
                mvwprintw( w, 13, 2, ">");
            }
            else if(i == 1){
                mvwprintw( w, 13, 2, " ");
                mvwprintw( w, 21, 2, ">");
            }

    }

    delwin(w);
    endwin();
    return i;}//Imprime e Faz a interface entre o usuario e o programa no menu de game over
int mainJanelaMenuGameMode() {

    //Imprime e Faz a interface entre o usuario e o programa no menu de entrada no Minigame

    WINDOW *w;
    int ch, i = 0;
    
    initscr();
    w = newwin(60,170,1,22);
    wmove(w, 2, 1);
    impressao(w, "Ascii_ART/image5.txt");
    wrefresh(w);
    noecho();
    keypad( w, TRUE );
    curs_set( 0 );
     

    while(( ch = wgetch(w)) != '\n')

    delwin(w);
    endwin();
    return i;}//Imprime e Faz a interface entre o usuario e o programa no menu 
int prologue (){
    
    //Printa o Prologo na tela

    FILE *f;
    f = fopen("Ascii_ART/inicio.txt", "r");
    int count  = 0;
    char c[200];
    while(!feof(f)){
        fgets(c, 200, f);
        printf("%s", c);
        usleep(10000);
        if(count == 127){
            system("sleep 6s");
            system("clear");

        } 
        count++;
        
    }
    system("sleep 6s");
    return 0;}
int creditos(){
    FILE *f;
    int count = 0;
    char c[200];
    f = fopen("Ascii_ART/creditos.txt", "r");
    system("clear");
    while(!feof(f)){
        count++;
        fgets(c, 200, f);
        printf("%s", c);
        if(count == 8)
            system("sleep 4s");
        if(count == 12)
           system("sleep 7s");
        if(count == 27)
           system("sleep 4s");
        if(count == 39)
           system("sleep 3s");
        if(count == 49)
           system("sleep 7s");
        if(count == 56)
           system("sleep 7s");
        else 
           system("sleep 1.5s");

    }
    return 0;}    
int Minigame(int ripley, int grafo, int dificuldade){

    //Função de controle do Minigame

    WINDOW *w;
    int ch = ' ', i = 0;
    int v = ripley;
    int alien = 9;
    insereGrafo(grafo);
    int *dist = vetorDistancias(G, saida);
    
    initscr();
    w = newwin( 60, 170, 1, 22 );
    wmove(w, 2, 1);
    wrefresh( w );
    noecho();
    keypad( w, TRUE );
    curs_set( 0 );

    PrintMinigame( Mapa(dist, 0, alien) );
    int Tinicial = clock();
    while(v != saida) {         
        if(_kbhit()) {
        	ch = wgetch(w);
	        switch( ch ) {
	            case 'w':
	                    if(v-10 >= 0 && dist[v-10] != -1)
	                        v = v-10;
	                        break;
	            case 's':
	                    if(v+10 <= 99 && dist[v+10] != -1)
	                        v = v+10;
	                        break;
	            case 'a':
	                    if(v-1 >= 0 && dist[v-1] != -1 && v%10 > 0)
	                        v--;
	                        break;
	            case 'd':
	                    if(v+1 <= 99 && dist[v+1] != -1 && (v)%10 < 9)
	                        v++;
	                        break;
	            default:
	            			break;
	        }
	        endwin();
        	PrintMinigame( Mapa(dist, v, alien) );
	    }
        if((clock()-Tinicial) / (CLOCKS_PER_SEC / 1000) >= (700 / dificuldade)) {
    		alien = AlienInteligente(v, alien);
    		endwin();
        	PrintMinigame( Mapa(dist, v, alien) );
        	Tinicial = clock();
		}
    	if(G[alien][v] == 1 || alien == v){
            sleep(1);
            return 1;
    	}
    }
    sleep(1);
    return 0;}