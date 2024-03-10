#include "eco_system.hpp"
#include <random>
#include<iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

/* 
-2 = Sels Minéraux
-1 = terre
0 = Herbe
1 = Moutons
2 = Loups
*/

using namespace std;

//Monde initiale
Life Life:: world[7][7] = {
                    {0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0}
};



//Init de l'univers dans lequel se passe la simulation
void Life::Univers_Init(){
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            world[i][j].type.animaltype = 0;
        }
    }
}

//génère un nbr aléatoire
int Life:: random_intervalle(int a, int b) {
    int r = std::rand() % (b - a + 1) + a;
    return r;
}

//Creér des moutons dans le monde
void Life::mouton_Init(){
    //On place des moutons sur la grille
    int nbMouton=0;
    std::cout << "Donnez le nombre de moutons : ";
    std::cin >> nbMouton;
    int nbCases = (7 * 7) - 2; //MOINS UNE CASE CAR ON LAISSE AU MINIMUM 1 LOUP et une herbe 
    while (nbMouton <= 0 || nbMouton > nbCases) { 
        std::cout << "Trop de Mouton : " << nbMouton << "\nDonnez un nombre de Mouton inferieur a : " << nbCases << std::endl;
        std::cin >> nbMouton;
    }

    int compteur = 0;
    while (nbMouton > compteur) {
        int indiceX_Alea = Life::random_intervalle(0, 7 - 1);
        int indiceY_Alea = Life::random_intervalle(0, 7 - 1);

        //On place des M que sur des cases H , donc on boucle si c'est égal à 1 ou 2
        while (world[indiceX_Alea][indiceY_Alea].type.animaltype == 1 || world[indiceX_Alea][indiceY_Alea].type.animaltype == 2) {
            indiceX_Alea = Life::random_intervalle(0, 7 - 1);
            indiceY_Alea = Life::random_intervalle(0, 7 - 1);
        }

        //si l'indice est correct on place un 1 cest a dire un Mouton
        world[indiceX_Alea][indiceY_Alea].type.animaltype = 1;
        compteur = compteur +1 ;
    }
}

//Creér des loups dans le monde
void Life:: loup_Init(){

    //On place des Loup sur la grille
    int nbCases= (7 * 7) - 1; //MOINS UNE CASE CAR ON LAISSE AU MINIMUM 1 herbe
    int nb_mouton_placer = 0;

    //on compte le nombre de loup
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (world[i][j].type.animaltype == 1) {
                nb_mouton_placer++;
            }
        }
    }
    int nb_place_dispo=  nbCases - nb_mouton_placer ; //Nb de cases (disons 4) -moins nb mouton (disons 2) = 2 place dispo
    int nombreLoup=0;
    std::cout << "Donnez le nombre de Loup que vous voulez  : ";
    std::cin >> nombreLoup;
    while ( nombreLoup<=0  || nombreLoup > nb_place_dispo){ 
        std::cout<<"Trop de Loup :"<<nombreLoup<<"\nDonnez un nombre de Loup egale ou inferieur a: "<<nb_place_dispo<<std::endl;
        std::cin>>nombreLoup;
    }

    while (nombreLoup > 0)
    {
        int indiceX_Alea= random_intervalle(0, 7-1);
        int indiceY_Alea= random_intervalle(0, 7-1);

        //On place des M que sur des cases H , donc on boucle si cest egal a 1 ou 2
        while ( (world[indiceX_Alea][indiceY_Alea].type.animaltype == 1) || 
            (world[indiceX_Alea][indiceY_Alea].type.animaltype == 2))  
        {
            indiceX_Alea= random_intervalle(0, 7-1);
            indiceY_Alea= random_intervalle(0, 7-1);
            
        }
        //si l'indice est correct on place la lettre M
        world[indiceX_Alea][indiceY_Alea].type.animaltype = 2;
        nombreLoup = nombreLoup -1;
        
    } 
}


