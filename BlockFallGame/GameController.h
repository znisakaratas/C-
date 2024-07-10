//
// Created by Zeynep Nisa on 17.11.2023.
//

#ifndef ASSIGNMENT2_GAMECONTROLLER_H
#define ASSIGNMENT2_GAMECONTROLLER_H

#include "BlockFall.h"

using namespace std;

class GameController {
public:
    bool play(BlockFall &game, const string &commands_file); // Function that implements the gameplay
    bool shapeStart( vector<std::vector<int>> &grid,Block* active_rotation,int starting_pos);
    void  printGrid(vector<vector<int>>& grid,unsigned long currentscore,Block* active,BlockFall& game);
    int findFallDistance(const vector<std::vector<int>> &grid, Block* active_rotation);
    bool checkForPowerUpShape(BlockFall& game);
    bool blockFits(const std::vector<std::vector<int>>& grid, Block* active_rotation, int fallDistance);
    bool isRowFull(BlockFall &game);

    void finalPrint(BlockFall &game);
};


#endif //ASSIGNMENT2_GAMECONTROLLER_H
