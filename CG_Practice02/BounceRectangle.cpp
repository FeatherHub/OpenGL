#include <glut.h>

//�簢���� ũ��� ���� ��ġ
GLfloat x1 = 0.f;
GLfloat y1 = 0.f;
GLsizei rSize = 50.f;

//x�� y �������� �����̴� ũ��
GLfloat xStep = 1.f;
GLfloat yStep = 1.f;

//������ ũ��
GLfloat winSizeWidth;
GLfloat winSizeHeight;

void SetupRC()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(x1, y1, x1/y1);

	glRectf(x1, y1, x1+rSize, y1+rSize);
	//�簢�� ������ �����Ͽ� �簢���� �׸���

	glutSwapBuffers();
	//����� ���� �� ���۸� ��ü�Ѵ�
	//glFlush()�� �����ϰ� �ִ�
}

void TimerFunc(int val)
{
	//���� ����
	if (x1 > winSizeWidth - rSize ||
		x1 < -winSizeWidth)
		xStep = -xStep;

	if (y1 > winSizeHeight - rSize ||
		y1 < -winSizeHeight)
		yStep = -yStep;

	//������ ũ�Ⱑ ����Ǿ� ������ ȭ�� ��踦 �Ѿ�� ��
	if (x1 > winSizeWidth - rSize)
		x1 = winSizeWidth - rSize - 1;
	
	if (y1 > winSizeHeight - rSize)
		y1 = winSizeHeight - rSize - 1;

	x1 += xStep;
	y1 += yStep;

	glutPostRedisplay();
	//������ �����츦 Refresh�Ѵ�
	//glutDisplayFunc()�� ȣ���Ѵ�

	glutTimerFunc(33, TimerFunc, 1);
	//33�и� �� �ڿ� ��ϵ� �Լ��� ȣ���Ѵ� 
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		winSizeWidth = 100.f;
		winSizeHeight = 100.f * h / w;

		glOrtho(-100.f, 100.f, -100.f * h / w, 100.f*h / w, 1.f, -1.f);
	}
	else
	{
		winSizeWidth = 100.f * w / h;
		winSizeHeight = 100.f;

		glOrtho(-100.f * w / h, 100.f*w / h, -100.f, 100.f, 1.f, -1.f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//ȭ�鿡 Draw�� �����ϴ� ���ÿ� 
	//ȭ�鿡 ��Ÿ���� �ʴ� ���ۿ� Render�� �����Ѵ�
	//���� �ɸ��� ������ �׸��� �׸��� �����ִ� �� �ƴ϶�
	//��� �׸� �Ŀ� �����شٴ� �����̴�

	glutInitWindowSize(800, 600);

	glutCreateWindow("Bounce Rectangle");
	
	glutDisplayFunc(RenderScene);
	//�׸� �� ���� ȣ���� �Լ��� ����Ѵ�

	glutReshapeFunc(ChangeSize);
	//������ ����� �ٲ� �� ���� ȣ���� �Լ��� ����Ѵ�

	glutTimerFunc(2000, TimerFunc, 1);
	//msecs : msecs ��ŭ ��ٸ� �� ��ϵ� �Լ��� ȣ���Ѵ�
	//val : ����� ���� ��

	SetupRC();

	glutMainLoop();
}