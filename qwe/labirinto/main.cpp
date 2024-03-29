#include "stdafx.h"

#include "headers.h"

/////////////////////////////////////
//variaveis globais

Estado estado;
Modelo model;
GLfloat mat_w[] = { 0.5, 0.5, 0.5, 0.5 };


////////////////////////////////////
//// Ilumina��o e materiais

void desenhaLuz(float p[])
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(p[0], p[1], p[2]);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_w);
	glutWireCube(0.05);

	glPopMatrix();
	glEnable(GL_LIGHTING);
}


void setLight()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLightfv(GL_LIGHT0, GL_POSITION, model.light_pos);
	desenhaLuz(model.light_pos);


	//light_pos[0] = 1;
	//light_pos[1] = 12;
	//light_pos[2] = 12;
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//desenhaLuz(light_pos);



	//light_pos[0] = 5;
	//light_pos[1] = 20;
	//light_pos[2] = -8;
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//desenhaLuz(light_pos);

	//light_pos[0] = 5;
	//light_pos[1] = 200;
	//light_pos[2] = -8;
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	//desenhaLuz(light_pos);

	//GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	//GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	//// ligar ilumina��o
	//glEnable(GL_LIGHTING);

	//// ligar e definir fonte de luz 0
	//glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, estado.localViewer);
}

void setMaterial()
{
	glColor4f(1, 1, 1, 1);

	GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_shininess = 104;

	// cria��o autom�tica das componentes Ambiente e Difusa do material a partir das cores
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// definir de outros par�metros dos materiais est�ticamente
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}


///////////////////////////////////
//// Redisplays

void reshapePlayerSubwindow(int janela, int width, int height)
{
	// glViewport(botom, left, width, height)
	// define parte da janela a ser utilizada pelo OpenGL
	glViewport(0, 0, (GLint)width, (GLint)height);
	// Matriz Projeccao
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(estado.fov, (GLfloat)width / height, 0.1, 100);
	// Matriz Modelview
	// Matriz onde s�o realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshapePlayer1Subwindow(int width, int height)
{
	reshapePlayerSubwindow(JANELA_P1, width, height);
}

void reshapePlayer2Subwindow(int width, int height)
{
	reshapePlayerSubwindow(JANELA_P2, width, height);
}

void reshapeMainWindow(int width, int height)
{
	GLint w, h;
	w = (width - GAP * 3)*.5;
	h = (height - GAP * 2);


	glutSetWindow(estado.player1Subwindow);
	glutPositionWindow(GAP, GAP);
	glutReshapeWindow(w > h ? h : w, w > h ? h : w);

	glutSetWindow(estado.player2Subwindow);
	glutPositionWindow(width - (GAP + (w > h ? h : w)), GAP);
	glutReshapeWindow(w > h ? h : w, w > h ? h : w);

}

void strokeCenterString(char *str, double x, double y, double z, double s)
{
	int i, n;

	n = strlen(str);
	glPushMatrix();
	glTranslated(x - glutStrokeLength(GLUT_STROKE_ROMAN, (const unsigned char*)str)*0.5*s, y - 119.05*0.5*s, z);
	glScaled(s, s, s);
	for (i = 0; i < n; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)str[i]);
	glPopMatrix();
}


/////////////////////////////////////
//Modelo

GLboolean detectaColisaoBala(Bullet b, GLfloat nx, GLfloat nz, Tanque t)
{

	if (model.mapa[(int)(nx + (MAZE_HEIGHT / 2) + 1)][(int)(nz + (MAZE_WIDTH / 2) + 1)] >= 'W') {
		b.IsAlive = false;

		return GL_TRUE;
	}
	else if (b.x + RAIO_BULLET > t.x - (COMPRIMENTO_BASE / 2.0 * cos(RAD(t.direccao + t.angTorre + 90)))
		&& b.x + RAIO_BULLET < t.x + (COMPRIMENTO_BASE / 2.0 * cos(RAD(t.direccao + t.angTorre + 90)))
		&& b.x + RAIO_BULLET > t.x - (LARGURA_BASE / 2.0 * sin(RAD(t.direccao + t.angTorre + 90)))
		&& b.x + RAIO_BULLET < t.x + (LARGURA_BASE / 2.0 * sin(RAD(t.direccao + t.angTorre + 90)))
		&& b.x + RAIO_BULLET < t.y + ((ALTURA_BASE + ALTURA_TORRE) / 2.0)
		&& b.x + RAIO_BULLET > t.y - ((ALTURA_BASE + ALTURA_TORRE) / 2.0)
		&& b.y + RAIO_BULLET > t.x - (COMPRIMENTO_BASE / 2.0 * cos(RAD(t.direccao + t.angTorre + 90)))
		&& b.y + RAIO_BULLET < t.x + (COMPRIMENTO_BASE / 2.0 * cos(RAD(t.direccao + t.angTorre + 90)))
		&& b.y + RAIO_BULLET > t.x - (LARGURA_BASE / 2.0 * sin(RAD(t.direccao + t.angTorre + 90)))
		&& b.y + RAIO_BULLET < t.x + (LARGURA_BASE / 2.0 * sin(RAD(t.direccao + t.angTorre + 90)))
		&& b.y + RAIO_BULLET < t.y + ((ALTURA_BASE + ALTURA_TORRE) / 2.0)
		&& b.y + RAIO_BULLET > t.y - ((ALTURA_BASE + ALTURA_TORRE) / 2.0)
		&& b.x - RAIO_BULLET > t.x - (COMPRIMENTO_BASE / 2.0 * cos(RAD(t.direccao + t.angTorre + 90)))
		&& b.x - RAIO_BULLET < t.x + (COMPRIMENTO_BASE / 2.0 * cos(RAD(t.direccao + t.angTorre + 90)))
		&& b.x - RAIO_BULLET > t.x - (LARGURA_BASE / 2.0 * sin(RAD(t.direccao + t.angTorre + 90)))
		&& b.x - RAIO_BULLET < t.x + (LARGURA_BASE / 2.0 * sin(RAD(t.direccao + t.angTorre + 90)))
		&& b.x - RAIO_BULLET < t.y + ((ALTURA_BASE + ALTURA_TORRE) / 2.0)
		&& b.x - RAIO_BULLET > t.y - ((ALTURA_BASE + ALTURA_TORRE) / 2.0)
		&& b.y - RAIO_BULLET > t.x - (COMPRIMENTO_BASE / 2.0 * cos(RAD(t.direccao + t.angTorre + 90)))
		&& b.y - RAIO_BULLET < t.x + (COMPRIMENTO_BASE / 2.0 * cos(RAD(t.direccao + t.angTorre + 90)))
		&& b.y - RAIO_BULLET > t.x - (LARGURA_BASE / 2.0 * sin(RAD(t.direccao + t.angTorre + 90)))
		&& b.y - RAIO_BULLET < t.x + (LARGURA_BASE / 2.0 * sin(RAD(t.direccao + t.angTorre + 90)))
		&& b.y - RAIO_BULLET < t.y + ((ALTURA_BASE + ALTURA_TORRE) / 2.0)
		&& b.y - RAIO_BULLET > t.y - ((ALTURA_BASE + ALTURA_TORRE) / 2.0)) {


		// EXPLOSAO + MUDAR TEXTURA/ALTERAR SCORE

	}

	return GL_FALSE;
}


