#include <iostream>
#include "Application.h"
#include "game/MainState.h"

using namespace std;

int main(int argc, char* argv[]) {
    StatePtr statePtr(new MainState);
    Application& application = Application::getInstance();

    application.pushState(statePtr);
    application.run();
    return 0;
}