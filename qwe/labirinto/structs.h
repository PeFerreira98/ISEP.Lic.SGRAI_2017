#pragma once

#include <GL/glut.h>
#include "const.h"

typedef struct {
	GLboolean   w, a, s, d, t, f, g, h, espaco;
	GLboolean   i, j, k, l, up, down, left, right, score;
}Teclas;

typedef struct {
	GLfloat    x, y, z;
}Pos;

typedef struct {
	GLfloat		x0, y0, z0;
	GLfloat		x, y, z;
	GLfloat		direcao;
	GLfloat		angulo;
	GLint		t;
	GLboolean	IsAlive;
}Bullet;

// almighty tank
typedef struct {
	// Posicao inicial
	GLfloat		spawnX, spawnY;

	// Posicao atual
	GLfloat     x, y;
	GLfloat     velocidade;

	// angulo base (direcao)
	GLfloat     direccao;
	//GLfloat     direccaoRodas;

	// angulo da torre
	GLfloat     angTorre;

	// angulo canhao
	GLfloat     angCanhao;

	// vida
	GLint		health;

	// escudo
	GLint		shield;

	// dano a aplicar
	GLint		power;

	// boost a aplicar ao dano
	GLint		powerBoost;

	// boost a aplicar a velocidade
	GLint		speedBoost;

	GLint		reloadCounter;
	GLint		powerBoostCounter;
	GLint		speedBoostCounter;

	GLboolean	IsShieldActive;
	GLboolean	IsReloading;
	GLboolean	IsPowerBoosted;
	GLboolean	IsSpeedBoosted;

	Bullet		bullets[NUM_BULLETS];

	GLuint		skin;
}Tanque;

typedef struct {
	GLfloat		fov;
	GLint       mainWindow, topSubwindow, navigateSubwindow, player1Subwindow, player2Subwindow;
	Teclas      teclas;
	GLboolean	localViewer;
	GLint       delayMovimento;
	GLuint      menu_id;
	GLboolean   menuActivo;
	GLboolean   debug;
	GLboolean   ortho;
	GLboolean	dia;
	GLboolean   nevoeiro;
}Estado;

typedef struct {
	GLuint			texID[NUM_TEXTURAS];

	GLuint			chao;

	GLuint			xMouse;
	GLuint			yMouse;
	GLboolean		andar;
	GLuint			prev;
	Tanque			tanque1;
	Tanque			tanque2;
	GLboolean		parado;
	GLuint			powerUpRotation;
	GLfloat light_pos[4] = { MAZE_HEIGHT,  MAZE_HEIGHT, 15, 1 };

	char mapa[MAZE_HEIGHT][MAZE_WIDTH + 1] = {
		"                                                                                                    ",
		" WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                               Hhhhhhhhh                                                        W ",
		" W                               hhhhhhhhh                                                        W ",
		" W                               hhhhhhhhh                                                        W ",
		" W                               hhhhhhhhh                                                        W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" W                                                                                                W ",
		" WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW ",
		"                                                                                                    "
	};

}Modelo;
