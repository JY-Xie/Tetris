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
    int dx = 0;
    bool rotate_flag = false;
    while (_kbhit()) {
        unsigned char ch = _getch();
        if (ch == 224) {
            ch = _getch();
            switch (ch) {
                case 72:
                    rotate_flag = true;
                    break;
                case 80:
                    delay = SPEED_QUICK;
                    break;
                case 75:
                    dx = -1;
                    break;
                case 77:
                    dx = 1;
                    break;
                default:
                    break;

            }
        }

    }

    if (rotate_flag) {
        rotate();
        update = true;
    }

    if (dx != 0) {
        move_left_right(dx);
        update = true;
    }

}

void Game::update_window() {
    putimage(0, 0, &img_bg);
    BeginBatchDraw();
    IMAGE ** imgs = Block::getImages();
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (map[i][j] == 0) continue;
            int x = j * block_size + left_margin;
            int y = i * block_size + top_margin;
            putimage(x, y, imgs[map[i][j]]);
        }

    }

    current_block->draw(left_margin, top_margin);
    next_block->draw(689, 150);
    EndBatchDraw();
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
    back_block = *current_block;
    current_block->drop();

    if (!current_block->block_in_map(map)) {
        back_block.solidify(map);
        delete current_block;
        current_block = next_block;
        next_block = new Block;
    }

    delay = SPEED_NORMAL;
}

void Game::clear_line() {
    int lines = 0;
    int k = rows-1;
    for (int i = rows-1; i >= 0; i--) {
        int count = 0;
        for (int j = 0; j < cols; j++) {
            if (map[i][j]) {
                count++;
            }
            map[k][j] = map[i][j];
        }

        if (count < cols) {
            k--;
        } else {
            lines++;
        }
    }

}

void Game::move_left_right(int offset) {
    back_block = *current_block;
    current_block->move_left_right(offset);

    if (!current_block->block_in_map(map)) {
        *current_block = back_block;
    }
}

void Game::rotate() {
    if (current_block->get_block_type() == 6) {
        return;
    }
    back_block = *current_block;
    current_block->rotate();
    if (!current_block->block_in_map(map)) {
        *current_block = back_block;
    }
}
