#pragma once
#include "ofMain.h"
#include "cg_drawing_extras.h"

class Paddle {
public:
    void setup(float x, float y, float width, float height);
    void moveUp(float fieldY);
    void moveDown(float fieldY, float fieldHeight);
    void autoMove(float targetY, float fieldY, float fieldHeight);
    void draw(int view);
    void setBounds(float screenHeight);

    void Paddle::increaseDiffPaddle(Paddle&);

    ofVec2f getPosition();
    float getWidth();
    float getHeight();

private:
    ofVec2f position;
    float width, height;
    float speed = 10.0f;
    float lastUpdate = 0.0f;
};
