//
// Created by Zeynep Nisa on 4.12.2023.
//

#ifndef ASSIGNMENT3_NETWORK_H
#define ASSIGNMENT3_NETWORK_H
#include <vector>
#include <iostream>
#include "Packet.h"
#include "Client.h"

using namespace std;

class Network {
public:
    Network();
    ~Network();

    // Executes commands given as a vector of strings while utilizing the remaining arguments.
    void process_commands(vector<Client> &clients, vector<string> &commands, int message_limit, const string &sender_port,
                          const string &receiver_port);

    // Initialize the network from the input files.
    vector<Client> read_clients(string const &filename);
    void read_routing_tables(vector<Client> & clients, string const &filename);
    vector<string> read_commands(const string &filename);
    int find_client(const vector<Client> &clients, const string &client_id);
    };

#endif //ASSIGNMENT3_NETWORK_H
