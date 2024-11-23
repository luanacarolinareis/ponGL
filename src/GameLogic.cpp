#include "GameLogic.h"

void GameLogic::handleCollisions(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, float fieldX, float fieldWidth) {
    // Colisão com o paddle esquerdo
    if (ball.getPosition().x - ball.getRadius() <= paddleLeft.getPosition().x + paddleLeft.getWidth() &&
        ball.getPosition().x - ball.getRadius() >= fieldX &&
        ball.getPosition().y >= paddleLeft.getPosition().y &&
        ball.getPosition().y <= paddleLeft.getPosition().y + paddleLeft.getHeight()) {
        ball.reverseX();
    }

    // Colisão com o paddle direito
    if (ball.getPosition().x + ball.getRadius() >= paddleRight.getPosition().x &&
        ball.getPosition().x + ball.getRadius() <= fieldX + fieldWidth &&
        ball.getPosition().y >= paddleRight.getPosition().y &&
        ball.getPosition().y <= paddleRight.getPosition().y + paddleRight.getHeight()) {
        ball.reverseX();
    }
}

void GameLogic::updateScores(Ball& ball, float fieldX, float fieldY, float fieldWidth, float fieldHeight) {
    if (ball.getPosition().x - ball.getRadius() <= fieldX) {
        // Jogador direito marca ponto
        scoreRight++;
        ball.resetPosition(fieldX + fieldWidth / 2.0f, fieldY + fieldHeight / 2.0f, fieldX, fieldY, fieldWidth, fieldHeight);
        screenFlash = true;
        flashStartTime = ofGetElapsedTimef();
    }

    if (ball.getPosition().x + ball.getRadius() >= fieldX + fieldWidth) {
        // Jogador esquerdo marca ponto
        scoreLeft++;
        ball.resetPosition(fieldX + fieldWidth / 2.0f, fieldY + fieldHeight / 2.0f, fieldX, fieldY, fieldWidth, fieldHeight);
        screenFlash = true;
        flashStartTime = ofGetElapsedTimef();
    }
}

void GameLogic::drawScores(float fieldX, float fieldY, float fieldWidth) {
    ofSetColor(255);

    // Score esquerdo à esquerda dentro do campo
    ofDrawBitmapString("Left: " + ofToString(scoreLeft), fieldX + 20, fieldY + 30);

    // Sscore direito à direita dentro do campo
    ofDrawBitmapString("Right: " + ofToString(scoreRight), fieldX + fieldWidth - 120, fieldY + 30);
}

void GameLogic::handleScreenFlash(float fieldX, float fieldY, float fieldWidth, float fieldHeight) {
    if (screenFlash) {
        ofSetColor(255, 0, 0);
        ofDrawRectangle(fieldX, fieldY, fieldWidth, fieldHeight);

        // Desativa o flash após 0.5 segundos
        if (ofGetElapsedTimef() - flashStartTime > 0.5f) {
            screenFlash = false;
        }
    }
}

bool GameLogic::isFlashing() {
    return screenFlash;
}