//
// Created by TriD on 26.07.2015.
//

#include <algorithm>

#include "MessageManager.h"

void MessageManager::addListener(const std::string &type, MessageListenerPtr listener) {
    mapping[type].push_back(listener);
}

void MessageManager::removeListener(const std::string &type, MessageListenerPtr listener) {
    auto iter = std::remove(mapping[type].begin(), mapping[type].end(), listener);
    mapping[type].erase(iter, mapping[type].end());
}

void MessageManager::sendMessage(const std::string &type, const MessageParameters &parameters) {
    if (mapping.find(type) != mapping.end()) {
        for (auto listener: mapping[type]) {
            listener->onMessage(parameters);
        }
    }
}

void MessageManager::enqueuMessage(const std::string &type, MessageParameters &parameters) {
    auto pair = std::make_pair(type, parameters);
    messageQueue.push_back(pair);
}

void MessageManager::update() {
    for (auto& pair: messageQueue) {
        sendMessage(pair.first, pair.second);
    }
    messageQueue.clear();
}
