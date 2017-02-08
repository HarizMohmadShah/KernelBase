#define MEMORY 512
#define N_REGISTRES 5
#define N 4 //nb de processus

enum state {
  elu = 0,
  activable,
  endormi,
  mort,
};

struct processus{
  uint32_t pid;
  char nom[5];
  uint8_t etat;
  int32_t zds[N_REGISTRES]; //zone de sauvegarde
  int32_t pile_exec[MEMORY];
  int32_t tempsReveil;
};

extern void ctx_sw(int32_t *ancien, int32_t *nouveau);

int32_t cree_processus(void (*code)(void), char *nom);

void dors(uint32_t nb_secs);

void ordonnance();

int32_t mon_pid();

char* mon_nom();

void fin_processus();

void afficheEtat();

void idle();

void processus1();

void processus2();

void processus3();

void processus4();
