//
// Created by XieJiYe on 2024/2/2.
//
#pragma once
#ifndef TETRIS_BLOCK_HPP
#define TETRIS_BLOCK_HPP
#include "graphics.h"
#include "vector"
#include "conio.h"

struct Point{
    int row;
    int col;
};

class Block {
public:
    Block();
    void drop();
    void move_left_right(int offset);
    void rotate();
    void draw(int left_margin, int top_margin);

    Block& operator=(const Block& other);
//    Point * get_small_blocks();
    bool block_in_map(const std::vector<std::vector<int>> &map);
    void solidify(std::vector<std::vector<int>> &map);
    static IMAGE ** getImages();
    int get_block_type() const;

private:
    int block_type;
    Point small_blocks[4];
    IMAGE *image;
    static IMAGE *images[7];
    static int size;
//    friend class Game;
};


#endif //TETRIS_BLOCK_HPP
