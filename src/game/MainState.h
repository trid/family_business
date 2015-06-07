//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_MAPSTATE_H
#define FAMILY_BUSINESS_MAPSTATE_H


#include <memory>
#include <vector>

#include "../State.h"
#include "Family.h"
#include "../view/MainView.h"


using Families = std::vector<FamilyPtr>;


class MainState : public State {
    Families families;
    ViewPtr view;
public:
    MainState();

    virtual void onClick(const Point &point, int button) override;

    virtual void onActivate() override;
};


#endif //FAMILY_BUSINESS_MAPSTATE_H
