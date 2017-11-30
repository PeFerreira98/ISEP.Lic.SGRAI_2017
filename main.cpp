#include "stdafx.h"

#include "headers.h"

/////////////////////////////////////
//variaveis globais

Estado estado;
Modelo model;

//char mazedata[MAZE_HEIGHT][MAZE_WIDTH + 1] = {
//  "                  ",
//  " ******* ******** ",
//  " *       *      * ",
//  " * * *** * *    * ",
//  " * **  * ** * * * ",
//  " *     *      * * ",
//  " *          *** * ",
//  " *           *  * ",
//  " *     * *** **** ",
//  " * *   *   *    * ",
//  " *   ****  *    * ",
//  " ********  **** * ",
//  " *            * * ",
//  " *     *      * * ",
//  " ** ** *    *** * ",
//  " *   *      *   * ",
//  " *******  **** ** ",
//  "                  "
//};



////////////////////////////////////
//// Iluminação e materiais

void setLight()
{
	GLfloat light_pos[4] = { -5.0, 20.0, -8.0, 0.0 };
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	// ligar iluminação
	glEnable(GL_LIGHTING);

	// ligar e definir fonte de luz 0
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, estado.localViewer);
}

void setMaterial()
{
	GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_shininess = 104;

	// criação automática das componentes Ambiente e Difusa do material a partir das cores
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// definir de outros parâmetros dos materiais estáticamente
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
	gluPerspective(estado.camera[janela].fov, (GLfloat)width / height, 0.1, 50);
	// Matriz Modelview
	// Matriz onde são realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
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

GLboolean detectaColisao(GLfloat nx, GLfloat nz)
{

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
	GLfloat normais[][3] = { { 0,0,-1 },
		// acrescentar as outras normais...
	};


	glBindTexture(GL_TEXTURE_2D, texID);
	GLfloat textCoord[] = { texS, texT };

	desenhaPoligono(vertices[1], vertices[0], vertices[3], vertices[2], normais[0], textCoord);
	desenhaPoligono(vertices[2], vertices[3], vertices[7], vertices[6], normais[0], textCoord);
	desenhaPoligono(vertices[3], vertices[0], vertices[4], vertices[7], normais[0], textCoord);
	desenhaPoligono(vertices[6], vertices[5], vertices[1], vertices[2], normais[0], textCoord);
	desenhaPoligono(vertices[4], vertices[5], vertices[6], vertices[7], normais[0], textCoord);
	desenhaPoligono(vertices[5], vertices[4], vertices[0], vertices[1], normais[0], textCoord);

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void desenhaCubo() // default
{
	desenhaCubo(model.texID[0][ID_TEXTURA_CUBOS], 0, 0.25);
}

//void desenhaBussola(int width, int height)  // largura e altura da janela
//{

	// Altera viewport e projecção para 2D (copia de um reshape de um projecto 2D)

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


  // ropõe estado
 /* glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
*/

//repõe projecção chamando redisplay
	//reshapeNavigateSubwindow(width, height);

//}

//void desenhaModeloDir(objecto_t obj, int width, int height)
//{
	// Altera viewport e projecção
  //....

	// Blending (transparencias)
  /*
	glEnable(GL_BLEND);
	  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	  glDisable(GL_LIGHTING);
	  glDisable(GL_DEPTH_TEST);
  */

  //desenha Seta

  // ropõe estado
/*  glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
*/
//repõe projecção chamando redisplay
	//reshapeTopSubwindow(width, height);
//}

//void desenhaAngVisao(Camera *cam)
//{
	//GLfloat ratio;
	//ratio = (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT); // proporção 
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

void desenhaShield()
{
	// enable blending.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// choosing color and alpha
	glColor4f(0, 77, 232, SHIELD_ALPHA);
	glutSolidSphere(RAIO_ESCUDO, 32, 16);

	// disable blending
	glDisable(GL_BLEND);
}

void desenhaTanque(Tanque t, GLuint janela)
{

	/*GLUquadric *quad;
	quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);
	gluCylinder(quad, 0.5, 0.5, 0.4, 20, 2);*/

	//rodas
	//glTranslatef(t.x, t.y, 0);

	// base
	glTranslatef(t.x, t.y, ALTURA_BASE / 2.0);
	glRotatef(t.direccao, 0, 0, 1); //tanque
	glPushMatrix();
	glScalef(LARGURA_BASE, COMPRIMENTO_BASE, ALTURA_BASE);
	desenhaCubo(model.texID[janela][ID_TEXTURA_TANQUE], 0, 1);
	glPopMatrix();

	glPushMatrix();

	// torre
	glRotatef(t.angTorre, 0, 0, 1);					//rodar torre + canhao
	glTranslatef(0, 0, ALTURA_BASE / 2.0 + ALTURA_TORRE / 2.0);
	glPushMatrix();
	glScalef(LARGURA_TORRE, COMPRIMENTO_TORRE, ALTURA_TORRE);
	desenhaCubo(model.texID[janela][ID_TEXTURA_TANQUE], 0, 1);
	glPopMatrix();

	// canhao
	glTranslatef(0, COMPRIMENTO_TORRE / 2.0, 0);	//andar ate ao limite da torre
	glRotatef(t.angCanhao, 1, 0, 0);				//rodar canhao
	glTranslatef(0, COMPRIMENTO_CANHAO / 2.0, 0);	//mover o canhao
	glPushMatrix();
	glScalef(RAIO_CANHAO, COMPRIMENTO_CANHAO, RAIO_CANHAO);
	desenhaCubo(model.texID[janela][ID_TEXTURA_TANQUE], 0, 1);
	glPopMatrix();

	glPopMatrix();

	if (t.IsShieldActive)
	{
		glScalef(1, 1, 0.5);
		desenhaShield();
	}
}

void desenhaLabirinto()
{
	// código para desenhar o labirinto
	int i, j;

	glColor3f(0.5f, 0.5f, 0.5f);
	for (i = 0; i < MAZE_HEIGHT; i++)
	{
		for (j = 0; j < MAZE_WIDTH; j++)
		{
			if (model.mapa.mapa[i][j] == '*')
			{
				glPushMatrix();
				glTranslatef(j - (MAZE_WIDTH / 2), i - (MAZE_HEIGHT / 2), 0.5);
				desenhaCubo();
				glPopMatrix();
			}
		}
	}
}

#define STEP    1

void desenhaChao(GLfloat dimensao, GLuint texID)
{
	// código para desenhar o chão
	GLfloat i, j;
	glBindTexture(GL_TEXTURE_2D, texID);

	glColor3f(0.5f, 0.5f, 0.5f);
	for (i = -dimensao; i <= dimensao; i += STEP)
		for (j = -dimensao; j <= dimensao; j += STEP)
		{
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
	glBindTexture(GL_TEXTURE_2D, NULL);
}



/////////////////////////////////////
//navigateSubwindow

void motionNavigateSubwindow(int x, int y)
{

}

void mouseNavigateSubwindow(int button, int estado, int x, int y)
{

}

void setPlayerSubwindowCamera(Camera *cam, Tanque *t)
{
	cam->eye.x = t->x + cos(RAD(t->direccao + t->angTorre - 90))*-3;
	cam->eye.y = t->y + sin(RAD(RAD(t->direccao + t->angTorre - 90)))*-3;
	cam->eye.z = (ALTURA_BASE + ALTURA_TORRE) * 0.3 + 0.2;

	cam->center.x = t->x;
	cam->center.y = t->y;
	cam->center.z = (ALTURA_BASE + ALTURA_TORRE) * 0.3;

	gluLookAt(cam->eye.x, cam->eye.y, cam->eye.z, cam->center.x, cam->center.y, cam->center.z, 0, 0, 1);
}

void displayPlayer1Subwindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	setPlayerSubwindowCamera(&estado.camera[JANELA_P1], &model.tanque);  //mais tarde mudar para tanque do jogador 1
	setLight();

	glCallList(model.labirinto[JANELA_P1]);
	glCallList(model.chao[JANELA_P1]);

	if (!estado.vista[JANELA_P1])
	{
		glPushMatrix();
		desenhaTanque(model.tanque, JANELA_P1);    //mais tarde mudar para tanque do jogador 1
		int i;
		for (i = 0; i < NUM_BULLETS; i++)
		{
			if (model.tanque.bullets[i].IsAlive)
			{
				glPushMatrix();
				desenhaBullet(model.tanque.bullets[i]);
				glPopMatrix();
			}
		}
		glPopMatrix();
	}

	glutSwapBuffers();
}

void displayPlayer2Subwindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	setPlayerSubwindowCamera(&estado.camera[JANELA_P2], &model.tanque);  //mais tarde mudar para tanque do jogador 2
	setLight();

	glCallList(model.labirinto[JANELA_P2]);
	glCallList(model.chao[JANELA_P2]);

	if (!estado.vista[JANELA_P2])
	{
		glPushMatrix();
		desenhaTanque(model.tanque, JANELA_P2);    //mais tarde mudar para tanque do jogador 2
		int i;
		for (i = 0; i < NUM_BULLETS; i++)
		{
			if (model.tanque.bullets[i].IsAlive)
			{
				glPushMatrix();
				desenhaBullet(model.tanque.bullets[i]);
				glPopMatrix();
			}
		}
		glPopMatrix();
	}

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
	glutPostRedisplay();
}

void displayMainWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void Timer(int value)
{
	GLfloat nx = 0, nz = 0;
	GLboolean andar = GL_FALSE;

	GLuint curr = glutGet(GLUT_ELAPSED_TIME);
	// calcula velocidade baseado no tempo passado
	//float velocidade = model.objecto.vel*(curr - model.prev)*0.001;

	glutTimerFunc(estado.delayMovimento, Timer, 0);
	model.prev = curr;


	//if (estado.teclas.up) {
	//	// calcula nova posição nx,nz
	//	if (!detectaColisao(nx, nz)) {
	//		//model.objecto.pos.x = nx;
	//		//model.objecto.pos.z = nz;
	//	}
	//	andar = GL_TRUE;
	//}
	//if (estado.teclas.down) {
	//	// calcula nova posição nx,nz
	//	if (!detectaColisao(nx, nz)) {
	//		//model.objecto.pos.x = nx;
	//		//model.objecto.pos.z = nz;
	//	}
	//	andar = GL_TRUE;
	//}
	//if (estado.teclas.left) {
	//	// rodar camara e objecto
	//	//model.objecto.dir += RAD(2);
	//	//estado.camera.dir_long += RAD(2);
	//}
	//if (estado.teclas.right) {
	//	// rodar camara e objecto
	//	//model.objecto.dir -= RAD(2);
	//	//estado.camera.dir_long -= RAD(2);
	//}

	//if (estado.menuActivo || model.parado) // sair em caso de o jogo estar parado ou menu estar activo
	//	return;

	// canhao
	if (estado.teclas.down)
	{
		canonDown(&model.tanque);
	}
	if (estado.teclas.up)
	{
		canonUp(&model.tanque);
	}

	// torre
	if (estado.teclas.left)
	{
		towerLeft(&model.tanque);
	}
	if (estado.teclas.right)
	{
		towerRight(&model.tanque);
	}

	// tanque
	if (estado.teclas.a)
	{
		tankLeft(&model.tanque);
	}
	if (estado.teclas.d)
	{
		tankRight(&model.tanque);
	}

	if (estado.teclas.w)	// W ativo
	{
		tankFront(&model.tanque);
	}
	else if (!estado.teclas.s)	// W + S inativo
	{
		tankSlowDown(&model.tanque);
	}

	if (estado.teclas.s)	// S ativo
	{
		tankBack(&model.tanque);
	}

	if (estado.teclas.espaco)
	{
		if (shoot(&model.tanque)) PlaySound("fire.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

	if (model.tanque.IsReloading)
	{
		(&model.tanque)->reloadCounter--;
		(&model.tanque)->IsReloading = model.tanque.reloadCounter > 0;
	}

	if (model.tanque.IsPowerBoosted)
	{
		(&model.tanque)->powerBoostCounter--;
		(&model.tanque)->IsPowerBoosted = model.tanque.powerBoostCounter <= 0;
	}

	if (model.tanque.IsSpeedBoosted)
	{
		(&model.tanque)->speedBoostCounter--;
		(&model.tanque)->IsSpeedBoosted = model.tanque.speedBoostCounter <= 0;
	}

	updateTank(&model.tanque);


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
	case 'w': 
		estado.teclas.w = GL_TRUE;
		break;
	case 'A':
	case 'a': 
		estado.teclas.a = GL_TRUE;
		break;
	case 'S':
	case 's': 
		estado.teclas.s = GL_TRUE;
		break;
	case 'D':
	case 'd': 
		estado.teclas.d = GL_TRUE;
		break;
	case ' ': 
		estado.teclas.espaco = GL_TRUE;
		break;
	case 'h':
	case 'H':
		imprime_ajuda();
		break;
	case 'l':
	case 'L':
		estado.localViewer = !estado.localViewer;
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
	case ' ': estado.teclas.espaco = GL_FALSE;
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
	case GLUT_KEY_F1: estado.vista[JANELA_TOP] = !estado.vista[JANELA_TOP];
		break;
	case GLUT_KEY_F2: estado.vista[JANELA_NAVIGATE] = !estado.vista[JANELA_NAVIGATE];
		break;
	case GLUT_KEY_PAGE_UP:
		if (estado.camera[JANELA_P1].fov > 20 || estado.camera[JANELA_P2].fov > 20)
		{
			estado.camera[JANELA_P1].fov--;
			estado.camera[JANELA_P2].fov--;
			glutSetWindow(estado.player1Subwindow);
			reshapePlayerSubwindow(JANELA_P1, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			glutSetWindow(estado.player2Subwindow);
			reshapePlayerSubwindow(JANELA_P2, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			redisplayAll();
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (estado.camera[JANELA_P1].fov < 130 || estado.camera[JANELA_P2].fov < 130)
		{
			estado.camera[JANELA_P1].fov++;
			estado.camera[JANELA_P2].fov++;
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
// Inicializações

void createDisplayLists(int janelaID)
{
	model.labirinto[janelaID] = glGenLists(2);
	glNewList(model.labirinto[janelaID], GL_COMPILE);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
	desenhaLabirinto();
	glPopAttrib();
	glEndList();

	model.chao[janelaID] = model.labirinto[janelaID] + 1;
	glNewList(model.chao[janelaID], GL_COMPILE);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
	desenhaChao(CHAO_DIMENSAO, model.texID[janelaID][ID_TEXTURA_CHAO]);
	glPopAttrib();
	glEndList();
}


///////////////////////////////////
/// Texturas


// S— para windows (usa biblioteca glaux)
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

	if (read_JPEG_file(NOME_TEXTURA_TANQUE, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_TANQUE]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("Textura %s not Found\n", NOME_TEXTURA_CHAO);
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
}




void initThemeSound() {

	//open music
	mciSendString("open ./impact.wav alias wav", NULL, 0, NULL);
	mciSendString("play wav", NULL, 0, NULL);

	char *MidiLength, *MidiPos;

	MidiLength = (char*)malloc(7);
	MidiPos = (char*)malloc(7);

	//get music info
	mciSendString("status wav length", MidiLength, 255, 0);

	do{
		mciSendString("status wav position", MidiPos, 255, 0);

		int result = strcmp(MidiPos, MidiLength);

		if (result == 0) mciSendString("play wav", NULL, 0, NULL);
	}while (1);

}

void init()
{

	srand((unsigned)time(NULL));

	model.parado = GL_FALSE;

	estado.debug = DEBUG;
	estado.menuActivo = GL_FALSE;
	estado.delayMovimento = DELAY_MOVIMENTO;
	//estado.camera.eye.x = 40;
	//estado.camera.eye.y = 40;
	//estado.camera.eye.z = 40;
	//estado.camera.center.x = 0;
	//estado.camera.center.y = 0;
	//estado.camera.center.z = 0;
	//estado.camera.up.x = 0;
	//estado.camera.up.y = 0;
	//estado.camera.up.z = 1;
	//estado.ortho = GL_TRUE;
	//estado.camera.fov = 60;

	estado.teclas.a = estado.teclas.w = estado.teclas.s = estado.teclas.d = \
		estado.teclas.up = estado.teclas.down = estado.teclas.left = estado.teclas.right = GL_FALSE;

	GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };

	estado.camera[0].eye.x = 0;
	estado.camera[0].eye.y = OBJECTO_ALTURA * 2;
	estado.camera[0].eye.z = 0;
	estado.camera[0].dir_long = 0;
	estado.camera[0].dir_lat = 0;
	estado.camera[0].fov = 60;

	estado.camera[1].eye.x = 0;
	estado.camera[1].eye.y = OBJECTO_ALTURA * 2;
	estado.camera[1].eye.z = 0;
	estado.camera[1].dir_long = 0;
	estado.camera[1].dir_lat = 0;
	estado.camera[1].fov = 60;

	estado.localViewer = 1;
	estado.vista[JANELA_TOP] = 0;
	estado.vista[JANELA_NAVIGATE] = 0;


	model.xMouse = model.yMouse = -1;
	model.andar = GL_FALSE;

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

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800 + GAP * 3, 400 + GAP * 2);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	if ((estado.mainWindow = glutCreateWindow("Labirinto")) == GL_FALSE)
		exit(1);

	//mciSendString("open ./impact.wav alias wav", NULL, 0, NULL);
	//mciSendString("play wav repeat", NULL, 0, NULL);

	//mciSendString("play ./impact.wav", NULL, 0, NULL);

	initThemeSound();

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



	// Player 1 Window
	// criar a sub window player 1
	estado.player1Subwindow = glutCreateSubWindow(estado.mainWindow, 400 + GAP, GAP, 400, 800);
	init();
	setLight();
	setMaterial();

	createTextures(model.texID[JANELA_P1]);
	createDisplayLists(JANELA_P1);

	glutReshapeFunc(reshapePlayer1Subwindow);
	glutDisplayFunc(displayPlayer1Subwindow);
	//glutMouseFunc(mouseNavigateSubwindow);

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

	createTextures(model.texID[JANELA_P2]);
	createDisplayLists(JANELA_P2);

	glutReshapeFunc(reshapePlayer1Subwindow);
	glutDisplayFunc(displayPlayer1Subwindow);
	//glutMouseFunc(mouseNavigateSubwindow);

	glutTimerFunc(estado.delayMovimento, Timer, 0);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);


	glutMainLoop();
	return 0;

}
