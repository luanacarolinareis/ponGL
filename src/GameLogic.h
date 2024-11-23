#pragma once
#include "Ball.h"
#include "Paddle.h"

class GameLogic {
public:
    void handleCollisions(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight);
    void updateScores(Ball& ball);
    void drawScores();
    void handleScreenFlash();
    bool isFlashing();

private:
    int scoreLeft = 0;
    int scoreRight = 0;
    bool screenFlash = false;
    float flashStartTime = 0.0f;
};
