#include "glut.h"
#include "DrawJet.h"

#include <math.h>

GLfloat gRotX = 0.f;
GLfloat gRotY = 0.f;
GLfloat gDistZ = 0.f;

void SetupGL()
{
	glFrontFace(GL_CCW); //Counter clock-wise polygons face out
	glEnable(GL_DEPTH_TEST); //Hidden surface removal
	glEnable(GL_CULL_FACE); //Back face culling

	glEnable(GL_LIGHTING); //Enable lighting

	GLfloat ambientLight[]{ 0.5f, 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	GLfloat diffuseLight[]{ 0.7f, 0.7f, 0.7f, 1.f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	GLfloat specularLight[]{ 1.f, 1.f, 1.f, 1.f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL); //Enable material color tracking
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glClearColor(0.f, 0.f, 0.f, 1.f);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(gRotX, 1.f, 0.f, 0.f);
	glRotatef(gRotY, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, gDistZ);

	DrawJet();

	glPopMatrix();

	glutSwapBuffers();
}

void ControlKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		gRotX -= 5.f;
		break;
	case GLUT_KEY_DOWN:
		gRotX += 5.f;
		break;
	case GLUT_KEY_RIGHT:
		gRotY -= 5.f;
		break;
	case GLUT_KEY_LEFT:
		gRotY += 5.f;
		break;
	case GLUT_KEY_F1:
		gDistZ += 5.f;
		break;
	case GLUT_KEY_F2:
		gDistZ -= 5.f;
		break;
	}

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	GLfloat fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(45.f, fAspect, 1.f, 255.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat lightPos[]{ -50.f, 50.f, 100.f, 1.f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glTranslatef(0.f, 0.f, -150.f);
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Light Jet");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(ControlKey);

	SetupGL();

	glutMainLoop();
}