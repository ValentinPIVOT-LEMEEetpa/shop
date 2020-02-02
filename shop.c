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
	int price;
	int id;
};

struct Weapons{ //Structure pour des "Armes"
	char nom[50];
	int dmg;
	int price;
	int id;
};

struct Allies{	//Structure du joueur 
	int money;
	struct Weapons itemSlotsWeapons[2]; //Tableau d'armes 
	struct items itemSlotItems[5];		//NON UTILISE
};

struct PNJ{		//Structure du marchand
	int money;
	struct Weapons itemSlotsWeapons[10];
	struct items itemSlotsItems[100]; 	//NON UTILISE
	int size;
};


typedef struct Weapons sword ;
typedef struct Weapons bow ;
typedef struct Weapons axe ; //NON UTILISE
typedef struct Weapons wand ; //NON UTILISE

typedef struct items food; //NON UTILISE
typedef struct items boost; //NON UTILISE

typedef struct Allies human;
typedef struct PNJ merchant; 

void resetInv(human * inv){		//Remplace les valeurs NULL des noms dans les cases vide par "Vide"
	int i;
	
	 for (i = 0 ; i < 3 ; i++)
    {
		
			strcpy(inv -> itemSlotsWeapons[i].nom,"Vide"); // Ecrit "vide" dans les cases vide de l'inventaire du joueur
    }
}

void resetInvPNJ(merchant * inv){ //Remplace les valeurs NULL des noms dans les cases vide par "Z"
	int i;
	
	 for (i = 0 ; i < 4 ; i++)
    {
			strcpy(inv -> itemSlotsWeapons[i].nom,"Z"); // Ecrit Z dans la dernière case du marchand afin que le trie s'effectue correctement. FAIRE ATTENTION A NE JAMAIS AFFICHER LA DERNIRE CASE DU TABLEAU
    }
}

void swap(sword * itemSlotsWeapons, int i, int j) //Echange deux valeurs (trie à bulle) 
{
  sword tmp = itemSlotsWeapons[i];
  itemSlotsWeapons[i]=itemSlotsWeapons[j];
  itemSlotsWeapons[j]=tmp;
}

void tri_shop(merchant * merchant) //Comparaison pour Trier (trie à bulle) 
{
   	int v=0;
    int i;
	int j;
		for (i = 0, j = i+1 ; i < 3 ; i++, j++)
		{
			
			if (strcmp(merchant->itemSlotsWeapons[i].nom, merchant->itemSlotsWeapons[j].nom)>0) //Vérif si le terme avant (ou après je sais plus) est plus grand ou plus petit
			{
				printf("test\n");
				swap(&merchant->itemSlotsWeapons,i,j);
				
			}
			
		}
}

void displayInv(human inv){		//Affiche l'inventaire 
	int i;
	
	 for (i = 0 ; i < 3 ; i++)
    {
		
		printf("%s ",inv.itemSlotsWeapons[i].nom); printf("%d ",inv.itemSlotsWeapons[i].dmg); printf("%d ",inv.itemSlotsWeapons[i].price); printf("%d \n",inv.itemSlotsWeapons[i].id);
    }
}

void displayInvPNJ(merchant inv, int a){	//Affiche le marchand. Le a est une valeur lors de l'appelle de la fonction afin de modifier le nombre de valeurs à afficher
		int i;
	 for (i = 0 ; i < a ; i++)
    {
		printf("%s ",inv.itemSlotsWeapons[i].nom); printf("%d ",inv.itemSlotsWeapons[i].dmg); printf("%d ",inv.itemSlotsWeapons[i].price); printf("%d \n",inv.itemSlotsWeapons[i].id);
    }
	//  for (i = 0 ; i < a ; i++)
    // {
	// 	printf("%s ",inv.itemSlotsItems[i].nom); printf("%d ",inv.itemSlotsItems[i].hpRegen); printf("%d ",inv.itemSlotsItems[i].mpRegen);  printf("%d ",inv.itemSlotsItems[i].price); printf("%d \n",inv.itemSlotsItems[i].id);
    // }
}


