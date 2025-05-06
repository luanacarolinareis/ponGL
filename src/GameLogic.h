#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "cg_drawing_extras.h"

class GameLogic {
    public:
        void handleCollisions(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, float fieldX, float fieldWidth);
        void updateScores(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, float fieldX, float fieldY, float fieldWidth, float fieldHeight);
        void drawScores(float fieldX, float fieldY, float fieldWidth);
        void handleScreenFlash(float fieldX, float fieldY, float fieldWidth, float fieldHeight);
        bool isFlashing();

    private:
        int scoreLeft = 0;
        int scoreRight = 0;
        bool screenFlash = false;
        float flashStartTime = 0.0f;
        int counter = 0;
};
