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

private:
    Paddle paddleLeft;
    Paddle paddleRight;
    Ball ball;
    GameLogic gameLogic;

    ofEasyCam camera; // Para modo 3D
    int viewMode = 0; // Modos de visualização
};
