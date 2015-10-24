//
// Created by TriD on 23.09.2015.
//

#ifndef FAMILY_BUSINESS_RESOURCEMININGPROCESS_H
#define FAMILY_BUSINESS_RESOURCEMININGPROCESS_H

#include "../Process.h"

namespace Main {

    class ResourceMiningProcess: public MEng::Process {
    private:
        int time{0};
        int characterId;
        int partyId;
        bool stopped{false};
    public:
        ResourceMiningProcess(int characterId, int partyId) : characterId(characterId), partyId(partyId) { }

        virtual void update(int delta);

        virtual bool isFinished();

        virtual void stop();

        virtual void save(std::ofstream &out);

        virtual void load(std::ifstream &in);
    };

}

#endif //FAMILY_BUSINESS_RESOURCEMININGPROCESS_H
