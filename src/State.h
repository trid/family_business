//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_STATE_H
#define FAMILY_BUSINESS_STATE_H


#include <memory>
#include <vector>
#include "Point.h"
#include "view/View.h"
#include "MouseEventListener.h"
#include "KeyboardEventListener.h"


class State {
private:
    ViewPtr view;
    std::vector<MEng::MouseEventListenerPtr> mouseEventListeners;
    std::vector<MEng::KeyboardEventListenerPtr> keyboardEventListeners;
protected:
    void setView(ViewPtr viewPtr) { view = viewPtr; }

public:
    ViewPtr getView() { return view; }

    virtual void onPush(){};
    virtual void onPop(){};
    virtual void onActivate(){};
    virtual void onDeactivate(){};

    // System messages
    virtual void onClick(const MEng::Point &point, int button){ view->onClick(point, button); }
    virtual void onKeyDown(int keyCode) { view->onKeyDown(keyCode); }
    virtual void onKeyUp(int keyCode) { view->onKeyUp(keyCode); }

    virtual void run(){};

    void addMouseEventListener(MEng::MouseEventListenerPtr mouseEventListener);
    void addKeyboardEventListener(MEng::KeyboardEventListenerPtr keyboardEventListener);

    void removeMouseEventListener(MEng::MouseEventListenerPtr mouseEventListener);
    void removeKeyboardEventListener(MEng::KeyboardEventListenerPtr keyboardEventListener);

    void clearListeners();

    virtual ~State() {};
};

using StatePtr = std::shared_ptr<State>;

#endif //FAMILY_BUSINESS_STATE_H
