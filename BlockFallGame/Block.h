//
// Created by Zeynep Nisa on 17.11.2023.
//

#ifndef ASSIGNMENT2_BLOCK_H
#define ASSIGNMENT2_BLOCK_H

#include <vector>


using namespace std;

class Block {
public:
    int starting_position = 0;
    vector<vector<bool>> shape; // Two-dimensional vector corresponding to the block's shape
    Block * right_rotation = nullptr; // Pointer to the block's clockwise neighbor block (its right rotation)
    Block * left_rotation = nullptr; // Pointer to the block's counter-clockwise neighbor block (its left rotation)
    Block * next_block = nullptr; // Pointer to the next block to appear in the game
    vector<vector<bool>> pushBackRow(vector<string> line) {
        vector<vector<bool>> someShape;
        for (auto & j : line) {
            vector<bool> row;
            for (char ch : j) {
                if (ch == '0' || ch == '1') {
                    row.push_back(ch == '1');
                }
            }
            someShape.push_back(row);
        }
        return someShape;
    }

    bool operator==(const Block& other) const {
        if (shape.size() != other.shape.size()) {
            return false;
        } else if (shape.at(0).size() != other.shape.at(0).size()){
            return false;
        }
        for (size_t i = 0; i < shape.size(); ++i) {
            for (int j = 0; j < shape.at(i).size(); ++j) {
                if (shape[i][j] != other.shape[i][j]) {
                    return false;
                }
            }
        }
        return true;
        // TODO: Overload the == operator to compare two blocks based on their shapes

    }

    bool operator!=(const Block& other) const {
        return !(*this == other);
        // TODO: Overload the != operator to compare two blocks based on their shapes
    }
};

#endif //ASSIGNMENT2_BLOCK_H
