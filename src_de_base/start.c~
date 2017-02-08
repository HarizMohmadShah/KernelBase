#include <cpu.h>
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

#include "temps.h"
#include "ecran.h"
#include "processus.h"

/*
void initProcessus(processus *idle, processus *proc1, void (*fct_proc1)(void)){
  //idle
  idle -> pid = 0;
  char *name = "idle";
  for(uint8_t i = 0; i < strlen(name); i++){
    idle -> nom[i] = name[i];
  }
  idle -> etat = elu;
  actif = &oisive;
  //proc1
  proc1 -> pid = 1;
  name = "proc1";
  for(uint8_t i = 0; i < strlen(name); i++){
    proc1 -> nom[i] = name[i];
  }
  proc1 -> etat = activable;
  //Remarque : La sommet de pile = la dernier case
  proc1 -> zds[1] = (uint32_t) (proc1 -> pile_exec) + 4*(MEMORY - 1);
  proc1 -> pile_exec[511] = (uint32_t) fct_proc1;
}
*/

void init_moniteur_processus(){
  efface_ecran();
  printf("\fGestion de processus\n");
}


// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display
// une fonction bien connue
uint32_t fact(uint32_t n)
{
  uint32_t res;
  if (n <= 1) {
    res = 1;
  } else {
    res = fact(n - 1) * n;
  }
  return res;
}

//la fonction noyau
void kernel_start(void)
{
  //Initialisation
  init_moniteur_processus();
  init_traitant_IT(32, traitant_IT_32);
  freq_horloge_Hz(50);
  masque_IRQ(0,false);
  cree_processus(idle, "idle ");
  cree_processus(processus1, "proc1");
  cree_processus(processus2, "proc2");
  cree_processus(processus3, "proc3");
  //initProcessus(&oisive,&proc1,processus1);
  //demarrage du processus par defaut
  idle();
}

/*
//Gestion de l'interruption
void kernel_start(void)
{
  //Initialisation
  printf("\fGestion d'Interruption\n");
  init_traitant_IT(32, traitant_IT_32);
  freq_horloge_Hz(50);
  masque_IRQ(0,false);
  //demasquage des interruptions externes
  sti();
  // on ne doit jamais sortir de kernel_start
  while (1) {
    // cette fonction arrete le processeur
    hlt();
  }
}
*/
