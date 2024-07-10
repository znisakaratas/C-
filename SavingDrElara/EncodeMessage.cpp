//
// Created by Zeynep Nisa on 29.10.2023.
//

#include "EncodeMessage.h"
#include <cmath>
#include <bitset>

bool EncodeMessage::isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {

}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix& img, const std::string& message, const std::vector<std::pair<int, int>>& positions) {
    std::string transformedMessage = message;
    for (int i = 2; i < transformedMessage.length(); ++i) {
        int a = 0, fibNum = 1, c;
        if (isPrime(i)) {
            for (int k = 2; k <= i; ++k) {
                c = a + fibNum;
                a = fibNum;
                fibNum = c;
            }
            int asciiVal = static_cast<int>(transformedMessage[i]);
            int newAscii = asciiVal + fibNum;
            if (newAscii >= 33 && newAscii <= 126) {
                transformedMessage[i] = static_cast<char>(asciiVal+fibNum);
            }else if(newAscii <33){
                transformedMessage[i] = static_cast<char>(asciiVal+fibNum+33);
            }else{
                transformedMessage[i] = static_cast<char>(126);
            }
        }
    }
    int shiftBy = transformedMessage.length()/2;
    int len = transformedMessage.length();
    std::string shiftedMessage ;
    shiftedMessage = transformedMessage.substr(len - shiftBy) + transformedMessage.substr(0, len - shiftBy);
    ImageMatrix encodedImage(img);
    std::string boolText ;
    for (char eachChar: shiftedMessage) {
        int asciiValue = static_cast<int>(eachChar);
        std::bitset<7> bitset(asciiValue);
        std::string boolString = bitset.to_string();
        boolText += boolString;
    }
    if(positions.size() < boolText.length()){
        for (int i = 0; i < positions.size(); ++i) {
            int scaledValue = static_cast<int>(img.get_data(positions[i].first,positions[i].second));
            std::bitset<8> bits(scaledValue);
            std::string imgBool = bits.to_string();
            imgBool[imgBool.length()-1] = boolText[i];
            std::bitset<8> finalImg(imgBool);
            unsigned long long bitValue = finalImg.to_ullong();
            double imgResult;
            imgResult = static_cast<double>(bitValue);
            encodedImage.set_data(positions[i].first,positions[i].second,imgResult);
        }
    } else{
        for (int i = 0; i < boolText.length(); ++i) {
            int scaledValue = static_cast<int>(img.get_data(positions[i].first,positions[i].second));
            std::bitset<8> bits(scaledValue);
            std::string imgBool = bits.to_string();
            imgBool[imgBool.length()-1] = boolText[i];
            std::bitset<8> finalImg(imgBool);
            unsigned long long bitValue = finalImg.to_ullong();
            double imgResult;
            imgResult = static_cast<double>(bitValue);
            encodedImage.set_data(positions[i].first,positions[i].second,imgResult);
        }
    }
    return encodedImage; // Return the modified image
}