GLboolean detectaColisaoTanque(GLfloat nx, GLfloat ny, Tanque t, Tanque t1)
{
	if (model.mapa[(int)(nx + 9 + 1)][(int)(ny + 9 + 1)] >= 'W' || model.mapa[(int)(nx + 9 + 1)][(int)(ny + 9 + 1)] >= 'w') {

		return GL_TRUE;
	}
	else if (t.x + (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) < t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
		&& t.x + (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) > t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
		&& t.x + (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) > t1.x - (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
			&& t.x + (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) < t1.x + (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
				&& t.x + (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) < t1.y + METADE_ALTURA
					&&  t.x + (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) > t1.y - METADE_ALTURA

						&& t.x - (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) < t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
						&& t.x - (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) > t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
						&& t.x - (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) > t1.x - (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
							&& t.x - (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) < t1.x + (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
								&& t.x - (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) < t1.y + METADE_ALTURA
									&&  t.x - (METADE_BASE * cos(RAD(t.direccao + t.angTorre + 90) > t1.y - METADE_ALTURA

										&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) < t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
									&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) > t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
								&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) > t.x - (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
								&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) < t1.x + (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
								&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) < t1.y + METADE_ALTURA
								&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) > t1.y - METADE_ALTURA

								&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) < t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
							&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) > t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
						&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) > t1.x - (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
						&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) < t1.x + (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
						&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) < t1.y + METADE_ALTURA
						&& t.x - (METADE_LARGURA_BASE * sin(RAD(t.direccao + t.angTorre + 90))) > t1.y - METADE_ALTURA

						&& t.y + METADE_ALTURA < t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
					&& t.y + METADE_ALTURA > t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
				&& t.y + METADE_ALTURA > t1.x - (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
				&& t.y + METADE_ALTURA < t1.x + (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
				&& t.y + METADE_ALTURA < t1.y + METADE_ALTURA
				&& t.y + METADE_ALTURA > t1.y - METADE_ALTURA

				&& t.y - METADE_ALTURA < t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
			&& t.y - METADE_ALTURA > t1.x + (METADE_BASE * cos(RAD(t1.direccao + t1.angTorre + 90)))))
		&& t.y - METADE_ALTURA > t1.x - (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
		&& t.y - METADE_ALTURA < t1.x + (METADE_LARGURA_BASE * sin(RAD(t1.direccao + t1.angTorre + 90)))
		&& t.y - METADE_ALTURA < t1.y + METADE_ALTURA
		&& t.y - METADE_ALTURA > t1.y - METADE_ALTURA

		) {
		return GL_TRUE;
	}

	return GL_FALSE;
}

void desenhaPoligono(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], GLfloat texCoord[])
{
	glBegin(GL_POLYGON);
	glNormal3fv(normal);
	glTexCoord2f(texCoord[1], texCoord[1]);
	glVertex3fv(a);
	glTexCoord2f(texCoord[0], texCoord[1]);
	glVertex3fv(b);
	glTexCoord2f(texCoord[0], texCoord[0]);
	glVertex3fv(c);
	glTexCoord2f(texCoord[1], texCoord[0]);
	glVertex3fv(d);
	glEnd();
}

