#include "ofApp.h"

void ofApp::setup() {
    // Configurações iniciais
    ofBackground(0);
    ofSetFrameRate(60);

    // Inicializar posições
    paddleLeft.set(50.0f, ofGetHeight() / 2.0f - paddleHeight / 2.0f);
    paddleRight.set(ofGetWidth() - 50.0f - paddleWidth, ofGetHeight() / 2.0f - paddleHeight / 2.0f);
    ballPosition.set(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
    ballSpeed.set(5.0f, 3.0f);
}

void ofApp::update() {
    // Atualizar posição da bola
    ballPosition += ballSpeed;

    // Colisão com os limites superiores e inferiores
    if (ballPosition.y <= 0.0f || ballPosition.y >= ofGetHeight()) {
        ballSpeed.y *= -1.0f;
    }

    // Colisão com a raquete esquerda
    if (ballPosition.x - ballRadius <= paddleLeft.x + paddleWidth &&
        ballPosition.y >= paddleLeft.y && ballPosition.y <= paddleLeft.y + paddleHeight) {
        ballSpeed.x *= -1.0f;
    }

    // Colisão com a raquete direita
    if (ballPosition.x + ballRadius >= paddleRight.x &&
        ballPosition.y >= paddleRight.y && ballPosition.y <= paddleRight.y + paddleHeight) {
        ballSpeed.x *= -1.0f;
    }

    // Atualizar pontuação
    if (ballPosition.x <= 0.0f) {
        scoreRight++;
        ballPosition.set(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
        screenFlash = true;
        flashTime = ofGetElapsedTimef();
    }

    if (ballPosition.x >= ofGetWidth()) {
        scoreLeft++;
        ballPosition.set(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
        screenFlash = true;
        flashTime = ofGetElapsedTimef();
    }

    // Desativar flash após 0.5 segundos
    if (screenFlash && ofGetElapsedTimef() - flashTime > 0.5f) {
        screenFlash = false;
    }

    // IA para o jogador da esquerda (Player 1) com zona de tolerância
    float aiTargetY = ballPosition.y - paddleHeight / 2;

    // Tolerância para evitar tremores
    float tolerance = 10.0f;  // A IA não se move se a bola estiver dentro dessa distância

    if (abs(paddleLeft.y + paddleHeight / 2 - ballPosition.y) > tolerance) {
        if (paddleLeft.y + paddleHeight / 2 < ballPosition.y) {
            paddleLeft.y += paddleSpeed;
        }
        else if (paddleLeft.y + paddleHeight / 2 > ballPosition.y) {
            paddleLeft.y -= paddleSpeed;
        }
    }

    // Limitar movimento da raquete esquerda
    if (paddleLeft.y < 0.0f) paddleLeft.y = 0.0f;
    if (paddleLeft.y + paddleHeight > ofGetHeight()) paddleLeft.y = ofGetHeight() - paddleHeight;
}


void ofApp::draw() {
    // Flash de tela
    if (screenFlash) {
        ofSetColor(255, 0, 0);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }

    // Desenhar raquetes
    ofSetColor(255);
    ofDrawRectangle(paddleLeft.x, paddleLeft.y, paddleWidth, paddleHeight);
    ofDrawRectangle(paddleRight.x, paddleRight.y, paddleWidth, paddleHeight);

    // Desenhar bola
    ofDrawCircle(ballPosition, ballRadius);

    // Desenhar pontuação
    ofDrawBitmapString("Left: " + ofToString(scoreLeft), 50, 50);
    ofDrawBitmapString("Right: " + ofToString(scoreRight), ofGetWidth() - 150, 50);

    // Visualização 3D
    if (viewMode == 1 || viewMode == 2) {
        camera.begin();
        if (viewMode == 2) {
            camera.setPosition(ballPosition.x, ballPosition.y, 200.0f);
        }
        camera.end();
    }
}

void ofApp::keyPressed(int key) {
    switch (key) {
    case 'w': // Move barra esquerda para cima
        paddleLeft.y -= paddleSpeed;
        if (paddleLeft.y < 0.0f) paddleLeft.y = 0.0f;
        break;
    case 's': // Move barra esquerda para baixo
        paddleLeft.y += paddleSpeed;
        if (paddleLeft.y + paddleHeight > ofGetHeight()) paddleLeft.y = ofGetHeight() - paddleHeight;
        break;
    case OF_KEY_UP: // Move barra direita para cima
        paddleRight.y -= paddleSpeed;
        if (paddleRight.y < 0.0f) paddleRight.y = 0.0f;
        break;
    case OF_KEY_DOWN: // Move barra direita para baixo
        paddleRight.y += paddleSpeed;
        if (paddleRight.y + paddleHeight > ofGetHeight()) paddleRight.y = ofGetHeight() - paddleHeight;
        break;
    case '1':
        viewMode = 0;
        break;
    case '2':
        viewMode = 1;
        break;
    case '3':
        viewMode = 2;
        break;
    }
}

void ofApp::keyReleased(int key) {
    // Nenhuma funcionalidade atribuída ao soltar teclas
}
