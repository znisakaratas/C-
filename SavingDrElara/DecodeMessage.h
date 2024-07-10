//
// Created by Zeynep Nisa on 29.10.2023.
//

#ifndef DECODEMESSAGE_H
#define DECODEMESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

// Class `DecodeMessage`: Provides the functionality to decode a binary message into an ASCII representation.
class DecodeMessage {
public:
    // Constructors and destructors
    DecodeMessage(); // Default constructor
    ~DecodeMessage(); // Destructor

    std::string decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels);

private:
    // Any private helper functions or variables if necessary
};

#endif //DECODEMESSAGE_H
