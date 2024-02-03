//
// Created by XieJiYe on 2024/2/2.
//

#include "Game.hpp"
#include "ctime"
#include "cstdlib"


Game::Game(int rows, int cols, int left, int top, int block_size) {
    this->rows = rows;
    this->cols = cols;
    this->left_margin = left;
    this->top_margin = top;
    this->block_size = block_size;

    for (int i = 0; i < rows; i++){
        std::vector<int> map_row;
        for (int j = 0; j < cols; j++){
            map_row.push_back(0);
        }
        this->map.push_back(map_row);
    }
}

void Game::play() {
    init();

    int timer = 0;
    while (true){
        key_event();
        timer += get_delay();
        if (timer > delay) {
            timer = 0;
            drop();
            update = true;
        }

        if (update){
            update = false;
            update_window();

            clear_line();
        }
    }
}

void Game::init() {
    delay = 30;
    srand(time(NULL));

    initgraph(938, 896);

    loadimage(&img_bg, "res/bg2.png")
}

void Game::key_event() {
    // update = true;
}

void Game::update_window() {

}

int Game::get_delay() {

    return 0;
}

void Game::drop() {

}

void Game::clear_line() {

}
