//
// Created by TriD on 01.09.2015.
//

#ifndef FAMILY_BUSINESS_ABSTRACTAI_H
#define FAMILY_BUSINESS_ABSTRACTAI_H

#include <memory>

namespace Main {

    class AbstractAI {
    public:
        virtual void update(int delta) = 0;
    };

    using AbstractAIPtr = std::shared_ptr<AbstractAI>;

}

#endif //FAMILY_BUSINESS_ABSTRACTAI_H
