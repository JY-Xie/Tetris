//
// Created by XieJiYe on 2024/2/2.
//
#pragma once
#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP
#include "vector"
#include "graphics.h"
#include "Block.hpp"



class Game {
public:
    Game(int rows, int cols, int left, int top, int block_size);
    void init();
    void play();
private:
    void key_event();
    void update_window();
    int get_delay();
    void drop();
    void clear_line();
    void move_left_right(int offset);

private:
    int delay;
    bool update;
    std::vector<std::vector<int>> map;
    int rows;
    int cols;
    int left_margin;
    int top_margin;
    int block_size;
    IMAGE img_bg;

    Block *current_block;
    Block *next_block;
    Block back_block;
};


#endif //TETRIS_GAME_HPP
