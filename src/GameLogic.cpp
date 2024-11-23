#include "GameLogic.h"

void GameLogic::handleCollisions(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight) {
    if (ball.getPosition().x - 10 <= paddleLeft.getPosition().x + paddleLeft.getWidth() &&
        ball.getPosition().y >= paddleLeft.getPosition().y &&
        ball.getPosition().y <= paddleLeft.getPosition().y + paddleLeft.getHeight()) {
        ball.reverseX();
    }

    if (ball.getPosition().x + 10 >= paddleRight.getPosition().x &&
        ball.getPosition().y >= paddleRight.getPosition().y &&
        ball.getPosition().y <= paddleRight.getPosition().y + paddleRight.getHeight()) {
        ball.reverseX();
    }
}

void GameLogic::updateScores(Ball& ball) {
    if (ball.getPosition().x <= 0.0f) {
        // Jogador direito marca ponto
        scoreRight++;
        ball.resetPosition(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
        screenFlash = true;
        flashStartTime = ofGetElapsedTimef();
    }

    if (ball.getPosition().x >= ofGetWidth()) {
        // Jogador esquerdo marca ponto
        scoreLeft++;
        ball.resetPosition(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
        screenFlash = true;
        flashStartTime = ofGetElapsedTimef();
    }
}

void GameLogic::drawScores() {
    ofSetColor(255);
    ofDrawBitmapString("Left: " + ofToString(scoreLeft), 50, 50);
    ofDrawBitmapString("Right: " + ofToString(scoreRight), ofGetWidth() - 150, 50);
}

void GameLogic::handleScreenFlash() {
    if (screenFlash) {
        ofSetColor(255, 0, 0);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        // Desativa o flash após 0.5 segundos
        if (ofGetElapsedTimef() - flashStartTime > 0.5f) {
            screenFlash = false;
        }
    }
}

bool GameLogic::isFlashing() {
    return screenFlash;
}