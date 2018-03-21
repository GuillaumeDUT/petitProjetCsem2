#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 50

typedef struct noeud{
	unsigned char lettre;
	struct noeud *filsg;
	struct noeud *frered;
} Noeud, *Arbre;

Arbre allocNoeud(char l){
	Arbre tmp;
	tmp = malloc(sizeof(Noeud));
	if(tmp != NULL){
		tmp->lettre = l;
		tmp->filsg = NULL;
		tmp->frered = NULL;
	}
	else{
		return NULL;
	}
	return tmp;
}

int addNoeud(Arbre *a, char* mot){
	*mot = tolower(*mot);
	if(*a == NULL){
		*a = allocNoeud(*mot);
		if(*a == NULL) return 0;
		if(*mot != '\0'){
			addNoeud(&(*a)->filsg, mot+1);
		}
	}
	if(*mot > (*a)->lettre){
		addNoeud(&(*a)->frered, mot);
	}
	else if(*mot == (*a)->lettre){
		if(*mot != '\0'){
			addNoeud(&(*a)->filsg, mot+1);
		}
	}
	else{
		Arbre tmp = NULL;
		tmp = *a;
		*a = allocNoeud(*mot);
		if(*a == NULL) return 0;
		(*a)->frered = tmp;
		if(*mot != '\0'){
			addNoeud(&(*a)->filsg, mot+1);
		}
	}
	return 1;
}

int ajoutLexique(Arbre *a, FILE *lexique){
	char mot[MAX];
	int count = 0;
	while(fscanf(lexique,"%s", mot) != EOF){
		count += addNoeud(a, mot);
	}
	return count;
}

void afficheMot(Arbre a, char *mot, char *indice){
	if( a == NULL ){
		printf("Pas de mot");
	}
	if(a != NULL){
		*mot = a->lettre;
		if(a->lettre == '\0'){
			printf("%s\n", indice);
		}
		else{
			afficheMot(a->filsg, &mot[1], indice);
		}
		if( a->frered != NULL){
			afficheMot(a->frered, mot, indice);
		}
	}
}

void sauvegardeMots(Arbre a, char *mot, char *indice, FILE* lexique){
	if( a == NULL ){
		printf("Pas de mot");
	}
	if(a != NULL){
		*mot = a->lettre;
		if(a->lettre == '\0'){
			fprintf(lexique, "%s\n", indice);
		}
		else{
		 sauvegardeMots(a->filsg, &mot[1], indice, lexique);
		}
		if( a->frered != NULL){
			sauvegardeMots(a->frered, mot, indice, lexique);
		}
	}
}

void sauvegardeLexique(Arbre a, char *mot, char *indice, FILE *lexique){
	if(a != NULL){
		*mot = a->lettre;
		if(a->lettre == '\0'){
			fprintf(lexique, "%s ", indice);
			if( a->frered != NULL){
				return sauvegardeLexique(a->frered, mot, mot, lexique);
			}
		}
		else if(a->filsg != NULL){
			sauvegardeLexique(a->filsg, &mot[1], indice, lexique);
		}
		else{
			fprintf(lexique, "\n");
		}
		if( a->frered != NULL){
			sauvegardeLexique(a->frered, mot, mot, lexique);
		}
		else{
			fprintf(lexique, "\n");
		}
	}
}

void importLexique(FILE *lexique){
	Arbre a = NULL;
	char ligne[MAX];
	char buffer[MAX];
	int j = 0;
	while(fgets(ligne, MAX, lexique) != NULL){
		int i = 0;
		while(ligne[i] != '\n'){
			if(ligne[i] == ' '){
				addNoeud(&a, buffer);
			}
			else{
				buffer[j] = ligne[i];
				j++;
			}
			i++;
		}
		buffer[j] = '\0';
		j--;
	}
}

int estPresent(Arbre a, char* mot){
	if( a == NULL){
		return 0;
	}
	if(*mot < a->lettre){
		return 0;
	}
	if(*mot == a->lettre){
		if(*mot == '\0'){
			return 1;
		}
		return estPresent(a->filsg, mot+1);
	}
	return estPresent(a->frered,mot);
}

int main(int argc, char *argv[]){
	Arbre a;
	a = NULL;
	//char* mot;
	char buffer[MAX];
	char nom_dico[MAX];
	strcpy(nom_dico, argv[1]);
	strcat(nom_dico, ".DICO");
	char nom_lexiqueL[MAX];
	strcpy(nom_lexiqueL, argv[1]);
	strcat(nom_lexiqueL, ".L");

	char nom_lexique[MAX];
	strcpy(nom_lexique, argv[1]);

	FILE *lexique;
	lexique = fopen(nom_lexique,"r");

	FILE *listemot;
	listemot = fopen(nom_lexiqueL,"w");



	FILE *dico;
	dico = fopen(nom_dico,"w");

	printf("%d mots ont été ajoutés.\n", ajoutLexique(&a, lexique));


	afficheMot(a, buffer, buffer);

	sauvegardeLexique(a, buffer, buffer, dico);
	sauvegardeMots(a, buffer, buffer, listemot);
	char* recherche = "lettre";
	fclose(dico);
	dico = fopen(nom_dico,"w");

	importLexique(dico);

	sauvegardeLexique(a, buffer, buffer, dico);

	if(estPresent(a, recherche) == 1){
		printf("Le mot '%s' est présent dans le lexique.\n", recherche);
	}
	else{
		printf("Le mot '%s' est absent dans le lexique.\n", recherche);
	}

	return 1;
}
