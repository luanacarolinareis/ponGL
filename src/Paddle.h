#pragma once
#include "ofMain.h"

class Paddle {
public:
    void setup(float x, float y, float width, float height);
    void moveUp();
    void moveDown();
    void autoMove(float targetY);
    void draw();
    void setBounds(float screenHeight);

    ofVec2f getPosition();
    float getWidth();
    float getHeight();

private:
    ofVec2f position;
    float width, height;
    float speed = 10.0f;
};
