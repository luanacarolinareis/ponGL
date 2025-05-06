#pragma once

#include "ofMain.h"
#include "Materials.h"

#define M_PI 3.14159265358979323846

// Definição com y para cima
inline void cube_unit() {
	GLfloat p = 0.5;
	glBegin(GL_QUADS);

	//frente
	glNormal3f(0, 0, 1);
	glVertex3f(-p, p, p);
	glVertex3f(-p, -p, p);
	glVertex3f(p, -p, p);
	glVertex3f(p, p, p);

	//tras
	glNormal3f(0, 0, -1);
	glVertex3f(-p, p, -p);
	glVertex3f(p, p, -p);
	glVertex3f(p, -p, -p);
	glVertex3f(-p, -p, -p);

	//cima
	glNormal3f(0, 1, 0);
	glVertex3f(-p, p, -p);
	glVertex3f(-p, p, p);
	glVertex3f(p, p, p);
	glVertex3f(p, p, -p);

	//baixo
	glNormal3f(0, -1, 0);
	glVertex3f(-p, -p, p);
	glVertex3f(-p, -p, -p);
	glVertex3f(p, -p, -p);
	glVertex3f(p, -p, p);

	//esq
	glNormal3f(-1, 0, 0);
	glVertex3f(-p, p, p);
	glVertex3f(-p, p, -p);
	glVertex3f(-p, -p, -p);
	glVertex3f(-p, -p, p);

	//dir
	glNormal3f(1, 0, 0);
	glVertex3f(p, p, p);
	glVertex3f(p, -p, p);
	glVertex3f(p, -p, -p);
	glVertex3f(p, p, -p);

	glEnd();

}

// Desenha um retângulo com as dimensões e cor recebidas
inline void drawRectangle(float x, float y, float width, float height, float r, float g, float b) {
	glBegin(GL_QUADS);
	if (r >= 0.0f && g >= 0.0f && b >= 0.0f) glColor3f(r, g, b);
	glVertex3f(x, y, 0);					// Canto superior esquerdo
	glVertex3f(x + width, y, 0);			// Canto superior direito
	glVertex3f(x + width, y + height, 0);	// Canto inferior direito
	glVertex3f(x, y + height, 0);			// Canto inferior esquerdo
	glEnd();
}

// Função para desenhar uma linha tracejada vertical ou horizontal
inline void drawDashedLine(float x1, float y1, float x2, float y2, float dashLength, float lineWidth, float r, float g, float b) {
	glLineWidth(lineWidth);
	glColor3f(r, g, b);

	// Determinar o comprimento da linha
	float totalLength = (x1 == x2) ? fabs(y2 - y1) : fabs(x2 - x1);
	float direction = (x1 == x2) ? (y2 > y1 ? 1.0f : -1.0f) : (x2 > x1 ? 1.0f : -1.0f);

	glBegin(GL_LINES);
	for (float i = 0; i < totalLength; i += dashLength * 2) {
		if (x1 == x2) {
			// Linha vertical
			glVertex3f(x1, y1 + direction * i, 0.0f);
			glVertex3f(x1, y1 + direction * (i + dashLength), 0.0f);
		}
		else {
			// Linha horizontal
			glVertex3f(x1 + direction * i, y1, 0.0f);
			glVertex3f(x1 + direction * (i + dashLength), y1, 0.0f);
		}
	}
	glEnd();
}

inline void drawCircle(float x, float y, float radius, int segments = 100, float r = 1.0f, float g = 1.0f, float b = 1.0f) {
	glColor3f(r, g, b); // Define a cor
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, 0.0f); // Centro do círculo
	for (int i = 0; i <= segments; i++) {
		float angle = 2.0f * M_PI * i / segments; // Ângulo em radianos
		float px = x + cos(angle) * radius;
		float py = y + sin(angle) * radius;
		glVertex3f(px, py, 0.0f); // Pontos na circunferência
	}
	glEnd();
}

