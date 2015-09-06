//
// Created by TriD on 26.07.2015.
//

#ifndef FAMILY_BUSINESS_MESSAGEMANAGER_H
#define FAMILY_BUSINESS_MESSAGEMANAGER_H

#include <fstream>
#include <list>
#include <string>
#include <unordered_map>
#include <bits/stl_bvector.h>
#include "MessageListener.h"

namespace MEng {

    using Listeners = std::vector<MessageListenerPtr>;
    using Mapping = std::unordered_map<std::string, Listeners>;
    using MessageQueue = std::vector<std::pair<std::string, MessageParameters>>;

    class MessageManager {
    private:
        Mapping mapping;
        MessageQueue messageQueue;
    public:
        static MessageManager &getInstance() {
            static MessageManager messageManager;
            return messageManager;
        }

        void addListener(const std::string &type, MessageListenerPtr listener);

        void removeListener(const std::string &type, MessageListenerPtr listener);

        void sendMessage(const std::string &type, const MessageParameters &parameters);

        void enqueuMessage(const std::string &type, MessageParameters &parameters);

        void update();

        void clear() { messageQueue.clear(); }

        //Drop message in queue into file
        void save(std::ofstream &out);

        void load(std::ifstream &in);
    };

}

#endif //FAMILY_BUSINESS_MESSAGEMANAGER_H
