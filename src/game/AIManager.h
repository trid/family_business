//
// Created by TriD on 01.09.2015.
//

#ifndef FAMILY_BUSINESS_AIMANAGER_H
#define FAMILY_BUSINESS_AIMANAGER_H

#include <vector>
#include "AbstractAI.h"

namespace Main {

    using AIItems = std::vector<AbstractAIPtr>;

    class AIManager {
        AIItems aiItems;
    public:
        static AIManager &getInstance() {
            static AIManager instance;
            return instance;
        }

        void update(int delta);

        void addAi(AbstractAIPtr ai);

        void removeAi(AbstractAIPtr ai);

        void clear() { aiItems.clear(); }
    };

}

#endif //FAMILY_BUSINESS_AIMANAGER_H
