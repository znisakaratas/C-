//
// Created by Zeynep Nisa on 29.10.2023.
//

#ifndef ENCODEMESSAGE_H
#define ENCODEMESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

class EncodeMessage {
public:
    EncodeMessage();
    ~EncodeMessage();
    bool isPrime(int num);
    ImageMatrix encodeMessageToImage(const ImageMatrix& img, const std::string& message, const std::vector<std::pair<int, int>>& positions);
private:
    // Any private helper functions or variables if necessary
};


#endif //ENCODEMESSAGE_H
