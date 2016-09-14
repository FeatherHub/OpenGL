#include "GLLogic.h"
#include "glut.h"

/*for loading texture datas*/
#include "..\Reference\lodepng.h" 
#include <windows.h>
#include <vector>

GLLogic::GLLogic() :
	m_rotX(0.f), m_rotY(0.f), m_rotPlanet(0.f)
{
}

void GLLogic::Init(void(*updateCallback)(int))
{
	//param
	m_updateCallback = updateCallback;

	//glut 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rotating Planets");

	//cleaer
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	//lighting
	InitLighting();

	//textures
	glEnable(GL_TEXTURE_2D);
	m_texIds[EARTH_IDX] = LoadTexture("Resources/earth.png");
	m_texIds[VENUS_IDX] = LoadTexture("Resources/venus.png");
	m_texIds[SILVA_IDX] = LoadTexture("Resources/silva.png");

	//planets
	for (int i = 0; i < PLANET_NUM; i++)
	{
		m_planets[i] = gluNewQuadric();
	}
}

void GLLogic::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(m_rotX, 1.f, 0.f, 0.f);
	glRotatef(m_rotY, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, -100.f);
	
	//가운데공
	DrawPlanet(m_planets[EARTH_IDX], m_texIds[EARTH_IDX], 20);
	
	//오른공	
	glPushMatrix(); //가운데공에서 시작
	glRotatef(m_rotPlanet, 0.f, 1.f, 0.f); //오른쪽으로 회전
	glTranslatef(90.f, 0.f, 0.f); //회전한 상태에서 오른쪽으로 이동
	DrawPlanet(m_planets[VENUS_IDX], m_texIds[VENUS_IDX], 12);
	
	//위성 공
	glPushMatrix(); //오른공에서 시작
	glRotatef(m_rotPlanet, 0.f, 1.f, 1.f);
	glTranslatef(30.f, 0.f, 0.f);
	DrawPlanet(m_planets[SILVA_IDX], m_texIds[SILVA_IDX], 9);
	glPopMatrix();
	
	glPopMatrix();

	glutSwapBuffers();
}

void GLLogic::Update()
{
	m_rotPlanet += 3.f;
	if (m_rotPlanet > 360.f)
	{
		m_rotPlanet = 0.f;
	}

	glutPostRedisplay();
	glutTimerFunc(UPDATE_DELTA, m_updateCallback, 0);
}

void GLLogic::OnKeyPressed(int key)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		m_rotX += 4.f;
		break;
	case GLUT_KEY_DOWN:
		m_rotX -= 4.f;
		break;
	case GLUT_KEY_RIGHT:
		m_rotY += 4.f;
		break;
	case GLUT_KEY_LEFT:
		m_rotY -= 4.f;
		break;
	default:
		return;
	}

	glutPostRedisplay();
}

void GLLogic::OnWindowChanged(int w, int h)
{
	GLfloat range = 125.f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-range, range,
			-range * h / w, range * h / w,
			-range * 2, range * 2);
	else
		glOrtho(-range * w / h, range * w / h, 
			-range, range, 
			-range * 2, range * 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLLogic::InitLighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	GLfloat lightPos[] = { 12.f, 12.f, -35.f, 1.f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	GLfloat diffuse[] = { 0.7f, 0.7f, 0.7f, 1.f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	GLfloat specular[] = { 1.f, 1.f, 1.f, 1.f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	GLfloat specularRef[] = { 1.f, 1.f, 1.f, 1.f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularRef);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.f);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

UINT GLLogic::LoadTexture(const char* filePath)
{
	std::vector<UCHAR> image;
	UINT w, h;

	auto err = lodepng::decode(image, w, h, filePath); //pass by reference 
	
	if (err)
		printf("err %u : %s \n", err, lodepng_error_text(err));
	else
		printf("img size : %i \n", image.size());

	UINT texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//for mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

	//for tex2d
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

	return texId;
}

void GLLogic::DrawPlanet(GLUquadric* quad, unsigned char texId, int radius)
{
	glBindTexture(GL_TEXTURE_2D, texId);
	gluQuadricTexture(quad, 1);
	gluSphere(quad, radius, radius * 2, radius * 2);
}
