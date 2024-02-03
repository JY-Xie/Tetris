#include <iostream>
#include "Game.hpp"
#include "conio.h"
#include "Block.hpp"
#include "filesystem"

int main() {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current working directory: " << currentPath << std::endl;
    Game game(20, 10, 163, 133, 36);
    game.play();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
