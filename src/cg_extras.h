#ifndef CG_EXTRAS_H
#define CG_EXTRAS_H

#include "ofMain.h"

// Obter largura da janela
inline float gw() {
	return ofGetWidth();
}

// Obter altura da janela
inline float gh() {
	return ofGetHeight();
}

inline ofVec3f cross(ofVec3f A, ofVec3f B) {
	ofVec3f aux;
	aux.x = A.y * B.z - A.z * B.y;
	aux.y = A.z * B.x - A.x * B.z;
	aux.z = A.x * B.y - A.y * B.x;

	return aux;
}

#endif