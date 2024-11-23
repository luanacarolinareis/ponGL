#include "ofApp.h"

void ofApp::setup() {
    // Configurações iniciais
    ofSetFrameRate(60);

    // Configurações do campo
    fieldX = 100.0f;
    fieldY = 50.0f;
    fieldWidth = ofGetWidth() - 200.0f;
    fieldHeight = ofGetHeight() - 100.0f;

    // Configurar elementos do jogo
    paddleLeft.setup(fieldX + 30.0f, fieldY + fieldHeight / 2.0f - 50.0f, 20.0f, 100.0f);
    paddleRight.setup(fieldX + fieldWidth - 50.0f, fieldY + fieldHeight / 2.0f - 50.0f, 20.0f, 100.0f);
    ball.setup(fieldX + fieldWidth / 2.0f, fieldY + fieldHeight / 2.0f, 10.0f, 5.0f, 3.0f);

    // Definir limites do campo na bola
    ball.setFieldLimits(fieldX, fieldY, fieldWidth, fieldHeight);

    // Configurar câmera
    camera.setNearClip(0.1f);
    camera.setFarClip(10000.0f);

    baseHeight = fieldHeight / GLfloat(fieldWidth);
}

void ofApp::update() {
    ball.update(fieldX, fieldY, fieldWidth, fieldHeight);
    gameLogic.handleCollisions(ball, paddleLeft, paddleRight, fieldX, fieldWidth);
    gameLogic.updateScores(ball, fieldX, fieldY, fieldWidth, fieldHeight);
    paddleLeft.autoMove(ball.getPosition().y, fieldY, fieldHeight); // Simula IA
}

void ofApp::draw() {
    // Desenhar o fundo fora do campo
    ofSetColor(50, 50, 50);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        
    glPushMatrix(); // Push master

    if (viewMode == 1) {
        glTranslatef(fieldWidth * 0, fieldHeight * 0.75, -baseHeight*1000);
        glRotatef(65, 1, 0, 0);
    }

    // Desenhar o fundo do campo de jogo
    ofSetColor(0, 100, 0);
    ofDrawRectangle(fieldX, fieldY, fieldWidth, fieldHeight);

    // Desenhar o efeito de flash
    gameLogic.handleScreenFlash(fieldX, fieldY, fieldWidth, fieldHeight);

    // Desenhar linha tracejada no centro
    ofSetColor(255); // Branco
    ofSetLineWidth(4.0f); // Largura da linha
    float dashLength = 10.0f; // Tamanho de cada segmento
    for (float y = fieldY; y < fieldY + fieldHeight; y += dashLength * 2) {
        ofDrawLine(fieldX + fieldWidth / 2.0f, y, fieldX + fieldWidth / 2.0f, y + dashLength);
    }

    paddleLeft.draw();
    paddleRight.draw();
    ball.draw();
    gameLogic.drawScores(fieldX, fieldY, fieldWidth);

    glPopMatrix();  // Pop master

    // Configurar visualização
    /*if (viewMode == 0) {
        // Vista ortográfica principal
        ofSetupScreenOrtho(ofGetWidth(), ofGetHeight(), -1000, 1000);
    }
    else {
        // Início da câmera
        camera.begin();

        if (viewMode == 1) {
            // Vista perspectiva principal
            camera.setPosition(ofGetWidth() / 2.0f, ofGetHeight() * 1.5, 800.0f);
            camera.lookAt(ofVec3f(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, 0.0f));
        }
        else if (viewMode == 2) {
            // Vista em 1ª pessoa
            ofVec3f ballPos = ball.getPosition();
            camera.setPosition(ballPos.x - 50.0f, ballPos.y, 200.0f);
            camera.lookAt(ofVec3f(ballPos.x + 50.0f, ballPos.y, 0.0f));
        }
    }

    if (viewMode != 0) {
        camera.end();
    }*/
}

void ofApp::keyPressed(int key) {
    switch (key) {
        case 'w': paddleLeft.moveUp(fieldY); break;
        case 's': paddleLeft.moveDown(fieldY, fieldHeight); break;
        case OF_KEY_UP: paddleRight.moveUp(fieldY); break;
        case OF_KEY_DOWN: paddleRight.moveDown(fieldY, fieldHeight); break;
        case '1': viewMode = 0; break;
        case '2': viewMode = 1; break;
        case '3': viewMode = 2; break;
    }
}

void ofApp::keyReleased(int key) {
    // Sem ações ao soltar teclas
}

void ofApp::windowResized(int w, int h) {
    // Recalcular as dimensões do campo
    fieldWidth = w - 200.0f; // Largura do campo (ajustado para a largura da janela)
    fieldHeight = h - 100.0f; // Altura do campo (ajustada para a altura da janela)

    // Recalcular a posição do campo para manter o centro
    fieldX = 100.0f;
    fieldY = 50.0f;

    // Recalcular a posição inicial da bola para o centro do campo
    ball.setFieldLimits(fieldX, fieldY, fieldWidth, fieldHeight);
    ball.resetPosition(w / 2.0f, h / 2.0f, fieldX, fieldY, fieldWidth, fieldHeight);

    // Recalcular as posições dos paddles
    paddleLeft.setup(fieldX + 30.0f, fieldY + fieldHeight / 2.0f - 50.0f, 20.0f, 100.0f);
    paddleRight.setup(fieldX + fieldWidth - 50.0f, fieldY + fieldHeight / 2.0f - 50.0f, 20.0f, 100.0f);
}
