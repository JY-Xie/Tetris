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
        loadimage(&imgTmp, "../res/tiles.png");
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
    for (auto &block: small_blocks){
        block.row++;
    }
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

Block &Block::operator=(const Block &other) {
    if (this == &other) return *this;
    this->block_type = other.block_type;
    for (int i = 0; i < 4; i++) {
        this->small_blocks[i] = other.small_blocks[i];
    }
    return *this;
}

bool Block::block_in_map(const std::vector<std::vector<int>> &map) {
    auto rows = map.size();
    auto cols = map[0].size();
    for (int i = 0; i < 4; i++){
        if (
                small_blocks[i].col < 0 || small_blocks[i].col >= cols ||
                small_blocks[i].row < 0 || small_blocks[i].row >= rows ||
                map[small_blocks[i].row][small_blocks[i].col] != 0
        ) {
            return false;
        }
    }
    return true;
}

void Block::solidify(std::vector<std::vector<int>> &map) {
    int rows = map.size();
    int cols = map[0].size();

    for (int i = 0; i < 4; i++) {
        int row = small_blocks[i].row;
        int col = small_blocks[i].col;

        // 检查边界
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            map[row][col] = block_type;
            std::cout << "ppp" << std::endl;
        } else {
            // 如果越界，这里可以添加错误处理代码，例如输出错误信息或者抛出异常
            std::cerr << "Out of bounds access: row = " << row << ", col = " << col << std::endl;
        }
    }

    for (int i = 0; i < 4; i++){
        map[small_blocks[i].row][small_blocks[i].col] = block_type;
    }
}
