#pragma once
#include <map>
#include <vector>

void screen_clear();
void screen_draw_board(const std::map<std::pair<int,int>,bool> &board);
void screen_draw_snake(const std::vector<std::pair<int,int>> &snake);
void screen_draw_inside_board(const std::map<std::pair<int,int>,bool> &board);
void screen_draw_borders(const std::map<std::pair<int,int>,bool> &board);
void screen_draw_fruit(const std::pair<int,int> &fruit);