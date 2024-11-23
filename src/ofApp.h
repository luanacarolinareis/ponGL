#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
	public:
	    // M�todos padr�o
	    void setup();
	    void update();
	    void draw();

	    void keyPressed(int key);
	    void keyReleased(int key);

	    // Vari�veis de jogo
	    ofVec2f paddleLeft = ofVec2f(0.0f, 0.0f);   // Posi��o da raquete esquerda
	    ofVec2f paddleRight = ofVec2f(0.0f, 0.0f);  // Posi��o da raquete direita
	    ofVec2f ballPosition = ofVec2f(0.0f, 0.0f); // Posi��o da bola
	    ofVec2f ballSpeed = ofVec2f(0.0f, 0.0f);    // Velocidade da bola

	    float paddleWidth = 20.0f;                  // Largura da raquete
	    float paddleHeight = 100.0f;                // Altura da raquete
	    float ballRadius = 10.0f;                   // Raio da bola

	    int scoreLeft = 0;                          // Pontua��o do jogador esquerdo
	    int scoreRight = 0;                         // Pontua��o do jogador direito

		float paddleSpeed = 30.0f;					// Velocidade de movimento das barras

	    int viewMode = 0;                           // Modo de visualiza��o (0 = 2D, 1 = 3D, 2 = 1� pessoa)
	    ofEasyCam camera;                           // C�mera para visualiza��o 3D

	    bool screenFlash = false;                   // Efeito de flash
	    float flashTime = 0.0f;                     // Tempo do efeito de flash
};
