//
// Created by Zeynep Nisa on 4.12.2023.
//
#include "Network.h"

Network::Network() {

}
int Network::find_client(const vector<Client> &clients, const string &clientid) {
    for (int i = 0; i < clients.size(); ++i) {
        if (clients[i].client_id == clientid) {
            return i;
        }
    }
    return -1;
}


void Network::process_commands(vector<Client> &clients, vector<string> &commands, int message_limit,
                               const string &sender_port, const string &receiver_port) {
    // TODO: Execute the commands given as a vector of strings while utilizing the remaining arguments.
    /* Don't use any static variables, assume this method will be called over and over during testing.
     Don't forget to update the necessary member variables after processing each command. For example,
     after the MESSAGE command, the outgoing queue of the sender must have the expected frames ready to send. */

    for (const auto &command : commands) {
        istringstream iss(command);
        string command_type;
        iss >> command_type;
        string dashes(command.length()+9, '-');
        cout<<dashes<<"\nCommand: "<<command<<"\n"<<dashes<<endl;
        if (command_type == "MESSAGE") {
            int frame = 1;
            string sender_id, receiver_id, message_content;
            iss >> sender_id >> receiver_id;
            getline(iss, message_content);
            cout<<"Message to be sent: "<<'"'<<message_content.substr(2,message_content.length()-3)<<'"'<<"\n\n";
            for (size_t i = 2; i < message_content.length()-1; i += message_limit) {
                string eachmessage = message_content.substr(i, message_limit);
                char lastChar = eachmessage[eachmessage.length() - 2];
                if (lastChar== '.' || lastChar == '!'||lastChar== '?'){
                    eachmessage =eachmessage.substr(0, eachmessage.length()-1);
                }
                cout<<eachmessage<<endl;
                string sender_ip = clients[find_client(clients,sender_id)].client_ip;
                string receiver_ip = clients[find_client(clients,receiver_id)].client_ip;
                string sender_mac = clients[find_client(clients,sender_id)].client_mac;
                string tempReceive = clients[find_client(clients,sender_id)].routing_table[receiver_id];
                string tempReceiveMac =clients[find_client(clients,tempReceive)].client_mac;
                stack<Packet*> smallStack ;
                Packet* appLayer = new ApplicationLayerPacket(0,sender_id,receiver_id,eachmessage);
                Packet* transportLayer = new TransportLayerPacket(1,sender_port,receiver_port);
                Packet* networkLayer = new NetworkLayerPacket(2,sender_ip,receiver_ip);
                Packet* physicalLayer = new PhysicalLayerPacket(3,sender_mac,tempReceiveMac);
                smallStack.push(appLayer);
                smallStack.push(transportLayer);
                smallStack.push(networkLayer);
                smallStack.push(physicalLayer);
                clients[find_client(clients,sender_id)].outgoing_queue.push(smallStack);
                cout<<"Frame #"<<frame<<endl;
                cout<<"Sender MAC address: "<<sender_mac<<", Receiver MAC address: "<<tempReceiveMac<<endl;
                cout<<"Sender IP address: "<<sender_ip<<", Receiver IP address: "<<receiver_ip<<endl;
                cout<<"Sender port number: "<<sender_port<<", Receiver port number: "<<receiver_port<<endl;
                cout<<"Sender ID: "<<sender_id<<", Receiver ID: "<<receiver_id<<endl;
                clients[find_client(clients,sender_id)].client_hop = 0;
                cout<<"Message chunk carried: "<<'"'<<eachmessage<<'"'<<"\nNumber of hops so far: "<<
                clients[find_client(clients,sender_id)].client_hop<<"\n--------"<<endl;
                frame++;
            }
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm tm_now = *std::localtime(&now_c);
            std::stringstream ss;
            ss << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S");
            std::string str_time = ss.str();
            ActivityType activityType = ActivityType::MESSAGE_SENT;
            Log log(str_time,message_content.substr(2,message_content.length()-3),
                    frame,clients[find_client(clients,sender_id)].client_hop,sender_id,receiver_id,false,activityType);
            clients[find_client(clients,sender_id)].log_entries.push_back(log);

        }else if (command_type== "SHOW_FRAME_INFO"){
            string client_id, inOrOut;
            int frames;
            iss >> client_id >> inOrOut>>frames;
            queue<stack<Packet*>> temp_queue;
            int currentIndex = 1;
            if (inOrOut == "out" && clients[find_client(clients,client_id)].outgoing_queue.size() >= frames ){
                temp_queue = clients[find_client(clients,client_id)].outgoing_queue ;
                cout<<"Current Frame #"<<frames<<" on the outgoing queue of client "<<client_id<<endl;
            }else if(inOrOut == "in" && clients[find_client(clients,client_id)].incoming_queue.size()>= frames){
                temp_queue = clients[find_client(clients, client_id)].incoming_queue;
                cout << "Current Frame #" << frames << " on the incoming queue of client " << client_id << endl;
            }else{
                cout<<"No such frame."<<endl;
            }
            while (!temp_queue.empty()) {
                if (currentIndex == frames) {
                    stack<Packet*> target = temp_queue.front();
                    stack<Packet*> targetNew;
                    while(!target.empty()){
                        targetNew.push(target.top());
                        target.pop();
                    }
                    if (targetNew.top()->layer_ID == 0){
                        cout<<"Carried Message: "<<'"'<<
                        dynamic_cast<ApplicationLayerPacket*>(targetNew.top())->message_data<<'"'<<endl;
                    }
                    cout<<"Layer 0 info: ";
                    targetNew.top()->print();
                    targetNew.pop();
                    cout<<"Layer 1 info: ";
                    targetNew.top()->print();
                    targetNew.pop();
                    cout<<"Layer 2 info: ";
                    targetNew.top()->print();
                    targetNew.pop();
                    cout<<"Layer 3 info: ";
                    targetNew.top()->print();
                    cout<<"Number of hops so far: "<<clients[find_client(clients,client_id)].client_hop<<endl;
                    break;
                }
                temp_queue.pop();
                currentIndex++;
            }
        }else if (command_type== "SHOW_Q_INFO"){
            string idInfo, inOrOut;
            iss >> idInfo >> inOrOut;
            if(inOrOut == "out"){
                size_t frameNumber = clients[find_client(clients,idInfo)].outgoing_queue.size();
                cout<<"Client "<<idInfo<<" Outgoing Queue Status\nCurrent total number of frames: "<<frameNumber<<endl;
            }else{
                size_t frameNumber = clients[find_client(clients,idInfo)].incoming_queue.size();
                cout<<"Client "<<idInfo<<" Incoming Queue Status\nCurrent total number of frames: "<<frameNumber<<endl;
            }
        }else if (command_type== "SEND"){
            cout<<"SEND"<<endl;
        }else if (command_type== "RECEIVE"){
            cout<<"RECEIVE"<<endl;
        }else if (command_type== "PRINT_LOG"){
            string client_id;
            iss >> client_id ;
            if(!clients[find_client(clients,client_id)].log_entries.empty()){
                cout<<"Client "<<client_id<<"Logs"<<endl;
            }
            for (int i = 0; i <clients[find_client(clients,client_id)].log_entries.size() ; ++i) {
                string activity ;
                Log entries = clients[find_client(clients,client_id)].log_entries[i];
                if(entries.activity_type == ActivityType::MESSAGE_SENT){
                    activity = "Message Sent";
                }else if(entries.activity_type == ActivityType::MESSAGE_DROPPED){
                    activity = "Message Dropped";
                }else if(entries.activity_type == ActivityType::MESSAGE_FORWARDED){
                    activity = "Message Forwarded";
                }else if(entries.activity_type == ActivityType::MESSAGE_RECEIVED){
                    activity = "Message Received";
                }
                cout<<"--------------\nLog Entry #"<<i+1<<":\nActivity: "<<activity<<"\nTimestamp: "<<entries.timestamp<<endl;
                cout<<"Number of frames: "<<entries.number_of_frames<<"\nNumber of hops: "<<entries.number_of_hops<<endl;
                cout<<"Sender ID: "<<entries.sender_id<<"\nReceiver ID: "<<entries.receiver_id<<endl;
                cout<<"Success: "<<entries.success_status<<"\nMessage: "<<'"'<<entries.message_content<<'"'<<endl;
            }


        }else{
            cout<<"Invalid command."<<endl;
        }
    }
}

