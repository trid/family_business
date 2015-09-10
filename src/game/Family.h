//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_FAMILY_H
#define FAMILY_BUSINESS_FAMILY_H

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "Character.h"
#include "CreatureManager.h"

namespace Main {

    using Children = std::vector<int>;

    class Family {
        int id;

        int father;
        int mother;
        Children children;

        int home;

        std::string lastName;

        Main::Generator generator;
        Main::Distributor distributor{0, 100};
    public:
        Family(int id, int father, int &mother, Children &children) : id(id), father(father),
                                                                      mother(mother),
                                                                      children(std::move(children)) { }

        Family(int id) : id(id) { }

        Family(std::ifstream &in) { load(in); }

        const std::string &getLastName() {
            return static_cast<Main::Character &>(Main::getCreatureById(father)).getLastName();
        }

        Main::Character &getFather() { return static_cast<Main::Character &>(Main::getCreatureById(father)); }

        int getFatherId() { return father; }

        Main::Character &getMother() { return static_cast<Main::Character &>(Main::getCreatureById(mother)); }

        int getMotherId() { return mother; }

        Children &getChildren() { return children; }

        void addChild(int childId) { children.push_back(childId); }

        int getHome() const { return home; }

        void setHome(int home) { Family::home = home; }

        int getId() const { return id; }

        void updateDaily();

        void save(std::ofstream &out);

        void load(std::ifstream &in);
    };

}

#endif //FAMILY_BUSINESS_FAMILY_H