void desenhaCubo(GLuint texID, GLfloat texS, GLfloat texT)
{
	GLfloat vertices[][3] = { { -0.5,-0.5,-0.5 },
	{ 0.5,-0.5,-0.5 },
	{ 0.5,0.5,-0.5 },
	{ -0.5,0.5,-0.5 },
	{ -0.5,-0.5,0.5 },
	{ 0.5,-0.5,0.5 },
	{ 0.5,0.5,0.5 },
	{ -0.5,0.5,0.5 } };
	GLfloat normais[][3] = {
		{ 0,0,-1 },
		{ 0,1,0 },
		{ -1,0,0 },
		{ 1,0,0 },
		{ 0,0,1 },
		{ 0,-1,0 }
		// acrescentar as outras normais...
	};


	glBindTexture(GL_TEXTURE_2D, texID);
	GLfloat textCoord[] = { texS, texT };

	desenhaPoligono(vertices[1], vertices[0], vertices[3], vertices[2], normais[0], textCoord);
	desenhaPoligono(vertices[2], vertices[3], vertices[7], vertices[6], normais[1], textCoord);
	desenhaPoligono(vertices[3], vertices[0], vertices[4], vertices[7], normais[2], textCoord);
	desenhaPoligono(vertices[6], vertices[5], vertices[1], vertices[2], normais[3], textCoord);
	desenhaPoligono(vertices[4], vertices[5], vertices[6], vertices[7], normais[4], textCoord);
	desenhaPoligono(vertices[5], vertices[4], vertices[0], vertices[1], normais[5], textCoord);

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void desenhaCubo() // default
{
	desenhaCubo(model.texID[ID_TEXTURA_CUBOS], 0, 0.25);
}

//void desenhaBussola(int width, int height)  // largura e altura da janela
//{

// Altera viewport e projec��o para 2D (copia de um reshape de um projecto 2D)

//....

// Blending (transparencias)
/*  glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glDisable(GL_LIGHTING);
glDisable(GL_DEPTH_TEST);
glDisable(GL_COLOR_MATERIAL);
*/

//desenha bussola 2D

//glColor3f(1,0.4,0.4);
//strokeCenterString("N", 0, 20, 0 , 0.1); // string, x ,y ,z ,scale


// rop�e estado
/* glDisable(GL_BLEND);
glEnable(GL_LIGHTING);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_DEPTH_TEST);
*/

//rep�e projec��o chamando redisplay
//reshapeNavigateSubwindow(width, height);

//}

//void desenhaModeloDir(objecto_t obj, int width, int height)
//{
// Altera viewport e projec��o
//....

// Blending (transparencias)
/*
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glDisable(GL_LIGHTING);
glDisable(GL_DEPTH_TEST);
*/

//desenha Seta

// rop�e estado
/*  glDisable(GL_BLEND);
glEnable(GL_LIGHTING);
glEnable(GL_DEPTH_TEST);
*/
//rep�e projec��o chamando redisplay
//reshapeTopSubwindow(width, height);
//}

//void desenhaAngVisao(Camera *cam)
//{
//GLfloat ratio;
//ratio = (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT); // propor��o 
//glEnable(GL_BLEND);
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//glDepthMask(GL_FALSE);

//glPushMatrix();
//glTranslatef(cam->eye.x, OBJECTO_ALTURA, cam->eye.z);
//glColor4f(0, 0, 1, 0.2);
//glRotatef(GRAUS(cam->dir_long), 0, 1, 0);

//glBegin(GL_TRIANGLES);
//glVertex3f(0, 0, 0);
//glVertex3f(5 * cos(RAD(cam->fov*ratio*0.5)), 0, -5 * sin(RAD(cam->fov*ratio*0.5)));
//glVertex3f(5 * cos(RAD(cam->fov*ratio*0.5)), 0, 5 * sin(RAD(cam->fov*ratio*0.5)));
//glEnd();
//glPopMatrix();

//glDepthMask(GL_TRUE);
//glDisable(GL_BLEND);
//}


void desenhaBullet(Bullet b)
{
	glPushMatrix();

	glTranslatef(b.x, b.y, b.z);
	glColor3f(1, 1, 1);
	glutSolidSphere(RAIO_BULLET, 16, 8);

	glPopMatrix();
}

void desenhaBalas(Tanque t)
{
	int i;
	for (i = 0; i < NUM_BULLETS; i++)
	{
		if (model.tanque1.bullets[i].IsAlive)
		{
			desenhaBullet(t.bullets[i]);
		}
	}
}

void desenhaShield()
{
	glPushMatrix();
	glScalef(0.92, 1, 0.3);
	// enable blending.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// choosing color and alpha
	glColor4f(0, 77, 232, SHIELD_ALPHA);
	glutSolidSphere(RAIO_ESCUDO, 32, 16);

	// disable blending
	glDisable(GL_BLEND);
	glColor4f(1, 1, 1, 1);

	glPopMatrix();
}

void desenhaTanque(Tanque t)
{
	glPushMatrix();

	// base
	glTranslatef(t.x, t.y, ALTURA_BASE / 2.0);
	glRotatef(t.direccao, 0, 0, 1); //tanque
	glPushMatrix();
	glScalef(LARGURA_BASE, COMPRIMENTO_BASE, ALTURA_BASE);
	desenhaCubo(model.texID[t.skin], 0, 1);
	glPopMatrix();

	glPushMatrix();

	// torre
	glRotatef(t.angTorre, 0, 0, 1);					//rodar torre + canhao
	glTranslatef(0, 0, ALTURA_BASE / 2.0 + ALTURA_TORRE / 2.0);
	glPushMatrix();
	glScalef(LARGURA_TORRE, COMPRIMENTO_TORRE, ALTURA_TORRE);
	desenhaCubo(model.texID[t.skin], 0, 1);
	glPopMatrix();

	// canhao
	glTranslatef(0, COMPRIMENTO_TORRE / 2.0, 0);	//andar ate ao limite da torre
	glRotatef(t.angCanhao, 1, 0, 0);				//rodar canhao
	glTranslatef(0, COMPRIMENTO_CANHAO / 2.0, 0);	//mover o canhao
	glPushMatrix();
	glScalef(RAIO_CANHAO, COMPRIMENTO_CANHAO, RAIO_CANHAO);
	desenhaCubo(model.texID[t.skin], 0, 1);
	glPopMatrix();

	glPopMatrix();

	if (t.IsShieldActive)
	{
		desenhaShield();
	}
	glPopMatrix();
}


// Mapa

void desenhaSky(GLuint tex)
{

	float x, y, z;

	//x = CHAO_DIMENSAO / 2, y = CHAO_DIMENSAO / 2, z = 0;
	x = 0, y = 0, z = 0;

	// Center the Skybox around the given x,y,z position
	x = x - SKY_SIZE / 2;
	y = y - SKY_SIZE / 2;
	z = z - SKY_SIZE / 2;

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, model.texID[ID_TEXTURA_SKY]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + SKY_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + SKY_SIZE, z + SKY_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + SKY_SIZE, y + SKY_SIZE, z + SKY_SIZE);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + SKY_SIZE, y, z + SKY_SIZE);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, model.texID[ID_TEXTURA_SKY]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + SKY_SIZE, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + SKY_SIZE, y + SKY_SIZE, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + SKY_SIZE, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, model.texID[ID_TEXTURA_SKY]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + SKY_SIZE, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + SKY_SIZE, z + SKY_SIZE);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + SKY_SIZE);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, model.texID[ID_TEXTURA_SKY]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + SKY_SIZE, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + SKY_SIZE, y, z + SKY_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + SKY_SIZE, y + SKY_SIZE, z + SKY_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + SKY_SIZE, y + SKY_SIZE, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, model.texID[ID_TEXTURA_SKY]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + SKY_SIZE, y + SKY_SIZE, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + SKY_SIZE, y + SKY_SIZE, z + SKY_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + SKY_SIZE, z + SKY_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + SKY_SIZE, z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, model.texID[ID_TEXTURA_SKY]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + SKY_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + SKY_SIZE, y, z + SKY_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + SKY_SIZE, y, z);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, NULL);
}

