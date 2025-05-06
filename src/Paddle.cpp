#include "Paddle.h"

// Configura��o inicial da raquete
void Paddle::setup(float x, float y, float width, float height) {
    position.set(x, y);
    this->width = width;
    this->height = height;
}

// Movimenta��o da raquete para cima
void Paddle::moveUp(float fieldY) {
    position.y -= speed;
    if (position.y < fieldY) { // Limite superior do campo (n�o ultrapassa)
        position.y = fieldY;
    }
}

// Movimenta��o da raquete para baixo
void Paddle::moveDown(float fieldY, float fieldHeight) {
    position.y += speed;
    if (position.y + height > fieldY + fieldHeight) { // Limite inferior do campo (n�o ultrapassa)
        position.y = fieldY + fieldHeight - height;
    }
}

// Movimenta��o autom�tica da raquete
void Paddle::autoMove(float targetY, float fieldY, float fieldHeight) {
    static float moveDuration = 0.5f;  // Dura��o m�nima do movimento cont�nuo
    static float lastMoveTime = 0;     // Marca o in�cio do movimento
    static bool isMoving = false;      // Define se est� em movimento cont�nuo
    static int moveDirection = 0;      // -1 para cima, 1 para baixo, 0 para parado

    float stopChance = 0.4;            // Chance de parar
    float stopDuration = 0.2f;         // Tempo que a IA pode parar
    static float stopTime = 0;         // Tempo inicial da paragem
    static bool isStopped = false;     // Define se est� parado

    float reactionThreshold = 60.0f;  // Dist�ncia m�nima para decidir mover-se
    float randomError = ofRandom(-10.0f, 10.0f); // Desvio aleat�rio no alvo

    // Comportamento de "paragem"

    // 1. Decis�o de paragem
    if (ofRandom(1.0) < stopChance && !isStopped && !isMoving) {
        isStopped = true;
        stopTime = ofGetElapsedTimef();
    }

    // 2. Manuten��o de paragem (se pode ou n�o voltar a mover-se)
    if (isStopped) {
        if (ofGetElapsedTimef() - stopTime > stopDuration) { isStopped = false; }
        return;
    }

    // Movimento cont�nuo ativo
    if (isMoving) {
        if (ofGetElapsedTimef() - lastMoveTime < moveDuration) {
            // Continua o movimento na dire��o atual
            if (moveDirection == 1) moveDown(fieldY, fieldHeight);
            else if (moveDirection == -1) moveUp(fieldY);
            return;
        }
        else { isMoving = false; }  // Finaliza o movimento cont�nuo 
    }

    // Decis�o de nova dire��o com base no alvo e no erro
    float adjustedTargetY = targetY + randomError;  // C�lculo do alvo ajustado com um erro aleat�rio (simula imprecis�o)
    
    // Se a dist�ncia entre o centro da raquete e o alvo ajustado for maior que o limiar de rea��o,
    // a raquete decide mover-se
    if (abs(position.y + height / 2 - adjustedTargetY) > reactionThreshold) {

        // Se o centro da raquete est� abaixo do alvo ajustado, 
        // a dire��o � para baixo (moveDirection = 1)
        if (position.y + height / 2 < adjustedTargetY) { moveDirection = 1; }
        
        // Se o centro da raquete est� acima do alvo ajustado, 
        // a dire��o � para cima (moveDirection = -1).
        else { moveDirection = -1; }

        // Inicia movimento cont�nuo
        isMoving = true;
        lastMoveTime = ofGetElapsedTimef();
    }
}

// Limites da raquete no campo
void Paddle::setBounds(float screenHeight) {
    if (position.y < 0.0f) position.y = 0.0f;
    if (position.y + height > screenHeight) position.y = screenHeight - height;
}

// Desenho da raquete
void Paddle::draw(int view) {
    ofSetColor(255);
    if (view == 1) draw3DBox(position.x + width / 2, position.y + height / 2, 0, width, height, 20.0f); // x, y, z (centro), largura, altura, profundidade
	else drawRectangle(position.x, position.y, width, height, 1.0f, 1.0f, 1.0f); // x, y, largura, altura, r, g, b
}

void Paddle::increaseDiffPaddle(Paddle& paddle) {
    // Aumenta a velocidade da raquete
    paddle.speed *= 1.2;
}

ofVec2f Paddle::getPosition() { return position; }
float Paddle::getWidth() { return width; }
float Paddle::getHeight() { return height; }
