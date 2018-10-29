/*Projet : Puissance X
 *
 * \author Christ Mbombo Mokonda
 * \date 11 Avril 2018
 *
 */


#include <stdio.h>
#include <stdlib.h>

int c; //nombre de colonnes du tableau
int l; // nombre de lignes du tableau
int p; //nombre de points décisifs pour gagner 

#define EMPTY 0 //permet de savoir si une case du tableau est vide
#define VALID -2 //possibilité de joueur dans une case
#define INVALID -1 //impossibilté de joueur dans une case
#define PLAYER1 1
#define PLAYER2 2



void bufferScanf();
void opening();
void initTab (int t[l][c]);
void displayTab(int t[l][c]);
int horizontal(int t[l][c]);
int vertical(int t[l][c]);
//int diagonal(int t[l][c],int l,int c,int player);
int win(int t[l][c]);
int chooseCol(int player,int column,int t[l][c]);
void play(int t[l][c]);
void replay(int t[l][c]);


//--------------------------------------------//


void bufferScanf(){
  int c;
  while((c=getchar()) != EOF && c != '\n');
 
}

//---------------------AFFICHAGE-----------------------//

void opening(){
    printf("\n\n\n\n");
    printf("\t\t********************************************\n");
    printf("\t\t\n");
    printf("\t\t\t\tPUISSANCE %d \t\t   \n",p);
    printf("\t\t\n");
    printf("\t\t********************************************\n\n\n");
}


void initTab (int t[l][c]){
  int i, j;
  for (i = 0; i < l; i++){
    for (j = 0; j < c; j++){
      t[i][j] = 0;
    }
  }
}


void displayTab(int t[l][c]){
  int i, j;
  int a=1;
  
  printf("      ");
  for (j = 0; j < c; j++){
    printf(" %d",a++); 
  }
  a=l;
  printf("\n");
  for (i = 0; i < l; i++){    
    printf("  %2d ",a--);
    printf("|");  
    for(j = 0; j < c; j++){
      if ( t[i][j] == EMPTY ){ 
	printf(" .");
      }
      if ( t[i][j] == PLAYER1 ){  
	printf(" X"); 
      }
      if ( t[i][j] == PLAYER2 ){  
	printf( " #"); 
      }
      printf("|");
    }
    printf("\n");
  }
  printf("\n");
}

//---------------------ALIGNEMENT-----------------------//

int horizontal(int t[l][c]){
  int i,j;
  int cpt=0;
  int player=0;
  for(i=0;i<l;i++){
    for(j=0;j<c;j++) {
      if(t[i][j]!=player){
	      player=t[i][j];
	cpt=1;
      }
      else
	cpt++;
    
      if(cpt==p &&player!=0)
	return player;
    }
  }
  return 0;
}


int vertical(int t[l][c]){
  int i,j;
  int cpt=0;
  int player=0;		     
  for(j=0;j<c;j++){    
    for(i=0;i<l;i++){
      if(t[i][j]!=player){
	      player=t[i][j];
	      cpt=1;
      }
      else
	    cpt++;
      if(cpt==p && player!=0)
	    return player;
    }
  }
  return 0;   
}

//SOUCIS AVEC CETTE FONCTION => LES ALIGNEMENTS DIAGONALES NE SERONT PAS COMPTABILISÉS
/*
int diagonal(int t[l][c],int l,int c,int player){

//haut gauche
int cpt=0;
int j=c;


for(int i=l,cpt=0;i>0;i--,j--){
  if(t[i][j]==player){
    player=t[l][c];
    cpt=1;
  }
  else
  cpt++;
    if(cpt==p && player!=0){
      return player;
    }
  }



//haut droite
for(int i=l;i>0;i--,j++){
  if(t[i][j]==player){  
      player=t[l][c];
  }
    else
    cpt++;
    if(cpt==p && player!=0){
    return player;
    }
}

      
// bas gauche

for(int i=l;i>0;i++,j--){
  if(t[i][j]==player){
      player=t[l][c];
  }
    else
    cpt++;
    if(cpt==p && player!=0){
    return player;
    }    
}


//bas droite

for(int i=l;i>0;i++,j++){
  if(t[i][j]==player){
    player=t[l][c];
  }
    else
    cpt++;
      if(cpt==p && player!=0){
        return player;
      }
  }

return 0;

}
*/

int win(int t[l][c]){
  
  int  finalResult=0;
  
  finalResult=horizontal(t);
  if(finalResult!=0)
    return finalResult;
  
  finalResult=vertical(t);
  if(finalResult!=0)
    return finalResult;
  
  /*
  finalResult=gagner_diagonal(t,l,c, player);
      if(finalResult!=0)
      return finalResult;
  */
  
  return 0;
}

//---------------------MOTEUR DE JEU-----------------------//


int chooseCol(int player,int column,int  t[l][c]){
  int i;
  for(i=l-1;i>=0;i--)
    if(i>=0 && i<l && column>=0 && column<c){
      if(t[i][column]==EMPTY){
	t[i][column]=player; 
	return VALID; 
	printf("\n");
      }
    }else{
      return INVALID; 
    }
}



void play(int t[l][c]){
  int column;
  int nbcase = 0;
  int finalResult;
  int turn,result;
  
  opening();
  printf("Choisissez le joueur qui jouera en premier\n");
  scanf("%d",&turn);
  bufferScanf();
  
 
  while(nbcase <=l*c){ 
    
    printf("Choisissez la colonne où vous voulez placer votre pion\n");
    scanf("%d",&column);
    bufferScanf();
    
    //TOUR DU JOUEUR 1
    if(turn==PLAYER1){
      result=chooseCol(PLAYER1,column-1,t);
      if(result==VALID){
      	nbcase++;
        displayTab(t);
	      turn=PLAYER2;
      }

    }

    //TOUR DU JOUEUR 2
    else{
      result=chooseCol(PLAYER2,column-1,t);
      if(result==VALID){
      	nbcase++;
        displayTab(t);
  	  turn=PLAYER1;
       } 
    }      
    
    //displayTab(t);
    finalResult=win(t);
    
    if(finalResult!=0){  
      printf(" Le joueur numéro %d a gagné ! Fin de jeu!\n",finalResult);
      return;
      nbcase++;
    }   

  if(nbcase>=l*c){
    printf("Match nul! Fin de jeu!\n");
    replay(t);
    }

  }

}

void replay(int t[l][c]){
    int r=0;
    printf("\n\nVoulez vous rejouer ? (oui = 1 , non = 2)\n");
    scanf("%d",&r);
    bufferScanf();

    switch(r){
        case 1: 
        initTab(t);
        play(t);
        break;
        case 2 :
        exit(1);
        break;
        default:
        printf("Vous vous êtes trompés , veuillez retaper votre choix\n");
        replay(t);
        break;
    }
}

//--------------------------------------------//

int main(int argc,char **argv){
  if(argc!=4){
    printf("Usage: %s <nbcoupsDecisifs><nbLignes><nbColonnes>\n",argv[0]);
    return 0;
  }
  if(argc==4){

    p=atoi(argv[1]);
    l=atoi(argv[2]);
    c=atoi(argv[3]);
  }
  
  int t[l][c];
  initTab(t);
  play(t);
}
