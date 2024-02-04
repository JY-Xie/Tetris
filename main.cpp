#include <iostream>
#include "Game.hpp"
#include "conio.h"
#include "Block.hpp"


int main() {
    Game game(20, 10, 263, 133, 36);
    game.play();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
