//
// Created by TriD on 01.09.2015.
//

#ifndef FAMILY_BUSINESS_MONSTERAI_H
#define FAMILY_BUSINESS_MONSTERAI_H

#include <random>
#include "AbstractAI.h"

namespace Main {

    using Generator = std::default_random_engine;
    using Distributor = std::uniform_int_distribution<int>;

    class MonsterAI : public Main::AbstractAI {
    private:
        int monsterPartyId;
        int time{0};

        Generator generator;
        Distributor distributor{0, 3};
    public:
        MonsterAI(int monsterId) : monsterPartyId(monsterId) { }

        virtual void update(int delta) override;
    };

    using MonsterAIPtr = std::shared_ptr<MonsterAI>;

}

#endif //FAMILY_BUSINESS_MONSTERAI_H
