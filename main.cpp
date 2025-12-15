// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859
#include <iostream>
#include "Game.hpp"

int main() {

    Game game;
    game.loadFromFile("input.txt");

    // Run game logic based on loaded commands
    game.executeCommands();

    game.outputFinalState("output.txt");

    return 0;
}