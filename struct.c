#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "struct.h"

//
// void AjouteBranche(Arbre *A,char *mot){
//   if((*A=AlloueNoeud(*mot))!= NULL){
//     if(*mot != '\0')
//       AjouteBranche(&((*A)->filsg),mot+1);
//   }
// }
//
// void ajouteMot(Arbre *a, char *mot){
//   if(*a==NULL)
//     ajouteBranche(a,mot);
//   else{
//     if( (*a)->lettre < *mot)
//       ajouteMot(&((*a)->frered), mot);
//     else{
//       if(( (*a)->lettre == *mot) && (*mot != '\0'))
//         ajouteMot(&((*a)->filsg),mot+1);
//       else{
//         if(*mot !='\0'){
//           arbre tmp=NULL;
//           ajouteBranche(& tmp,mot);
//           tmp->frered=*a;
//           *a=tmp;
//         }
//       }
//     }
//   }
// }
//
//
// void afficheDico(Arbre a){
//   static char buffer[MAXLE];
//   static int lg=0; /* case à remplir */
//   if(a! = NULL){
//     buffer[lg++]=a->lettre;
//     if(a->lettre == '\0')
//       printf("%s\n",buffer);
//     else
//       afficheDico(a->filsg);
//     lg--;
//     if(a->frered != NULL)
//       afficheDico(a->frered);
//   }
// }
//
// int recherche(Arbre a, char *mot){
//   if(a==NULL)
//     return 0;
//   if(*mot<a->lettre)
//     return 0;
//   if(*mot ==a->lettre)
//     if(*mot== '\0')
//       return 1;
//     return recherch(a->filsg,mot+1);
//   return recherche(a->frere,mot);
// }
