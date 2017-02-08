extern void traitant_IT_32(void);

void afficheEnHautADroite(char *chaine);

void afficheADroite(char *chaine, int32_t ligne);

void tic_PIT();

void freq_horloge_Hz(uint32_t freq);

void init_traitant_IT(uint32_t num_IT, void (*traitant)(void));

void masque_IRQ(uint32_t num_IRQ,bool masque);

uint32_t nbr_secondes();
