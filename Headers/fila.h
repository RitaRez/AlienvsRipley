#define N 10000

struct fila{
    int n;
    int ini;
    float vet[N];
};

struct lista{
    int info;
    struct lista *prox;
};

struct filal{
    struct lista *ini;
    struct lista *fim;
};

typedef struct fila Fila;
typedef struct filal FilaL;
typedef struct lista Lista;

Fila *fila_cria_vet();
void fila_insere_vet(Fila *f, float v);
int fila_retira_vet(Fila *f);
int fila_vazia_vet(Fila *f);
void fila_libera_vet(Fila *f);

FilaL *fila_cria_l();
void fila_insere_l(FilaL *f, int v);
char *fila_retira_l(FilaL *f);
int fila_vazia_l(FilaL *f);
void fila_libera_l(FilaL *f);
void fila_imprime_l(FilaL *f);
char *fila_ultimo_l(FilaL *f);
