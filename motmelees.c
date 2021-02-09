/* MAKENDI Bryan *
 * Groupe 6      */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <MLV/MLV_all.h>
#define TAILLE_X 700
#define TAILLE_Y 700
#define N 20





/* Structure qui permet
   de faire la liste des mots */

typedef struct cellulemot{

	char* mot;
	int num_mot;
	int x;						// x et y position de la premiere lettre de mot
	int y;						// a et b position de la derniere lettre de mot
	int a;
	int b;
	struct cellulemot* suivant;

}CelluleMot, *ListeMot; 




char* alloue_mot(int n){

	char* tmp;
	tmp = (char*)malloc(sizeof(char) * n);
	return tmp;

}




/* Alloue l'espace necessaire
   a la creation d'une liste de mots */

ListeMot alloue_liste(char* mot, int numero_mot, int x, int y, int direction){

	ListeMot tmp = (CelluleMot*)malloc(sizeof(CelluleMot));

	if(tmp != NULL){

		tmp->mot = alloue_mot(N);
		strcpy(tmp->mot, mot);
		tmp->num_mot = numero_mot;
		tmp->x = x;
		tmp->y = y;

		if(direction == 0){

			tmp->a = tmp->x - (strlen(mot) - 1);
			tmp->b = tmp->y - (strlen(mot) - 1);

		}

		else if(direction == 1){

			tmp->a = tmp->x - (strlen(mot) - 1);
			tmp->b = tmp->y;

		}

		else if(direction == 2){

			tmp->a = tmp->x - (strlen(mot) - 1);
			tmp->b = tmp->y + (strlen(mot) - 1);

		}

		else if(direction == 3){

			tmp->a = tmp->x;
			tmp->b = tmp->y + (strlen(mot) - 1);

		}

		else if(direction == 4){

			tmp->a = tmp->x;
			tmp->b = tmp->y + (strlen(mot) - 1);

		}

		else if(direction == 5){

			tmp->a = tmp->x + (strlen(mot) - 1);
			tmp->b = tmp->y - (strlen(mot) - 1);

		}

		else if(direction == 6){

			tmp->a = tmp->x + (strlen(mot) - 1);
			tmp->b = tmp->y;

		}

		else if(direction == 7){

			tmp->a = tmp->x + (strlen(mot) - 1);
			tmp->b = tmp->y + (strlen(mot) - 1);

		}

		tmp->suivant = NULL;

	}

	return tmp;

}




/* Alloue l'espace necessaire
   pour la grille             */


char** alloue_grille(int n){

	char** tmp;
	int i;

	tmp = (char**)malloc(sizeof(char*) * n);
	if(tmp != NULL){

		for(i = 0; i < n; i++)

			tmp[i] = (char*)malloc(sizeof(char) * n);

	}

	return tmp;

}

/* Initialise la grille en
   mettant des espaces
   dans toutes les cases   */

char** initialise_grille(char** grille, int taille){

	int i, j;

	for(i = 0; i < taille; i++){

		for(j = 0; j < taille; j++)

			grille[i][j] = ' ';

	}

	return grille;

}



/*Affiche la grille */

void affiche_grille(char** grille, int taille){

	int i, j;

	for(i = 0; i < taille; i++){

		for(j = 0; j < taille; j++)

			printf("|%c |", grille[i][j]);

		printf("\n");

	}

}


/* Renvoie 1 si mot ne contient
   que des lettres, 0 sinon     */

int est_mot(char* mot){

	int i = 0;

	while(mot[i] != '\0'){

		if(mot[i] < 'a' || mot[i] > 'z'){
			
			return 0;

		}

		i += 1;

	}

	return 1;

}


/* insere le mot en fonction de n sa direction
   et i et j les coordonees de la position de
   sa premiere lettre                          */


