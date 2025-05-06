#pragma once
#include "ofMain.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameLogic.h"
#include "Materials.h"
#include "cg_drawing_extras.h"
#include "cg_cam_extras.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void img(int);

private:
    Paddle paddleLeft;
    Paddle paddleRight;
    Ball ball;
    GameLogic gameLogic;
   
    // Ligar/desligar fontes de luz
    bool ambientOn = true;
    bool dirOn = false;
    bool pointOn = false;
	bool spotOn = false;
    
    // Ligar/desligar componentes de luz
    bool ambientCompDir, diffuseCompDir, specularCompDir;       // Luz direcional
    bool ambientCompPoint, diffuseCompPoint, specularCompPoint; // Luz pontual
    bool ambientCompSpot, diffuseCompSpot, specularCompSpot;    // Luz de foco

	// Movimento automático
    bool autoMove;

    GLfloat ambientLight[4];

	// Luz direcional
    GLfloat dirVec[4];
	GLfloat dirAmb[4];  // Componente ambiente
	GLfloat dirDif[4];  // Componente difusa
	GLfloat dirSpec[4]; // Componente especular
    ofVec3f dirVec3f;
    GLfloat dirVecTheta;

	// Luz pontual
    GLfloat pointPos[4];
	GLfloat pointAmb[4];    // Componente ambiente
	GLfloat pointDif[4];    // Componente difusa
	GLfloat pointSpec[4];   // Componente especular
    GLfloat pointZtheta;
    GLfloat pointAtC, pointAtL, pointAtQ;

	// Luz de foco
    GLfloat spotPos[4];
    GLfloat spotDir[3];
    ofVec3f spotDirVec;
    ofVec3f spotDirAux;
    ofVec3f spotPosVec;
	GLfloat spotAmb[4];     // Componente ambiente
	GLfloat spotDif[4];	    // Componente difusa
	GLfloat spotSpec[4];    // Componente especular
    GLfloat spotExponent;
    GLfloat spotCutoff;
    GLfloat spotTheta;
    GLfloat spotAtC, spotAtL, spotAtQ;
      
    // Materiais
	bool customMat;
    int mat;

    // Texturas
	ofImage img1, img2, img3;

    int viewMode = 0;   // Modo de visualização
	ofCamera cam;	    // Câmera

    float fieldX;       // Posição X do retângulo verde
    float fieldY;       // Posição Y do retângulo verde
    float fieldWidth;   // Largura do campo
    float fieldHeight;  // Altura do campo

    float startTime;    // Tempo de início
    float delayTime;    // Tempo de atraso
};
