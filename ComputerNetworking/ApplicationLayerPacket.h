//
// Created by Zeynep Nisa on 4.12.2023.
//

#ifndef ASSIGNMENT3_APPLICATIONLAYERPACKET_H
#define ASSIGNMENT3_APPLICATIONLAYERPACKET_H

#include "Packet.h"

// Extends Packet class. Have additional layer-specific member variables and overrides the virtual print function.
class ApplicationLayerPacket : public Packet {
public:
    ApplicationLayerPacket(int _layer_ID, const string& _sender_ID, const string& _receiver_ID, const string& _message_data);
    ~ApplicationLayerPacket() override;

    string sender_ID;
    string receiver_ID;
    string message_data;

    void print() override;
};




#endif //ASSIGNMENT3_APPLICATIONLAYERPACKET_H
