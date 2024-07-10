//
// Created by Zeynep Nisa on 17.11.2023.
//
#include <fstream>
#include <iostream>
#include "GameController.h"
#include "BlockFall.h"
using namespace std;
bool GameController::shapeStart(vector<vector<int>>& grid,Block* active_rotation,int starting_pos) {
    for (size_t i = 0; i < active_rotation->shape.size(); ++i) {
        for (size_t j = 0; j < active_rotation->shape[0].size(); ++j) {
            if(grid[i][j+starting_pos] == 1 && active_rotation->shape[i][j]==1){
                return false;
            }
        }
    }
    return true;
}
bool GameController:: checkForPowerUpShape(BlockFall& game) {
    int gridRows = static_cast<int>(game.grid.size());
    int gridCols = static_cast<int>(game.grid[0].size());

    int shapeRows =static_cast<int>(game.power_up.size()) ;
    int shapeCols = static_cast<int>(game.power_up[0].size());
    int counts = 0;
    // Iterate through the grid
    for (int i = 0; i <= gridRows - shapeRows; ++i) {
        for (int j = 0; j <= gridCols - shapeCols; ++j) {
            // if the power-up shape matches the grid at the specified position
            for (int srow = 0; srow < shapeRows; ++srow) {
                for (int scol = 0; scol < shapeCols; ++scol) {
                    if (game.power_up[srow][scol] == game.grid[i + srow][j + scol]) {
                        counts++;
                    }
                }
            }
            if (counts == shapeCols * shapeRows) return true;
            counts = 0;
        }
    }
    // If the power-up shape is not found in the entire grid, return false
    return false;
}

