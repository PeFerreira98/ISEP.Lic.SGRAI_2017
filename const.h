#pragma once

/**************************************
***				Math				***
**************************************/

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)


/**************************************
***				Sistema				***
**************************************/

#define G					0.0981

#define DEBUG				1

#define DELAY_MOVIMENTO     6.5
#define TAMANHO_ARENA		20
#define TAMANHO_PAREDE		1

#define	GAP					              25

#define MAZE_HEIGHT			          18
#define MAZE_WIDTH			          18

#define	OBJECTO_ALTURA		      0.4
#define OBJECTO_VELOCIDADE	      0.5
#define OBJECTO_ROTACAO		        5
#define OBJECTO_RAIO		      0.12
#define SCALE_HOMER               0.005
#define EYE_ROTACAO			        1

#define DISTANCIA_CAMERA		8


/**************************************
***			Texturas				***
**************************************/

#ifdef _WIN32
#define NOME_TEXTURA_CUBOS        "Textura.bmp"
#else
#define NOME_TEXTURA_CUBOS        "Textura.jpg"
#endif

#define NOME_TEXTURA_CHAO         "Chao.jpg"
#define NOME_TEXTURA_TANQUE		  "Tanque.jpg"


#define NUM_TEXTURAS            3
#define ID_TEXTURA_CUBOS        0
#define ID_TEXTURA_CHAO         1
#define ID_TEXTURA_TANQUE		2

#define	CHAO_DIMENSAO		    10

#define NUM_JANELAS             2
#define JANELA_TOP              0
#define JANELA_NAVIGATE         1
#define JANELA_P1               0
#define JANELA_P2				1


/**************************************
***			Labirinto				***
**************************************/

#define LAB_VAZIO			' '
#define LAB_PAREDE			'w'
#define LAB_LIMITE			'W'
#define LAB_HOUSE

#define	LAB_SHILED			'S'
#define	LAB_SHILED_OFF		's'
#define	LAB_POWER			'P'
#define	LAB_POWER_OFF		'p'
#define	LAB_SPEED			'V'
#define	LAB_SPEED_OFF		'v'


/**************************************
***		Dimensoes Tanque			***
**************************************/

#define LARGURA_BASE        4
#define COMPRIMENTO_BASE    7
#define ALTURA_BASE         1

#define LARGURA_TORRE       2
#define COMPRIMENTO_TORRE   2
#define ALTURA_TORRE        0.5


#define COMPRIMENTO_CANHAO  4
#define RAIO_CANHAO         0.4

#define RAIO_ESCUDO			4.2
#define RAIO_BULLET			0.2


/**************************************
***		Settings Adicionais			***
**************************************/

#define HEALTH				100
#define SHIELD				100
#define POWER				50
#define NUM_BULLETS			5

#define POWER_BOOST			0.25
#define SPEED_BOOST			0.25
#define SHIELD_ALPHA		0.5

#define RELOAD_TIME			1 * (1000 / DELAY_MOVIMENTO)
#define SPEED_TIME			5 * (1000 / DELAY_MOVIMENTO)
#define POWER_TIME			5 * (1000 / DELAY_MOVIMENTO)



/**************************************
***			Constantes				***
**************************************/

#define K					0.1

#define MIN_VEL				0
#define ACCEL_TANQUE		0.08
#define DECEL_TANQUE		0.03
#define VEL_ROTACAO			2
#define VEL_ROTACAO_TORRE	2
#define VEL_ROTACAO_CANHAO	2
#define VEL_ROTACAO_RODAS	5
#define VEL_BULLET			2.5

#define MAX_VEL				0.3
#define MAX_ANG_CANHAO		60
#define MIN_ANG_CANHAO		0

//	GLfloat		recoilStrength = 0.7f;
//	GLfloat		curRecoilForce = 0.0f;