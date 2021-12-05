#include "snake.h"


void snake_init()
{


}

//Je définie une fonction push_front pour les std::vector qui permet d'ajouter un élément devant.d
void push_front(std::vector<std::pair<int,int>> &snake,const std::pair<int,int> &valeur){
    snake.push_back(snake.back()); //La size augmente de 1

    for( int i =snake.size()-2; i>=1;i--){
        snake[i]=snake[i-1];
    }
    snake[0]=valeur;
}

//De même je définie une fonction pop_front qui enlève le premier élément du std:vector. //Pas forcément optimal... Et
// agit sur le snake par effet de bord + renvoie l'ancienne queue --> utile lorsqu'il mange un fruit pour ne pas l'effacer.
std::pair<int,int> pop_front(std::vector<std::pair<int,int>> &snake){ 
    std::pair<int,int> queue;
    queue=snake[0];
    for( int i =0; i<snake.size()-1;i++ ){
        snake[i]=snake[i+1];

    }
    snake.pop_back();
    return(queue);
}

//La fonction qui permet de faire grandir le snake de 1 quand il mange un fruit
void snake_growth(std::vector<std::pair<int,int>> &snake, const std::pair<int,int> &ancient_queue){
    push_front(snake,ancient_queue);
}

bool snake_eat_himself(const std::vector<std::pair<int,int>> &snake){
    std::pair<int,int> fin = snake.back();

    for(int i=0;i<snake.size()-1;i++){ //J'itère sur les indices et pas sur les éléments car je ne veux pas la tête du serpent.
        if (snake[i]==fin){
            return(true);
        }

    }
    return(false);
    

}