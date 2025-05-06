#include "ofApp.h"

void ofApp::setup() {
    // Configurações iniciais
    ofSetFrameRate(60);
    ofSetVerticalSync(false);

    // Para utilizar coordenadas de textura normalizadas
    ofDisableArbTex();

    // Obtém o tamanho do ecrã
    int screenWidth = ofGetScreenWidth();
    int screenHeight = ofGetScreenHeight();

    // Calcula a posição central do ecrã
    int windowWidth = gw();    // Largura da janela
    int windowHeight = gh();  // Altura da janela

    int windowPosX = (screenWidth - windowWidth) / 2;    // Posição X centralizada
    int windowPosY = (screenHeight - windowHeight) / 2;  // Posição Y centralizada

    // Define a posição da janela
    ofSetWindowPosition(windowPosX, windowPosY);

    // Configurações do campo
    fieldX = -gw() / 2. + 100;
	fieldY = -gh() / 2. + 50;
    fieldWidth = gw() - 200.0f;
    fieldHeight = gh() - 100.0f;

    // Configurações dos elementos do jogo
    paddleLeft.setup(fieldX + 30.0f, fieldY + fieldHeight / 2.0f - 50.0f, 20.0f, 100.0f);
    paddleRight.setup(fieldX + fieldWidth - 50.0f, fieldY + fieldHeight / 2.0f - 50.0f, 20.0f, 100.0f);
    ball.setup(fieldX + fieldWidth / 2.0f, fieldY + fieldHeight / 2.0f, 10.0f, 6.0f, 4.0f);

    // Definição de limites do campo para a bola
    ball.setFieldLimits(fieldX, fieldY, fieldWidth, fieldHeight);

    startTime = ofGetElapsedTimeMillis();  // Inicializar o temporizador
    delayTime = 1500;                      // 1,5 segundos de atraso

	// Iluminação
    ambientOn = true;   // Presente em toda a cena de forma uniforme, sem direção específica
    dirOn = false;      // Luz que vem de direção específica e ilumina todos os objetos na cena de forma paralela
    pointOn = false;    // Luz que emana de um ponto específico no espaço e se espalha em todas as direções
	spotOn = false;     // Luz que emana de um ponto específico no espaço e se espalha num cone

    ambientCompDir = true;  // Comp. ambiente: parte da luz que é refletida de forma difusa por todas as superfícies, independentemente da orientação
    diffuseCompDir = true;  // Comp. especular: parte da luz que é refletida de forma especular (como espelho) por superfícies brilhantes (depende da orientação da superfície e da posição do observador)
    specularCompDir = true; // Comp. difusa: parte da luz que é refletida de forma difusa por superfícies diretamente expostas à luz (depende da orientação da superfície em relação à direção da luz)

    ambientCompPoint = true;
    diffuseCompPoint = true;
    specularCompPoint = true;

    ambientCompSpot = true;
    diffuseCompSpot = true;
    specularCompSpot = true;

    autoMove = true;

    // Controla ângulo de rotação da luz pontual ao longo do eixo z
    // Usada para calcular a posição da luz pontual num movimento circular
    pointZtheta = 0;

    // Controla ângulo de rotação da luz direcional
    // Usada para calcular a direção da luz direcional, permitindo que esta se mova ou gire ao longo do tempo
    dirVecTheta = 0.;

    // Define concentração do feixe de luz do tipo foco
    // Valores + altos resultam num feixe mais concentrado, enquanto valores mais baixos num feixe mais disperso
    spotExponent = 64;

    // Define ângulo de corte do feixe de luz do tipo foco
    // É o ângulo máximo a partir do eixo central do feixe dentro do qual a luz é emitida
    // Fora desse ângulo, a luz é cortada
    spotCutoff = 45;

    // Controla o ângulo de rotação da luz de foco
    // Usada para calcular a direção da luz de foco, permitindo que esta se mova ou gire ao longo do tempo
    spotTheta = 0;

    // Vetor normalizado que representa a direção da luz de foco (calculado com base em spotDirAux e spotPosVec)
    spotDirVec = ofVec3f(0, 0, 0);
    // Vetor auxiliar usado para calcular direção da luz de foco: é atualizado com base na rotação (spotTheta) e na posição (spotPosVec)
    spotDirAux = ofVec3f(0, 0, 0);
    // Vetor que representa a posição da luz de foco: inicialmente definido para uma posição específica no ecrã
    spotPosVec = ofVec3f(-ofGetScreenWidth() * 0.25, 0., ofGetScreenHeight() * 0.25);

    // Materiais
    customMat = true;
    mat = 0;

    // Texturas
	img1.load("back1.jpg");
    img2.load("back2.png");
    img3.load("back3.jpg");
}