int insere_direction(char** grille, char* mot, int n, int i, int j){

	int i2, cpt;
	cpt = 0;

	if(n == 0){		//Nord ouest

		for(i2 = 0; i2 < strlen(mot); i2++){

			grille[i--][j--] = mot[cpt];
			cpt += 1;
		}

		return 1;
	}

	if(n == 1){		//Nord

		for(i2 = 0; i2 < strlen(mot); i2++){

			grille[i--][j] = mot[cpt];
			cpt += 1;
		}

		return 1;

	}

	if(n == 2){		//Nord est

		for(i2 = 0; i2 < strlen(mot); i2++){

			grille[i--][j++] = mot[cpt];
			cpt += 1;
		}

	}

	if(n == 3){		//Ouest

		for(i2 = 0; i2 < strlen(mot); i2++){

			grille[i][j--] = mot[cpt];
			cpt += 1;
		}

		return 1;

	}

	if(n == 4){		//Est

		for(i2 = 0; i2 < strlen(mot); i2++){

			grille[i][j++] = mot[cpt];
			cpt += 1;
		}

		return 1;

	}

	if(n == 5){		//Sud ouest

		for(i2 = 0; i2 < strlen(mot); i2++){

			grille[i++][j--] = mot[cpt];
			cpt += 1;
		}

		return 1;

	}

	if(n == 6){		//Sud

		for(i2 = 0; i2 < strlen(mot); i2++){

			grille[i++][j] = mot[cpt];
			cpt += 1;
		}

		return 1;

	}

	if(n == 7){		//Sud est

		for(i2 = 0; i2 < strlen(mot); i2++){

			grille[i++][j++] = mot[cpt];
			cpt += 1;
		}

		return 1;

	}

	return 0;

}


/*Renvoie 1 si la case est libre,
  0 sinon                        */

int est_case_libre(char** grille, int i, int j){

	if(grille[i][j] != ' ')

		return 0;

	return 1;

}


/* Met les caracteres de mot 
   en majuscule              */

void majuscule(char* mot){

	int i;

	for(i = 0; mot[i] != '\0'; i++)

		mot[i] = toupper(mot[i]);
}


/* Remplit les cases vides
   de la grille avec des lettres */

void remplit(char** grille, int taille){

	int i, j;

	for(i = 0; i < taille; i++){

		for(j = 0; j < taille; j++){

			if(est_case_libre(grille, i, j) == 1)

				grille[i][j] = 'a' + rand()%26;

		}

	}

}



/* Insere un mot dans la grille
   en fonction de ce que rentre
   l'utilisateur                */



void affiche_liste(ListeMot lst){

	while(lst != NULL){
		
		printf("Mot %d: %s / Premiere lettre en (%d, %d)\n", lst->num_mot, lst->mot, lst->x, lst->y);
		lst = lst->suivant;
		
	}

}



int insere_en_tete(ListeMot *lst, char* mot, int numero_mot, int x, int y, int direction){

	ListeMot tmp = alloue_liste(mot, numero_mot, x, y, direction);

	if(tmp == NULL)

		return 0;

	tmp->suivant = *lst;
	*lst = tmp;

	return 1;

}



int inserer_mot(char** grille, int taille, ListeMot *lst){

	int i, j, direction, numero_mot;
	char* mot;
	ListeMot tmp = *lst;
	mot = alloue_mot(N);
	i = 0;
	j = 0;
	numero_mot = 0;

	do{

		printf("Entrez un mot à inserer dans la grille :\n");
		scanf("%s", mot);

		if(est_mot(mot) == 0)
			break;


		if(strlen(mot) > taille)

			printf("Mot trop long\n");

		else{

			printf("Entrez les coordonnees dans la grille de la premiere lettre :\ni : ");
			scanf("%d", &i);
			printf("j : ");
			scanf("%d", &j);
			printf("Direction du mot / 0 pour nord ouest, 1 pour nord, 2 pour nord est 3 pour ouest, 4 pour est, 5 pour sud ouest, 6 pour sud, 7 pour sud est :\n");
			scanf("%d", &direction);

			while(direction < 0 && direction > 7){

				printf("Direction inconnue, recommencez : ");
				scanf("%d", &direction);

			}
		
			if(est_case_libre(grille, i, j) == 1){

				majuscule(mot);
				numero_mot += 1;
				insere_en_tete(&tmp, mot, numero_mot, i, j, direction);
				insere_direction(grille, mot, direction, i, j);
				affiche_grille(grille, taille);
				strcpy(mot, "nul");

			}

			else

				printf("Impossible de rentrer ce mot, conflit avec un mot deja place.\n");
		}

	}while(est_mot(mot) == 1);

	*lst = tmp;

	return 1;

}



