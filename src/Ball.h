#pragma once
#include "ofMain.h"

class Ball {
public:
    void setup(float x, float y, float radius, float speedX, float speedY);
    void update(float fieldX, float fieldY, float fieldWidth, float fieldHeight);
    void draw();

    ofVec2f getPosition();
    void reverseX();
    void reverseY();
    void resetPosition(float x, float y, float fieldX, float fieldY, float fieldWidth, float fieldHeight);
    void setFieldLimits(float x, float y, float width, float height);
    float getRadius() const {
        return radius;
    }

private:
    ofVec2f position, speed;
    float radius;

    // Limites do campo
    float fieldX, fieldY, fieldWidth, fieldHeight;
};
