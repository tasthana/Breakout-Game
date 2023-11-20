// Include statements
#include <iostream>
#include "breakout.h"
#include "paddle.h"
#include "brick.h"
#include "ball.h"

// Enum definition for game states
enum State { START, PLAY, OVER };
State screen;

// paddle for the game, will need to move around
Paddle* paddle;

// Constructor + keys and pointers
Breakout::Breakout() : keys(), window(nullptr), ball(nullptr){
    this->initWindow();
    paddle = initShapes();

    //my vector for bricks
    bricks = vector<Brick*>();
    Ball* ball;
}

// Initialization function for the window
unsigned int Breakout::initWindow(bool debug) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    // Create the GLFW window
    window = glfwCreateWindow(width, height, "Breakout Game!", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set the OpenGL context to the window
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    };

    // OpenGL configuration
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);

    // Set values for brick parameters
    brickWidth = 60.0f;
    brickHeight = 20.0f;
    brickPosition = glm::vec2(2.0, 2.0 ); // filler numbers for now

    return 0;
}

Paddle* Breakout::initShapes() {
    // give me a paddle boi
    Paddle* paddle = new Paddle(windowWidth / 2 - paddleWidth / 2, windowHeight - paddleHeight - 10, paddleWidth, paddleHeight);

     // adding a brick to my vector
    bricks.push_back(new Brick(shapeShader, brickPosition, glm::vec2(brickWidth, brickHeight), brickColor, brickWidth, brickHeight));

    // Create the ball
    ball = new Ball(shapeShader, glm::vec2(width / 2, height / 2), ballRadius, ballColor);

    return paddle;
}

// function to handle arrow key input for any arrow key inputs
void Breakout::handleArrowKeyInput() {
    float deltaTime;

    if (keys[GLFW_KEY_LEFT] && spawnButton->getPosX() > spawnButton->getSize().x / 2)
        spawnButton->moveX(-5);  // Move left

    // Move paddle based on arrow key input
    if (keys[GLFW_KEY_LEFT]) {
        //  paddle is a pointer to a Paddle object
        paddle->moveLeft(deltaTime);
    }

    if (keys[GLFW_KEY_RIGHT]) {
        //  paddle is a pointer to a Paddle object
        paddle->moveRight(deltaTime);
    }
}


// Input processing function
void Breakout::processInput() {
    glfwPollEvents();

    // Set keys to true if pressed, false if released
    for (int key = 0; key < 1024; ++key) {
        if (glfwGetKey(window, key) == GLFW_PRESS)
            keys[key] = true;
        else if (glfwGetKey(window, key) == GLFW_RELEASE)
            keys[key] = false;
    }

    // Close window if escape key is pressed
    if (keys[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, true);

    // Mouse position saved to check for collisions
    glfwGetCursorPos(window, &MouseX, &MouseY);
}

// Function to handle input during the play screen
void Breakout::handlePlayInput() {
    handleArrowKeyInput();
}

void Breakout::handleOverState() {
    if (keys[GLFW_KEY_R]) {
        // Restart the game
        // TODO: finish implementing the over state functions, such as resetting the game to the start screen
        // also, if the escape button is pressed, close the screen.
//        resetGame();
    }
}

void Breakout::render() {
    // Set background color (black)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Set shader to use for all shapes
    shapeShader.use();

    switch (screen) {
        case START: {
            // instructions + rendering
            string message = "Welcome to the classic game Breakout!";
            string message2 = "Move the paddle to bounce the ball off of the bricks!";
            string message3 = "Press S to  start :)!";

            // (12 * message.length()) is the offset to center text.
            // 12 pixels is the width of each character scaled by 1.
            this->fontRenderer->renderText(message, width/2 - (12 * message.length()), height/1.5, 0.8, vec3{0.5, 1, 1});
            this->fontRenderer->renderText(message2, width/2 - (12 * message2.length()), height/2.0, 0.5, vec3{0.5, 1, 1});
            this->fontRenderer->renderText(message3, width/2 - (12 * message3.length()), height/2.1, 0.5, vec3{0.5, 1, 1});

            break;
        }
        case PLAY: {
            // render my paddle boi
            paddle->render();

            // draw my bricks
            for (const auto& brick : bricks) {
                brick->draw();
            }

        }
        case OVER: {
            // win message + rendering
            string message = "You win!";
            this->fontRenderer->renderText(message, width/2 - (12 * message.length()), height/1.5, 0.5, vec3{0.5, 1, 1});

            // play again message + rendering
            string message2 = "Would you like to play again? Press Y for yes and N for no.";
            this->fontRenderer->renderText(message2, width/2 - (12 * message2.length()), height/2.0, 0.5, vec3{0.5, 1, 1});

            // send it back to over state to reset game!
            if (keys[GLFW_KEY_Y]) {
            handleOverState();
            }
            // kill the game :/
            else{
                glfwSetWindowShouldClose(window, true);
            }

        }
    }
    glfwSwapBuffers(window);
}

void Breakout::update() {
    // Calculate delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Update the bricks
    for (auto& brick : bricks) {
        brick->update(deltaTime);
    }
}

