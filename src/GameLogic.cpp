#include "GameLogic.h"

// Colis�es com as raquetes
void GameLogic::handleCollisions(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, float fieldX, float fieldWidth) {
    // Colis�o com a raquete esquerda
    if (ball.getPosition().x - ball.getRadius() <= paddleLeft.getPosition().x + paddleLeft.getWidth() &&
        ball.getPosition().x - ball.getRadius() >= fieldX &&
        ball.getPosition().y >= paddleLeft.getPosition().y &&
        ball.getPosition().y <= paddleLeft.getPosition().y + paddleLeft.getHeight()) {
        ball.reverseX();
    }

    // Colis�o com a raquete direita
    if (ball.getPosition().x + ball.getRadius() >= paddleRight.getPosition().x &&
        ball.getPosition().x + ball.getRadius() <= fieldX + fieldWidth &&
        ball.getPosition().y >= paddleRight.getPosition().y &&
        ball.getPosition().y <= paddleRight.getPosition().y + paddleRight.getHeight()) {
        ball.reverseX();
    }
}

// Atualiza��o de pontua��o
void GameLogic::updateScores(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, float fieldX, float fieldY, float fieldWidth, float fieldHeight) {
    if (ball.getPosition().x - ball.getRadius() <= fieldX) {
        // Bateu na parede esquerda
        // Jogador direito marca ponto
        scoreRight++;
        ball.resetPosition(fieldX + fieldWidth / 2.0f, fieldY + fieldHeight / 2.0f, fieldX, fieldY, fieldWidth, fieldHeight);
        screenFlash = true;
        flashStartTime = ofGetElapsedTimef();

        // Aumenta a dificuldade se a pontua��o for 5
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

        // Aumenta a dificuldade se a pontua��o for 5
        if (scoreLeft == 5) {
            paddleLeft.increaseDiffPaddle(paddleLeft);
            paddleRight.increaseDiffPaddle(paddleRight);
            ball.increaseDiffBall(ball);
        }
    }
}

// Desenho das pontua��es
void GameLogic::drawScores(float fieldX, float fieldY, float fieldWidth) {
    glDisable(GL_TEXTURE_2D);
    ofSetColor(255);

    // Score esquerdo � esquerda dentro do campo
    ofDrawBitmapString("Left: " + ofToString(scoreLeft), fieldX + 20, fieldY); // text, x, y

    // Sscore direito � direita dentro do campo
    ofDrawBitmapString("Right: " + ofToString(scoreRight), fieldX + fieldWidth - 120, fieldY); // text, x, y

	glEnable(GL_TEXTURE_2D);
}

// Flash no ecr�
void GameLogic::handleScreenFlash(float fieldX, float fieldY, float fieldWidth, float fieldHeight) {
    if (screenFlash) {
        drawRectangle(fieldX, fieldY, fieldWidth, fieldHeight, 1.0f, 0.0f, 0.0f);

        // Desativa o flash ap�s 0.5 segundos
        if (ofGetElapsedTimef() - flashStartTime > 0.5f) { screenFlash = false; }
    }
}

bool GameLogic::isFlashing() { return screenFlash; }
