#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void Color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
};

struct items{ //Structure pour des "Objets" NON UTILISE POUR LE MOMENT
	char nom[50];
	int hpRegen;
	int mpRegen;
	int prix;
	int id;
};

struct Armes{ //Structure pour des "Armes"
	char nom[50];
	int dmg;
	int prix;
	int id;
};

struct Personnage{	//Structure du joueur 
	int money;
	struct Armes itemSlotsArmes[2]; //Tableau d'armes 
};

struct Marchant{		//Structure du marchand
	int money;
	struct Armes itemSlotsArmes[10];
	int size;
};


typedef struct Armes sword ;
typedef struct Armes bow ;


typedef struct Personnage joueur;
typedef struct Marchant vendeur; 

void resetInv(joueur * inv){		//Remplace les valeurs NULL des noms dans les cases vide par "Vide"
	int i;
	
	 for (i = 0 ; i < 3 ; i++)
    {
		
			strcpy(inv -> itemSlotsArmes[i].nom,"Vide"); // Ecrit "vide" dans les cases vide de l'inventaire du joueur
    }
}

void resetInvMarchant(vendeur * inv){ //Remplace les valeurs NULL des noms dans les cases vide par "Z"
	int i;
	
	 for (i = 0 ; i < 3 ; i++)
    {
			strcpy(inv -> itemSlotsArmes[i].nom,"Z"); // Ecrit Z dans la dernière case du marchand afin que le trie s'effectue correctement. FAIRE ATTENTION A NE JAMAIS AFFICHER LA DERNIRE CASE DU TABLEAU
    }
}

void swap(sword * itemSlotsArmes, int i, int j) //Echange deux valeurs (trie à bulle) 
{
  sword tmp = itemSlotsArmes[i];
  itemSlotsArmes[i]=itemSlotsArmes[j];
  itemSlotsArmes[j]=tmp;
}

void tri_shop(vendeur * vendeur) //Comparaison pour Trier (trie à bulle) 
{
   	int v=0;
    int i;
	int j;
		for (i = 0, j = i+1 ; i < 3 ; i++, j++)
		{
			
			if (strcmp(vendeur->itemSlotsArmes[i].nom, vendeur->itemSlotsArmes[j].nom)>0) //Vérif si le terme avant (ou après je sais plus) est plus grand ou plus petit
			{
				printf("test\n");
				swap(&vendeur->itemSlotsArmes,i,j);
				
			}
			
		}
}

void displayInv(joueur inv){		//Affiche l'inventaire 
	int i;
	
	 for (i = 0 ; i < 3 ; i++)
    {
		
		printf("%s ",inv.itemSlotsArmes[i].nom); printf("%d ",inv.itemSlotsArmes[i].dmg); printf("%d ",inv.itemSlotsArmes[i].prix); printf("%d \n",inv.itemSlotsArmes[i].id);
    }
}

void displayInvMarchant(vendeur inv, int a){	//Affiche le marchand. Le a est une valeur lors de l'appelle de la fonction afin de modifier le nombre de valeurs à afficher
		int i;
	 for (i = 0 ; i < a ; i++)
    {
		printf("%s ",inv.itemSlotsArmes[i].nom); printf("%d ",inv.itemSlotsArmes[i].dmg); printf("%d ",inv.itemSlotsArmes[i].prix); printf("%d \n",inv.itemSlotsArmes[i].id);
    }
}

void invvendeurRdm(vendeur * inv, int a){		//Attribue aléatoirement des armes au marchand. Le a est une valeur lors de l'appelle de la fonction afin de modifier le nombre d'armes à initialiser
	int i;
	int choicevendeur;
	const int MIN = 1, MAX = 6;

	sword ironSword = {"Epee", 5, 10, 1};
	sword katana = {"katana", 10 , 15, 2};
	sword knife = {"couteau", 2 , 5, 3};

	bow woodBow = {"Arc", 5, 10, 1}; 	
	bow godBow = {"Feu_des_dieux", 2 , 5, 2};				
	bow crossbow = {"Arbalete", 10 , 15, 3};

	for (i = 0 ; i < 3 ; i++){

		choicevendeur = (rand() % (MAX + 1 - MIN)) + MIN; 
		switch (choicevendeur)
		{
		case 1:
			inv->itemSlotsArmes[i] = ironSword; 
		break;
		case 2:
			inv->itemSlotsArmes[i] = katana; 
		break;
		case 3:
			inv->itemSlotsArmes[i] = knife;
		break;
		case 4:
			inv->itemSlotsArmes[i] = woodBow;
		break;
		case 5 :
			inv->itemSlotsArmes[i] = godBow;
		break;
		case 6:
			inv->itemSlotsArmes[i] = crossbow;
		break;
		}
		sleep(1);
	}
}

