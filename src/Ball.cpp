#include "Ball.h"
#include "ofApp.h"

// Configuração inicial da bola
void Ball::setup(float x, float y, float radius, float speedX, float speedY) {
    position.set(x, y);
    speed.set(speedX, speedY);
	this->radius = radius;  // 10.0f
}

// Atualização da posição da bola
void Ball::update(float fieldX, float fieldY, float fieldWidth, float fieldHeight) {
    position += speed;
	// Verificar colisão com as bordas do campo
    if (position.y - radius <= fieldY || position.y + radius >= fieldY + fieldHeight) { reverseY(); }
    if (position.x - radius <= fieldX || position.x + radius >= fieldX + fieldWidth) { reverseX(); }
}

// Desenho da bola
void Ball::draw(int view) {
    ofSetColor(255);
	if (view == 1) drawSphere(position.x, position.y, radius, 20, 20, 1.0f, 1.0f, 1.0f); // x, y, raio
	else drawCircle(position.x, position.y, radius, 100, 1.0f, 1.0f, 1.0f);   // posição (xy), raio
}

void Ball::increaseDiffBall(Ball& ball) {
    // Aumenta a velocidade da bola
    ball.speed *= 1.5;
}

void Ball::reverseX() { speed.x *= -1.0f; }
void Ball::reverseY() { speed.y *= -1.0f; }

// Reset da posição da bola (centro do campo)
void Ball::resetPosition(float x, float y, float fieldX, float fieldY, float fieldWidth, float fieldHeight) { 
    position.set(fieldX + fieldWidth / 2.0f, fieldY + fieldHeight / 2.0f); 
}

ofVec2f Ball::getPosition() { return position; }

// Configuração dos limites do campo
void Ball::setFieldLimits(float x, float y, float width, float height) {
    fieldX = x;
    fieldY = y;
    fieldWidth = width;
    fieldHeight = height;
}
