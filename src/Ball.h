#pragma once
#include "ofMain.h"

class Ball {
public:
    void setup(float x, float y, float radius, float speedX, float speedY);
    void update();
    void draw();

    ofVec2f getPosition();
    void reverseX();
    void reverseY();
    void resetPosition(float x, float y);

private:
    ofVec2f position, speed;
    float radius;
};