void invMerchantRdm(merchant * inv, int a){		//Attribue aléatoirement des armes au marchand. Le a est une valeur lors de l'appelle de la fonction afin de modifier le nombre d'armes à initialiser
	int i;
	int choiceMerchant;
	const int MIN = 1, MAX = 6;

	sword blade = {"Epee", 5, 10, 1};
	sword dagger = {"Dague", 2 , 5, 2};
	sword saber = {"Saber", 10 , 15, 3};

	bow woodBow = {"Arc", 5, 10, 1}; 	
	bow fireBow = {"Feu_des_dieux", 2 , 5, 2};				
	bow ironBow = {"Arbalete", 10 , 15, 3};

	for (i = 0 ; i < 3 ; i++){

		choiceMerchant = (rand() % (MAX + 1 - MIN)) + MIN; 
		switch (choiceMerchant)
		{
		case 1:
			inv->itemSlotsWeapons[i] = blade; 
		break;
		case 2:
			inv->itemSlotsWeapons[i] = dagger; 
		break;
		case 3:
			inv->itemSlotsWeapons[i] = saber;
		break;
		case 4:
			inv->itemSlotsWeapons[i] = woodBow;
		break;
		case 5 :
			inv->itemSlotsWeapons[i] = fireBow;
		break;
		case 6:
			inv->itemSlotsWeapons[i] = ironBow;
		break;
		}
		sleep(1);
	}
}

int main() {
	srand(time(NULL)); 
	int i;
	int inventoryVerif = 0;
	int choicePlayer;
	int choixItem;
	int choiceItemVerif;
	char* choixItemChar[50];	//Variable pour les test

	human player = {100,{"vide",0,0,0}}; 
	merchant merchant = {1000,{"",0,0,0}};
	//FONCTION DE DEPART
	resetInv(&player); // Ecrit "Vide" dans les cases nom

	//Deroulement

	// scanf("%s", &choixItemChar);
	// printf("%s", choixItemChar);


	// for(i = 0 ; i < 3 ; i++){ // TEST : Parcour les trois. cases du marchand pour voir si le Fgets et le "nom" de l'arme dans chaqu'une des cases du tableau concordais. C'est pas le cas et je sais pas pourquoi.
   	// 	if(strcmp(choixItemChar,merchant.itemSlotsWeapons[i].nom)==0){
   	// 	printf("ca marche !\n");	//Non.. ça n'a jamais marché :( 
    //     }
    // }
	
	// MARCHAND !! PEUT ETRE MIS EN COMMENTAIRE, LES TEST QUE J'EFFECTUAIS ETAIT JUSTE AVANT .
    Color(3,0);
	printf("__________MENU__________\n");
	printf("Inventaire: [1]\nBoutique: [2]\n");
	Color(4,0);
	printf("[4] QUITTER\n");
	Color(3,0);
	scanf("%d", &choicePlayer);
	Color(15,0);
	do{
	switch (choicePlayer)
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
			resetInvPNJ(&merchant); //Appel de la fonction Reset
			invMerchantRdm(&merchant, 3); //Donnes des armes au marchand
			tri_shop(&merchant);	//Appel de la fonction Trie 
			displayInvPNJ(merchant, 3);
			printf("\nVeuillez ecrire le nom de l'objet que vous voulez sans accents et avec les majuscules: \n");
			Color(8,0);
			printf("(Apres avoir appuyer sur [entre] pour valider l'objet achete, appuyer sur [1] puis sur [entre])\n");
			Color(13,0);
			printf("votre choix: \n");
			scanf("%s \n", choixItemChar);
			inventoryVerif = 0;
			for (i = 0 ; i < 3 ; i++){ // Boucle pour parcourir les trois armes afin de faire la suite
				if(strcmp(choixItemChar,merchant.itemSlotsWeapons[i].nom)==0){ //Si ce que le joueur à écrit corresponds avec le nom d'un des objets;
					int d = i; //Stocker l'objet choisis dans le "d"
					if(player.money >= merchant.itemSlotsWeapons[d].price){ //Si le joueur à assez d'argent Alors..
						for (i = 0 ; i < 3 ; i++){	
								if ((strcmp(player.itemSlotsWeapons[i].nom, "Vide"))==0){ //Vérifie si le slot d'inventaire est dispo
									player.itemSlotsWeapons[i] = merchant.itemSlotsWeapons[d]; // Met l'objet dans l'inventaire
									printf("Vous avez achetee %s qui a coute ", merchant.itemSlotsWeapons[d].nom);
									Color(14,0);
									printf("%d ", merchant.itemSlotsWeapons[d].price);
									Color(13,0);
									printf("d'argent. Vous le mettez dans l'emplacement %d \n", i);
									player.money = player.money - merchant.itemSlotsWeapons[d].price; // Dépense l'argent
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
	scanf("%d", &choicePlayer);
	Color(15,0);
	}while(choicePlayer != 4);
	
	Color(12,0);
	printf("Vous avez quitter le marchand\n");
	Color(15,0);
	
}