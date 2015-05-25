#include <iostream>
#include "Application.h"
#include "game/MainState.h"

using namespace std;

int main() {
    StatePtr statePtr(new MainState);
    Application& application = Application::getInstance();

    application.pushState(statePtr);
    application.run();
    return 0;
}