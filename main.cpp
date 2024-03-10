#include <iostream>
#include "eco_system_marche.cpp"
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(NULL));
    Life life1;
    Life life2;

    //on met de lherbe partout
    life1.Univers_Init();
    life1.print_world();

    //On ajoute les moutons AVANT les loups 
    life2.mouton_Init();
    std::cout << "Grille après placement mouton pour life1:\n";
    life1.print_world();

    //On ajoute les Loups
    life2.loup_Init();
    std::cout << "\n\nGrille après placement Loup pour life1:\n";
    life1.print_world();
    
    std::cout << "\n\nGrille après Deplacement des animaux :\n";

    verif_world(life1);
    life2.print_world();
    return 0;
}
