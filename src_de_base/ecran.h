void efface_ecran(void);

void find_curseur(uint8_t *lig,uint8_t *col);

void place_curseur(uint32_t lig, uint32_t col);

uint16_t *ptr_mem(uint32_t lig, uint32_t col);

void ecrit_car(uint32_t lig, uint32_t col, char c);

void efface_ligne(void);

void next_pos(uint8_t *lig, uint8_t *col);

void traite_car(char c);

void defilement(void);

void console_putbytes(char *chaine,int32_t taille);
