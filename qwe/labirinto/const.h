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

//#define G					0.0981
#define G					0.045

#define DEBUG					1
#define STEP					1

#define DELAY_MOVIMENTO			6.5
#define TAMANHO_ARENA			100
#define TAMANHO_PAREDE			1

#define	GAP						25

#define NUM_JANELAS             2
#define JANELA_P1               0
#define JANELA_P2				1

#define SKY_SIZE				120
#define MAZE_HEIGHT			    TAMANHO_ARENA
#define MAZE_WIDTH			    TAMANHO_ARENA

#define EYE_ROTACAO			    1

#define DISTANCIA_CAMERA		2


/**************************************
***			Texturas				***
**************************************/

#ifdef _WIN32
#define NOME_TEXTURA_CUBOS        "texturas\\cubo.bmp"
#else
#define NOME_TEXTURA_CUBOS        "texturas\\cubo.jpg"
#endif

//#define NOME_TEXTURA_CHAO			"texturas\\chao.jpg"
#define NOME_TEXTURA_CHAO				"texturas\\floor.jpg"
#define NOME_TEXTURA_CASA				"texturas\\house.jpg"
#define NOME_TEXTURA_TELHADO			"texturas\\roof.jpg"
#define NOME_TEXTURA_PAREDE				"texturas\\wall.jpg"
#define NOME_TEXTURA_PAREDE2			"texturas\\wall2.jpg"
#define NOME_TEXTURA_SKY				"texturas\\sky.jpg"
#define NOME_TEXTURA_SKY_NIGHT			"texturas\\night_sky.jpg"

#define NOME_TEXTURA_TANQUE_HEXA		"texturas\\hexa_camo.jpg"
#define NOME_TEXTURA_TANQUE_CAMO		"texturas\\camo.jpg"
#define NOME_TEXTURA_TANQUE_DESERT		"texturas\\desert_camo.jpg"
#define NOME_TEXTURA_TANQUE_STRIPE		"texturas\\stripe_camo.jpg"
#define NOME_TEXTURA_TANQUE_TIGER		"texturas\\tiger.jpg"
#define NOME_TEXTURA_TANQUE_TIGER2		"texturas\\tiger2.jpg"


#define NUM_TEXTURAS				14

#define ID_TEXTURA_CUBOS			0
#define ID_TEXTURA_CHAO				1
#define ID_TEXTURA_CASA				2
#define ID_TEXTURA_TELHADO			3
#define ID_TEXTURA_PAREDE			4
#define ID_TEXTURA_PAREDE2			5
#define ID_TEXTURA_SKY				6
#define ID_TEXTURA_SKY_NIGHT		7

#define ID_TEXTURA_TANQUE_HEXA		8
#define ID_TEXTURA_TANQUE_CAMO		9
#define ID_TEXTURA_TANQUE_DESERT	10
#define ID_TEXTURA_TANQUE_STRIPE	11
#define ID_TEXTURA_TANQUE_TIGER		12
#define ID_TEXTURA_TANQUE_TIGER2	13



/**************************************
***		Dimensoes Tanque			***
**************************************/
/*
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
*/

#define LARGURA_BASE        0.57142
#define COMPRIMENTO_BASE    1
#define ALTURA_BASE         0.14285

#define LARGURA_TORRE		0.28571
#define COMPRIMENTO_TORRE   0.28571
#define ALTURA_TORRE        0.07142

#define METADE_BASE  COMPRIMENTO_BASE/2
#define METADE_LARGURA_BASE LARGURA_BASE / 2
#define METADE_ALTURA (ALTURA_TORRE+ALTURA_BASE)/2

#define COMPRIMENTO_CANHAO  0.57142
#define RAIO_CANHAO         0.05714

#define RAIO_ESCUDO			0.6
#define RAIO_BULLET			0.1



/**************************************
***		Settings Adicionais			***
**************************************/

#define HEALTH				100
#define SHIELD				100
#define POWER				50
#define NUM_BULLETS			5

#define POWER_BOOST			0.25
#define SPEED_BOOST			0.25
#define SHIELD_ALPHA		0.25

#define RELOAD_TIME			1 * (1000 / DELAY_MOVIMENTO)
#define SPEED_TIME			5 * (1000 / DELAY_MOVIMENTO)
#define POWER_TIME			5 * (1000 / DELAY_MOVIMENTO)


/**************************************
***			Labirinto				***
**************************************/

#define LAB_VAZIO			' '
#define LAB_PAREDE			'w'
#define LAB_LIMITE			'W'
#define LAB_HOUSE			'H'
#define LAB_HOUSE2			'h'
#define LAB_T1				'T'
#define LAB_T2				't'

#define	LAB_SHILED			'S'
#define	LAB_SHILED_OFF		's'
#define	LAB_POWER			'P'
#define	LAB_POWER_OFF		'p'
#define	LAB_SPEED			'V'
#define	LAB_SPEED_OFF		'v'


/**************************************
***			Constantes				***
**************************************/

#define K					0.1

#define MIN_VEL				0
#define ACCEL_TANQUE		0.01
#define DECEL_TANQUE		0.03
#define VEL_ROTACAO			1
#define VEL_ROTACAO_TORRE	1
#define VEL_ROTACAO_CANHAO	2
#define VEL_BULLET			1

#define MAX_VEL				0.001
#define MAX_ANG_CANHAO		60
#define MIN_ANG_CANHAO		0
