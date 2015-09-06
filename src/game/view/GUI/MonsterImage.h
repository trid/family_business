//
// Created by TriD on 29.08.2015.
//

#ifndef FAMILY_BUSINESS_MONSTERIMAGE_H
#define FAMILY_BUSINESS_MONSTERIMAGE_H


#include "../../../view/Image.h"

class MonsterImage: public MEng::View::Image {
private:
    int partyId;
public:
    MonsterImage(SDL_Texture *texture, int monsterId) : Image(texture, {-32, -32}), partyId(monsterId) { }
    int getPartyId() const { return partyId; }
};

using MonsterImagePtr = std::shared_ptr<MonsterImage>;

#endif //FAMILY_BUSINESS_MONSTERIMAGE_H