void desenhaPowerUpSymbol()
{
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(model.powerUpRotation, 0, 0, 1);
	glScalef(0.5, 0.5, 0.5);
	glutSolidOctahedron();
	glPopMatrix();
}

void desenhaPowerUp() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// choosing color and alpha
	glColor4f(232, 0, 0, SHIELD_ALPHA);
	desenhaPowerUpSymbol();

	// disable blending
	glDisable(GL_BLEND);
	glColor4f(1, 1, 1, 1);
}

void desenhaSpeedUp() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// choosing color and alpha
	glColor4f(0, 232, 77, SHIELD_ALPHA);
	desenhaPowerUpSymbol();

	// disable blending
	glDisable(GL_BLEND);
	glColor4f(1, 1, 1, 1);
}

void desenhaShieldUp() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// choosing color and alpha
	glColor4f(0, 77, 232, SHIELD_ALPHA);
	desenhaPowerUpSymbol();

	// disable blending
	glDisable(GL_BLEND);
	glColor4f(1, 1, 1, 1);
}

void desenhaCasa(GLfloat x, GLfloat y)
{
	glPushMatrix();
	glTranslatef(x / 2.0, y / 2.0, 0);
	glScalef(x, y, 1);

	glBindTexture(GL_TEXTURE_2D, model.texID[ID_TEXTURA_CASA]);
	desenhaCubo(model.texID[ID_TEXTURA_CASA], 0, 1);
	glTranslatef(0, 0, 0.5);

	glBindTexture(GL_TEXTURE_2D, model.texID[ID_TEXTURA_TELHADO]);
	glRotatef(45, 0, 0, 1);
	GLfloat scale = sqrtf(2) / 2.0;
	glScalef(scale, scale, scale);
	glutSolidOctahedron();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();
}

void desenhaParede()
{
	desenhaCubo(model.texID[ID_TEXTURA_PAREDE], 0, 1);
}

void desenhaLimite()
{
	glPushMatrix();
	desenhaParede();
	glTranslatef(0, 0, 1);
	desenhaParede();
	glPopMatrix();
}


void desenhaLabirintoElemento(char element, int x, int y)
{
	switch (element)
	{
	case LAB_LIMITE:
		desenhaLimite();
		break;
	case LAB_PAREDE:
		desenhaParede();
		break;
	case LAB_SHILED:
		desenhaShieldUp();
		break;
	case LAB_SPEED:
		desenhaSpeedUp();
		break;
	case LAB_POWER:
		desenhaPowerUp();
		break;
	case LAB_HOUSE:
		int sizeX = 1, sizeY = 1;
		int cx = 0, cy = 1;
		while (true)
		{
			if (model.mapa[x + cx][y + cy] == LAB_HOUSE2)
			{
				cy++;
				sizeY = cy > sizeY ? cy : sizeY;
			}
			else
			{
				if (model.mapa[x + cx + 1][y] == LAB_HOUSE2)
				{
					cx++;
					cy = 0;
				}
				else
				{
					break;
				}
			}
		}
		sizeX += cx;
		desenhaCasa(sizeX, sizeY);
		break;
	}
}

