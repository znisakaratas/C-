//
// Created by Zeynep Nisa on 17.11.2023.
//
#include "BlockFall.h"
#include <iostream>
#include "Block.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}

void BlockFall::read_blocks(const string &input_file) {
    ifstream inputFile(input_file);
    string line;
    vector<string> everyLine;
    vector<vector<vector<bool>>> eachShape;
    Block block;
    while (getline(inputFile, line)) {
        if (!line.empty()){
            if (line[line.length()-1] != ']' ) {
                if (line[0] == '[') {
                    everyLine.push_back(line.substr(1));
                } else {
                    everyLine.push_back(line);
                }
            }else {
                if (line[0] == '['){
                    everyLine.push_back(line.substr(1,line.length()-2));
                } else{
                    everyLine.push_back(line.substr(0,line.length()-1));
                }
                eachShape.push_back(block.pushBackRow(everyLine));
                everyLine.clear();
            }
        }
    }
    Block* initBlock = new Block() ;
    initial_block = initBlock;
    active_rotation = initBlock;
    Block * currentShape = initial_block;
    initial_block ->shape = eachShape[0];
    Block* rightBlock = new Block();
    rightBlock->shape = turnRight(eachShape[0].size(), eachShape[0][0].size(), eachShape[0]);
    initial_block->right_rotation= rightBlock ;
    if(rightBlock->shape == initial_block->shape){
        rightBlock->shape.clear();
        delete rightBlock;
        initial_block->right_rotation = initial_block;
        initial_block->left_rotation = initial_block;
    } else{
        Block* rotatedBlock = new Block();
        rotatedBlock->shape = turnRight(rightBlock->shape.size(), rightBlock->shape[0].size(), rightBlock->shape);
        rightBlock->left_rotation =initial_block;
        if (rotatedBlock->shape == initial_block->shape){
            rotatedBlock->shape.clear();
            delete rotatedBlock;
            rightBlock->right_rotation= initial_block;
            initial_block->left_rotation = rightBlock;
        } else{
            Block* leftRotated = new Block();
            leftRotated->shape = turnRight(rotatedBlock->shape.size(),rotatedBlock->shape[0].size(),rotatedBlock->shape);
            initial_block->left_rotation = leftRotated;
            leftRotated->right_rotation = initial_block;
            rightBlock->right_rotation = rotatedBlock;
            rotatedBlock->right_rotation = leftRotated;
            leftRotated->left_rotation = rotatedBlock;
            rotatedBlock->left_rotation = rightBlock;
        }
    }
    for (size_t i = 1; i < eachShape.size() - 1 ; ++i) {
        Block * addedShape = new Block();
        addedShape->shape = eachShape[i];
        currentShape->next_block = addedShape;
        if (currentShape->left_rotation != nullptr){
            currentShape->left_rotation->next_block = addedShape;
        }
        if (currentShape->right_rotation != nullptr){
            currentShape->right_rotation->next_block = addedShape;
        }
        if (currentShape->right_rotation->right_rotation != nullptr){
            currentShape->right_rotation->right_rotation->next_block = addedShape;
        }
        Block* rightShape = new Block();
        rightShape->shape = turnRight(addedShape->shape.size(),addedShape->shape[0].size(),addedShape->shape);
        if (rightShape->shape == addedShape->shape){
            rightShape->shape.clear();
            delete rightShape;
            addedShape->right_rotation = addedShape;
            addedShape->left_rotation = addedShape;
        }else{
            addedShape->right_rotation = rightShape;
            rightShape->left_rotation = addedShape;
            Block * fullRotated = new Block();
            fullRotated->shape = turnRight(rightShape->shape.size(),rightShape->shape[0].size(),rightShape->shape);
            //addedShape->next_block = rightShape->next_block;
            if (fullRotated->shape == addedShape->shape){
                fullRotated->shape.clear();
                delete fullRotated;
                addedShape->left_rotation = rightShape;
                rightShape->right_rotation = addedShape;
            } else{
                Block * leftShape = new Block();
                leftShape->shape = turnRight(fullRotated->shape.size(),fullRotated->shape[0].size(),fullRotated->shape);
                addedShape->left_rotation = leftShape;
                leftShape->right_rotation = addedShape;
                fullRotated->right_rotation = leftShape;
                leftShape->left_rotation = fullRotated;
                rightShape->right_rotation = fullRotated;
                fullRotated->left_rotation = rightShape;
            }
        }
        currentShape = addedShape;
    }
    power_up = eachShape[static_cast<int>(eachShape.size())-1];
    // TODO: Read the blocks from the input file and initialize "initial_block" and "active_rotation" member variables
    // TODO: For every block, generate its rotations and properly implement the multilevel linked list structure
    //       that represents the game blocks, as explained in the PA instructions.
    // TODO: Initialize the "power_up" member variable as the last block from the input file (do not add it to the linked list!)
}

void BlockFall::initialize_grid(const string &input_file) {
    ifstream inputFile(input_file);
    int value;
    string line;
    while (getline(inputFile, line)) {
        vector<int> row;
        istringstream iss(line);
        while (iss >> value) {
            row.push_back(value);
        }
        grid.push_back(row);
    }
    rows = grid.size();
    cols = grid[0].size();
    inputFile.close();

    // TODO: Initialize "rows" and "cols" member variables
    // TODO: Initialize "grid" member variable using the command-line argument 1 in main
}
vector<vector<bool>> BlockFall::turnRight(size_t row,size_t column,vector<vector<bool>> shapeData){
    vector<vector<bool>> rightShape(column, std::vector<bool>(row, false));
    for (size_t k = 0; k < row; ++k) {
        for (size_t j = 0; j < column; ++j) {
            rightShape[j][row-1-k] = shapeData[k][j];
        }
    }
    return rightShape;
}

BlockFall::~BlockFall() {
    // TODO: Free dynamically allocated memory used for storing game blocks
    while (initial_block != nullptr) {
        Block* temp = initial_block;
        initial_block = initial_block->next_block;
        if(temp->right_rotation == temp){
            temp->shape.clear();
            delete temp;
        }else if(temp->right_rotation->right_rotation == temp){
            temp->right_rotation->shape.clear();
            delete temp->right_rotation;
            temp->shape.clear();
            delete temp;
        }else{
            temp->right_rotation->right_rotation->shape.clear();
            delete temp->right_rotation->right_rotation;
            temp->right_rotation->shape.clear();
            delete temp->right_rotation;
            temp->left_rotation->shape.clear();
            delete temp->left_rotation;
            temp->shape.clear();
            delete temp;
        }
    }

}
