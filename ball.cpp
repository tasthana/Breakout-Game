
#include "ball.h"

// constructor
Ball::Ball(Shader& shader, glm::vec2 pos, float radius, struct color)
        : Shape(shader, pos, glm::vec2(radius * 2, radius * 2), color), radius(radius) {
    // Initialize
    initVAO();
    initVBO();
    initEBO();
}

    // update function
    void Ball::update(float deltaTime) {
        // Move the ball based on its velocity
        pos += velocity * deltaTime;

        // TODO: Handle collisions with the window boundaries

    };
