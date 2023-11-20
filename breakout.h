//
// Created by Tushar Asthana  on 11/14/23.
//

#ifndef INC_4OEP_TASTHANA_BREAKOUT_H
#define INC_4OEP_TASTHANA_BREAKOUT_H

#include "GLFW/glfw3.h"

#include <vector>
#include <memory>
#include <iostream>
#include <GLFW/glfw3.h>

#include "shaderManager.h"
#include "fontRenderer.h"
#include "../shapes/rect.h"
#include "../shapes/shape.h"
#include "debug.h"
#include "paddle.h"
#include "brick.h"

using std::vector, std::unique_ptr, std::make_unique, glm::ortho, glm::mat4, glm::vec3, glm::vec4;


class Breakout {

private:
    /// @brief The actual GLFW window.
    GLFWwindow* window{};

    /// @brief Keyboard state (True if pressed, false if not pressed).
    /// @details Index this array with GLFW_KEY_{key} to get the state of a key.
    bool keys[1024];

    // Add any other private member variables or functions as needed
    bool glfwInit() {
        return false;
    };

    /// @brief Responsible for loading and storing all the shaders used in the project.
    /// @details Initialized in initShaders()
    unique_ptr<ShaderManager> shaderManager;

    /// @brief Responsible for rendering text on the screen.
    /// @details Initialized in initShaders()
    unique_ptr<FontRenderer> fontRenderer;


    std::vector<Brick*> bricks;

    // Shaders
    Shader shapeShader;
    Shader textShader;

    double MouseX{}, MouseY{};

public:
    // constructor
    Breakout();

    //destructor
    ~Breakout();

    // window variables
    int width = 800;
    int height = 600;
    int windowWidth = 800;
    int windowHeight = 600;

    // paddle variables
    int paddleWidth = 100;
    int paddleHeight = 20;

    // brick variables
    float brickWidth;
    float brickHeight;
    glm::vec2 brickPosition;
    struct color brickColor;

    // ball variables
    float ballRadius;
    struct color ballColor;

    unsigned int initWindow(bool debug = false);

    GLFWwindow* getWindow() const;

    /// @brief Updates the game state.
    /// @details (e.g. collision detection, delta time, etc.)
    void update();

    /// @brief Processes input from the user.
    /// @details (e.g. keyboard input, mouse input, etc.)
    void processInput();

    /// @brief Renders the game state.
    /// @details Displays/renders objects on the screen.
    void render();

    /// @brief handles all inpyts for play state
    /// @details I am splitting all the states into their own functions for the sake of my sanity
    void handlePlayInput();

    /// @brief handles all inpyts for over state
    /// @details I am splitting all the states into their own functions for the sake of my sanity
    void handleOverState();

    /// @brief Loads shaders from files and stores them in the shaderManager.
    /// @details Renderers are initialized here.
    void initShaders();

    /// @brief Initializes the shapes to be rendered.
    Paddle * initShapes();

    /// @brief Returns true if the window should close.
    /// @details (Wrapper for glfwWindowShouldClose()).
    /// @return true if the window should close
    /// @return false if the window should not close
     bool shouldClose();

    /// @brief Projection matrix used for 2D rendering (orthographic projection).
    /// @details OpenGL uses the projection matrix to map the 3D scene to a 2D viewport.
    /// @details The projection matrix transforms coordinates in the camera space into
    /// normalized device coordinates. (view space to clip space).
    /// @note The projection matrix is used in the vertex shader.
    /// @note We don't have to change this matrix since the screen size never changes.
    mat4 PROJECTION = ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);

    /// @brief Checks for all arrow key inputs
    /// @note means to seperate and organize the code
    void handleArrowKeyInput();

    // time calculation
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // ball pointer
    void *ball;
};
#endif //INC_4OEP_TASTHANA_BREAKOUT_H

