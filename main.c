#include <stdlib.h>
#include "Headers/kbhit.h"
#include "Headers/visual.h"
#include "Headers/grafo.h"

int main(){
		system("mocp -S");
		int res, malien = 0, mnostromus = 0;
		int q = 0, res1 = 0, res2 = 0;
        system("clear");
			// start musica
			system("mocp  -c -a Musicas/HereKitty.mp3");
			system("mocp  -a Musicas/SarradnessandSarrow.mp3");			
			system("mocp -p");
			system("mocp -o r");
        prologue();
		while(q != 1){
		
			res = mainJanelaMenu();
			if(res == 0){
				res1 = MainAlien(mnostromus +1, malien+1);
                q = mainJanelaMenuRepeticao(res1);
            }
			if(res == 2)
				malien = mainJanelaMenuAlien(malien);
			if(res == 1)
				mnostromus = mainJanelaMenuNostromos(mnostromus);
			if(res == 3)
				creditos();
            if(res == 4){
			// musica jogo			
			system("mocp -f");
            	mainJanelaMenuGameMode();
                res2 = Minigame(0, mnostromus+1, malien+1);
                q = mainJanelaMenuRepeticao(res2);
            }
			// start musica
			system("mocp -r");
		}

		// stop musica
		system("mocp -s -x");
        return 0;
}
