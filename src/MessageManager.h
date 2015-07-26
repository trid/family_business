//
// Created by TriD on 26.07.2015.
//

#ifndef FAMILY_BUSINESS_MESSAGEMANAGER_H
#define FAMILY_BUSINESS_MESSAGEMANAGER_H

#include <list>
#include <string>
#include <unordered_map>
#include "MessageListener.h"

using Listeners = std::list<MessageListenerPtr>;
using Mapping = std::unordered_map<std::string, Listeners>;

class MessageManager {
private:
    Mapping mapping;
public:
    void addListener(std::string &type, MessageListenerPtr listener);
    void removeListener(std::string &type, MessageListenerPtr listener);
    void sendMessage(std::string& type, MessageParameters& parameters);
};


#endif //FAMILY_BUSINESS_MESSAGEMANAGER_H