void ofApp::update() {
    // Verificar se o tempo de espera já passou
    if (ofGetElapsedTimeMillis() - startTime < delayTime) {
        return; // Ainda à espera, não atualizar o jogo
    }

    ball.update(fieldX, fieldY, fieldWidth, fieldHeight);
    gameLogic.handleCollisions(ball, paddleLeft, paddleRight, fieldX, fieldWidth);
    gameLogic.updateScores(ball, paddleLeft, paddleRight ,fieldX, fieldY, fieldWidth, fieldHeight);
    paddleLeft.autoMove(ball.getPosition().y, fieldY, fieldHeight); // Simula IA

    // Iluminação
    if (autoMove) {
        // Cálculo da posição da luz pontual (movimento circular dinâmico ao longo do tempo)
        pointPos[0] = gw() * 0.5 * sin(3 * pointZtheta * PI / 180.0);   // Coordenada x (varia sinusoidalmente: criar mov. circular)
        pointPos[1] = gh() * 0.5 * cos(pointZtheta * PI / 180.0);       // Coordenada y (varia cosinusoidalmente: criar mov. circular)
        pointPos[2] = 200 + 199 * cos(8 * pointZtheta * PI / 180.0);    // Coordenada z (varia cosinusoidalmente: criar mov. de vaivém no eixo)
        pointZtheta += 0.25;                                            // Garantir que a posição da luz continue a mudar ao longo do tempo

        // Cálculo da direção da luz direcional (movimento dinâmico ao longo do tempo)
        float z = gh() * 0.25 * (cos(dirVecTheta * PI / 180.) * 0.5 + 0.45);    // Coordenada z (varia cosinusoidalmente: criar mov. dinâmico)
        float y = gh() * 0.5;                                                   // Coordenada y (constante)
        float x = 0;                                                            // Coordenada x (luz direcional não se move no eixo x)
        dirVec3f = ofVec3f(x, y, z) - ofVec3f(0, 0, 0);                         // Cálculo do vetor de direção
        dirVecTheta += 0.5;                                                     // Garantir que a direção da luz continue a mudar ao longo do tempo

        // Cálculo da direção da luz de foco
        float sx = gh() * 0.1 * cos(spotTheta * PI / 180.) + spotPosVec.x;      // Coordenada x da direção da luz de foco
        float sy = gh() * 0.1 * sin(spotTheta * PI / 180.) + spotPosVec.y;      // Coordenada y da direção da luz de foco
        spotDirAux = ofVec3f(sx, sy, 0.);       // Vetor auxiliar usado para calcular direção da luz de foco
        spotDirVec = spotDirAux - spotPosVec;   // Vetor de direção que aponta da posição inicial da luz de foco para a nova posição calculada
        spotDirVec = spotDirVec.normalize();    // Garante que o vetor de direção tenha comprimento unitário (1)
        spotTheta += 0.75;                      // Garantir que a direção da luz de foco continue a mudar ao longo do tempo)
    } else {
        // Luz pontual
        // Centro acima
        pointPos[0] = 0;
        pointPos[1] = 0;
        pointPos[2] = 90;

        // Luz direcional
        // Auto max 
        dirVec3f = ofVec3f(0, gh() * 0.5, gh() * 0.25 * 0.95) - ofVec3f(0, 0, 0);

		// Luz de foco
        spotDir[0] = 0;
        spotDir[1] = 0;
    }
}