int main() {
	srand(time(NULL)); 
	int i;
	int inventoryVerif = 0;
	int choixJoueur;
	int choixItem;
	int choiceItemVerif;
	char* choixItemChar[50];	//Variable pour les test

	joueur player = {100,{"vide",0,0,0}}; 
	vendeur bernard = {1000,{"",0,0,0}};
	//FONCTION DE DEPART
	resetInv(&player); // Ecrit "Vide" dans les cases nom

	//Deroulement

    Color(3,0);
	printf("__________MENU__________\n");
	printf("Inventaire: [1]\nBoutique: [2]\n");
	Color(4,0);
	printf("[4] QUITTER\n");
	Color(3,0);
	scanf("%d", &choixJoueur);
	Color(15,0);
	do{
	switch (choixJoueur)
	{
	case 1:
		Color(5,0);
		printf("__________INVENTAIRE__________\n");
 		printf("Mon argent est de");
 		Color(14,0);
 		printf(" %d\n",player.money);
 		Color(5,0);
        displayInv(player);
        Color(15,0);
	break;
	case 2: 
			Color(13,0);
			printf("__________MARCHANT__________\n");
			resetInvMarchant(&bernard); //Appel de la fonction Reset
			invvendeurRdm(&bernard, 3); //Donnes des armes au marchand
			tri_shop(&bernard);	//Appel de la fonction Trie 
			displayInvMarchant(bernard, 3);
			printf("\nVeuillez ecrire le nom de l'objet que vous voulez sans accents et avec les majuscules\n");
			Color(8,0);
			printf("(Apres avoir appuyer sur [entre] pour valider l'objet achete, appuyer sur [1] puis sur [entre])\n");
			Color(13,0);
			printf("votre choix: ");
			scanf("%s \n", choixItemChar);
			inventoryVerif = 0;
			for (i = 0 ; i < 3 ; i++){ // Boucle pour parcourir les trois armes afin de faire la suite
				if(strcmp(choixItemChar,bernard.itemSlotsArmes[i].nom)==0){ //Si ce que le joueur à écrit corresponds avec le nom d'un des objets;
					int d = i; //Stocker l'objet choisis dans le "d"
					if(player.money >= bernard.itemSlotsArmes[d].prix){ //Si le joueur à assez d'argent Alors..
						for (i = 0 ; i < 3 ; i++){	
								if ((strcmp(player.itemSlotsArmes[i].nom, "Vide"))==0){ //Vérifie si le slot d'inventaire est dispo
									player.itemSlotsArmes[i] = bernard.itemSlotsArmes[d]; // Met l'objet dans l'inventaire
									printf("Vous avez achetee %s qui a coute ", bernard.itemSlotsArmes[d].nom);
									Color(14,0);
									printf("%d ", bernard.itemSlotsArmes[d].prix);
									Color(13,0);
									printf("d'argent. Vous le mettez dans l'emplacement %d \n", i);
									player.money = player.money - bernard.itemSlotsArmes[d].prix; // Dépense l'argent
									printf("");
									inventoryVerif = 1; //Vérifie si l'achat à été effectué 
									i = 5; //Sors de la boucle
								}
						};
						if(inventoryVerif == 0){		 // Si l'achat n'a pas été effectué
							printf("Vous avez n'avez pas assez de place dans votre inventaire\n"); 
							Color(15,0);
						}
						
					};
					choiceItemVerif = 1; // Si l'objet écrit est bien présent
				};
			};
			if(choiceItemVerif == 0){ // L'objet écrit n'est pas présent
					printf("Vous n'avez pas choisi un objet dans la boutique\n");
					Color(15,0);
			}
			
	break;
	default:
	 printf("");
	break;
	}
	Color(3,0);
	printf("__________MENU__________\n");
	printf(" MENU:\n[1] Inventaire\n[2] Boutique\n[3] Vendre\n");
	Color(15,0);
    Color(4,0);
	printf("[4] QUITTER\n");
	Color(3,0);
	scanf("%d", &choixJoueur);
	Color(15,0);
	}while(choixJoueur != 4);
	
	Color(12,0);
	printf("Vous avez quitter le marchand\n");
	Color(15,0);

}	
