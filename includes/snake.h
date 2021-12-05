#pragma once
#include <vector>


//On définit une structure ici !
struct snake_segment_st
{
    int dx = 0;
    int dy = 0;
    int size = 0;
    int x = 0;
    int y = 0;
};


// Fonctions du snake
void snake_init ();
void push_front(std::vector<std::pair<int,int>> &snake,const std::pair<int,int> &valeur);
void snake_growth(std::vector<std::pair<int,int>> &snake, const std::pair<int,int> &ancient_queue);
std::pair<int,int> pop_front(std::vector<std::pair<int,int>> &snake);