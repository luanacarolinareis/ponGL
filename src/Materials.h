#pragma once
#include "ofMain.h"

#define NUM_MAT 6

inline extern string Materiais[] = {"Esmerald", "Ruby", "Bronze", "Silver", "White", "Red"};

inline void loadMaterial(int material) {

	GLfloat  esmeraldAmb[] = { 0.0215 ,0.1745 ,0.0215, 1. };
	GLfloat  esmeraldDif[] = { 0.07568 ,0.61424 ,0.07568, 1. };
	GLfloat  esmeraldSpec[] = { 0.633 ,0.727811 ,0.633, 1. };
	GLint    esmeraldCoef = 0.6 * 128;

	GLfloat  rubyAmb[] = { 0.1745 ,0.01175 ,0.01175, 1. };
	GLfloat  rubyDif[] = { 0.61424 ,0.04136 ,0.04136, 1. };
	GLfloat  rubySpec[] = { 0.727811 ,0.626959 ,0.626959, 1. };
	GLint    rubyCoef = 0.6 * 128;

	GLfloat  bronzeAmb[] = { 0.2125 ,0.1275 ,0.054, 1. };
	GLfloat  bronzeDif[] = { 0.714 ,0.4284 ,0.18144, 1. };
	GLfloat  bronzeSpec[] = { 0.393548 ,0.271906 ,0.166721, 1. };
	GLint    bronzeCoef = 0.2 * 128;

	GLfloat  silverAmb[] = { 0.19225 ,0.19225 ,0.19225, 1. };
	GLfloat  silverDif[] = { 0.50754 ,0.50754 ,0.50754, 1. };
	GLfloat  silverSpec[] = { 0.508273 ,0.508273 ,0.508273, 1. };
	GLint    silverCoef = 0.4 * 128;

	GLfloat  whiteAmb[] = { 1. ,1. ,1., 1. };
	GLfloat  whiteDif[] = { 1. ,1. ,1., 1. };
	GLfloat  whiteSpec[] = { 1. ,1. ,1., 1. };
	GLint    whiteCoef = 1 * 128;

	GLfloat  redAmb[] = { 0.5 ,0.0 ,0.0, 1. };
	GLfloat  redDif[] = { 0.7 ,0.6 ,0.6, 1. };
	GLfloat  redSpec[] = { 0.7 ,0.6 ,0.6, 1. };
	GLint    redCoef = 0.25 * 128;

	switch (material) {
		case 0: // Esmerald
			glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec);
			glMaterialf(GL_FRONT, GL_SHININESS, esmeraldCoef);
			break;
		case 1: // Ruby
			glMaterialfv(GL_FRONT, GL_AMBIENT, rubyAmb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpec);
			glMaterialf(GL_FRONT, GL_SHININESS, rubyCoef);
			break;
		case 2: // Bronze
			glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpec);
			glMaterialf(GL_FRONT, GL_SHININESS, bronzeCoef);
			break;
		case 3: // Silver
			glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
			glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
			break;
		case 'w': // White 
			glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteDif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpec);
			glMaterialf(GL_FRONT, GL_SHININESS, whiteCoef);
			break;
		case 'r':	// Red
			glMaterialfv(GL_FRONT, GL_AMBIENT, redAmb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, redDif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, redSpec);
			glMaterialf(GL_FRONT, GL_SHININESS, redCoef);
			break;
	}
}
