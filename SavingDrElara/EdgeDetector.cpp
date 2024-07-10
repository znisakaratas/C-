//
// Created by Zeynep Nisa on 29.10.2023.
//

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {
    Gx =new double*[3] {
            new double[3]{-1.0, 0.0, 1.0},
            new double[3]{-2.0, 0.0, 2.0},
            new double[3]{-1.0, 0.0, 1.0}
    };
    Gy = new double * [3]{
            new double[3]{-1.0, -2.0, -1.0},
            new double[3]{0.0, 0.0, 0.0},
            new double[3]{1.0, 2.0, 1.0}
    };
}

// Destructor
EdgeDetector::~EdgeDetector() {
    if (Gx != nullptr) {
        for (int i = 0; i < 3; ++i) {
            delete[] Gx[i];
        }
        delete[] Gx;
        Gx = nullptr;
    }

    if (Gy != nullptr) {
        for (int i = 0; i < 3; ++i) {
            delete[] Gy[i];
        }
        delete[] Gy;
        Gy = nullptr;
    }
}

// Detect Edges using the given algorithm
// Sobel operators

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {

    Convolution convolutionx(Gx,3,3,1,true);
    ImageMatrix Ix = convolutionx.convolve(input_image);
    Convolution convolutiony(Gy,3,3,1,true);
    ImageMatrix Iy = convolutiony.convolve(input_image);

    std::vector<std::pair<int, int>> EdgePixels;
    double threshold = 0.0;

    // Calculate magnitude and threshold
    for (int i = 0; i < input_image.get_height(); ++i) {
        for (int j = 0; j < input_image.get_width(); ++j) {
            double gradient = sqrt(pow(Ix.get_data(i, j), 2) + pow(Iy.get_data(i, j), 2));
            threshold += gradient;
        }
    }
    threshold /= (input_image.get_height() * input_image.get_width());

    // Collect edge pixels
    for (int i = 0; i < input_image.get_height(); ++i) {
        for (int j = 0; j < input_image.get_width(); ++j) {
            double gradient = sqrt(pow(Ix.get_data(i, j), 2) + pow(Iy.get_data(i, j), 2));
            if (gradient > threshold) {
                EdgePixels.emplace_back(i, j);
            }
        }
    }

    return EdgePixels;
}
ImageMatrix EdgeDetector::detectEdgesX(const ImageMatrix& input_image) {

    ImageMatrix iX;
    Convolution horizontal_edge(Gx, 3, 3, 1, true);
    iX = horizontal_edge.convolve(input_image);

    return iX;
}

// To control iY
ImageMatrix EdgeDetector::detectEdgesY(const ImageMatrix& input_image) {

    ImageMatrix iY;
    Convolution vertical_edge(Gy, 3, 3, 1, true);
    iY = vertical_edge.convolve(input_image);

    return iY;
}

