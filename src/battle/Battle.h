//
// Created by TriD on 22.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLE_H
#define FAMILY_BUSINESS_BATTLE_H

#include "BattleCreature.h"
#include "BattleMap.h"
#include "../game/Party.h"

namespace BattleState {

    class Battle {
    private:
        BattleMap battleMap;
        std::vector<BattleCreaturePtr> turns;
        std::vector<BattleCreaturePtr>::iterator current;

        std::vector<BattleCreaturePtr> left;
        std::vector<BattleCreaturePtr> right;

        void updateTurns();

        void nextCreature();

        bool isFinished();

        bool blockInput;
    public:
        Battle(Main::Party &first, Main::Party &second);

        BattleMap &getBattleMap() { return battleMap; }

        void makeTurn();

        std::vector<BattleCreaturePtr>::iterator &getCurrent() { return current; }

        void makeAttack(Point targetPosition);

        std::vector<BattleCreaturePtr> &getLeft() { return left; }

        std::vector<BattleCreaturePtr> &getRight() { return right; }

        bool isBlockInput() const { return blockInput; }

        void setBlockInput(bool blockInput) { Battle::blockInput = blockInput; }
    };

}

#endif //FAMILY_BUSINESS_BATTLE_H
