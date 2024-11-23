#include "Ball.h"

void Ball::setup(float x, float y, float radius, float speedX, float speedY) {
    position.set(x, y);
    speed.set(speedX, speedY);
    this->radius = radius;
}

void Ball::update() {
    position += speed;

    if (position.y <= 0.0f || position.y >= ofGetHeight()) {
        reverseY();
    }
}

void Ball::draw() {
    ofSetColor(255);
    ofDrawCircle(position, radius);
}

void Ball::reverseX() { speed.x *= -1.0f; }
void Ball::reverseY() { speed.y *= -1.0f; }
void Ball::resetPosition(float x, float y) { position.set(x, y); }

ofVec2f Ball::getPosition() { return position; }