//Print le monde sous forme de grille de la taille du monde (7x7)
void Life::print_world(){
    for (int a=0; a<7; a++){
        std::cout << "\033[1;30m"; //Couleur Grise avec echappement
        std::cout << "+---";
        std::cout << "\033[0m";  //Fin echappementt
    }
    std::cout << "\033[1;30m";
    printf("+\n");
    std::cout << "\033[0m";

    for (int i=0 ; i< 7; i++){
        std::cout << "\033[1;30m";
        std::cout <<"|";
        std::cout << "\033[0m";

        for (int y=0; y<7; y++){ //Couleur selon la lettre
            if (world[i][y].type ==0){
                          //debut couleur    Lettre      Fin couleur     Debut couleur Mur    Fin CouleurMUR
                std::cout <<" " <<"\033[32m"<< "H" <<"\033[0m" << "\033[1;30m" << " |" << "\033[0m";
            }
            if (world[i][y].type ==1){
                std::cout <<" "                 <<"M"         << "\033[1;30m" << " |" << "\033[0m";
            }
            if (world[i][y].type ==2){
                std::cout <<" " <<"\033[1;31m"<<"L" <<"\033[0m" << "\033[1;30m" << " |" << "\033[0m";
            }
            if (world[i][y].type == -1){
                std::cout <<" " <<"\033[38;2;170;85;0m"<<"T" <<"\033[0m" << "\033[1;30m" << " |" << "\033[0m";
            }

            if (world[i][y].type == -2){
                std::cout <<" " <<"\033[36m"<<"S" <<"\033[0m" << "\033[1;30m" << " |" << "\033[0m";
            }
            
        }

        printf("\n");
        for (int z=0; z<7; z++){
            std::cout << "\033[1;30m";
            std::cout << "+---";
            std::cout << "\033[0m";
        }
        std::cout << "\033[1;30m";
        printf("+\n");
        std::cout << "\033[0m";
    }
}

//Cette fonction parcours le tableau et remplace les sel mineraux ou appel Moveset
int verif_world(Life life){
    for (int i=0; i<7; i++){
        for (int j=0; j<7; j++){
            if(Life::world[i][j].grass == -2)//remplace les sels minéraux par de l'herbe
                Life::world[i][j] = 0;
            else if(Life::world[i][j].type.animaltype == 1 || Life::world[i][j].type.animaltype == 2){//si l'objet aux coordonnées i j de world est 1 ou 2 (mouton ou loup)
                Life::world[i][j].type.x = i;//On lui attribue la coordonné i, soit le n° de la liste 
                Life::world[i][j].type.y = j;//On lui attribue la coordonné j, soit le n° de l'élément dans la liste i
                moveset(Life::world[i][j]);//On appel mouveset
            }
        }
    }
    life.reset(life);//On reset la possibilité de bouger aux animaux (<objet>.move)
    return 0;
}

//reset le <objet>.move à 0
void  Life::reset(Life life){
    for (int i=0; i<7; i++){
        for (int j=0; j<7; j++){
            if(Life::world[i][j].type.animaltype == 1 || Life::world[i][j].type.animaltype == 2){
                Life::world[i][j].type.move = 0;
            }
        }
    }
}

