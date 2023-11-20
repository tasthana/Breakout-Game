#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../shapes/shape.h"

class Paddle {
public:
    Paddle(float startX, float startY, float paddleWidth, float paddleHeight);
    ~Paddle();

    // Methods to move the paddle
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    // Render the paddle
    void render();

    // Getters for paddle position and size
    glm::vec2 getPosition() const;
    glm::vec2 getSize() const;

private:
    glm::vec2 position;
    glm::vec2 size;
    float speed;  // this value is to control the paddle's movement speed
};















#endif //INC_4OEP_TASTHANA_PADDLE_H
