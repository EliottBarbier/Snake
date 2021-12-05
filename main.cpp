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
std::map<std::pair<int,int>,bool> snake_board;

std::vector<std::pair<int,int>> snake;

std::pair<int,int> coordhaut {1,1}; //Le haut gauche de la grille est à (1,1)
std::pair<int,int> coordbas {21,51};
std::map<std::pair<int,int>,bool> borders_map;
std::map<std::pair<int,int>,bool> board_map;

// Variables de contexte du snake
int snake_size = 5;
std::vector<snake_segment_st> snake_segments;

std::pair<int,int> pop_front(std::vector<std::pair<int,int>> &snake){ //Pas forcément optimal... Et agit sur le sanke par effet
//de bord + renvoie l'ancienne queue, utile lorsqu'il mange un fruit pour ne pas l'effacer.
    std::pair<int,int> queue;
    queue=snake[0];
    for( int i =0; i<snake.size()-1;i++ ){
        snake[i]=snake[i+1];

    }
    snake.pop_back();
    return(queue);
}






int main(int, char**) {

    std::cout << "Snake starting...\n";

    borders(borders_map,coordhaut,coordbas);
    inside_board(board_map,coordhaut,coordbas);
    
    keyboard_init();
    int x = 2; //On démarre en haut à droite de la grille
    int y = snake_size+1;

    for(int i =2;i<=snake_size+1;i++){
        std::pair<int,int> pix {x,i};
        snake.push_back(pix);
    }

    std::pair<int,int> posi_of_fruit;
    posi_of_fruit=posi_fruit(coordhaut,coordbas);


    while (true)
    {

        // Affichage de la scène
        screen_clear();

        screen_draw_inside_board(board_map);
        screen_draw_borders(borders_map);
        screen_draw_fruit(posi_of_fruit);
        //board_clear(snake_board); //On clean
        screen_draw_snake(snake);


        //board_set_pixel(snake_board, x, y); //On dit que on met la croix en (0,0) ie en haut à gauch, puis on actualise 
                                            //en fonction du clavier.
        //for(int i =1;i<= snake_size;i++){
        //std::pair<int,int> posi {0,i};
        //snake_board[posi]=true;
        //}
        //screen_draw_board(snake_board); //On affiche le serpent


        // Lecture clavier et actions
        int key_scan = keyboard_scan();
        std::pair<int,int> ancient_queue;
        if (key_scan == UP_ARROW)
        {
            x--;
            ancient_queue = pop_front(snake); 
            snake.push_back({x,y});
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
            posi_of_fruit=posi_fruit(coordhaut,coordbas);
            snake_growth(snake,ancient_queue); //Agit par effet de bord aussi
        }
        


        // Exemple d'attente si besoin était (attention, suspend entièrement l'application)
        //std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }

    keyboard_end();

}