vector<Client> Network::read_clients(const string &filename) {
    vector<Client> clients;
    ifstream file(filename);
    if (!file.is_open()) {
        return clients;
    }
    string line;
    getline(file,line);
    while (getline(file, line)) {
        istringstream iss(line);
        string client_id, client_ip, client_mac; // Add more fields as needed
        iss >> client_id >> client_ip >> client_mac; // Add more fields as needed
        clients.emplace_back(client_id, client_ip, client_mac); // Use appropriate constructor
    }
    file.close();
    // TODO: Read clients from the given input file and return a vector of Client instances.
    return clients;
}

void Network::read_routing_tables(vector<Client> &clients, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"File is not open";
    }
    string line;
    string sender_id, receiver_id;
    int index= 0;
    while (getline(file, line)) {
        if (line == "-") {
            index++;
            continue;
        }
        istringstream iss(line);
        iss >> sender_id >> receiver_id;
        clients[index].routing_table[sender_id] = receiver_id;
    }
    file.close();
    // TODO: Read the routing tables from the given input file and populate the clients' routing_table member variable.
}

vector<string> Network::read_commands(const string &filename) {
    vector<string> commands;
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"File is not open";
    }
    string line;
    getline(file,line);
    while(getline(file,line)){
        commands.push_back(line);
    }
    // TODO: Read commands from the given input file and return them as a vector of strings.
    return commands;
}

Network::~Network() {
    // TODO: Free any dynamically allocated memory if necessary.
}

