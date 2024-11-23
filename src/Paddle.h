#pragma once
#include "ofMain.h"

class Paddle {
public:
    void setup(float x, float y, float width, float height);
    void moveUp(float fieldY);
    void moveDown(float fieldY, float fieldHeight);
    void autoMove(float targetY, float fieldY, float fieldHeight);
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
