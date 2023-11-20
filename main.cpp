#include "framework/breakout.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Breakout breakout;

    while (!glfwWindowShouldClose(breakout.getWindow())) {
        breakout.processInput();
        breakout.handlePlayInput();
        breakout.update();
        breakout.render();
    }

    glfwTerminate();
    return 0;
}