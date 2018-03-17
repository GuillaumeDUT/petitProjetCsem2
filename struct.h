#include <stdio.h>

typedef struct noeud{
  unsigned char lettre;
  struct noeud *filsg,*frered;
}Noeud, *Arbre;
