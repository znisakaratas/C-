//
// Created by Zeynep Nisa on 4.12.2023.
//

#include "Client.h"

Client::Client(string const& _id, string const& _ip, string const& _mac) {
    client_id = _id;
    client_ip = _ip;
    client_mac = _mac;
}

ostream &operator<<(ostream &os, const Client &client) {
    os << "client_id: " << client.client_id << " client_ip: " << client.client_ip << " client_mac: "
       << client.client_mac << endl;
    return os;
}

Client::~Client() {
    while (!outgoing_queue.empty()) {
        stack<Packet*>& currentStack = outgoing_queue.front();
        while (!currentStack.empty()) {
            Packet* currentPacket = currentStack.top();
            delete currentPacket;
            currentStack.pop();
        }
        outgoing_queue.pop();
    }
    while (!incoming_queue.empty()) {
        stack<Packet*>& currentStack = incoming_queue.front();
        while (!currentStack.empty()) {
            Packet* currentPacket = currentStack.top();
            delete currentPacket;
            currentStack.pop();
        }
        incoming_queue.pop();
    }
    // TODO: Free any dynamically allocated memory if necessary.
}
