//
// Created by TriD on 25.05.2015.
//

#ifndef FAMILY_BUSINESS_EVENTMANAGER_H
#define FAMILY_BUSINESS_EVENTMANAGER_H

namespace MEng {

    class EventManager {
    private:
        EventManager() { }

    public:
        static EventManager &getInstance() {
            static EventManager instance;
            return instance;
        }

        void process();
    };

}

#endif //FAMILY_BUSINESS_EVENTMANAGER_H
