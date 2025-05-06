#include "GameLogic.h"

// Colisões com as raquetes
void GameLogic::handleCollisions(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, float fieldX, float fieldWidth) {
    // Colisão com a raquete esquerda
    if (ball.getPosition().x - ball.getRadius() <= paddleLeft.getPosition().x + paddleLeft.getWidth() &&
        ball.getPosition().x - ball.getRadius() >= fieldX &&
        ball.getPosition().y >= paddleLeft.getPosition().y &&
        ball.getPosition().y <= paddleLeft.getPosition().y + paddleLeft.getHeight()) {
        ball.reverseX();
    }

    // Colisão com a raquete direita
    if (ball.getPosition().x + ball.getRadius() >= paddleRight.getPosition().x &&
        ball.getPosition().x + ball.getRadius() <= fieldX + fieldWidth &&
        ball.getPosition().y >= paddleRight.getPosition().y &&
        ball.getPosition().y <= paddleRight.getPosition().y + paddleRight.getHeight()) {
        ball.reverseX();
    }
}

// Atualização de pontuação
void GameLogic::updateScores(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, float fieldX, float fieldY, float fieldWidth, float fieldHeight) {
    if (ball.getPosition().x - ball.getRadius() <= fieldX) {
        // Bateu na parede esquerda
        // Jogador direito marca ponto
        scoreRight++;
        ball.resetPosition(fieldX + fieldWidth / 2.0f, fieldY + fieldHeight / 2.0f, fieldX, fieldY, fieldWidth, fieldHeight);
        screenFlash = true;
        flashStartTime = ofGetElapsedTimef();

        // Aumenta a dificuldade se a pontuação for 5
		if (scoreRight == 5) {
			paddleLeft.increaseDiffPaddle(paddleLeft);
            paddleRight.increaseDiffPaddle(paddleRight);
			ball.increaseDiffBall(ball);
		}
    }

    if (ball.getPosition().x + ball.getRadius() >= fieldX + fieldWidth) {
		// Bateu na parede direita
        // Jogador esquerdo marca ponto
        scoreLeft++;
        ball.resetPosition(fieldX + fieldWidth / 2.0f, fieldY + fieldHeight / 2.0f, fieldX, fieldY, fieldWidth, fieldHeight);
        screenFlash = true;
        flashStartTime = ofGetElapsedTimef();

        // Aumenta a dificuldade se a pontuação for 5
        if (scoreLeft == 5) {
            paddleLeft.increaseDiffPaddle(paddleLeft);
            paddleRight.increaseDiffPaddle(paddleRight);
            ball.increaseDiffBall(ball);
        }
    }
}

// Desenho das pontuações
void GameLogic::drawScores(float fieldX, float fieldY, float fieldWidth) {
    glDisable(GL_TEXTURE_2D);
    ofSetColor(255);

    // Score esquerdo à esquerda dentro do campo
    ofDrawBitmapString("Left: " + ofToString(scoreLeft), fieldX + 20, fieldY); // text, x, y

    // Sscore direito à direita dentro do campo
    ofDrawBitmapString("Right: " + ofToString(scoreRight), fieldX + fieldWidth - 120, fieldY); // text, x, y

	glEnable(GL_TEXTURE_2D);
}

// Flash no ecrã
void GameLogic::handleScreenFlash(float fieldX, float fieldY, float fieldWidth, float fieldHeight) {
    if (screenFlash) {
        drawRectangle(fieldX, fieldY, fieldWidth, fieldHeight, 1.0f, 0.0f, 0.0f);

        // Desativa o flash após 0.5 segundos
        if (ofGetElapsedTimef() - flashStartTime > 0.5f) { screenFlash = false; }
    }
}

bool GameLogic::isFlashing() { return screenFlash; }
