#include <stdio.h>

typedef struct noeud{
	unsigned char lettre;
	struct noeud *filsg;
	struct noeud *frered;
} Noeud, *Arbre;

Arbre allocNoeud(char l);
/* 
// Fonction permettant l'allocation dynamique d'un noeud
// Entrée : un char
// Sortie : un pointeur sur le noeud créé ou NULL en cas de problème
*/

int addNoeud(Arbre *a, char* mot);
/*
// Fonction permettant d'ajouter des noeuds à un arbre
// Entrée : un pointeur sur arbre et un string
// Sortie : 0 si l'allocation n'a pas fonctionné ou 1 si tout est bon
*/

int ajoutLexique(Arbre *a, FILE *lexique);
/* 
// Fonction permettant de créer un arbre à partir d'un fichier de mots
// Entrée : un pointeur sur arbre ainsi qu'un fichier contenant des mots
// Sortie : le nombre de mots ayant été ajoutés
*/

void afficheMot(Arbre a, char *mot, char *indice);
/*
// Fonction permettant d'afficher dans la console tous les mots de l'arbre dans l'ordre alphabétique
// Entrée : un pointeur sur arbre ainsi qu'un tableau donné deux fois en paramètre
// Sortie : //
*/

void sauvegardeMots(Arbre a, char *mot, char *indice, FILE* lexique);
/*
// Fonction permettant de sauvegarder l'ensemble des mots dans l'ordre alphabétique d'un arbre dans un fichier (créait un .L)
// Entrée : un arbre, un tableau donné deux fois en paramètre et un fichier de sortie
// Sortie : //
*/

void sauvegardeLexique(Arbre a, char *mot, char *indice, FILE *lexique);
/*
// Fonction permettant de sauvegarder l'ensemble des mots selon un format spécifique (créait un .DICO)
// Entrée : un arbre, un tableau donné deux fois en paramètre et un fichier de sortie
// Sortie : //
*/

Arbre importLexique(FILE *lexique);
/*
// Fonction permettant de créer un arbre à partir d'un fichier avec un format spécifique (.DICO)
// Entrée : un fichier au bon format
// Sortie : retourne le pointeur sur l'arbre créé
*/

int estPresent(Arbre a, char* mot);
/*
// Fonction permettant de chercher si un mot est présent dans un arbre ou non
// Entrée : un arbre et un string
// Sortie : 0 si le mot n'est pas présent, 1 s'il l'est
*/

void infos();
/*
// Fonction qui permet d'afficher les informations pour un menu spécifique
// Entrée : //
// Sortie : //
*/

int choixMenu();
/*
// Fonction qui permet de traiter des choix précis d'un utilisateur
// Entrée : //
// Sortie : 0 : erreur, 1 : afficheMot, 2: sauvegarderLexique, 3 : rechercheMot, 4 : sauvegarderFormatee
*/