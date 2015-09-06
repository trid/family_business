#include "Application.h"
#include "game/MenuState.h"

using namespace MEng;

int main(int argc, char* argv[]) {
    StatePtr statePtr(new MenuState);
    Application& application = Application::getInstance();

    application.pushState(statePtr);
    application.run();
    return 0;
}