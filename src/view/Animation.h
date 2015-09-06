//
// Created by TriD on 04.08.2015.
//

#ifndef FAMILY_BUSINESS_ANIMATION_H
#define FAMILY_BUSINESS_ANIMATION_H

#include <memory>

namespace MEng {
    namespace View {

        class Animation {
        public:
            virtual ~Animation() { }

            virtual void update(int delta) = 0;

            virtual bool isFinished() = 0;

            virtual void finalize() = 0;
        };

        using AnimationPtr = std::shared_ptr<Animation>;
    }
}


#endif //FAMILY_BUSINESS_ANIMATION_H
