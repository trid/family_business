//
// Created by TriD on 04.09.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTERAI_H
#define FAMILY_BUSINESS_CHARACTERAI_H


#include "AbstractAI.h"

namespace Main {

    class CharacterAI : public Main::AbstractAI {
    private:
        int characterId;
    public:
        CharacterAI(int characterId) : characterId(characterId) { }

        virtual void update(int delta) override;
    };

}

#endif //FAMILY_BUSINESS_CHARACTERAI_H
