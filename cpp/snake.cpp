#include "snake.h"


void snake_init()
{


}

void push_front(std::vector<std::pair<int,int>> &snake,const std::pair<int,int> &valeur){ //Pas forcément optimal... Et agit sur le sanke par effet
//de bord + renvoie l'ancienne queue, utile lorsqu'il mange un fruit pour ne pas l'effacer.
    
    snake.push_back(snake.back()); //La size augmente de 1

    for( int i =snake.size()-2; i>=1;i--){
        snake[i]=snake[i-1];
    }
    snake[0]=valeur;
}


void snake_growth(std::vector<std::pair<int,int>> &snake, const std::pair<int,int> &ancient_queue){
    push_front(snake,ancient_queue);
}