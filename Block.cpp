//
// Created by XieJiYe on 2024/2/2.
//

#include <iostream>
#include "Block.hpp"
#include "array"
#include "cstdlib"


IMAGE * Block::images[7] = {nullptr, };
int Block::size = 36;


Block::Block() {
    if (images[0] == nullptr){
        IMAGE imgTmp;
        loadimage(&imgTmp, "res/titles.png");
        SetWorkingImage(&imgTmp);
        for (int i = 0; i < 7; i++) {
            images[i] = new IMAGE;
            getimage(images[i], i*size, 0, size, size);
        }
        SetWorkingImage();
    }


    std::array<std::array<int, 4>, 7> blocks = {{
        {1, 3, 5, 7},
        {2, 4, 5, 7},
        {3, 5, 4, 6},
        {3, 5, 4, 7},
        {2, 3, 5, 7},
        {3, 5, 7, 6},
        {2, 3, 4, 5}
    }};

//    for (int i = 0; i < blocks.size(); i++) {
//        for (int j = 0; j < blocks[i].size(); j++) {
//            std::cout << blocks[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

    block_type = rand() % 7;

    for (int i = 0; i < 4; i++) {
        int value = blocks[block_type][i];
        small_blocks[i].row = value / 2;
        small_blocks[i].col = value % 2;
    }

    image = images[block_type];




}

void Block::drop() {

}

void Block::move_left_right(int offset) {

}

void Block::rotate() {

}

void Block::draw(int left_margin, int top_margin) {
    for (int i = 0; i < 4; i++){
        int x = left_margin + small_blocks[i].col * size;
        int y = top_margin + small_blocks[i].row * size;
        putimage(x, y, image);
    }
}
