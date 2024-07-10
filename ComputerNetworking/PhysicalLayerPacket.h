//
// Created by Zeynep Nisa on 4.12.2023.
//

#ifndef ASSIGNMENT3_PHYSICALLAYERPACKET_H
#define ASSIGNMENT3_PHYSICALLAYERPACKET_H

#include "Packet.h"

using namespace std;

// Extends Packet class. Have additional layer-specific member variables and overrides the virtual print function.
class PhysicalLayerPacket : public Packet {
public:
    PhysicalLayerPacket(int layerID, const string& senderMAC, const string& receiverMAC);
    ~PhysicalLayerPacket() override;

    string sender_MAC_address;
    string receiver_MAC_address;

    void print() override;
};


#endif //ASSIGNMENT3_PHYSICALLAYERPACKET_H
