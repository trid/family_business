//
// Created by TriD on 02.08.2015.
//

#ifndef FAMILY_BUSINESS_MOVEMENT_H
#define FAMILY_BUSINESS_MOVEMENT_H

#include <fstream>

#include "Party.h"
#include "../Point.h"

namespace Main {

    class Movement {
    private:
        int partyId;
        Point target;
        int time{0};
    public:
        Movement(Party &party, Point target) : partyId(party.getId()), target(target) { }

        Movement(std::ifstream &in) { load(in); }

        void update(int delta);

        bool isFinished() { return time >= 500; }

        void save(std::ofstream &out);

        void load(std::ifstream &in);
    };

    using MovementPtr = std::shared_ptr<Movement>;

}

#endif //FAMILY_BUSINESS_MOVEMENT_H
