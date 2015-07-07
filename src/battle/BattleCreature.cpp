//
// Created by TriD on 27.06.2015.
//

#include "BattleCreature.h"

BattleCreature::BattleCreature(CreaturePtr creature): creaturePtr(creature), steps(creature->getSpeed()) {

}
