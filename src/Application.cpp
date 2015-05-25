//
// Created by TriD on 24.05.2015.
//

#include "Application.h"
#include "view/Screen.h"

void Application::run() {
    while (running) {
        Screen::getInstance().draw();
    }
}
