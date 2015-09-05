//
// Created by TriD on 04.09.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTERAI_H
#define FAMILY_BUSINESS_CHARACTERAI_H


#include "AbstractAI.h"

class CharacterAI: public AbstractAI {
private:
    int characterId;
public:
    CharacterAI(int characterId) : characterId(characterId) { }
    virtual void update(int delta) override;
};


#endif //FAMILY_BUSINESS_CHARACTERAI_H
