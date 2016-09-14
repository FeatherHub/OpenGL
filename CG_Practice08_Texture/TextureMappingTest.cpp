#include "glut.h"
#include "lodepng.h"

#include <Windows.h>
#include <vector>

void RenderScene();
void OnWinChange(int w, int h);
void OnSpecialKey(int key, int x, int y);
void OnNormalKey(UCHAR key, int x, int y);
void Init();
void LoadTexture();

const float PI = 3.14159f;

GLfloat gRotX = 0.f;
GLfloat gRotY = 0.f;
GLfloat gDistZ = 0.f;

GLfloat gAmbLight[]{ 0.3f, 0.3f, 0.3f, 1.f };
GLfloat gDifLight[]{ 0.8f, 0.8f, 0.8f, 1.f };
GLfloat gLightPos[]{ -50.f, 50.f, 100.f, 1.f };

GLuint gTexIdx;

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE |
						GLUT_RGB |
						GLUT_DEPTH);

	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2d Texture");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(OnWinChange);
	glutSpecialFunc(OnSpecialKey);
	glutKeyboardFunc(OnNormalKey);

	Init();
	
	glutMainLoop();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	//Move Camera
	glRotatef(gRotX, 1.f, 0.f, 0.f);
	glRotatef(gRotY, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, gDistZ);

	//Create Light
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gAmbLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, gDifLight);
	glLightfv(GL_LIGHT0, GL_POSITION, gLightPos);
	glEnable(GL_LIGHT0);

	//Draw Object
	glColor3f(1.f, 1.f, 1.f);
	glutSolidTeapot(10.f);

	glPopMatrix();

	glutSwapBuffers();
}

void OnWinChange(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(45.f, aspect, 1.f, 500.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.f, 0.f, -50.f);
}

void Init()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);

	glEnable(GL_DEPTH_TEST);

	LoadTexture();
}

//Texture Filtering
/*
- It is hard mapping texel to pixel 1:1
- Map texel to pixel by mag or min operation  
*/

void LoadTexture()
{
	std::vector<UCHAR> image;
	UINT w, h, err;

	err = lodepng::decode(image, w, h, 
						"texture.png");

	if (err)
		printf("err %u : %s \n",
			err, lodepng_error_text(err));

	printf("img size : %i \n",
			image.size());

	//�ؽ��ĸ� ������ ���� �ʱ�ȭ
	glGenTextures(1, //��ȣ 
				&gTexIdx); //������ �ؽ��� ������ŭ ����

	//ID���� ������ ���� �ؽ��� �� ���� ����� �ؽ��� ����
	glBindTexture(GL_TEXTURE_2D, gTexIdx);

	glEnable(GL_TEXTURE_2D);

	//�ݺ� ��� ���� : �ؽ��� ��ǥ�� ��谪�� ����� �Ǵ� ���
	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_WRAP_S, //����(s��)
					GL_REPEAT); //�ݺ� cf) GL_CLAMP : ��ü

	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_WRAP_T, //����(t��)
					GL_REPEAT); //�ݺ�

	//Ȯ�� ����
	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MAG_FILTER,
					GL_LINEAR); //���� ���͸� cf) GL_NEAREST: �̿����͸�

	//��� ����
	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER,
					GL_LINEAR); //���� ���͸�

	//2D �ؽ��� ����
	glTexImage2D(GL_TEXTURE_2D, 
				0, //mipmap �󼼵�, ���� 0
				4, 
				w, 
				h, //height of texture image, �ݵ�� 2�� ������  
				0, //border
				GL_RGBA, //format 
				GL_UNSIGNED_BYTE, //data type 
				image.data() //�ؽ��� �̹��� �ּ�
	);
}

void OnSpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		gRotX += 5.f;
		break;
	case GLUT_KEY_UP:
		gRotX -= 5.f;
		break;
	case GLUT_KEY_RIGHT:
		gRotY += 5.f;
		break;
	case GLUT_KEY_LEFT:
		gRotY -= 5.f;
		break;
	default:
		return;
	}

	glutPostRedisplay();
}

void OnNormalKey(UCHAR key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case 'w':
		gDistZ += 5.f;
		break;
	case 's':
		gDistZ -= 5.f;
		break;
	default:
		return;
	}

	glutPostRedisplay();
}