inline void drawSphere(float x, float y, float radius, int stacks = 20, int slices = 20, float r = 1.0f, float g = 1.0f, float b = 1.0f) {
	glColor3f(r, g, b); // Define a cor
	for (int i = 0; i < stacks; i++) {
		float lat0 = M_PI * (-0.5 + (float)i / stacks);
		float z0 = radius * sin(lat0);
		float zr0 = radius * cos(lat0);

		float lat1 = M_PI * (-0.5 + (float)(i + 1) / stacks);
		float z1 = radius * sin(lat1);
		float zr1 = radius * cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= slices; j++) {
			float lng = 2 * M_PI * (float)j / slices;
			float x1 = cos(lng);
			float y1 = sin(lng);

			glVertex3f(x + x1 * zr0, y + y1 * zr0, z0); // Primeiro ponto
			glVertex3f(x + x1 * zr1, y + y1 * zr1, z1); // Segundo ponto
		}
		glEnd();
	}
}

inline void draw3DBox(float x, float y, float z, float width, float height, float depth) {
	GLfloat p = 0.5f; // Tamanho da metade do cubo para centralizar

	// Pontos do cubo (baseado em x, y, z para o centro)
	ofVec3f topLeftFront(x - width / 2, y + height / 2, z - depth / 2);
	ofVec3f topRightFront(x + width / 2, y + height / 2, z - depth / 2);
	ofVec3f bottomLeftFront(x - width / 2, y - height / 2, z - depth / 2);
	ofVec3f bottomRightFront(x + width / 2, y - height / 2, z - depth / 2);
	ofVec3f topLeftBack(x - width / 2, y + height / 2, z + depth / 2);
	ofVec3f topRightBack(x + width / 2, y + height / 2, z + depth / 2);
	ofVec3f bottomLeftBack(x - width / 2, y - height / 2, z + depth / 2);
	ofVec3f bottomRightBack(x + width / 2, y - height / 2, z + depth / 2);

	// Desenhar as faces com preenchimento
	glBegin(GL_QUADS);

	// Frente
	glNormal3f(0, 0, 1); // Normal para a frente
	glVertex3f(topLeftFront.x, topLeftFront.y, topLeftFront.z);
	glVertex3f(topRightFront.x, topRightFront.y, topRightFront.z);
	glVertex3f(bottomRightFront.x, bottomRightFront.y, bottomRightFront.z);
	glVertex3f(bottomLeftFront.x, bottomLeftFront.y, bottomLeftFront.z);

	// Trás
	glNormal3f(0, 0, -1); // Normal para trás
	glVertex3f(topLeftBack.x, topLeftBack.y, topLeftBack.z);
	glVertex3f(bottomLeftBack.x, bottomLeftBack.y, bottomLeftBack.z);
	glVertex3f(bottomRightBack.x, bottomRightBack.y, bottomRightBack.z);
	glVertex3f(topRightBack.x, topRightBack.y, topRightBack.z);

	// Cima
	glNormal3f(0, 1, 0); // Normal para cima
	glVertex3f(topLeftBack.x, topLeftBack.y, topLeftBack.z);
	glVertex3f(topLeftFront.x, topLeftFront.y, topLeftFront.z);
	glVertex3f(topRightFront.x, topRightFront.y, topRightFront.z);
	glVertex3f(topRightBack.x, topRightBack.y, topRightBack.z);

	// Baixo
	glNormal3f(0, -1, 0); // Normal para baixo
	glVertex3f(bottomLeftFront.x, bottomLeftFront.y, bottomLeftFront.z);
	glVertex3f(bottomRightFront.x, bottomRightFront.y, bottomRightFront.z);
	glVertex3f(bottomRightBack.x, bottomRightBack.y, bottomRightBack.z);
	glVertex3f(bottomLeftBack.x, bottomLeftBack.y, bottomLeftBack.z);

	// Lado esquerdo
	glNormal3f(-1, 0, 0); // Normal para a esquerda
	glVertex3f(topLeftFront.x, topLeftFront.y, topLeftFront.z);
	glVertex3f(topLeftBack.x, topLeftBack.y, topLeftBack.z);
	glVertex3f(bottomLeftBack.x, bottomLeftBack.y, bottomLeftBack.z);
	glVertex3f(bottomLeftFront.x, bottomLeftFront.y, bottomLeftFront.z);

	// Lado direito
	glNormal3f(1, 0, 0); // Normal para a direita
	glVertex3f(topRightFront.x, topRightFront.y, topRightFront.z);
	glVertex3f(bottomRightFront.x, bottomRightFront.y, bottomRightFront.z);
	glVertex3f(bottomRightBack.x, bottomRightBack.y, bottomRightBack.z);
	glVertex3f(topRightBack.x, topRightBack.y, topRightBack.z);

	glEnd();
}

// Desenha preenchido
inline void filled() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}