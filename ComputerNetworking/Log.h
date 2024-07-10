//
// Created by Zeynep Nisa on 4.12.2023.
//

#ifndef ASSIGNMENT3_LOG_H
#define ASSIGNMENT3_LOG_H
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

enum class ActivityType {
    MESSAGE_RECEIVED,
    MESSAGE_FORWARDED,
    MESSAGE_SENT,
    MESSAGE_DROPPED
};

class Log {
public:

    Log(const string &timestamp, const string &message, int number_of_frames, int number_of_hops, const string &client_id,
        const string &receiver_id, bool success, ActivityType type);
    ~Log();

    string timestamp;
    string message_content;
    int number_of_frames;
    int number_of_hops;
    string sender_id;
    string receiver_id;
    bool success_status;
    ActivityType activity_type;
};

#endif //ASSIGNMENT3_LOG_H
