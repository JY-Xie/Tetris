//
// Created by XieJiYe on 2024/2/2.
//

#include "Game.hpp"
#include "ctime"
#include "cstdlib"
#include "iostream"
#include "Block.hpp"

const int SPEED_NORMAL = 500;
const int SPEED_QUICK = 50;


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

    next_block = new Block;
    current_block = next_block;
    next_block = new Block;

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
    delay = SPEED_NORMAL;
    srand(time(NULL));

    initgraph(938, 896);

    loadimage(&img_bg, "../res/bg2.png");
//    char data[20][10];
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            map[i][j] = 0;
        }
    }
}

void Game::key_event() {
    // update = true;
}

void Game::update_window() {
    putimage(0, 0, &img_bg);
    BeginBatchDraw();
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (map[i][j] == 0) continue;
            int x = j * block_size + left_margin;
            int y = i * block_size + top_margin;
            putimage(x, y, &Block::images[i][j]);
        }
    }

    current_block->draw(left_margin, top_margin);
    next_block->draw(689, 150);
    EndBatchDraw();
//    Block block;
//    block.draw(left_margin, top_margin);
}

int Game::get_delay() {
    static unsigned long last_time = 0;
    auto current_time = GetTickCount();
    if (last_time == 0) {
        last_time = current_time;
        return 0;
    } else {
        auto ret = current_time - last_time;
        last_time = current_time;
        return ret;
    }
}

void Game::drop() {
    back_block = current_block;
    current_block->drop();

    if (!current_block->block_in_map(map)) {
        back_block->solidify(map);

        delete current_block;
        current_block = next_block;
        next_block = new Block;
    }
}

void Game::clear_line() {

}
