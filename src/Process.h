//
// Created by TriD on 22.09.2015.
//

#ifndef FAMILY_BUSINESS_PROCESS_H
#define FAMILY_BUSINESS_PROCESS_H

#include <fstream>
#include <memory>

namespace MEng {

    class Process {
    public:
        virtual void update(int delta) = 0;
        virtual bool isFinished() = 0;
        virtual void stop() = 0;

        virtual void save(std::ofstream& out) = 0;
        virtual void load(std::ifstream& in) = 0;

        using ProcessPtr = std::shared_ptr<Process>;
    };

}

#endif //FAMILY_BUSINESS_PROCESS_H