//Fonction chargé qui gere le deplacement des Moutons et Loups
int moveset(Life& Life){
    pos moves[9]; //Liste des mouvements
    pos prey[9]; //liste des proies (pour les loups)
    int indice=0; //indice pour iterer les listes

    memset(moves, 0, sizeof(moves));
    indice = 0;

    //Moutons : mouvements des moutons
    if(Life.type.animaltype == 1){
        if(Life.type.move==0){ //si il a un mouvement possible  
            if(Life.type.x-1>=0 && Life.type.y-1>=0){ //Si on sort en haut à gauche
                if(Life::world[Life.type.x-1][Life.type.y-1].type.animaltype == 0 || Life::world[Life.type.x-1][Life.type.y-1].type.animaltype == -1 || Life::world[Life.type.x-1][Life.type.y-1].type.animaltype == -2){ //si la case est del'herbe, de la terre, ou des sels minéraux
                    //On enregistre les coordonnées x-y de la case, et on incrémente indice
                    moves[indice].x = Life.type.x-1;
                    moves[indice].y = Life.type.y-1;
                    indice++;
                }
            }

            if(Life.type.x-1>=0){ //Si on sort en haut
                 if(Life::world[Life.type.x-1][Life.type.y].type.animaltype == 0 || Life::world[Life.type.x-1][Life.type.y].type.animaltype == -1 || Life::world[Life.type.x-1][Life.type.y].type.animaltype == -2){
                    moves[indice].x = Life.type.x-1;
                    moves[indice].y = Life.type.y;
                    indice++;
                }
            }

            if(Life.type.x-1>=0 && Life.type.y+1<=6){ //Si on sort en haut à droite
               if(Life::world[Life.type.x-1][Life.type.y+1].type.animaltype == 0 || Life::world[Life.type.x-1][Life.type.y+1].type.animaltype == -1 || Life::world[Life.type.x-1][Life.type.y+1].type.animaltype == -2){
                    moves[indice].x = Life.type.x-1;
                    moves[indice].y = Life.type.y+1;
                    indice++;
                }
            }

            if(Life.type.y+1<=6){ //Si on sort à droite
                if(Life::world[Life.type.x][Life.type.y+1].type.animaltype == 0 || Life::world[Life.type.x][Life.type.y+1].type.animaltype == -1 || Life::world[Life.type.x][Life.type.y+1].type.animaltype == -2){
                    moves[indice].x = Life.type.x;
                    moves[indice].y = Life.type.y+1;
                    indice++;
                }
            }

            if(Life.type.x+1<=6 && Life.type.y+1<=6){ //Si on sort en bas à droite
                 if(Life::world[Life.type.x+1][Life.type.y+1].type.animaltype == 0 || Life::world[Life.type.x+1][Life.type.y+1].type.animaltype == -1 || Life::world[Life.type.x+1][Life.type.y+1].type.animaltype == -2){
                    moves[indice].x = Life.type.x+1;
                    moves[indice].y = Life.type.y+1;
                    indice++;
                }
            }
            
            if(Life.type.x+1<=6){ //Si on sort en bas
                if(Life::world[Life.type.x][Life.type.y+1].type.animaltype == 0 || Life::world[Life.type.x][Life.type.y+1].type.animaltype == -1 ||  Life::world[Life.type.x][Life.type.y+1].type.animaltype == -2){
                    moves[indice].x = Life.type.x+1;
                    moves[indice].y = Life.type.y;
                    indice++;
                }
            }

            if(Life.type.x+1<=6 && Life.type.y-1>=0){ //Si on sort en bas à gauche
                if(Life::world[Life.type.x+1][Life.type.y-1].type.animaltype == 0 || Life::world[Life.type.x+1][Life.type.y-1].type.animaltype == -1 || Life::world[Life.type.x+1][Life.type.y-1].type.animaltype == -2){
                    moves[indice].x = Life.type.x+1;
                    moves[indice].y = Life.type.y-1;
                    indice++;
                }
            }
            
            if(Life.type.y+1>=0){ //Si on sort à gauche
                if(Life::world[Life.type.x][Life.type.y-1].type.animaltype == 0 || Life::world[Life.type.x][Life.type.y-1].type.animaltype == -1 || Life::world[Life.type.x][Life.type.y-1].type.animaltype == -2){
                    moves[indice].x = Life.type.x;
                    moves[indice].y = Life.type.y-1;
                    indice++;
                }
            }
            //Position même de l'animal
            moves[indice].x = Life.type.x;
            moves[indice].y = Life.type.y;

            //Crée un nombre aléatoire
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(0, (sizeof moves/sizeof * moves)-1);
            int randomNum = dis(gen);

        //Déplacement

            //On retire l'animal à l'ancienne pos
            Life::world[Life.type.x][Life.type.y].type.animaltype = -1;
            //On lui change les coords
            Life.type.x = moves[randomNum].x;
            Life.type.y = moves[randomNum].y;
            //On met move à 1 (dire qu'il à déjà bougé)
            //Life.type.move = 1;
            Life::world[Life.type.x][Life.type.y].type.move = 1;
            //On met l'animal sur la nouvelle pos
            Life::world[Life.type.x][Life.type.y].type.animaltype = 1;
        } 
    }

    pos reset;
    reset.x = -1;
    reset.y = -1;
    indice=0;
    int indiceP = 0;


    

    //Loup
    if(Life.type.animaltype == 2){
        if(Life.type.move==0){//Si il peut bouger
            if(Life.type.x-1>=0 && Life.type.y-1>=0){ //Si on sort en haut à gauche
            //si la case est del'herbe, de la terre, ou des sels minéraux, ou un mouton
                if(Life::world[Life.type.x-1][Life.type.y-1] == 0 || Life::world[Life.type.x-1][Life.type.y-1] == -1 || Life::world[Life.type.x-1][Life.type.y-1] == -2 || Life::world[Life.type.x-1][Life.type.y-1] == 1){
                    if(Life::world[Life.type.x-1][Life.type.y-1] == 1){//Si mouton on l'ajoute aux proies
                        prey[indiceP].x = Life.type.x-1;
                        prey[indiceP].y = Life.type.y-1;
                        indiceP++;
                    } else { // sinon on ajoute juste un mouvement
                        moves[indice].x = Life.type.x-1;
                        moves[indice].y = Life.type.y-1;
                        indice++;
                    }
                }
            }

            if(Life.type.x-1>=0){ //Si on sort en haut
                if(Life::world[Life.type.x-1][Life.type.y] == 0 || Life::world[Life.type.x-1][Life.type.y] == -1 || Life::world[Life.type.x-1][Life.type.y] == -2 || Life::world[Life.type.x-1][Life.type.y] == 1){
                    if( Life::world[Life.type.x-1][Life.type.y] == 1){
                        prey[indiceP].x = Life.type.x-1;
                        prey[indiceP].y = Life.type.y;
                        indiceP++;
                    }else {
                        moves[indice].x = Life.type.x-1;
                        moves[indice].y = Life.type.y;
                        indice++;
                    }
                }
            }

            if(Life.type.x-1>=0 && Life.type.y+1<=6){ //Si on sort en haut à droite
                if(Life::world[Life.type.x-1][Life.type.y+1] == 0 || Life::world[Life.type.x-1][Life.type.y+1] == -1 || Life::world[Life.type.x-1][Life.type.y+1] == -2 || Life::world[Life.type.x-1][Life.type.y+1] == 1){
                    if(Life::world[Life.type.x-1][Life.type.y+1] == 1){
                        prey[indiceP].x = Life.type.x-1;
                        prey[indiceP].y = Life.type.y+1;
                        indiceP++;
                    } else {
                        moves[indice].x = Life.type.x-1;
                        moves[indice].y = Life.type.y+1;
                        indice++;
                    }
                }
            }

            if(Life.type.y+1<=6){ //Si on sort à droite
                if(Life::world[Life.type.x][Life.type.y+1] == 0 || Life::world[Life.type.x][Life.type.y+1] == -1 || Life::world[Life.type.x][Life.type.y+1] == -2 || Life::world[Life.type.x][Life.type.y+1] == 1){
                    if(Life::world[Life.type.x][Life.type.y+1] == 1){
                        prey[indiceP].x = Life.type.x;
                        prey[indiceP].y = Life.type.y+1;
                        indiceP++;
                    } else {
                        moves[indice].x = Life.type.x;
                        moves[indice].y = Life.type.y+1;
                        indice++;
                    }
                }
            }

            if(Life.type.x+1<=6 && Life.type.y+1<=6){ //Si on sort en bas à droite
                if(Life::world[Life.type.x+1][Life.type.y+1] == 0 || Life::world[Life.type.x+1][Life.type.y+1] == -1 || Life::world[Life.type.x+1][Life.type.y+1] == -2 || Life::world[Life.type.x+1][Life.type.y+1] == 1){
                    if(Life::world[Life.type.x+1][Life.type.y+1] == 1){
                        prey[indiceP].x = Life.type.x+1;
                        prey[indiceP].y = Life.type.y+1;
                        indiceP++;
                    } else {
                        moves[indice].x = Life.type.x+1;
                        moves[indice].y = Life.type.y+1;
                        indice++;
                    }
                }
            }
            
            if(Life.type.x+1<=6){ //Si on sort en bas
                if(Life::world[Life.type.x+1][Life.type.y+1] == 0 || Life::world[Life.type.x+1][Life.type.y+1] == -1 || Life::world[Life.type.x+1][Life.type.y+1] == -2 || Life::world[Life.type.x+1][Life.type.y+1] == 1){
                    if(Life::world[Life.type.x+1][Life.type.y+1] == 1){
                        prey[indiceP].x = Life.type.x+1;
                        prey[indiceP].y = Life.type.y;
                        indiceP++;
                    } else {
                        moves[indice].x = Life.type.x+1;
                        moves[indice].y = Life.type.y;
                        indice++;
                    }
                }
            }

            if(Life.type.x+1<=6, Life.type.y-1>=0){ //Si on sort en bas à gauche
                if(Life::world[Life.type.x+1][Life.type.y-1] == 0 || Life::world[Life.type.x+1][Life.type.y-1] == -1 || Life::world[Life.type.x+1][Life.type.y-1] == -2 || Life::world[Life.type.x+1][Life.type.y-1] == 1){
                    if(Life::world[Life.type.x+1][Life.type.y-1] == 1){
                        prey[indiceP].x = Life.type.x+1;
                        prey[indiceP].y = Life.type.y-1;
                        indiceP++;
                    } else {
                        moves[indice].x = Life.type.x+1;
                        moves[indice].y = Life.type.y-1;
                        indice++;
                    }
                }
            }
            
            if(Life.type.y+1>=0){ //Si on sort à gauche
                if(Life::world[Life.type.x][Life.type.y-1] == 0 || Life::world[Life.type.x][Life.type.y-1] == -1 || Life::world[Life.type.x][Life.type.y-1] == -2 || Life::world[Life.type.x][Life.type.y-1] == 1){
                    if(Life::world[Life.type.x][Life.type.y-1] == 1){
                        prey[indiceP].x = Life.type.x;
                        prey[indiceP].y = Life.type.y-1;
                        indiceP++;
                    } else {
                        moves[indice].x = Life.type.x;
                        moves[indice].y = Life.type.y-1;
                        indice++;
                    }
                }
            }

            //pos x-y du loup
            moves[indice].x = Life.type.x;
            moves[indice].y = Life.type.y;

            //Nbr aléatoire
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(0, (sizeof moves/sizeof * moves)-1);
            int randomNum = dis(gen);

            //Si mouton, on le mange et monte la saturation
            if(Life::world[moves[randomNum].x][moves[randomNum].y]==1){
                Life.type.saturation=10;
            }
            
        //Déplacement
            //pareil qu'au dessus
            Life::world[Life.type.x][Life.type.y].type.animaltype = -2;
            Life.type.x = moves[randomNum].x;
            Life.type.y = moves[randomNum].y;
            //Life.type.move =1;
            Life::world[Life.type.x][Life.type.y].type.move = 1;
            Life::world[Life.type.x][Life.type.y].type.animaltype = 2;
        }
            
    }
    return 0;
}