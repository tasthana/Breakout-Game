#ifndef GRAPHICS_BRICK_H
#define GRAPHICS_BRICK_H
#include "../shapes/shape.h"

class Brick : public Shape {
public:
    // constructor
    Brick(Shader &shader, vec2 pos, vec2 size, struct color color, float width, float height);

    // destructor
    ~Brick() = default;

    // methods for updating and rendering the brick
    void update(float deltaTime);
    void draw() const ;

    float brickWidth;
    float brickHeight;
    struct color brickColor;

};





















#endif //GRAPHICS_BRICK_H