void desenhaLabirinto()
{
	// c�digo para desenhar o labirinto
	int i, j;

	for (i = 0; i < MAZE_HEIGHT; i++)
	{
		for (j = 0; j < MAZE_WIDTH; j++)
		{
			if (model.mapa[i][j] != LAB_VAZIO)
			{
				glPushMatrix();
				glTranslatef(j - (MAZE_WIDTH / 2), i - (MAZE_HEIGHT / 2), 0.5);
				desenhaLabirintoElemento(model.mapa[i][j], i, j);
				glPopMatrix();
			}
		}
	}
}

void desenhaNevoeiro() {
	GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

	if (estado.nevoeiro) {
		glFogi(GL_FOG_MODE, GL_EXP2);        // Fog Mode
		glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
		glFogf(GL_FOG_DENSITY, 0.25f);              // How Dense Will The Fog Be
		glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
		glFogf(GL_FOG_START, 1.0f);             // Fog Start Depth
		glFogf(GL_FOG_END, 10.0f);               // Fog End Depth
		glEnable(GL_FOG);
	}
	else {
		glDisable(GL_FOG);
	}
}

void desenhaChao()
{
	// c�digo para desenhar o ch�o
	int i, j;
	glBindTexture(GL_TEXTURE_2D, model.texID[ID_TEXTURA_CHAO]);

	glColor3f(1.0f, 1.0f, 1.0f);
	for (i = -TAMANHO_ARENA / 2.0; i <= TAMANHO_ARENA / 2.0; i += STEP)
		for (j = -TAMANHO_ARENA / 2.0; j <= TAMANHO_ARENA / 2.0; j += STEP)
		{
			//char e = model.mapa[i][j];
			//if (e == LAB_POWER)
			//	glColor4i(255, 0, 0, 1);
			//else if (e == LAB_SHILED)
			//	glColor4i(0, 0, 255, 1);
			//else if (e == LAB_SPEED)
			//	glColor4i(0, 255, 0, 1);
			//else
			//	glColor4i(255, 255, 255, 1);

			glBegin(GL_POLYGON);
			glNormal3f(0, 0, 1);

			glTexCoord2f(1, 1);
			glVertex3f(i + STEP, j + STEP, 0);

			glTexCoord2f(0, 1);
			glVertex3f(i, j + STEP, 0);

			glTexCoord2f(0, 0);
			glVertex3f(i, j, 0);

			glTexCoord2f(1, 0);
			glVertex3f(i + STEP, j, 0);

			glEnd();
		}
	glColor4i(255, 255, 255, 1);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void desenhaModels()
{
	glPushMatrix();
	desenhaSky(estado.dia ? model.texID[ID_TEXTURA_SKY] : model.texID[ID_TEXTURA_SKY_NIGHT]);
	desenhaLabirinto();
	desenhaTanque(model.tanque1); //player1 window2

	int i;
	for (i = 0; i < NUM_BULLETS; i++)
	{
		if (model.tanque1.bullets[i].IsAlive)
		{
			glPushMatrix();
			desenhaBullet(model.tanque1.bullets[i]);
			glPopMatrix();
		}
	}
	glPopMatrix();

	glPushMatrix();
	desenhaTanque(model.tanque2); //player1 window2

	for (i = 0; i < NUM_BULLETS; i++)
	{
		if (model.tanque2.bullets[i].IsAlive)
		{
			glPushMatrix();
			desenhaBullet(model.tanque2.bullets[i]);
			glPopMatrix();
		}
	}
	glPopMatrix();

	glPushMatrix();
	desenhaNevoeiro();
	glPopMatrix();
}


/////////////////////////////////////

void setPlayerSubwindowCamera(Tanque *t)
{
	GLfloat eyex = t->x + cos(RAD(t->direccao + t->angTorre - 90)) * cos(RAD(t->angCanhao)) * DISTANCIA_CAMERA;
	GLfloat eyey = t->y + sin(RAD(t->direccao + t->angTorre - 90)) * cos(RAD(t->angCanhao)) * DISTANCIA_CAMERA;
	GLfloat eyez = (ALTURA_BASE + ALTURA_TORRE) + 1 /*+ sin(RAD(-t->angCanhao)) * DISTANCIA_CAMERA*/;

	GLfloat centerx = t->x + (COMPRIMENTO_TORRE / 2.0 + (COMPRIMENTO_CANHAO * cos(RAD(t->angCanhao))))* cos(RAD(t->direccao + t->angTorre + 90));
	GLfloat centery = t->y + (COMPRIMENTO_TORRE / 2.0 + (COMPRIMENTO_CANHAO * cos(RAD(t->angCanhao))))* sin(RAD(t->direccao + t->angTorre + 90));
	GLfloat centerz = ALTURA_BASE + (ALTURA_TORRE / 2.0) + COMPRIMENTO_CANHAO * sin(RAD(t->angCanhao)) + 1;

	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, 0, 0, 1);
}

void displayPlayer1Subwindow()
{
	setPlayerSubwindowCamera(&model.tanque1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	setPlayerSubwindowCamera(&model.tanque1); //player1 window2

	setLight();

	glCallList(model.chao);

	desenhaModels();

	glutSwapBuffers();
}

void displayPlayer2Subwindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	setPlayerSubwindowCamera(&model.tanque2);  //player2 window2

	setLight();

	glCallList(model.chao);

	desenhaModels();

	glutSwapBuffers();
}


/////////////////////////////////////
//mainWindow

void redisplayAll(void)
{

	glutSetWindow(estado.mainWindow);
	glutPostRedisplay();
	glutSetWindow(estado.player1Subwindow);
	glutPostRedisplay();
	glutSetWindow(estado.player2Subwindow);
	glutPostRedisplay();
}

void displayMainWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}



