#include "grafo.h"

int **criaGrafo(){
    int **matriz = (int**)malloc((TAMG)*sizeof(int*));
    for (int i = 0; i < TAMG; ++i){
        matriz[i] = (int*)malloc(TAMG*sizeof(int));
    }
    return matriz;}
void insereGrafo(int grafo){
	G = criaGrafo();
	int a,b;
	for (int i = 0; i < TAMG; ++i){
		for (int j = 0; j < TAMG; ++j){
			G[i][j] = 0;
		}
	}
	FILE *f;
    switch(grafo){
        case 1:
	        f = fopen("Mapas/1.txt", "r");
            break;
	    case 2:
            f = fopen("Mapas/2.txt", "r");
            break;
        case 3:
            f = fopen("Mapas/3.txt", "r");
            break;
        case 4:
            f = fopen("Mapas/4.txt", "r");
            break;
        default: exit(1);
        	break;
    }

    while (!feof(f)){
		fscanf(f,"%d %d\n", &a, &b);
		G[a][b] = 1;
	}
	fclose(f);}
int *vetorDistancias(int **m, int ini){
    Fila *f = fila_cria_vet();
    int *res = (int*) malloc (TAMG*sizeof(int));
    for(int i = 0; i <TAMG; ++i){
        res[i] = -1;
    }
    res[ini] = 0;

    fila_insere_vet(f, ini);
    do{
        ini = fila_retira_vet(f);
        for (int i = 0; i < TAMG; ++i){ 
            if (m[ini][i] == 1 && res[i] == -1){ //ini = saida
                fila_insere_vet(f, i); 
                res[i] = res[ini]+1;
            }
        }
    }while(!fila_vazia_vet(f));
    return res;}
int Busca(int ripley, int *dist){
    int v, menor = TAMG;
    for (int i = 0; i < TAMG; ++i){
        if (G[ripley][i] == 1){ //Caso adjacente
        	if(rand()%2) {
	            if(dist[i] < menor){ //Se este vertice possuir menor distancia
	                menor = dist[i];            
	                v = i;
	            }
        	} else {
        		if(dist[i] <= menor){ //Se este vertice possuir menor distancia
	                menor = dist[i];            
	                v = i;
	            }
	        }
        }
    } 
    return v;}
int BuscaFoge(int ripley, int alien){
	int *distAlien = vetorDistancias(G, alien);
	int *distSaida = vetorDistancias(G, saida);
    int v = TAMG, menorSaida = TAMG, menorAlien = TAMG;
    int vAlien;
    for (int i = 0; i < TAMG; ++i){
        if (G[ripley][i] == 1){ //Caso adjacente
	        if(distAlien[i] < menorAlien){ 
	            menorAlien = distAlien[i];
	            vAlien = i;            
	        }
        }
    }
    for (int i = 0; i < TAMG; ++i){
        if (G[ripley][i] == 1){ //Caso adjacente
	        if(rand()%2) {
	            if(distSaida[i] < menorSaida){ //Se este vertice possuir menor distancia
	                menorSaida = distSaida[i];            
	            	if(distAlien[i] <= 3) {
	            		if(vAlien != i) {
	            			v = i;
	            		}
	            	} else {
	            		v = i;
	            	}
	            }
        	} else {
        		if(distSaida[i] <= menorSaida){ //Se este vertice possuir menor distancia
	                menorSaida = distSaida[i];            
	            	if(distAlien[i] <= 3) {
	            		if(vAlien != i) {
	            			v = i;
	            		}
	            	} else {
	            		v = i;
	            	}
	            }
	        }
	    }
    } 
    return v;}
int CaminhoAlienLinear(int alien, Fila *f){
    int ant = fila_retira_vet(f);
    int count = 0;
    int aux[4];
    for (int i = 0; i < TAMG; ++i){
        if(G[alien][i] == 1){ //caso i seja adjacente
            aux[count] = i; //colocamos ele no vetor de adjacentes
            count++; //qtd de adjacentes aumenta

        }
            
    }
    while(1){
    int prox = rand()%count; //está funcionando
        if(aux[prox] != ant || count == 1){
            return aux[prox];
        }
    }}
int PercorreLinear(int *dist, int ripley, int alien){
    Fila *f = fila_cria_vet();
    fila_insere_vet(f,TAMG);
    
    while(ripley != saida){ 
        if(G[alien][ripley] == 1 || alien == ripley){
            return 1;
        }
        ripley = Busca(ripley, dist);
        fila_insere_vet(f,alien);
        alien = CaminhoAlienLinear(alien, f);
        PrintMapa( Mapa(dist, ripley, alien) );
        
    }
    return 0;       }
int CaminhoAlienAleatorio(){
    int count = 0, j = 0;
    int aux[TAMG];
    //precisa de maneira de contar espaços vazios
    for (int i = 0; i < TAMG; ++i){
        for(int j = 0; j <TAMG; ++j){
            if (G[i][j] == 1){
                aux[count] = i;
                count++;
                break;
            }
        }
    }
    int prox = rand()%count; //0 até vazios

    return aux[prox];}
int PercorreAleatorio(int *dist, int ripley, int alien){
    while(ripley != saida){ 
        if(G[alien][ripley] == 1 || alien == ripley){
            return 1;
        }
        ripley = Busca(ripley, dist);
        alien = CaminhoAlienAleatorio();
        PrintMapa( Mapa(dist, ripley, alien) );

    }
    return 0;}
int AlienInteligente(int ripley, int alien){
    int *dist = vetorDistancias(G, ripley); //Caminho que Ripley irá seguir
    return Busca(alien, dist); }
int PercorreInteligente(int *dist, int ripley, int alien){
    while(ripley != saida){ 
        if(G[alien][ripley] == 1 || alien == ripley){
            return 1;
        }
        ripley = BuscaFoge(ripley, alien);
	if(ripley == TAMG) {
		return 1;
	} 
        alien = AlienInteligente(ripley, alien);
        PrintMapa( Mapa(dist, ripley, alien) );
    }
    return 0;}    
