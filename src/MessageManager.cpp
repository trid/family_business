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

void MessageManager::save(std::ofstream &out) {
    int count = messageQueue.size();
    out.write((char*)&count, sizeof(count));

    for (auto& item: messageQueue) {
        int size = item.first.size();
        out.write((char*)&size, sizeof(size));
        out.write(item.first.c_str(), size);
        item.second.save(out);
    }
}

void MessageManager::load(std::ifstream &in) {
    int count{0};
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        int size{0};
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        char* buff = new char[size + 1];
        buff[size] = '\0';
        in.read(buff, size);
        std::string key{buff};
        delete[] buff;
        MessageParameters messageParameters{in};
        enqueuMessage(key, messageParameters);
    }
}
