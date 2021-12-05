#include <iostream>
#include <thread>
#include <chrono>

#include "snake.h"
#include "screen.h"
#include "board.h"
#include "keyboard.h"
#include "borders.h"
#include "generator_fruit.h"

#define UP_ARROW    65 //On définit les touches du clavier qui vont permettre de intéragir
#define LEFT_ARROW  68
#define DOWN_ARROW  66
#define RIGHT_ARROW 67

// Variables de contexte du board

std::vector<std::pair<int,int>> snake; //Je définie le snake comme ceci, l'avantage est que l'ordre donné par le vector
                                       //est l'ordre du snake : le premier élément est la queue, le dernier la tête.

std::pair<int,int> coordhaut {1,1}; //Le haut gauche de la grille est à (1,1). On définit la taille de la grille de jeux, 
std::pair<int,int> coordbas {21,51};//bords inclus ici

std::map<std::pair<int,int>,bool> borders_map; //La carte des bordures
std::map<std::pair<int,int>,bool> board_map; //La carte de la grille de jeux


// Variables de contexte du snake
int snake_size = 5; // J'ai choisi de démarer avecun snake de taille 5 pour l'instant. A CHANGER

std::vector<snake_segment_st> snake_segments; //Par compris comment l'utiliser
std::map<std::pair<int,int>,bool> snake_board; //Non plus, j'ai pas compris comment savoir dans quel ordre le snake est

int main(int, char**) {

    std::cout << "Snake starting...\n";

    borders(borders_map,coordhaut,coordbas);
    inside_board(board_map,coordhaut,coordbas);
    
    keyboard_init();
    int x = 2; //On démarre en haut à droite de la grille
    int y = snake_size+1;

    for(int i =2;i<=snake_size+1;i++){ //Je définis le snake à afficher initialement
        std::pair<int,int> pix {x,i};
        snake.push_back(pix);
    }

    std::pair<int,int> posi_of_fruit; //On définit le fruit initial 
    posi_of_fruit=posi_fruit(coordhaut,coordbas);


    while (true) //On démarre le jeux, il faudra mettre un cadençage + le fait que le snake continue en 
                 //ligne droite quand on ne touche à rien/
    {

        // Affichage de la scène
        screen_clear();
        screen_draw_inside_board(board_map); //La grille
        screen_draw_borders(borders_map); //La bordure
        screen_draw_fruit(posi_of_fruit); //Le fruit
        screen_draw_snake(snake); //Le snake

        //board_clear(snake_board)
        //board_set_pixel(snake_board, x, y); //On dit que on met la croix en (0,0) ie en haut à gauch, puis on actualise //en fonction du clavier.
        //for(int i =1;i<= snake_size;i++){
        //std::pair<int,int> posi {0,i};
        //snake_board[posi]=true;
        //}
        //screen_draw_board(snake_board); //On affiche le serpent


        // Lecture clavier et actions
        int key_scan = keyboard_scan();
        std::pair<int,int> ancient_queue; //L'ancienne queue du serpent avant son déplacement
        if (key_scan == UP_ARROW)
        {
            x--;
            ancient_queue = pop_front(snake); //On change le snake par effet de bord + on récupère l'ancienne queue
            snake.push_back({x,y}); //On rajoute la nouvelle tête
        }
        else if (key_scan == DOWN_ARROW)
        {
            x++;
            ancient_queue = pop_front(snake);
            snake.push_back({x,y});
        }
        else if (key_scan == LEFT_ARROW)
        {
            y--;
            ancient_queue = pop_front(snake);
            snake.push_back({x,y});
        }
        else if (key_scan == RIGHT_ARROW)
        {
            y++;
            ancient_queue = pop_front(snake);
            snake.push_back({x,y});
        }
        // Contrôle  des limites
        if (x < 0) x=0;
        if (y < 0) y=0;

        if (snake.back()==posi_of_fruit){ //Il faudra traiter le cas pour qu'il ne se mette pas où le snake est déjà
                                          //On regarde si le snake mange le fruit
            posi_of_fruit=posi_fruit(coordhaut,coordbas);
            snake_growth(snake,ancient_queue); //Agit par effet de bord aussi
        }
        if (snake_eat_himself(snake)){
            screen_clear();
            std::cout <<"Game over" <<std::endl;
            return(0); //On arrête le programme, on pourra demander plus tard si l'on veut rejouer A FAIRE
        }

        // Exemple d'attente si besoin était (attention, suspend entièrement l'application)
        //std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }

    keyboard_end();

}
