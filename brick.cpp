#include "brick.h"

// constructor
Brick::Brick(Shader& shader, glm::vec2 pos, glm::vec2 size, struct color color, float width, float height)
        : Shape(shader, pos, size, color), brickWidth(width), brickHeight(height), brickColor(color)
    {
        // variables
        float halfWidth = width / 2.0f;
        float halfHeight = height / 2.0f;

        // vertices to draw the bricks
        vertices = {
                -halfWidth, -halfHeight,
                halfWidth, -halfHeight,
                halfWidth,  halfHeight,
                -halfWidth,  halfHeight
        };

        // indices to draw the bricks
        indices = {
                0, 1, 2,
                2, 3, 0
        };

        // Initialize VAO, VBO, and EBO
        initVAO();
        initVBO();
        initEBO();
    }


void Brick::update(float deltaTime) {
    // TODO :Update logic
}

void Brick::draw() const {
    // TODO: Drawing logic for the brick
}