#include <iostream>
#include <random>
#include <utility>
#include <map>



std::pair<int,int> posi_fruit(const std::pair<int,int> &coordhaut,const std::pair<int,int> &coordbas);
bool fruit_on_snake(const std::vector<std::pair<int,int>> &snake,const std::pair<int,int> &posi_fruit);
std::pair<int,int> gene_fruit_out_snake(const std::vector<std::pair<int,int>> &snake,const std::map<std::pair<int,int>,bool> &board_map, const std::pair<int,int> &posi_fruit);