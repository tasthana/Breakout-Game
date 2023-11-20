//
// Created by Tushar Asthana  on 11/15/23.
//
#include "paddle.h"
// constructor
Paddle::Paddle(float startX, float startY, float paddleWidth, float paddleHeight)
        : position(startX, startY), size(paddleWidth, paddleHeight), speed(200.0f) {
}

// destructor
Paddle::~Paddle() {
}

// I like to move it, move it (left)
void Paddle::moveLeft(float deltaTime) {
    // Move the paddle left based on the speed and deltaTime
    position.x -= speed * deltaTime;
}

// I like to move it, move it (right)
void Paddle::moveRight(float deltaTime) {
    // Move the paddle right based on the speed and deltaTime
    position.x += speed * deltaTime;
}

glm::vec2 Paddle::getPosition() const {
    return position;
}

glm::vec2 Paddle::getSize() const {
    return size;
}