void ofApp::draw() {
    // Define viewport
	glViewport(0, 0, gw(), gh()); // x canto inf. esq., y canto inf. esq., largura, altura

	// Define projeção
	perspective(60, 100, 100);

    // Ajustar a posição e orientação da câmera conforme o viewMode
    switch (viewMode) {
        case 0:
            lookat(0, 0, 665.108, 0, 0, 0, 0, 1, 0);
            break;
        case 1:
            lookat(0, -gh() * 1.25, gh() * 0.75, 0, 0, 0, 0, 0, 1);
            break;
    }

    // Iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    // Fonte de luz com apenas componente ambiente
    if (ambientOn) {
        ambientLight[0] = 1.; // R
        ambientLight[1] = 1.; // G
        ambientLight[2] = 1.; // B
		ambientLight[3] = 1.;
    }
    else {
		ambientLight[0] = 0.; // R
		ambientLight[1] = 0.; // G
		ambientLight[2] = 0.; // B
		ambientLight[3] = 1.;
    }
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    // Fonte de luz direcional

    // Direção
    dirVec[0] = dirVec3f.x; // x
    dirVec[1] = dirVec3f.y; // y
    dirVec[2] = dirVec3f.z; // z
	dirVec[3] = 0;		    // Vetor: direção
    glLightfv(GL_LIGHT0, GL_POSITION, dirVec);

    if (dirOn) {
        glEnable(GL_LIGHT0);

        dirAmb[0] = ambientCompDir ? 0.0 : 0.2;
        dirAmb[1] = ambientCompDir ? 0.0 : 0.2;
        dirAmb[2] = ambientCompDir ? 0.0 : 0.2;
        glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmb);

        dirDif[0] = diffuseCompDir ? 0.5 : 0.0;
        dirDif[1] = diffuseCompDir ? 0.5 : 0.0;
        dirDif[2] = diffuseCompDir ? 0.5 : 0.0;
        glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDif);

        dirSpec[0] = specularCompDir ? 0.0 : 0.5;
        dirSpec[1] = specularCompDir ? 0.0 : 0.5;
        dirSpec[2] = specularCompDir ? 0.0 : 0.5;
        glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpec);
    } else {
        glDisable(GL_LIGHT0);
    }

    // Fonte de luz pontual

    // Posição
    pointPos[3] = 1; // Ponto: posição
    glLightfv(GL_LIGHT1, GL_POSITION, pointPos);

	// Atenuação da luz pontual (diminuição da intensidade da luz à medida que a distância da fonte aumenta)
    pointAtC = 1;           // Fator de atenuação constante (não diminui intensidade com a distância)
    pointAtL = 0.0001;      // Fator de atenuação linear (diminui linearmente com a distância)
    pointAtQ = 0.00001;     // Fator de atenuação quadrática (diminui quadraticamente com a distância)
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, pointAtC);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, pointAtL);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, pointAtQ);

    if (pointOn) {
        glEnable(GL_LIGHT1);

        pointAmb[0] = ambientCompPoint ? 0.25 : 0.0;
        pointAmb[1] = ambientCompPoint ? 0.25 : 0.0;
        pointAmb[2] = ambientCompPoint ? 0.25 : 0.0;
        glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmb);

        pointDif[0] = diffuseCompPoint ? 1.0 : 0.0;
        pointDif[1] = diffuseCompPoint ? 1.0 : 0.0;
        pointDif[2] = diffuseCompPoint ? 1.0 : 0.0;
        glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDif);

        pointSpec[0] = specularCompPoint ? 0.0 : 1.0;
        pointSpec[1] = specularCompPoint ? 0.0 : 1.0;
        pointSpec[2] = specularCompPoint ? 0.0 : 1.0;
        glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec);
    } else {
        glDisable(GL_LIGHT1);
    }

    // Fonte de luz do tipo foco

    // Posição
    spotPos[0] = -gw() * 0.25;
    spotPos[1] = 0.;
    spotPos[2] = gh() * 0.25;
    spotPos[3] = 1.;

    // Direção
    spotDir[0] = spotDirVec.x;
    spotDir[1] = spotDirVec.y;
    spotDir[2] = spotDirVec.z;

    glLightfv(GL_LIGHT2, GL_POSITION, spotPos);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);

    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);

    // Atenuação da luz de foco
    spotAtC = 1.;
    spotAtL = 0.;
    spotAtQ = 0.;
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, spotAtC);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, spotAtL);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, spotAtQ);

    if (spotOn) {
        glEnable(GL_LIGHT2);

        spotAmb[0] = ambientCompSpot ? 1.0 : 0.0;
        spotAmb[1] = ambientCompSpot ? 1.0 : 0.0;
        spotAmb[2] = ambientCompSpot ? 1.0 : 0.0;
        glLightfv(GL_LIGHT2, GL_AMBIENT, spotAmb);

        spotDif[0] = diffuseCompSpot ? 1.0 : 0.0;
        spotDif[1] = diffuseCompSpot ? 1.0 : 0.0;
        spotDif[2] = diffuseCompSpot ? 1.0 : 0.0;
        glLightfv(GL_LIGHT2, GL_DIFFUSE, spotDif);

        spotSpec[0] = specularCompSpot ? 1.0 : 0.0;
        spotSpec[1] = specularCompSpot ? 1.0 : 0.0;
        spotSpec[2] = specularCompSpot ? 1.0 : 0.0;
        glLightfv(GL_LIGHT2, GL_SPECULAR, spotSpec);
    } else {
        glDisable(GL_LIGHT2);
    }

    // Material pré definido (0 - Esmeralda)
    // Desenhar o fundo do campo de jogo
    if (customMat) {
        loadMaterial(mat);
        drawRectangle(fieldX, fieldY, fieldWidth, fieldHeight, 0.0f, 0.39f, 0.0f); // x, y, largura, altura, r, g, b
    } else {
        img(mat - 3);
    }

    // Desenhar o efeito de flash
    loadMaterial('r');
    gameLogic.handleScreenFlash(fieldX, fieldY, fieldWidth, fieldHeight);

    // Desenhar linha tracejada no centro
    loadMaterial('w');
    drawDashedLine(
        fieldX + fieldWidth / 2.0f, fieldY,                    // Ponto inicial (x1, y1)
        fieldX + fieldWidth / 2.0f, fieldY + fieldHeight,      // Ponto final (x2, y2)
        10.0f, 4.0f,                                           // Tamanho dos traços e espessura
        1.0f, 1.0f, 1.0f                                       // Cor branca normalizada (r, g, b)
    );

    paddleLeft.draw(viewMode);
    paddleRight.draw(viewMode);
    ball.draw(viewMode);
    gameLogic.drawScores(fieldX, fieldY + 640, fieldWidth);

    // Desenha representação das luzes e vetores utilizados sem iluminação
    glDisable(GL_LIGHTING); // Desabilita iluminação

	// Representação da posição da luz pontual
    if (pointOn) {
        glColor3f(1, 1, 1);
        glPushMatrix();
        glTranslatef(pointPos[0], pointPos[1], pointPos[2]);
        glScalef(30, 30, 30);
        cube_unit();
        glPopMatrix();
    }

	// Representação da posição da luz direcional
    if (dirOn) {
        glColor3f(1, 1, 1);
        glPushMatrix();
        glTranslatef(dirVec3f.x, dirVec3f.y, dirVec3f.z);
        glScalef(30, 30, 30);
        cube_unit();
        glPopMatrix();

        glPushMatrix();
        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(dirVec3f.x, dirVec3f.y, dirVec3f.z);
        glEnd();
        glPopMatrix();
    }

    // Representação da posição da luz de foco
    if (spotOn) {
        glColor3f(1, 1, 1);
        glPushMatrix();
        glTranslatef(spotPos[0], spotPos[1], spotPos[2]);
        glScalef(30, 30, 30);
        cube_unit();
        glPopMatrix();
    }
}

