#include <iostream>
#include "screen.h"
#define clear() printf("\033[H\033[J")

void screen_clear()
{
    // Clear terminal
    std::cout << "\x1b[H\x1b[J";
    // Hide cursor
    std::cout << "\e[?25l";
}

//Cette fonction ne me sert pas
void screen_draw_board(const std::map<std::pair<int,int>,bool> &board) //On a un dictionnaire board ou pour chaque clé, qui correspond à si le 
//pixel est occupé ou non grâce à un booléen en valeur.
{
    for (std::pair<const std::pair<int, int>, bool> element : board) //On aurait pu mettre auto.
    {
        std::pair<int, int> coords = element.first;
        bool bdummy = element.second;
        int x = coords.first;
        int y = coords.second;

        // Positionnement en row/column.
        // (1,1) en haut a gauche
        // x = row, y = column
        std::cout << "\x1b["<<x << ";"<< y <<";H";
        std::cout << "*";

    }

    std::cout << std::flush;
}

//Fonction sui affiche le snake
void screen_draw_snake(const std::vector<std::pair<int,int>> &snake){

    for( std::pair<int,int> pix : snake){
        bool bdummy = true;
        int x = pix.first;
        int y = pix.second;
        std::cout << "\x1b["<<x << ";"<< y <<";H";
        std::cout << "*";
    }
    std::cout << std::flush;
}

//Fonction qui affiche les bordures
void screen_draw_borders(const std::map<std::pair<int,int>,bool> &board){

    for (std::pair<const std::pair<int, int>, bool> element : board) //On aurait pu mettre auto.
    {
        std::pair<int, int> coords = element.first;
        bool bdummy = element.second;
        int x = coords.first;
        int y = coords.second;

        // Positionnement en row/column.
        // (1,1) en haut a gauche
        // x = row, y = column
        std::cout << "\x1b["<<x << ";"<< y <<";H";
        std::cout << "|";

    }

    std::cout << std::flush;
}

//Fonction qui affiche la grille de jeux
void screen_draw_inside_board(const std::map<std::pair<int,int>,bool> &board){

    for (std::pair<const std::pair<int, int>, bool> element : board) //On aurait pu mettre auto.
    {
        std::pair<int, int> coords = element.first;
        bool bdummy = element.second;
        int x = coords.first;
        int y = coords.second;

        // Positionnement en row/column.
        // (1,1) en haut a gauche
        // x = row, y = column
        std::cout << "\x1b["<<x << ";"<< y <<";H";
        std::cout << "-";

    }

    std::cout << std::flush;
}

//Fonction qui affiche le fruit
void screen_draw_fruit(const std::pair<int,int> &fruit){
    int x=fruit.first;
    int y=fruit.second;
    std::cout << "\x1b["<<x << ";"<< y <<";H";
    std::cout << "0";
    std::cout << std::flush;

}
