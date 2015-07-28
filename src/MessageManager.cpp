//
// Created by TriD on 26.07.2015.
//

#include "MessageManager.h"

void MessageManager::addListener(const std::string &type, MessageListenerPtr listener) {
    mapping[type].push_back(listener);
}

void MessageManager::removeListener(const std::string &type, MessageListenerPtr listener) {
    mapping[type].remove(listener);
}

void MessageManager::sendMessage(const std::string &type, const MessageParameters &parameters) {
    if (mapping.find(type) != mapping.end()) {
        for (auto listener: mapping[type]) {
            listener->onMessage(parameters);
        }
    }
}
