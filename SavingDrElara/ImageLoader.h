//
// Created by Zeynep Nisa on 29.10.2023.
//

#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <string>


class ImageLoader {
public:
    ImageLoader(const std::string& filepath); // Constructor for loading image from file
    ImageLoader(const ImageLoader &other); // copy constructor
    ImageLoader& operator=(const ImageLoader &other); // copy assignment operator

    // Destructor
    ~ImageLoader();


    int getHeight() const;
    int getWidth() const;
    double** getImageData() const;

private:
    int height;
    int width;
    double** imageData;
};


#endif //IMAGELOADER_H
