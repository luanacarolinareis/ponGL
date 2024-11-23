#include "ofApp.h"

void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(60);

    paddleLeft.setup(50.0f, ofGetHeight() / 2.0f - 50.0f, 20.0f, 100.0f);
    paddleRight.setup(ofGetWidth() - 70.0f, ofGetHeight() / 2.0f - 50.0f, 20.0f, 100.0f);
    ball.setup(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, 10.0f, 5.0f, 3.0f);
}

void ofApp::update() {
    ball.update();
    gameLogic.handleCollisions(ball, paddleLeft, paddleRight);
    gameLogic.updateScores(ball);
    paddleLeft.autoMove(ball.getPosition().y); // Simula IA
}

void ofApp::draw() {
    // Desenhar o efeito de flash
    gameLogic.handleScreenFlash();

    // Desenhar linha tracejada no centro
    ofSetColor(255); // Branco
    ofSetLineWidth(4.0f); // Largura da linha
    float dashLength = 10.0f; // Tamanho de cada segmento
    for (float y = 0; y < ofGetHeight(); y += dashLength * 2) {
        ofDrawLine(ofGetWidth() / 2.0f, y, ofGetWidth() / 2.0f, y + dashLength);
    }

    // Visualização 3D
    if (viewMode == 1 || viewMode == 2) {
        camera.begin();
        if (viewMode == 2) {
            camera.setPosition(ball.getPosition().x, ball.getPosition().y, 200.0f);
        }
        camera.end();
    }

    paddleLeft.draw();
    paddleRight.draw();
    ball.draw();
    gameLogic.drawScores();
}

void ofApp::keyPressed(int key) {
    switch (key) {
        case 'w': paddleLeft.moveUp(); break;
        case 's': paddleLeft.moveDown(); break;
        case OF_KEY_UP: paddleRight.moveUp(); break;
        case OF_KEY_DOWN: paddleRight.moveDown(); break;
        case '1': viewMode = 0; break;
        case '2': viewMode = 1; break;
        case '3': viewMode = 2; break;
    }
}

void ofApp::keyReleased(int key) {
    // Sem ações ao soltar teclas
}
