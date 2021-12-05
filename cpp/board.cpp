#include "board.h"


void board_clear(std::map<std::pair<int,int>,bool> &board)
{
    board.clear();
}

void board_set_pixel(std::map<std::pair<int,int>,bool> &board, int x, int y) // On ne met pas de const car on modifie ici
{
    board[{x,y}] = true;
}
