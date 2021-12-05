#include <utility>
#include <map>

void borders(std::map<std::pair<int,int>,bool> &board,const std::pair<int,int> &coordhaut,const std::pair<int,int> &coordbas);
void inside_board(std::map<std::pair<int,int>,bool> &board,const std::pair<int,int> &coordhaut,const std::pair<int,int> &coordbas);
