//
// Created by Zeynep Nisa on 4.12.2023.
//

#ifndef ASSIGNMENT3_TRANSPORTLAYERPACKET_H
#define ASSIGNMENT3_TRANSPORTLAYERPACKET_H


#include "Packet.h"

// Extends Packet class. Have additional layer-specific member variables and overrides the virtual print function.
class TransportLayerPacket : public Packet {

public:
    TransportLayerPacket(int _layer_ID, string _sender_port, string _receiver_port);
    ~TransportLayerPacket() override;

    string sender_port_number;
    string receiver_port_number;

    void print() override;
};

#endif //ASSIGNMENT3_TRANSPORTLAYERPACKET_H
