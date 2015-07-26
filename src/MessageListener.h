//
// Created by TriD on 26.07.2015.
//

#ifndef FAMILY_BUSINESS_MESSAGELISTENER_H
#define FAMILY_BUSINESS_MESSAGELISTENER_H


#include <memory>
#include "MessageParameters.h"

class MessageListener {
public:
    virtual void onMessage(MessageParameters& messageParameters) = 0;
};

using MessageListenerPtr = std::shared_ptr<MessageListener>;

#endif //FAMILY_BUSINESS_MESSAGELISTENER_H