void TimerMovTanque1() {

	// canhao
	if (estado.teclas.g)
	{
		canonDown(&model.tanque1);
	}
	if (estado.teclas.t)
	{
		canonUp(&model.tanque1);
	}

	// torre
	if (estado.teclas.f)
	{
		towerLeft(&model.tanque1);
	}
	if (estado.teclas.h)
	{
		towerRight(&model.tanque1);
	}

	// tanque
	if (estado.teclas.a)
	{
		tankLeft(&model.tanque1);
	}
	if (estado.teclas.d)
	{
		tankRight(&model.tanque1);
	}

	if (estado.teclas.w)	// W ativo
	{
		tankFront(&model.tanque1);
	}
	else if (!estado.teclas.s)	// W + S inativo
	{
		tankSlowDown(&model.tanque1);
	}

	if (estado.teclas.s)	// S ativo
	{
		tankBack(&model.tanque1);
	}


}


void TimerMovTanque2() {

	// canhao
	if (estado.teclas.down)
	{
		canonDown(&model.tanque2);
	}
	if (estado.teclas.up)
	{
		canonUp(&model.tanque2);
	}

	// torre
	if (estado.teclas.left)
	{
		towerLeft(&model.tanque2);
	}
	if (estado.teclas.right)
	{
		towerRight(&model.tanque2);
	}

	// tanque
	if (estado.teclas.j)
	{
		tankLeft(&model.tanque2);
	}
	if (estado.teclas.l)
	{
		tankRight(&model.tanque2);
	}

	if (estado.teclas.i)	// i ativo
	{
		tankFront(&model.tanque2);
	}
	else if (!estado.teclas.k)	// i + k inativo
	{
		tankSlowDown(&model.tanque2);
	}

	if (estado.teclas.k)	// k ativo
	{
		tankBack(&model.tanque2);
	}


}

