//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_STATE_H
#define FAMILY_BUSINESS_STATE_H


#include  <memory>


class State {
public:
    virtual void onPush(){};
    virtual void onPop(){};
    virtual void onActivate(){};
    virtual void onDeactivate(){};

    virtual void run(){};

    virtual ~State() {};
};

using StatePtr = std::shared_ptr<State>;

#endif //FAMILY_BUSINESS_STATE_H
