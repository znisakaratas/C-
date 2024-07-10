//
// Created by Zeynep Nisa on 29.10.2023.
//

#ifndef EDGEDETECTOR_H
#define EDGEDETECTOR_H

#include "ImageMatrix.h"
#include "Convolution.h"
#include <vector>

class EdgeDetector {
public:
    EdgeDetector();
    ~EdgeDetector();

    std::vector<std::pair<int, int>> detectEdges(const ImageMatrix& input_image);

    ImageMatrix detectEdgesY(const ImageMatrix &input_image);

    ImageMatrix detectEdgesX(const ImageMatrix &input_image);
private:
    // add your private member variables and functions
    double** Gx;
    double** Gy;

};



#endif //EDGEDETECTOR_H
