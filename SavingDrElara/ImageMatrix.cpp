#include "ImageMatrix.h"
#include <iostream>
#include <fstream>


// Default constructor
ImageMatrix::ImageMatrix(){

}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    // Allocate memory for the matrix data
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        // Optionally, initialize the matrix elements to zero or another default value
        for (int j = 0; j < width; ++j) {
            data[i][j] = 0.0; // Initializing to zero
        }
    }
}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }
}
// Destructor
ImageMatrix::~ImageMatrix() {
    // Deallocate memory for the matrix data
    if (data != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;  // Optional: Set to nullptr for safety
    }
}


// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth)
        : height(imgHeight), width(imgWidth) {

    // Allocate memory for the matrix data
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = inputMatrix[i][j];  // Copy the input matrix data to the ImageMatrix
        }
    }
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) {
    height = other.height;
    width = other.width;
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    if (this != &other) {
        // Deallocate the existing data in the current object
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;

        // Copy the dimensions from the 'other' object
        height = other.height;
        width = other.width;

        // Allocate memory for the matrix data in the current object
        data = new double*[height];
        for (int i = 0; i < height; ++i) {
            data[i] = new double[width];
        }

        // Copy the data from the 'other' object to the current object
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this; // Return a reference to the current object
}

// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}


// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;  // Return the resulting matrix
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

int ImageMatrix::get_height() const{
    return height;
}
int ImageMatrix::get_width() const {
    return width;
}

// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;
}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    return data[i][j];
}
void ImageMatrix::WriteToText(std::string Header)
{
    std::ofstream File(Header);
    File << "\t";
    for (int w = 0; w < width; w++)
    {
        File << w << "\t";
    }
    File << std::endl;
    for (int h = 0; h < height; h++)
    {
        File << h << "\t";
        for (int w = 0; w < width; w++)
        {
            File << data[h][w] << "\t";
        }
        File << std::endl;
    }
    File << std::endl;
    File.close();
}