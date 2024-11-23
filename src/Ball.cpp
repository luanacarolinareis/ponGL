#include "Ball.h"
#include "ofApp.h"

void Ball::setup(float x, float y, float radius, float speedX, float speedY) {
    position.set(x, y);
    speed.set(speedX, speedY);
    this->radius = radius;
}

void Ball::update(float fieldX, float fieldY, float fieldWidth, float fieldHeight) {
    position += speed;

    // Verificar colisão com as bordas do campo
    if (position.y - radius <= fieldY || position.y + radius >= fieldY + fieldHeight) {
        reverseY();
    }

    if (position.x - radius <= fieldX || position.x + radius >= fieldX + fieldWidth) {
        reverseX();
    }
}

void Ball::draw() {
    ofSetColor(255);
    ofDrawCircle(position, radius);
}

void Ball::reverseX() { speed.x *= -1.0f; }
void Ball::reverseY() { speed.y *= -1.0f; }
void Ball::resetPosition(float x, float y, float fieldX, float fieldY, float fieldWidth, float fieldHeight) { 
    position.set(fieldX + fieldWidth / 2.0f, fieldY + fieldHeight / 2.0f); 
}

ofVec2f Ball::getPosition() { return position; }
void Ball::setFieldLimits(float x, float y, float width, float height) {
    fieldX = x;
    fieldY = y;
    fieldWidth = width;
    fieldHeight = height;
}
