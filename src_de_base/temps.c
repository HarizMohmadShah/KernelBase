#include <cpu.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <segment.h>
#include <stdio.h>

#include "ecran.h"
#include "processus.h"

#define QUARTZ 0x1234DD

uint8_t it_counter = 0;
uint8_t second,minute,hour = 0;
uint32_t secondTotal = 0;

void afficheEnHautADroite(char *chaine){
  int pos = strlen(chaine);
  for(int32_t i = 0; i <= pos; i++){
    ecrit_car(0,79 - pos + i,chaine[i]);
  }
}

void afficheADroite(char *chaine, int32_t ligne){
  if(ligne >= 25)return;

  int pos = strlen(chaine);
  for(int32_t i = 0; i <= pos; i++){
    ecrit_car(ligne,79 - pos + i,chaine[i]);
  }
}

void tic_PIT(){
  outb(0x20,0x20);
  char time[8];
  if(it_counter < 50){
    it_counter = it_counter + 1;
  }else{
    if(second > 59){
      second = 0;
      minute++;
      if(minute > 59){
	hour = 0;
	hour++;
	if(hour > 23){
	  hour = 0;
	}
      }
    }else{
      second++;
      secondTotal++;
    }

    it_counter = 0;
  }
  sprintf(time, "%02d:%02d:%02d",hour,minute,second);
  afficheEnHautADroite(time);
  ordonnance();
}

void freq_horloge_Hz(uint32_t freq){
  uint16_t freq_16bits = QUARTZ/freq;
  outb(0x34,0x43);
  outb(freq_16bits, 0x40);
  freq_16bits = freq_16bits >> 8;
  outb(freq_16bits, 0x40);
}

void init_traitant_IT(uint32_t num_IT, void (*traitant)(void)){
  uint32_t* p;
  uint16_t faible,fort = 0;
  uint32_t code1 = 0;
  uint32_t code2 = 0;
  p = (uint32_t *) (0x1000);
  faible = (uint32_t) traitant;
  fort = (uint32_t) traitant >> 16;
  code1 = KERNEL_CS << 16 | faible;
  code2 = fort << 16 | 0x8E00;
  p[2*num_IT] = code1;
  p[2*num_IT + 1] = code2;
}

void masque_IRQ(uint32_t num_IRQ,bool masque){
  uint8_t pos = 1;
  uint8_t value = 0;
  pos = pos << num_IRQ;
  value = inb(0x21);
  if(masque){
    value = value | pos;
  }else{
    value = value & ~pos;
  }
  outb(value,0x21);
}

uint32_t nbr_secondes(){
  return secondTotal;
}
