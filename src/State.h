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
#include "Process.h"

namespace MEng {

    class State {
    private:
        std::vector<Process::ProcessPtr> processes;

        View::ViewPtr view;
        std::vector<MEng::MouseEventListenerPtr> mouseEventListeners;
        std::vector<MEng::KeyboardEventListenerPtr> keyboardEventListeners;

        int prevTime{SDL_GetTicks()};
    protected:
        void setView(View::ViewPtr viewPtr) { view = viewPtr; }

    public:
        View::ViewPtr getView() { return view; }

        virtual void onPush() { };

        virtual void onPop() { };

        virtual void onActivate() { };

        virtual void onDeactivate() { };

        // System messages
        virtual void onClick(const MEng::Point &point, int button) { view->onClick(point, button); }

        virtual void onKeyDown(int keyCode) { view->onKeyDown(keyCode); }

        virtual void onKeyUp(int keyCode) { view->onKeyUp(keyCode); }

        virtual void run();

        void addMouseEventListener(MEng::MouseEventListenerPtr mouseEventListener);

        void addKeyboardEventListener(MEng::KeyboardEventListenerPtr keyboardEventListener);

        void addProcess(Process::ProcessPtr processPtr) { processes.push_back(processPtr); }

        void removeMouseEventListener(MEng::MouseEventListenerPtr mouseEventListener);

        void removeKeyboardEventListener(MEng::KeyboardEventListenerPtr keyboardEventListener);

        void clearListeners();

        virtual void save(std::ofstream& out);

        virtual void load(std::ifstream& in);

        virtual ~State() { };
    };

    using StatePtr = std::shared_ptr<State>;

}
#endif //FAMILY_BUSINESS_STATE_H
