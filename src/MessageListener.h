//
// Created by TriD on 26.07.2015.
//

#ifndef FAMILY_BUSINESS_MESSAGELISTENER_H
#define FAMILY_BUSINESS_MESSAGELISTENER_H


#include <memory>
#include "MessageParameters.h"

namespace MEng {

    class MessageListener {
    public:
        virtual void onMessage(const MessageParameters &messageParameters) = 0;
    };

    using MessageListenerPtr = std::shared_ptr<MessageListener>;
}

#endif //FAMILY_BUSINESS_MESSAGELISTENER_H
