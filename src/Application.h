//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_APPLICATION_H
#define FAMILY_BUSINESS_APPLICATION_H


#include "State.h"

#include <vector>

namespace MEng {
    using States = std::vector<StatePtr>;

    class Application {
    private:
        Application() { };
        bool running = true;
        States states;
    public:
        static Application &getInstance() {
            static Application instance;
            return instance;
        }

        void run();

        void finish() { running = false; }

        void pushState(StatePtr state);

        void popState();

        State &getCurrentState() { return *states.back(); }

        bool hasState() { return !states.empty(); }
    };
}
#endif //FAMILY_BUSINESS_APPLICATION_H
