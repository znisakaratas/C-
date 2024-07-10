//
// Created by Zeynep Nisa on 4.12.2023.
//

#ifndef ASSIGNMENT3_PACKET_H
#define ASSIGNMENT3_PACKET_H
#include <string>
#include <iostream>

using namespace std;

class Packet {
public:
    Packet(int layerID);
    virtual ~Packet();

    int layer_ID;

    friend ostream &operator<<(ostream &os, const Packet &packet);
    virtual void print() {};
};

#endif //ASSIGNMENT3_PACKET_H
