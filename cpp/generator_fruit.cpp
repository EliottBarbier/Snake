#include "generator_fruit.h"


//On génère la position du fruit dans la grille, de manière aléatoire
std::pair<int,int> posi_fruit(const std::pair<int,int> &coordhaut,const std::pair<int,int> &coordbas){

    int MINx=coordhaut.first+1;
    int MAXx=coordbas.first-1;
    int MINy=coordhaut.second+1;
    int MAXy=coordbas.second-1;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(MINx, MAXx);
    int posix = distr(eng);

    std::uniform_int_distribution<int> distr2(MINy, MAXy);
    int posiy = distr2(eng);

    std::pair<int,int> posi {posix,posiy};
    return(posi);
}

bool fruit_on_snake(const std::vector<std::pair<int,int>> &snake,const std::pair<int,int> &posi_fruit){
    for(std::pair<int,int> posi :snake){
        if (posi==posi_fruit){
            return true;
        }
    }
    return false;
}
std::pair<int,int> gene_fruit_out_snake(const std::vector<std::pair<int,int>> &snake,const std::map<std::pair<int,int>,bool> &board_map, const std::pair<int,int> &posi_fruit){
    std::vector<std::pair<int,int>> posi_libre;
    for(auto p : board_map){

        for(auto posi:snake){
            if(posi != p.first){
            posi_libre.push_back(p.first);
            }
        }  
        }   //La il aurait mieux fallu qu'un est une map pour le snake, avec les mêmes clés que board,on aurait pu le faire

    int MIN = 0;
    int MAX= posi_libre.size() - 1;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(MIN, MAX);
    int indice = distr(eng);
    return(posi_libre[indice]);
}