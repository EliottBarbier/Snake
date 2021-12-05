#include "generator_fruit.h"

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