void libere_listemot(ListeMot *lst){

	ListeMot tmp = *lst;
	ListeMot index = NULL;

	while(tmp != NULL){

		index = tmp;
		tmp = tmp->suivant;
		index->suivant = NULL;
		free(index->mot);
		free(index);

	}

	*lst = NULL;

}



void libere_grille(char** grille, int taille){

	int i;

	for(i = 0; i < taille; i++)

		free(grille[i]);

	free(grille);
	grille = NULL;

}


void minuscule(char* mot){

	int i;

	for(i = 0; mot[i] != '\0'; i++)

		mot[i] = tolower(mot[i]);
}


/* Renvoie 1 si le joueur a trouve le mot souhaite
   et enleve le numero du mot. Renvoie 0 sinon     */


int trouve_mot(ListeMot *lst, int numero_mot, int x1, int y1, int x2, int y2){

	ListeMot tmp = *lst;

	while (tmp != NULL){

		if(tmp->num_mot == numero_mot){

			if(x1 == tmp->x && y1 == tmp->y && x2 == tmp->a && y2 == tmp->b){

				printf("Vous avez trouvé le mot %s\n", tmp->mot);
				minuscule(tmp->mot);
				tmp->num_mot = 0;
				return 1;

			}

		}

		tmp = tmp->suivant;

	}

	printf("Pas de mot trouvé, continuez.\n");

	return 0;

}


/* Renvoie 1 si tous les mots 
   ont ete trouves, 0 sinon   */


int tous_trouves(ListeMot lst){

	while(lst != NULL){

		if(lst->num_mot != 0)

			return 0;

		lst = lst->suivant;

	}

	return 1;

}



int main(int argc, char *argv[]){
	
	int taille, numero_mot, x, a, y, b, cpt, choix, code; // cpt compte le nombre de mots trouvés, code reçoit le code de trouve_mot, choix reçoit le souhait de continuer ou non du joueur
	char** grille;
	ListeMot lst = NULL;

    srand((unsigned)time(NULL));

    if(argv[1][1] == 'c'){

		printf("Choisissez la taille de la grille : ");
		scanf("%d", &taille);

		grille = alloue_grille(taille);
		grille = initialise_grille(grille, taille);
		inserer_mot(grille, taille, &lst);
		remplit(grille, taille);

	}
	
	if(argv[1][2] == 'a'){		// VERSION ASCII

		do{

			affiche_grille(grille, taille);
			printf("LISTE DE MOTS | les mots trouvés ont pour numero 0\n");
			affiche_liste(lst);

			printf("Numero du mot que vous cherchez :");
			scanf("%d", &numero_mot);
			printf("Entrez la position en x et y de la premiere lettre de ce mot\nx : ");
			scanf("%d", &x);
			printf("y : ");
			scanf("%d", &y);
			printf("Entrez la position en a et b de la derniere lettre de ce mot\na : ");
			scanf("%d", &a);
			printf("b : ");
			scanf("%d", &b);
			code = trouve_mot(&lst, numero_mot, x, y, a, b);

			if(code == 1)

				cpt += 1;

			printf("Tapez 1 pour continuer : ");
			scanf("%d", &choix);

		}while(tous_trouves(lst) == 0 || choix == 0);

		if(cpt > 1)

			printf("Vous avez trouvé %d mots.\n", cpt);

		else if(cpt == 1)

			printf("Vous avez trouvé %d mot.\n", cpt);

		else

			printf("Vous n'avez rien trouvé, rien du tout.\n");

	}

	else if(argv[1][2] == 'g'){			// VERSION GRAPHIQUE

		int j = 100;
		int cpt = 0;
		MLV_create_window( "Mot melees", "Mots melees", TAILLE_X, TAILLE_Y);

		while(cpt <= 5){

			MLV_draw_line(j, 100, j, TAILLE_Y - 100, MLV_COLOR_WHITE);
			MLV_draw_line(100, j, TAILLE_X - 100, j, MLV_COLOR_WHITE);

			cpt+=1;
			j+=100;

		}
		
		
		MLV_actualise_window();
		MLV_wait_seconds(20);
		MLV_free_window();


	}


	libere_listemot(&lst);
	libere_grille(grille, taille);

	return 0;

}