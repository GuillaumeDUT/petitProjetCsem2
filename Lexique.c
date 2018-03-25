/* 

Projet : Mini dictionnaire utilisant les arbres
Date de rendu : 26/03/2018
Auteur : Guillaume Lollier && Axel Donadio 

*/

#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 50 /* Définition du maximum de caractère d'un mot */


/* 
// Fonction permettant l'allocation dynamique d'un noeud
// Entrée : un char
// Sortie : un pointeur sur le noeud créé ou NULL en cas de problème
*/
Arbre allocNoeud(char l){
/* On créait un arbre temporaire */
	Arbre tmp;
/* On alloue la mémoire en fonction de la structure noeud */
	tmp = malloc(sizeof(Noeud));
/* Si l'allocation a fonctionné, on initialise les champs puis on retourne le noeud. Sinon on renvoie NULL*/
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

/*
// Fonction permettant d'ajouter des noeuds à un arbre
// Entrée : un pointeur sur arbre et un string
// Sortie : 0 si l'allocation n'a pas fonctionné ou 1 si tout est bon
*/
int addNoeud(Arbre *a, char* mot){
/* On transforme toutes les lettres du mot récupéré en argument par des minuscules */
	*mot = tolower(*mot);
/* Si l'arbre est vide, on lance l'ajout */
	if(*a == NULL){
		*a = allocNoeud(*mot); /* On commence par ajouter une lettre */
		if(*a == NULL) return 0; /* On vérifie que l'allocation a bien fonctionné */
		if(*mot != '\0'){ /* On vérifie ensuite si la lettre ajoutée n'est pas le caractère définissant la fin d'un mot */
			addNoeud(&(*a)->filsg, mot+1); /* Si ce n'est pas le cas, il reste des lettres à ajouter donc on appelle récursivement la fonction en avançant dans le mot et dans le fils de l'arbre */
		}
	}
/* Si l'arbre n'est pas nul, on vérifie les différents cas possibles */
	if(*mot > (*a)->lettre){ /* On compare la première lettre du mot à celle de l'arbre. */
		addNoeud(&(*a)->frered, mot); /* Si elle est plus grande, on part sur la droite de l'arbre */
	}
	else if(*mot == (*a)->lettre){ /* Si la première lettre est égale à celle de l'arbre, on descend dans les fils et on avance dans le mot */
		if(*mot != '\0'){ /* On s'assure bien que la lettre n'est pas le caractère de fin */
			addNoeud(&(*a)->filsg, mot+1); /* On avance dans le mot et dans les fils */
		}
	}
	else{ /* Sinon on est dans le cas où la première lettre est inférieure à celle du mot de l'arbre */
		Arbre tmp = NULL; 
		tmp = *a; /* Après avoir initialisé un arbre temporaire, on stock l'adresse de l'arbre courant dedans pour ne pas la perdre */
		*a = allocNoeud(*mot); /* On écrase le pointeur stocké précédemment par la nouvelle lettre prenant la place de l'ancienne */
		if(*a == NULL) return 0; /* On vérifie qu'il n'y a pas de problème d'allocation */
		(*a)->frered = tmp; /* On remet en place la liaison grâce à la variable temporaire */
		if(*mot != '\0'){ /* On s'assure bien que la lettre n'est pas le caractère de fin */
			addNoeud(&(*a)->filsg, mot+1); /* On avance dans le mot et dans les fils */
		}
	}
	return 1;
}

/* 
// Fonction permettant de créer un arbre à partir d'un fichier de mots
// Entrée : un pointeur sur arbre ainsi qu'un fichier contenant des mots
// Sortie : le nombre de mots ayant été ajoutés
*/
int ajoutLexique(Arbre *a, FILE *lexique){
/* On initialise un tableau qui stockera temporairement les mots du lexique et un compteur de mot */
	char mot[MAX];
	int count = 0;
/* Tant qu'il reste des mots dans le lexique, on stocke chaque mot dans notre tableau */
	while(fscanf(lexique,"%s", mot) != EOF){
		count += addNoeud(a, mot); /* On ajoute chaque mot à l'arbre et on incrémente le compteur */
	}
	return count; /* On retourne le nombre de mot ajouté */
}

/*
// Fonction permettant d'afficher dans la console tous les mots de l'arbre dans l'ordre alphabétique
// Entrée : un pointeur sur arbre ainsi qu'un tableau donné deux fois en paramètre.
// Sortie : //
*/
void afficheMot(Arbre a, char *mot, char *indice){
/* Si l'arbre est NULL, on avertit l'utilisateur */
	if( a == NULL ){
		printf("Aucun mot n'est présent.");
	}
/* Sinon, on gère les différents cas */
	if(a != NULL){
		*mot = a->lettre;  /* On stocke la lettre courante dans notre tableau */
		if(a->lettre == '\0'){ /* Si la lettre est le caractère \0, on est en fin de mot */
			printf("%s\n", indice); /* On peut donc l'afficher grâce à notre second pointeur qui nous permet de rester sur le début du mot */
		}
		else{
			afficheMot(a->filsg, &mot[1], indice); /* Sinon on avance le filsg et dans le tableau sans toucher notre pointeur de référence de début de mot */
		}
		if( a->frered != NULL){ /* S'il existe un frered, on bascule vers lui */
			afficheMot(a->frered, mot, indice);
		}
	}
}

/*
// Fonction permettant de sauvegarder l'ensemble des mots dans l'ordre alphabétique d'un arbre dans un fichier (créait un .L)
// Entrée : un arbre, un tableau donné deux fois en paramètre et un fichier de sortie
// Sortie : //
*/
void sauvegardeMots(Arbre a, char *mot, char *indice, FILE* lexique){
/* Si l'arbre est NULL, on avertit l'utilisateur */
	if( a == NULL ){
		printf("Aucun mot n'est présent.");
	}
/* Sinon, on gère les différents cas */
	if(a != NULL){
		*mot = a->lettre; /* On stocke la lettre courante dans notre tableau */
		if(a->lettre == '\0'){ /* Si la lettre est le caractère \0, on est en fin de mot */
			fprintf(lexique, "%s\n", indice); /* On peut donc l'écrire dans le fichier grâce à notre second pointeur qui nous permet de rester sur le début du mot */
		}
		else{
			sauvegardeMots(a->filsg, &mot[1], indice, lexique); /* Sinon on avance le filsg et dans le tableau sans toucher notre pointeur de référence de début de mot */
		}
		if( a->frered != NULL){ /* S'il existe un frered, on bascule vers lui */
			sauvegardeMots(a->frered, mot, indice, lexique);
		}
	}
}

/*
// Fonction permettant de sauvegarder l'ensemble des mots selon un format spécifique (créait un .DICO)
// Entrée : un arbre, un tableau donné deux fois en paramètre et un fichier de sortie
// Sortie : //
*/
void sauvegardeLexique(Arbre a, char *mot, char *indice, FILE *lexique){
/* On vérifie que l'arbre n'est pas NULL */
	if(a != NULL){
		*mot = a->lettre; /* On stocke la lettre courante dans notre tableau */
		if(a->lettre == '\0'){ /* Si la lettre est le caractère \0, on est en fin de mot */
			fprintf(lexique, "%s ", indice); /* On écrit le mot suivi d'un espace pour remplacé le caractère de fin de mot grâce à notre pointeur étant resté sur le début du mot */
			if( a->frered != NULL){ /* On vérifie si le noeud courant possède un frered */
				return sauvegardeLexique(a->frered, mot, mot, lexique); /* Si c'est le cas, on bascule vers lui */
			}
		}
		else if(a->filsg != NULL){ /* S'il existe un filsg, on appelle récursivement la fonction en avançant dans le filsg et dans le tableau */
			sauvegardeLexique(a->filsg, &mot[1], indice, lexique);
		}
		else{
			fprintf(lexique, "\n"); /* S'il est NULL, on le précise grâce au caractère \n */
		}
		if( a->frered != NULL){ /* S'il existe un frered, on appelle résursivement la fonction en basculant vers lui */
			sauvegardeLexique(a->frered, mot, mot, lexique);
		}
		else{
			fprintf(lexique, "\n"); /* S'il est NULL, on le précise grâce au caractère \n */
		}
	}
}

/*
// Fonction permettant de créer un arbre à partir d'un fichier avec un format spécifique (.DICO)
// Entrée : un fichier au bon format
// Sortie : //
*/
Arbre importLexique(FILE *lexique){
	Arbre a = NULL; /* On créait un arbre */
	char ligne[MAX]; /* Un première tableau qui stockera une ligne du fichier */
	char buffer[MAX]; /* Un second qui stockera les mots à ajouter */
	int i = 0;
	int j = 0;
/* Tant qu'il reste des lignes au fichier, on boucle */
	while(fgets(ligne, MAX, lexique) != NULL){ 
		i = 0;
		while(ligne[i] != '\n'){ /* Tant qu'on ne croise pas le caractère \n qui correspond à un filsg NULL ou un frered NULL, on boucle */
			if(ligne[i] == ' '){ /* Si la lettre est un espace, on est en fin de mot. */
				addNoeud(&a, buffer); /* On ajoute donc le mot grâce au buffer contenant toutes ses lettres */
			}
			else{ /* Sinon le mot à encore des lettres */
				buffer[j] = ligne[i]; /* Dans ce cas on ajoute la lettre à notre mot et on incrémente le compteur*/
				j++;
			}
			i++;
		}
		buffer[j] = '\0'; /* Lorsque le caractère \n est atteint, on ajoute un \0 pour spécifié la fin de mot*/
		j--; /* On revient en arrière dans notre tableau contenant les mots d'autant de fois que l'on croise le \n qui correspond soit à un filsg NULL soit à un frered NULL */
	}
	return a;
}

int estPresent(Arbre a, char* mot){
/* Si l'arbre est NULL, aucune chance qu'il contienne le mot. On retourne 0*/
	if( a == NULL){
		return 0;
	}
/* Si la première lettre du mot est inférieur à celle de l'arbre, on retourne 0 car les lettres sont triés de manière alphabétique dans l'arbre*/
	if(*mot < a->lettre){
		return 0;
	}
/* Si la première lettre du mot est égale à celle de l'arbre, deux cas */
	if(*mot == a->lettre){
		if(*mot == '\0'){ /* Si le caractère est celui de fin de mot, on a donc trouvé notre mot. On retourne 1*/
			return 1;
		}
		return estPresent(a->filsg, mot+1); /* Sinon on avance dans le mot à rechercher et dans le filsg*/
	}
	return estPresent(a->frered,mot); /* Sinon c'est que la lettre est supérieure à celle de l'arbre. On bascule donc sur les frered */
}

/*
// Fonction qui permet d'afficher les informations pour un menu spécifique
// Entrée : //
// Sortie : //
*/
void infos(){
	printf("            ===============================\n");
	printf("\n     Bienvenue dans le menu du dictionnaire virtuel.\n");
	printf("\n            ===============================\n");
	printf("\n\n- Pour afficher les mots du lexique dans l'ordre alphabétique, rentrer la commande 'afficheMot' \n\n");
	printf("- Pour sauvegarder les mots du lexique dans l'ordre alphabétique, rentrer la commande 'sauvegarderLexique'\n\n");
	printf("- Pour rechercher un mot dans le lexique, rentrer la commande 'rechercheMot'\n\n");
	printf("- Pour sauvegarder le lexique d'une manière formatée, rentrer la commande 'sauvegarderFormatee'\n\n");
}

/*
// Fonction qui permet de traiter des choix précis d'un utilisateur
// Entrée : //
// Sortie : 0 : erreur, 1 : afficheMot, 2: sauvegarderLexique, 3 : rechercheMot, 4 : sauvegarderFormatee
*/
int choixMenu(){
	char menu[30];
	scanf("%s", menu); /* On récupère du texte renseigné par l'utilisateur */
/* On retourne une valeur en fonction des différentes commandes acceptées */
	if(strcmp(menu, "afficheMot") == 0){
		return 1;
	}
	else if(strcmp(menu, "sauvegarderLexique") == 0){
		return 2;
	}
	else if(strcmp(menu, "rechercheMot") == 0){
		return 3;
	}
	else if(strcmp(menu, "sauvegarderFormatee") == 0){
		return 4;
	}
	else{
		printf("Veuillez saisir une commande valide\n");
		return choixMenu(); /* Si cela ne correspond pas à une commande valide, on boucle jusqu'à ce que la commande soit bonne */
	}
	return 0;
}

int main(int argc, char *argv[]){
	Arbre a;
	a = NULL;
	char buffer[MAX]; /* Initialisation d'un tableau nécessaire pour les fonctions récursives */
	char nom_lexiqueL[MAX]; /* Variable qui contiendra le nom du fichier .L en fonction de l'argument de l'utilisateur */
	char nom_dico[MAX]; /* Variable qui contiendra le nom du fichier .DICO en fonction de l'argument de l'utilisateur */
	
	if( (argv[2] != NULL) && (argv[3] != NULL) ){ /* On vérifie si des options ont été spécifiées */
		strcpy(nom_dico, argv[3]);
		strcat(nom_dico, ".DICO"); /* On initialise le nom du dico en fonction de l'argument de l'utilisateur */
		FILE *dico; /* On ouvre le fichier */

		if(strcmp(argv[2], "-l") == 0){ /* Si l'utilisateur a rentré en argument -l */
			if( (dico = fopen(nom_dico,"r")) != NULL){ /* On commence par vérifier si un .DICO existe */
				a = importLexique(dico); /* Si oui, on créait l'arbre à partir de lui */
				printf("Les mots du dico sont :\n");
				afficheMot(a, buffer, buffer); /* On affiche les mots dans l'ordre alphabétique */
				fclose(dico); /* On ferme le fichier */
			}
			else{
				FILE *lexique; /* Sinon on fait la même chose mais en ouvrant le fichier source et en créant un arbre avec */
				lexique = fopen(argv[3],"r");
				ajoutLexique(&a, lexique);

				printf("Les mots du lexique sont :\n");
				afficheMot(a, buffer, buffer);
				fclose(lexique);
			}		
		}
		else if(strcmp(argv[2], "-s") == 0){ /* Si l'utilisateur a rentré en argument -s */
			strcpy(nom_lexiqueL, argv[3]); /* On initialise le nom du fichier .L en fonction de l'argument de l'utilisateur */
			strcat(nom_lexiqueL, ".L");

			FILE *listemot;
			listemot = fopen(nom_lexiqueL,"w"); /* On ouvre ce fichier */

			if( (dico = fopen(nom_dico,"r")) != NULL){ /* On commence par vérifier si un .DICO existe */
				a = importLexique(dico); /* Si oui, on créait l'arbre à partir de lui */

				sauvegardeMots(a, buffer, buffer, listemot); /* On sauvegarde les mots dans l'ordre croissant dans le fichier .L */
				printf("Les mots du dico ont été sauvegardés avec l'extension .L\n");
				fclose(dico); /* On ferme le fichier */
			}
			else{ /* Sinon on fait la même chose mais en ouvrant le fichier source et en créant un arbre avec */
				FILE *lexique;
				lexique = fopen(argv[3],"r");
				ajoutLexique(&a, lexique);

				sauvegardeMots(a, buffer, buffer, listemot);
				printf("Les mots du lexique ont été sauvegardés avec l'extension .L\n");
				fclose(lexique);
			}
		}
		else if(strcmp(argv[2], "-r") == 0){ /* Si l'utilisateur a rentré en argument -r */
			if(argv[4] != NULL){ /* On vérifie qu'un quatrième argument a bien été donné */
				if( (dico = fopen(nom_dico,"r")) != NULL){ /* On vérifie si un .DICO existe */
					a = importLexique(dico); /* Si oui, on créait l'arbre à partir de lui */

					if(estPresent(a, argv[3]) == 1){ /* On recherche le mot est indique s'il est présent ou non */
						printf("Le mot '%s' est présent dans le lexique.\n", argv[3]);
					}
					else{
						printf("Le mot '%s' est absent dans le lexique.\n", argv[3]);
					}
					fclose(dico); /* On ferme le fichier */
				}
				else{ /* Sinon on fait la même chose mais en ouvrant le fichier source et en créant un arbre avec */
					FILE *lexique;
					lexique = fopen(argv[4],"r");
					ajoutLexique(&a, lexique);
					
					if(estPresent(a, argv[3]) == 1){ 
						printf("Le mot '%s' est présent dans le dico.\n", argv[3]);
					}
					else{
						printf("Le mot '%s' est absent dans le dico.\n", argv[3]);
					}
					fclose(lexique);
				}
			}	
		}
		else if(strcmp(argv[2], "-S") == 0){ /* Si l'utilisateur a rentré en argument -S */
			FILE *lexique;
			lexique = fopen(argv[3],"r"); /* On ouvre le fichier source */
			ajoutLexique(&a, lexique); /* On créait un arbre à partir de son contenu */

			dico = fopen(nom_dico,"w"); /* On ouvre un fichier .DICO */

			sauvegardeLexique(a, buffer, buffer, dico); /* On sauvegarde l'arbre à l'intérieur */
			printf("\nLe lexique a été sauvegardé avec l'extension .DICO\n");
			fclose(lexique); /* On ferme les fichiers */
			fclose(dico);
		}
	}
	else{ /* Si aucune option n'a été spécifiée */
		if(argv[1] != NULL){ /* On vérifie qu'un nom de fichier a bien été fourni */
			FILE *lexique;
			lexique = fopen(argv[1],"r"); /* On ouvre ce fichier */
			ajoutLexique(&a, lexique); /* On créait un arbre à partir de ses mots */

			infos(); /* On affiche le menu */
			int choix;
			choix = choixMenu(); /* On appelle la fonction qui s'occupe des choix de l'utilisateur */

			switch(choix){ /* On regarde son choix */
				case 1: /* Cas 1 : Afficher le lexique */
					printf("\nLes mots du lexique sont :\n");
					afficheMot(a, buffer, buffer);
				break;
				case 2: /* Cas 2 : Sauvegarder le lexique en .L */
					strcpy(nom_lexiqueL, argv[1]);
					strcat(nom_lexiqueL, ".L");

					FILE *listemot;
					listemot = fopen(nom_lexiqueL,"w");

					sauvegardeMots(a, buffer, buffer, listemot);
					printf("\nLes mots ont été sauvegardés avec l'extension .L\n");
				break;
				case 3: /* Cas 3 : Chercher un mot */
					printf("\nVeuillez saisir le mot à rechercher\n");
					char recherche[MAX];
					scanf("%s", recherche);
					if(estPresent(a, recherche) == 1){
						printf("\nLe mot '%s' est présent dans le lexique.\n", recherche);
					}
					else{
						printf("\nLe mot '%s' est absent dans le lexique.\n", recherche);
					}
				break;
				case 4: /* Cas 4 : Sauvegarde le lexique de manière formatée dans un .DICO*/
					strcpy(nom_dico, argv[1]);
					strcat(nom_dico, ".DICO");
					FILE *dico;
					dico = fopen(nom_dico,"w");

					sauvegardeLexique(a, buffer, buffer, dico);
					printf("\nLe lexique a été sauvegardé avec l'extension .DICO\n");
				break;
			}
		}
	}
	return 1;
}