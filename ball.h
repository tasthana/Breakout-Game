#include "../shapes/shape.h"


class Ball : public Shape {
public:
    //constructor
    Ball(Shader& shader, glm::vec2 pos, float radius, struct color);

    //destructor
    ~Ball();

    // Update the ball's position and handle collisions
    void update(float deltaTime);

    // Render the ball
    void render() const override;

private:
    float radius;
    glm::vec2 velocity;
};