void GameController:: printGrid(vector<vector<int>>& grid,unsigned long currentscore,Block* active,BlockFall& game){
    cout<<"Score:"<< currentscore<<endl;
    cout<<"Highest Score: "<<game.leaderboard.head_leaderboard_entry->score<<endl;
    std::vector<std::vector<int>> copyGrid(grid.begin(), grid.end());
    for (int i = 0; i < active->shape.size(); ++i) {
        for (int j = 0; j < active->shape[0].size(); ++j) {
            copyGrid[i][j+active->starting_position] = active->shape[i][j];
        }
    }
    for (const auto& row : copyGrid) {
        for (bool cell : row) {
            if (cell){
                cout << occupiedCellChar ;
            }else{
                cout<<unoccupiedCellChar;
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

bool GameController::blockFits(const std::vector<std::vector<int>>& grid, Block* active_rotation, int fallDistance) {
    for (size_t i = 0; i < active_rotation->shape.size(); ++i) {
        for (size_t j = 0; j < active_rotation->shape[i].size(); ++j) {
            if (active_rotation->shape[i][j] == 1) {
                size_t rowInGrid = i + fallDistance +1;
                if (rowInGrid >= grid.size() || grid[rowInGrid][j+active_rotation->starting_position] == 1) {
                    return false;
                }
            }
        }
    }
    return true;
}
bool GameController:: isRowFull(BlockFall& game){
    vector<int> fullRow(game.cols,1);
    for (int j = 0; j < game.rows; ++j) {
        if (game.grid[j] == fullRow){
            return true;
        }
    }
    return false;
}
void GameController::finalPrint(BlockFall& game){
    cout<<"Final grid and score:\nScore:" <<game.current_score <<
        "\nHighest Score: 40000\n";
    for (int i = 0; i < game.grid.size(); ++i) {
        for (int k = 0; k < game.grid[0].size(); ++k) {
            if (game.grid[i][k] == 1){
                cout<<occupiedCellChar;
            } else{
                cout<<unoccupiedCellChar;
            }
        }
        cout<<endl;
    }
}
int GameController::findFallDistance(const std::vector<std::vector<int>>& grid, Block* active_rotation) {
    int maxFallDistance = static_cast<int>(grid.size()) - static_cast<int>(active_rotation->shape.size());

    for (int fallDistance = 0; fallDistance < maxFallDistance; ++fallDistance) {
        if (!blockFits(grid, active_rotation, fallDistance)) {
            return fallDistance ;
        }
    }

    return maxFallDistance;
}
bool GameController::play(BlockFall& game, const string& commands_file){
    ifstream commandFile(commands_file);
    string line;
    while (getline(commandFile, line)) {
        if(line.empty()){
            break;
        }
        else if (line == "PRINT_GRID"){
            printGrid(game.grid,game.current_score,game.active_rotation,game);
        }else if(line == "DROP"){
            int rowsToBeFalled = findFallDistance(game.grid,game.active_rotation);
            int positiveVal = 0;
            for (int i = 0; i < game.active_rotation->shape.size(); ++i) {
                for (int j = 0; j < game.active_rotation->shape[0].size(); ++j) {
                    if (game.active_rotation->shape[i][j] ==1){
                        positiveVal++;
                    }
                }
            }
            game.current_score += positiveVal*rowsToBeFalled;
            if (!game.gravity_mode_on) {
                for (int i = rowsToBeFalled; i < rowsToBeFalled + game.active_rotation->shape.size(); ++i) {
                    int start = game.active_rotation->starting_position;
                    for (int j = start; j < start + game.active_rotation->shape[0].size(); ++j) {
                        if (game.grid[i][j] != 1){
                            game.grid[i][j] = game.active_rotation->shape[i - rowsToBeFalled][j - game.active_rotation->starting_position];
                        }
                    }
                }
            }
            else if (game.gravity_mode_on){
                int col =game.active_rotation->starting_position;
                for (int c = col; c < col + game.active_rotation->shape[0].size() ; ++c) {
                    vector<int> shapeRowTrue = {};
                    for (int i = 0; i < static_cast<int>(game.rows); ++i) {
                        if (game.grid[i][c] == 1 && game.grid[i - 1][c] == 1){
                            continue;
                        }else if (game.grid[i][c] == 1 || i == game.rows-1){
                            for (int k= 0; k< game.active_rotation->shape.size(); k++) {
                                if (game.active_rotation->shape[k][c-col] == 1) {
                                    shapeRowTrue.insert(shapeRowTrue.begin(),k);
                                }
                            }
                            for (int score = 0; score < shapeRowTrue.size(); ++score) {
                                if (i == game.rows-1 && game.grid[i-score][c] == 0){
                                    game.grid[i-score][c]=1;
                                }else{
                                    int rowToBeChanged = i- (score+1);
                                    game.grid[rowToBeChanged][c] = 1;
                                }
                            }
                            shapeRowTrue.clear();
                        }
                    }

                }
            }
            if (checkForPowerUpShape(game)){
                int count = 0;
                for(int i=0 ; i<game.rows;i++){
                    for(int j=0; j<game.cols; j++){
                        if (game.grid[i][j] == 1){
                            count++;
                        }
                    }
                }
                game.current_score += count + 1000;
                count = 0;
                cout<<"Before clearing:" <<endl;
                for (int i = 0; i < game.rows; ++i) {
                    for (int j = 0; j < game.cols; ++j) {
                        if (game.grid[i][j] == 0){
                            cout<<unoccupiedCellChar;
                        }else{
                            cout<<occupiedCellChar;
                        }
                    }
                    cout<<endl;
                }
                for(int i=0 ; i<game.rows;i++){
                    for(int j=0; j<game.cols; j++){
                        game.grid[i][j] = 0;
                    }
                }
                cout<<"\nScore:  "<<game.current_score<<"\nHighest score:  "<<endl;
                for (int i = 0; i < game.rows; ++i) {
                    for (int j = 0; j < game.cols; ++j) {
                        if (game.grid[i][j] == 0){
                            cout<<unoccupiedCellChar;
                        }else{
                            cout<<occupiedCellChar;
                        }
                    }
                    cout<<endl;
                }
                }else if(isRowFull(game)){
                vector<int> rowsToBeDeleted = {};
                vector<int> fullRow(game.cols,1);
                vector<int> emptyRow(game.cols,0);
                for (int j = 0; j < game.rows; ++j) {
                    if (game.grid[j] == fullRow){
                        rowsToBeDeleted.push_back(j);
                    }
                }
                cout<<"Before cleaning:" <<endl;
                for (int i = 0; i < game.rows; ++i) {
                    for (int j = 0; j < game.cols; ++j) {
                        if (game.grid[i][j] == 0){
                            cout<<unoccupiedCellChar;
                        }else{
                            cout<<occupiedCellChar;
                        }
                    }
                    cout<<endl;
                }
                for (int row: rowsToBeDeleted) {
                    game.grid.erase(game.grid.begin() + row);
                    game.grid.insert(game.grid.begin(),emptyRow);
                    game.current_score += game.cols;
                }
                for (int i = 0; i < game.rows; ++i) {
                    for (int j = 0; j < game.cols; ++j) {
                        if (game.grid[i][j] == 0){
                            cout<<unoccupiedCellChar;
                        }else{
                            cout<<occupiedCellChar;
                        }
                    }
                    cout<<endl;
                }
            }
            if(game.active_rotation->next_block == nullptr){
                cout<<"YOU WIN!\nNo more blocks.\n";
                finalPrint(game);
                return true;
            }
            game.active_rotation = game.active_rotation->next_block;
            if (!shapeStart(game.grid, game.active_rotation,game.active_rotation->starting_position)){
                cout<<"GAME OVER!\nNext block that couldn't fit:\n";
                for (int i = 0; i < game.active_rotation->shape.size(); ++i) {
                    for (int k = 0; k < game.active_rotation->shape[0].size(); ++k) {
                        if (game.active_rotation->shape[i][k] == 1){
                            cout<<occupiedCellChar;
                        } else{
                            cout<<unoccupiedCellChar;
                        }
                    }
                    cout<<endl;
                }
                finalPrint(game);
                return false;
            }

        }else if(line == "MOVE_RIGHT"){
            int position = static_cast<int>(game.active_rotation->starting_position + game.active_rotation->shape[0].size());
            if ( position<game.cols && shapeStart(game.grid,game.active_rotation,game.active_rotation->starting_position+1)){
                game.active_rotation->starting_position ++;
            }
        } else if (line =="MOVE_LEFT"){
            int position = game.active_rotation->starting_position - 1;
            if ( position>= 0 && shapeStart(game.grid,game.active_rotation,position)){
                game.active_rotation->starting_position --;
            }
        }else if(line =="ROTATE_RIGHT"){
            if (shapeStart(game.grid,game.active_rotation->right_rotation,game.active_rotation->starting_position)){
                game.active_rotation = game.active_rotation->right_rotation;
            }
        }else if (line =="ROTATE_LEFT"){
            if (shapeStart(game.grid,game.active_rotation->left_rotation,game.active_rotation->starting_position)){
                game.active_rotation = game.active_rotation->left_rotation;
            }
        }else if(line =="GRAVITY_SWITCH"){
            if (game.gravity_mode_on){
                game.gravity_mode_on = false;
            }else{
                game.gravity_mode_on = true;
                vector<vector<int>> emptyGrid(game.rows, std::vector<int>(game.cols, 0));
                int countTrue = 0;
                for (int i = 0; i < game.cols; ++i) {
                    for (int j = 0; j < game.rows; ++j) {
                        if (game.grid[j][i] == 1){
                            countTrue++;
                        }
                    }
                    for (int k = game.rows-countTrue; k < game.rows; ++k) {
                        emptyGrid[k][i] =1;
                        countTrue = 0;
                    }
                }
                for (int i = 0; i < game.rows; ++i) {
                    for (int j = 0; j < game.cols; ++j) {
                        game.grid[i][j] = emptyGrid[i][j];

                    }
                }
            }
        }else{
            cout<<"Unknown command:"<<line<<endl;
        }

    }
    cout<<"GAME FINISHED!\nNo more commands.\n";
    finalPrint(game);

    return true;
    // TODO: Implement the gameplay here while reading the commands from the input file given as the 3rd command-line
    //       argument. The return value represents if the gameplay was successful or not: false if game over,
    //       true otherwise.

}