// Movimentação e troca de vista
void ofApp::keyPressed(int key) {
    switch (key) {
        case 's': paddleLeft.moveUp(fieldY); break;
        case 'w': paddleLeft.moveDown(fieldY, fieldHeight); break;
        case OF_KEY_DOWN: paddleRight.moveUp(fieldY); break;
        case OF_KEY_UP: paddleRight.moveDown(fieldY, fieldHeight); break;
        case '1': viewMode = 0; break;
        case '2': viewMode = 1; break;

        // META 2: Iluminação

        // Ligar/desligar fontes de luz
        case 'a': ambientOn = !ambientOn; break;
        case 'p': pointOn = !pointOn; break;
        case 'd': dirOn = !dirOn; break;
        case 'f': spotOn = !spotOn; break;

        // Ligar/desligar componentes das fontes de luz
        
        // Controlar componentes das luzes direcionais
        case 'j': ambientCompDir = !ambientCompDir; break;
        case 'k': diffuseCompDir = !diffuseCompDir; break;
        case 'l': specularCompDir = !specularCompDir; break;

		// Controlar componentes das luzes pontuais
        case 'z': ambientCompPoint = !ambientCompPoint; break;
        case 'x': diffuseCompPoint = !diffuseCompPoint; break;
        case 'c': specularCompPoint = !specularCompPoint; break;

        // Controlar componentes das luzes de foco
        case 'v': ambientCompSpot = !ambientCompSpot; break;
        case 'b': diffuseCompSpot = !diffuseCompSpot; break;
        case 'n': specularCompSpot = !specularCompSpot; break;

		// Mudar o material do campo
        case OF_KEY_RIGHT:
            mat++;
            switch (mat) {
                case 0: customMat = true; break;
				case 1: customMat = true; break;
				case 2: customMat = true; break;
				case 3: customMat = true; break;
				case 4: customMat = false; break;
				case 5: customMat = false; break;
				case 6: customMat = false; break;
                default: mat = 0; customMat = true; break;
            }
            break;
        case OF_KEY_LEFT:
            mat--;
            switch (mat) {
			    case 6: customMat = false; break;
			    case 5: customMat = false; break;
			    case 4: customMat = false; break;
			    case 3: customMat = true; break;
				case 2: customMat = true; break;
				case 1: customMat = true; break;
				case 0: customMat = true; break;
				default: mat = 4; customMat = false; break;
            }
            break;
    }
}

