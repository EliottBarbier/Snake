#include <iostream>
#include "borders.h"

//On génère un std::map avec les coordonnées des bordures, pour qu'ensuite on les affiche
void borders(std::map<std::pair<int,int>,bool> &board,const std::pair<int,int> &coordhaut,const std::pair<int,int> &coordbas){
    int x1=coordhaut.first;
    int y1=coordhaut.second;

    int x2=coordbas.first;
    int y2=coordbas.second;

    for(int i=y1;i<=y2;i++){
        board[{x1,i}]=true;
        board[{x2,i}]=true;
    }
    for(int i=x1;i<=x2;i++){
        board[{i,y1}]=true;
        board[{i,y2}]=true;
    }
}

//On génère un std::map avec les coordonnées de la grille de jeux, pour qu'ensuite on l'affiche
void inside_board(std::map<std::pair<int,int>,bool> &board,const std::pair<int,int> &coordhaut,const std::pair<int,int> &coordbas){
    int x1=coordhaut.first;
    int y1=coordhaut.second;

    int x2=coordbas.first;
    int y2=coordbas.second;

    for(int i=y1+1;i<=y2-1;i++){
        for(int j=x1+1;j<=x2-1;j++){
        board[{j,i}]=true;
        board[{j,i}]=true;
    }
    }
    
}
