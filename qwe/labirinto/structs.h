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
	GLfloat		x, y;
	GLint       pontuacao;
}Marcador;

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
	//GLfloat		spawnX, spawnY;

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
	Marcador	marcador;

	GLuint		skin;
}Tanque;

typedef struct {
	Pos      eye, center, up;
	GLfloat  dir_long;  // longitude olhar (esq-dir)
	GLfloat  dir_lat;   // latitude olhar	(cima-baixo)
	GLfloat  fov;
}Camera;

typedef struct {
	Camera      camera[NUM_JANELAS];
	GLint       mainWindow, topSubwindow, navigateSubwindow, player1Subwindow, player2Subwindow;
	Teclas      teclas;
	GLboolean	localViewer;
	GLuint		vista[NUM_JANELAS];
	GLboolean   doubleBuffer;
	GLint       delayMovimento;
	GLuint      menu_id;
	GLboolean   menuActivo;
	GLboolean   debug;
	GLboolean   ortho;
}Estado;

typedef struct {
	int width;
	int height;
	char mapa[MAZE_HEIGHT][MAZE_WIDTH + 1] = {
		"                   ",
		" WWWWWWWWWWWWWWWWW ",
		" W T             W ",
		" W     P S V     W ",
		" W               W ",
		" W    wwwwwww    W ",
		" W               W ",
		" W               W ",
		" W     Hh        W ",
		" W     hh        W ",
		" W               W ",
		" W          w    W ",
		" W    H     w    W ",
		" W          w    W ",
		" W          w    W ",
		" W            t  W ",
		" WWWWWWWWWWWWWWWWW ",
		"                   "
	};
}Mapa;

typedef struct {
	//GLuint			texID[NUM_JANELAS][NUM_TEXTURAS];
	GLuint			texID[NUM_TEXTURAS];

	GLuint			labirinto[NUM_JANELAS];
	GLuint			chao[NUM_JANELAS];
	GLuint			xMouse;
	GLuint			yMouse;
	GLboolean		andar;
	GLuint			prev;
	//Tanque			tanque;
	Tanque			tanque1;
	Tanque			tanque2;
	GLboolean		parado;
	Mapa			mapa;
	GLint			powerUpRotation;
}Modelo;
