//
// Created by Zeynep Nisa on 29.10.2023.
//

#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


#include <bitset>

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string decodedMessage;
    std::string binaryString;

    for (const auto& pixel : edgePixels) {
        // Get the pixel color (assuming a grayscale image)
        int pixelValue = image.get_data(pixel.first, pixel.second);

        // Extract the LSB
        int lsb = pixelValue & 1;

        // Append the LSB to the binary string
        binaryString += std::to_string(lsb);
    }

    // Pad binary string with leading zeros to ensure consistent 7-bit segments
    while (binaryString.length() % 7 != 0) {
        binaryString = "0" + binaryString;
    }

    // Convert 7-bit segments into ASCII characters
    for (size_t i = 0; i < binaryString.length(); i += 7) {
        std::string segment = binaryString.substr(i, 7);
        char asciiChar = static_cast<char>(std::bitset<7>(segment).to_ulong());

        // Adjust ASCII values for printing
        if (asciiChar <= 32) {
            asciiChar += 33;
        } else if (asciiChar == 127) {
            asciiChar = 126;
        }

        decodedMessage += asciiChar;
    }

    return decodedMessage;
}


