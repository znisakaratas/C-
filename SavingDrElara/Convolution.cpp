//
// Created by Zeynep Nisa on 29.10.2023.
//

#include "Convolution.h"
#include <iostream>


// Default constructor
Convolution::Convolution() {
}

// Parametrized constructor for custom kernel and other parameters
// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad)
        : kernelHeight(kh), kernelWidth(kw), stride(stride_val), padEnabled(pad) {

    // Allocate memory for the kernel and copy the custom kernel data
    kernel = new double *[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = customKernel[i][j];
        }
    }

    // Additional setup if needed based on other parameters
}


// Destructor
Convolution::~Convolution() {
    if (kernel != nullptr){
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }

}
// Copy constructor
Convolution::Convolution(const Convolution &other)
        : kernelHeight(other.kernelHeight), kernelWidth(other.kernelWidth), stride(other.stride), padEnabled(other.padEnabled) {
    // Allocate memory for the kernel and copy the data from 'other' object
    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this != &other) {
        // Deallocate existing resources
        if (kernel != nullptr){
            for (int i = 0; i < kernelHeight; ++i) {
                delete[] kernel[i];
            }
            delete[] kernel;
        }

        // Allocate new memory and copy the data from 'other' object
        kernelHeight = other.kernelHeight;
        kernelWidth = other.kernelWidth;
        stride = other.stride;
        padEnabled = other.padEnabled;

        kernel = new double*[kernelHeight];
        for (int i = 0; i < kernelHeight; ++i) {
            kernel[i] = new double[kernelWidth];
            for (int j = 0; j < kernelWidth; ++j) {
                kernel[i][j] = other.kernel[i][j];
            }
        }
    }
    return *this;
}
// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int inputHeight = input_image.get_height();
    int inputWidth = input_image.get_width();
    int paddedHeight = inputHeight + (padEnabled ? 2 : 0);
    int paddedWidth = inputWidth + (padEnabled ? 2 : 0);
    ImageMatrix paddedInput(paddedHeight, paddedWidth);
    for (int y = 0; y < paddedHeight; ++y) {
        for (int x = 0; x < paddedWidth; ++x) {
            if (padEnabled) {
                if (x == 0 || y == 0 || x == paddedWidth - 1 || y == paddedHeight - 1) {
                    paddedInput.set_data(y, x, 0);
                } else {
                    paddedInput.set_data(y, x, input_image.get_data(y - 1, x - 1));
                }
            } else {
                paddedInput.set_data(y, x, input_image.get_data(y, x));
            }
        }
    }
    int outHeight = ((inputHeight - kernelHeight + 2*padEnabled) / stride ) + 1;
    int outWidth =((inputWidth - kernelWidth + 2*padEnabled) / stride ) + 1;
    ImageMatrix outputImage(outHeight, outWidth);
    // Iterate over the padded input image pixels
    for (int y = 0, i=0 ; i< outHeight ; y+= stride, ++i) {
        for (int x = 0, j= 0; j < outWidth; x+=stride, ++j) {
            // Apply convolution using the kernel on the current input pixel
            double sum = 0.0;
            for (int ky = 0; ky < kernelHeight; ++ky) {
                for (int kx = 0; kx < kernelWidth; ++kx) {
                    int pixelY = y + ky;
                    int pixelX = x + kx;
                    sum += kernel[ky][kx] * paddedInput.get_data(pixelY, pixelX) ;
                }
            }
            outputImage.set_data(i, j, sum);
        }
    }
    return outputImage;
}
