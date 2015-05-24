//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_APPLICATION_H
#define FAMILY_BUSINESS_APPLICATION_H


class Application {
private:
    Application(){};
    bool running;
public:
    static Application getInstance() {
        static Application instance;
        return instance;
    }

    void run();
    void finish() { running = false; }
};


#endif //FAMILY_BUSINESS_APPLICATION_H