void Timer(int value)
{
	GLfloat nx1 = 0, ny1 = 0, nz1 = 0;
	GLfloat nx2 = 0, ny2 = 0, nz2 = 0;

	glutTimerFunc(estado.delayMovimento, Timer, 0);

	model.prev++;
	if (model.prev % 60000 == 0)
	{
		if (estado.dia)
			if (estado.nevoeiro)
				estado.dia = false;
			else
				estado.nevoeiro = true;
		else
			if (estado.nevoeiro)
				estado.nevoeiro = false;
			else
				estado.dia = true;
	}

	if (model.powerUpRotation++ == 360) model.powerUpRotation = 0;


	//if (estado.menuActivo || model.parado) // sair em caso de o jogo estar parado ou menu estar activo
	//	return;

	TimerMovTanque1();
	TimerMovTanque2();

	if (estado.teclas.espaco)
	{
		if (shoot(&model.tanque1)) PlaySound("sounds\\fire.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

	if (estado.teclas.score)
	{
		if (shoot(&model.tanque2)) PlaySound("sounds\\fire.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

	if (model.tanque1.IsReloading)
	{
		(&model.tanque1)->reloadCounter--;
		(&model.tanque1)->IsReloading = model.tanque1.reloadCounter > 0;
	}

	if (model.tanque2.IsReloading)
	{
		(&model.tanque2)->reloadCounter--;
		(&model.tanque2)->IsReloading = model.tanque2.reloadCounter > 0;
	}

	if (model.tanque1.IsPowerBoosted)
	{
		(&model.tanque1)->powerBoostCounter--;
		(&model.tanque1)->IsPowerBoosted = model.tanque1.powerBoostCounter <= 0;
	}

	if (model.tanque2.IsPowerBoosted)
	{
		(&model.tanque2)->powerBoostCounter--;
		(&model.tanque2)->IsPowerBoosted = model.tanque2.powerBoostCounter <= 0;
	}

	if (model.tanque1.IsSpeedBoosted)
	{
		(&model.tanque1)->speedBoostCounter--;
		(&model.tanque1)->IsSpeedBoosted = model.tanque1.speedBoostCounter <= 0;
	}

	if (model.tanque2.IsSpeedBoosted)
	{
		(&model.tanque2)->speedBoostCounter--;
		(&model.tanque2)->IsSpeedBoosted = model.tanque2.speedBoostCounter <= 0;
	}

	nx1 = model.tanque1.x;
	ny1 = model.tanque1.y;
	updateTank(&model.tanque1);

	nx2 = model.tanque2.x;
	ny2 = model.tanque2.y;
	updateTank(&model.tanque2);


	nx1 = model.tanque2.x;
	ny1 = model.tanque2.y;
	updateTank(&model.tanque2);



	//Colisao Bullet
	for (int i = 0; i < NUM_BULLETS; i++) {
		if (detectaColisaoBala((&model.tanque1)->bullets[i], (&model.tanque1)->bullets[i].x, (&model.tanque1)->bullets[i].y, (model.tanque1))) {
			printf("colision detected bullet %d\n", i); //FIXME return always true
														//PlaySound("sounds\\impact.wav", NULL, SND_ASYNC | SND_FILENAME);
		}
	}

	for (int i = 0; i < NUM_BULLETS; i++) {
		detectaColisaoBala((&model.tanque2)->bullets[i], (&model.tanque2)->bullets[i].x, (&model.tanque2)->bullets[i].y, (model.tanque2));
	}

	//Colisao Tanque
	if (detectaColisaoTanque(model.tanque1.x, model.tanque1.y, model.tanque1, model.tanque2)) {
		model.tanque1.x = nx1;
		model.tanque1.y = ny1;

		printf("wall colision detected \n"); //FIX ME detects colision middle map
											 //PlaySound("sounds\\wallhit.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

	if (detectaColisaoTanque(model.tanque1.x, model.tanque1.y, model.tanque1, model.tanque2)) {

		model.tanque2.x = nx1;
		model.tanque2.y = ny1;
	}


	redisplayAll();
}


void imprime_ajuda(void)
{
	printf("\n\nDesenho de um quadrado\n");
	printf("h,H - Ajuda \n");
	printf("******* Diversos ******* \n");
	printf("l,L - Alterna o calculo luz entre Z e eye (GL_LIGHT_MODEL_LOCAL_VIEWER)\n");
	printf("w,W - Wireframe \n");
	printf("f,F - Fill \n");
	printf("******* Movimento ******* \n");
	printf("up  - Acelera \n");
	printf("down- Trava \n");
	printf("left- Vira rodas para a direita\n");
	printf("righ- Vira rodas para a esquerda\n");
	printf("******* Camara ******* \n");
	printf("F1 - Alterna camara da janela da Esquerda \n");
	printf("F2 - Alterna camara da janela da Direita \n");
	printf("PAGE_UP, PAGE_DOWN - Altera abertura da camara \n");
	printf("botao esquerdo + movimento na Janela da Direita altera o olhar \n");
	printf("ESC - Sair\n");
}



////////////////////////////////////
// Teclas

void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(1);
		break;

	case 'W':
	case 'w': estado.teclas.w = GL_TRUE;
		break;
	case 'S':
	case 's': estado.teclas.s = GL_TRUE;
		break;
	case 'A':
	case 'a': estado.teclas.a = GL_TRUE;
		break;
	case 'D':
	case 'd': estado.teclas.d = GL_TRUE;
		break;

	case 'T':
	case 't': estado.teclas.t = GL_TRUE;
		break;
	case 'G':
	case 'g': estado.teclas.g = GL_TRUE;
		break;
	case 'F':
	case 'f': estado.teclas.f = GL_TRUE;
		break;
	case 'H':
	case 'h': estado.teclas.h = GL_TRUE;
		break;

	case ' ': estado.teclas.espaco = GL_TRUE;
		break;

	case 'I':
	case 'i': estado.teclas.i = GL_TRUE;
		break;
	case 'K':
	case 'k': estado.teclas.k = GL_TRUE;
		break;
	case 'J':
	case 'j': estado.teclas.j = GL_TRUE;
		break;
	case 'L':
	case 'l': estado.teclas.l = GL_TRUE;
		break;

	case '-': estado.teclas.score = GL_TRUE;
		break;

	case 'p':
	case 'P':
		glutSetWindow(estado.player1Subwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_TEXTURE_2D);
		glutSetWindow(estado.player2Subwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_TEXTURE_2D);
		break;
	case 'o':
	case 'O':
		glutSetWindow(estado.player1Subwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_TEXTURE_2D);
		glutSetWindow(estado.player2Subwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_TEXTURE_2D);
		break;
	}

}

void KeyUp(unsigned char key, int x, int y)
{
	switch (key) {
		// ... accoes sobre largar teclas ... 
	case 'W':
	case 'w': estado.teclas.w = GL_FALSE;
		break;
	case 'A':
	case 'a': estado.teclas.a = GL_FALSE;
		break;
	case 'S':
	case 's': estado.teclas.s = GL_FALSE;
		break;
	case 'D':
	case 'd': estado.teclas.d = GL_FALSE;
		break;

	case 'T':
	case 't': estado.teclas.t = GL_FALSE;
		break;
	case 'G':
	case 'g': estado.teclas.g = GL_FALSE;
		break;
	case 'F':
	case 'f': estado.teclas.f = GL_FALSE;
		break;
	case 'H':
	case 'h': estado.teclas.h = GL_FALSE;
		break;

	case ' ': estado.teclas.espaco = GL_FALSE;
		break;

	case 'I':
	case 'i': estado.teclas.i = GL_FALSE;
		break;
	case 'K':
	case 'k': estado.teclas.k = GL_FALSE;
		break;
	case 'J':
	case 'j': estado.teclas.j = GL_FALSE;
		break;
	case 'L':
	case 'l': estado.teclas.l = GL_FALSE;
		break;

	case '-': estado.teclas.score = GL_FALSE;
		break;

	}
}

void SpecialKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: estado.teclas.up = GL_TRUE;
		break;
	case GLUT_KEY_DOWN: estado.teclas.down = GL_TRUE;
		break;
	case GLUT_KEY_LEFT: estado.teclas.left = GL_TRUE;
		break;
	case GLUT_KEY_RIGHT: estado.teclas.right = GL_TRUE;
		break;

	case GLUT_KEY_F1:
		break;
	case GLUT_KEY_F2:
		break;
	case GLUT_KEY_F3: imprime_ajuda();
		break;
	case GLUT_KEY_F4:
		break;
	case GLUT_KEY_F5:
		break;

	case GLUT_KEY_PAGE_UP:
		if (estado.fov > 60 || estado.fov > 60)
		{
			estado.fov--;
			glutSetWindow(estado.player1Subwindow);
			reshapePlayer1Subwindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			glutSetWindow(estado.player2Subwindow);
			reshapePlayer2Subwindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			redisplayAll();
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (estado.fov < 120 || estado.fov < 120)
		{
			estado.fov++;
			glutSetWindow(estado.player1Subwindow);
			reshapePlayerSubwindow(JANELA_P1, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			glutSetWindow(estado.player2Subwindow);
			reshapePlayerSubwindow(JANELA_P2, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}
		break;
	}
}

// Callback para interaccao via teclas especiais (largar na tecla)
void SpecialKeyUp(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: estado.teclas.up = GL_FALSE;
		break;
	case GLUT_KEY_DOWN: estado.teclas.down = GL_FALSE;
		break;
	case GLUT_KEY_LEFT: estado.teclas.left = GL_FALSE;
		break;
	case GLUT_KEY_RIGHT: estado.teclas.right = GL_FALSE;
		break;
	}
}



////////////////////////////////////
// Inicializa��es

void createDisplayLists(int janelaID)
{
	model.chao = glGenLists(1);
	glNewList(model.chao, GL_COMPILE);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
	desenhaChao();
	glPopAttrib();
	glEndList();
}


///////////////////////////////////
/// Texturas

// S� para windows (usa biblioteca glaux)
#ifdef _WIN32

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File = NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File = fopen(Filename, "r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}
#endif

void createTextures(GLuint texID[])
{
	char *image;
	int w, h, bpp;

#ifdef _WIN32
	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage, 0, sizeof(void *) * 1);           	// Set The Pointer To NULL
#endif

	glGenTextures(NUM_TEXTURAS, texID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef _WIN32
	if (TextureImage[0] = LoadBMP(NOME_TEXTURA_CUBOS))
	{
		// Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_CUBOS]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
}
#else
	if (read_JPEG_file(NOME_TEXTURA_CUBOS, &image, &w, &h, &bpp))
	{
		// Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_CUBOS]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
#endif
	else
	{
		printf("Textura %s not Found\n", NOME_TEXTURA_CUBOS);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_CHAO, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_CHAO]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_CHAO);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_CASA, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_CASA]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_CASA);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_TELHADO, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_TELHADO]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_TELHADO);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_PAREDE, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_PAREDE]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_PAREDE);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_PAREDE2, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_PAREDE2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_PAREDE2);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_SKY, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_SKY]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_SKY);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_SKY_NIGHT, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_SKY_NIGHT]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_SKY_NIGHT);
		exit(0);
	}

	// Tanque

	if (read_JPEG_file(NOME_TEXTURA_TANQUE_HEXA, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_TANQUE_HEXA]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_TANQUE_HEXA);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_TANQUE_CAMO, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_TANQUE_CAMO]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_TANQUE_CAMO);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_TANQUE_DESERT, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_TANQUE_DESERT]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_TANQUE_DESERT);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_TANQUE_STRIPE, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_TANQUE_STRIPE]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_TANQUE_STRIPE);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_TANQUE_TIGER, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_TANQUE_TIGER]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_TANQUE_TIGER);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_TANQUE_TIGER2, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_TANQUE_TIGER2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_TANQUE_TIGER2);
		exit(0);
	}


	glBindTexture(GL_TEXTURE_2D, NULL);
}


