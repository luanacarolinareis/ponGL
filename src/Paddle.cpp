#include "Paddle.h"

void Paddle::setup(float x, float y, float width, float height) {
    position.set(x, y);
    this->width = width;
    this->height = height;
}

void Paddle::moveUp(float fieldY) {
    position.y -= speed;
    if (position.y < fieldY) { // Limite superior do campo
        position.y = fieldY;
    }
}

void Paddle::moveDown(float fieldY, float fieldHeight) {
    position.y += speed;
    if (position.y + height > fieldY + fieldHeight) { // Limite inferior do campo
        position.y = fieldY + fieldHeight - height;
    }
}

void Paddle::autoMove(float targetY, float fieldY, float fieldHeight) {
    if (abs(position.y + height / 2 - targetY) > 10.0f) {
        if (position.y + height / 2 < targetY) moveDown(fieldY, fieldHeight);
        else moveUp(fieldY);
    }
    setBounds(ofGetHeight());
}

void Paddle::setBounds(float screenHeight) {
    if (position.y < 0.0f) position.y = 0.0f;
    if (position.y + height > screenHeight) position.y = screenHeight - height;
}

void Paddle::draw() {
    ofSetColor(255);
    ofDrawRectangle(position.x, position.y, width, height);
}

ofVec2f Paddle::getPosition() { return position; }
float Paddle::getWidth() { return width; }
float Paddle::getHeight() { return height; }
