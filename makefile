comp = gcc
fila = Headers/fila
grafo = Headers/grafo
kbhit = Headers/kbhit
visual = Headers/visual
executavel = AlienVsRipley

all: grafo fila kbhit visual compilacao clean
	@clear
	@echo Pronto!

grafo: $(grafo).o
	$(comp) -c $(grafo).c

fila: $(fila).o
	$(comp) -c $(fila).c

kbhit: $(kbhit).o
	$(comp) -c $(kbhit).c

visual: $(visual).o
	$(comp) -c $(visual).c

compilacao: main.c
	$(comp) main.c grafo.o visual.o fila.o kbhit.o -lncurses -o $(executavel)

clean: clean_folders
	rm *.o

clean_folders:
	rm $(grafo).o
	rm $(kbhit).o
	rm $(fila).o
	rm $(visual).o

	