void ofApp::img(int nr) {
    glEnable(GL_TEXTURE);

	if (nr == 1) img1.bind();
	else if (nr == 2) img2.bind();
	else img3.bind();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    // Configuração para tiling apenas para a imagem 3
    if (nr == 3) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Filtro de ampliação (GL_LINEAR - interpolação linear entre texels próximos suaviza a textura reduzida)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // Filtro de redução
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // Parâmetro de repetição (S - direção horizontal) (GL_REPEAT - textura repete-se indefinidamente)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       // Parâmetro de repetição (T - direção vertical)
    }
    else { // Sem repetição para outras imagens
        glTexParameteri(GL_TEXTURE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE, GL_TEXTURE_WRAP_S, GL_CLAMP);           // As bordas da textura são esticadas para preencher áreas fora do intervalo [0, 1]
        glTexParameteri(GL_TEXTURE, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }
 
    glPushMatrix();
    glScalef(fieldWidth, fieldHeight, 1.);

    glBegin(GL_QUADS);
    if (nr == 1 || nr == 2) glNormal3f(0, 0, 1);    // Direção da normal para as texturas

    if (nr == 3) {
        glTexCoord2f(0., 0.);       // Coordenada de textura
        glVertex3f(-0.5, 0.5, 0);   // vertex(x, y, z) canto sup. esquerdo

        glTexCoord2f(0., 2);        // Coordenada de textura
        glVertex3f(-0.5, -0.5, 0);  // vertex(x, y, z) canto inf. esquerdo

        glTexCoord2f(2, 2);         // Coordenada de textura
        glVertex3f(0.5, -0.5, 0);   // vertex(x, y, z)  canto inf. direito

        glTexCoord2f(2, 0.);        // Coordenada de textura
        glVertex3f(0.5, 0.5, 0);    // vertex(x, y, z) canto sup. direito
    } else {
        glTexCoord2f(0, 0);         // Coordenada de textura
        glVertex3f(-0.5, 0.5, 0);   // vertex(x, y, z)

        glTexCoord2f(0, 1);         // Coordenada de textura
        glVertex3f(-0.5, -0.5, 0);  // vertex(x, y, z)

        glTexCoord2f(1, 1);         // Coordenada de textura
        glVertex3f(0.5, -0.5, 0);   // vertex(x, y, z)

        glTexCoord2f(1, 0);         // Coordenada de textura
        glVertex3f(0.5, 0.5, 0);    // vertex(x, y, z)
    }
    glEnd();
    glPopMatrix();

    if (nr == 1) img1.unbind();
    else if (nr == 2) img2.unbind();
	else img3.unbind();

    glDisable(GL_TEXTURE);
}
