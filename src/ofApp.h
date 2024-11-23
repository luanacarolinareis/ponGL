#pragma once
#include "ofMain.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameLogic.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void windowResized(int w, int h);

private:
    Paddle paddleLeft;
    Paddle paddleRight;
    Ball ball;
    GameLogic gameLogic;

    ofEasyCam camera; // Para modo 3D
    int viewMode = 0; // Modos de visualiza��o

    float fieldX;       // Posi��o X do ret�ngulo verde
    float fieldY;       // Posi��o Y do ret�ngulo verde
    float fieldWidth;   // Largura do campo
    float fieldHeight;  // Altura do campo

    GLfloat baseHeight;
};
