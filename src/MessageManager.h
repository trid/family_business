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
    static MessageManager& getInstance() {
        static MessageManager messageManager;
        return messageManager;
    }

    void addListener(const std::string &type, MessageListenerPtr listener);
    void removeListener(const std::string &type, MessageListenerPtr listener);
    void sendMessage(const std::string &type, MessageParameters &parameters);
};


#endif //FAMILY_BUSINESS_MESSAGEMANAGER_H
