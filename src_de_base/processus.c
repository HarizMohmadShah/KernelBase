#include <cpu.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#include "processus.h"
#include "temps.h"

typedef struct processus processus;

int nb_proc = 0;
bool full = false;
processus p[N];
processus *actif;

const char *e[] = {
  "e",
  "a",
  "d",
  "m"
};

int32_t cree_processus(void (*code)(void), char *nom){
  if(nb_proc > N){
    return -1;
  }else{
    if(!full){
      p[nb_proc].pid = nb_proc;
    
      for(uint8_t i = 0; i < strlen(nom); i++){
	p[nb_proc].nom[i] = nom[i];
      }

      if(nb_proc == 0){
	p[nb_proc].etat = elu;
	actif = &p[nb_proc];
      }else{
	  p[nb_proc].etat = activable;
	
	  p[nb_proc].zds[1] = (uint32_t) (p[nb_proc].pile_exec) + 4*(MEMORY - 2);
	  //Remarque : La sommet de pile = la dernier case
	  //fin automatique : debut au sommet de pile 
	  p[nb_proc].pile_exec[511] = (uint32_t) fin_processus;
	  p[nb_proc].pile_exec[510] = (uint32_t) code;
	  p[nb_proc].tempsReveil = 0;
      }
    }else{
      int j;
      for(j=1; j<N; j++){
	p[j].pid = j;
    
	for(uint8_t i = 0; i < strlen(nom); i++){
	  p[j].nom[i] = nom[i];
	}

	p[j].etat = activable;
	
	p[j].zds[1] = (uint32_t) (p[j].pile_exec) + 4*(MEMORY - 2);
	//Remarque : La sommet de pile = la dernier case
	//fin automatique : debut au sommet de pile 
	p[j].pile_exec[511] = (uint32_t) fin_processus;
	p[j].pile_exec[510] = (uint32_t) code;
	p[j].tempsReveil = 0;
	break;
      }
    }
  }
  nb_proc++;
  if(nb_proc == N){
    full = true;
  }
  return p[nb_proc-1].pid;
}

void dors(uint32_t nbr_secs){
  actif -> tempsReveil = nbr_secondes() + nbr_secs;
  sti();
  hlt();
  cli();
}

void afficheEtat(){
  char state[6];
  for(uint32_t i=0; i<N; i++){
    sprintf(state, "%d:%s", i,e[p[i].etat]);
    afficheADroite(state, i+1);
  }
}

void ordonnance(){
  int pid = actif -> pid;

  if(actif -> tempsReveil > nbr_secondes()){
    actif -> etat = endormi;
  }else{
    if(actif -> etat != mort){
      actif -> etat = activable;
    }
  }

  do{
     actif = &p[(actif -> pid + 1) % 4];
  }while( (actif -> tempsReveil > nbr_secondes()) || ( actif -> etat == mort) );

  actif -> etat = elu;

  if(actif -> pid != pid){
    ctx_sw(p[pid].zds, p[actif -> pid].zds);
  }
}

int32_t mon_pid(){
  return actif -> pid;
}

char* mon_nom(){
  return actif -> nom;
}

void fin_processus(){
  nb_proc--;
  actif -> etat = mort;
  ordonnance();
}

void idle(){
  for (;;) {
    //   printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(), mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
    afficheEtat();
  }
}

void processus1(){
  for (int i=0; i<2; i++) {
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(), mon_nom(), mon_pid());
    dors(2);
  }
}

void processus2(){
  for (int i=0; i<5; i++) {
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(), mon_nom(), mon_pid());
    dors(3);
  }
}

void processus3(){
  for (int i=0; i<10; i++) {
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(), mon_nom(), mon_pid());
    dors(5);
  }
}

void processus4(){
  for(;;){
    cree_processus(processus2, "proc4");
    dors(3);
  }
}