/////////////////////////////////////
void initModel()
{
	model.parado = GL_FALSE;
	model.tanque1.skin = ID_TEXTURA_TANQUE_HEXA;
	model.tanque2.skin = ID_TEXTURA_TANQUE_CAMO;

	estado.debug = DEBUG;
	estado.menuActivo = GL_FALSE;
	estado.delayMovimento = DELAY_MOVIMENTO;

	estado.teclas.a = estado.teclas.w = estado.teclas.s = estado.teclas.d = \
		estado.teclas.up = estado.teclas.down = estado.teclas.left = estado.teclas.right = GL_FALSE;

	estado.fov = 100;

	estado.localViewer = 1;
}

void init()
{
	srand((unsigned)time(NULL));

	GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);  // por causa do Scale



	if (glutGetWindow() == estado.mainWindow)
		glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	else
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}

/////////////////////////////////////
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	initModel();

	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800 + GAP * 3, 400 + GAP * 2);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	if ((estado.mainWindow = glutCreateWindow("Labirinto")) == GL_FALSE)
		exit(1);

	imprime_ajuda();

	// Registar callbacks do GLUT da janela principal
	init();
	glutReshapeFunc(reshapeMainWindow);
	glutDisplayFunc(displayMainWindow);

	glutTimerFunc(estado.delayMovimento, Timer, 0);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);

	// Start Theme
	mciSendString("play ./Sounds/metal_theme.wav", NULL, 0, NULL);

	// Player 1 Window
	// criar a sub window player 1
	estado.player1Subwindow = glutCreateSubWindow(estado.mainWindow, 400 + GAP, GAP, 400, 800);
	model.tanque1.spawnX = 5;
	model.tanque1.spawnY = 5;
	model.tanque1.x = model.tanque1.spawnX;
	model.tanque1.y = model.tanque1.spawnY;

	init();
	setLight();
	setMaterial();

	createTextures(model.texID);
	createDisplayLists(JANELA_P1);

	glutReshapeFunc(reshapePlayer1Subwindow);
	glutDisplayFunc(displayPlayer1Subwindow);

	glutTimerFunc(estado.delayMovimento, Timer, 0);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);


	// Player 2 Window
	// criar a sub window player 2
	estado.player2Subwindow = glutCreateSubWindow(estado.mainWindow, 400 + GAP, GAP, 400, 800);

	init();
	setLight();
	setMaterial();

	createTextures(model.texID);
	createDisplayLists(JANELA_P2);

	glutReshapeFunc(reshapePlayer2Subwindow);
	glutDisplayFunc(displayPlayer2Subwindow);

	glutTimerFunc(estado.delayMovimento, Timer, 0);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);


	glutMainLoop();
	return 0;
}
