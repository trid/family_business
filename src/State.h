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
    std::vector<MouseEventListenerPtr> mouseEventListeners;
    std::vector<KeyboardEventListenerPtr> keyboardEventListeners;
protected:
    void setView(ViewPtr viewPtr) { view = viewPtr; }

public:
    ViewPtr getView() { return view; }

    virtual void onPush(){};
    virtual void onPop(){};
    virtual void onActivate(){};
    virtual void onDeactivate(){};

    // System messages
    virtual void onClick(const Point &point, int button){ view->onClick(point, button); }
    virtual void onKeyDown(int keyCode) { view->onKeyDown(keyCode); }
    virtual void onKeyUp(int keyCode) { view->onKeyUp(keyCode); }

    virtual void run(){};

    void addMouseEventListener(MouseEventListenerPtr mouseEventListener);
    void addKeyboardEventListener(KeyboardEventListenerPtr keyboardEventListener);

    void removeMouseEventListener(MouseEventListenerPtr mouseEventListener);
    void removeKeyboardEventListener(KeyboardEventListenerPtr keyboardEventListener);

    void clearListeners();

    virtual ~State() {};
};

using StatePtr = std::shared_ptr<State>;

#endif //FAMILY_BUSINESS_STATE_H
