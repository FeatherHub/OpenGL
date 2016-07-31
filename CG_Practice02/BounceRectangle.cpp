#include <glut.h>

//사각형의 크기와 시작 위치
GLfloat x1 = 0.f;
GLfloat y1 = 0.f;
GLsizei rSize = 50.f;

//x와 y 방향으로 움직이는 크기
GLfloat xStep = 1.f;
GLfloat yStep = 1.f;

//윈도우 크기
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
	//사각형 정보를 참고하여 사각형을 그린다

	glutSwapBuffers();
	//드로잉 실행 후 버퍼를 교체한다
	//glFlush()를 내장하고 있다
}

void TimerFunc(int val)
{
	//방향 변경
	if (x1 > winSizeWidth - rSize ||
		x1 < -winSizeWidth)
		xStep = -xStep;

	if (y1 > winSizeHeight - rSize ||
		y1 < -winSizeHeight)
		yStep = -yStep;

	//윈도우 크기가 변경되어 윈도우 화면 경계를 넘어갔을 때
	if (x1 > winSizeWidth - rSize)
		x1 = winSizeWidth - rSize - 1;
	
	if (y1 > winSizeHeight - rSize)
		y1 = winSizeHeight - rSize - 1;

	x1 += xStep;
	y1 += yStep;

	glutPostRedisplay();
	//현재의 윈도우를 Refresh한다
	//glutDisplayFunc()를 호출한다

	glutTimerFunc(33, TimerFunc, 1);
	//33밀리 초 뒤에 등록된 함수를 호출한다 
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
	//화면에 Draw를 수행하는 동시에 
	//화면에 나타나지 않는 버퍼에 Render를 수행한다
	//오래 걸리는 복잡한 그림을 그리며 보여주는 게 아니라
	//모두 그린 후에 보여준다는 전략이다

	glutInitWindowSize(800, 600);

	glutCreateWindow("Bounce Rectangle");
	
	glutDisplayFunc(RenderScene);
	//그릴 때 마다 호출할 함수를 등록한다

	glutReshapeFunc(ChangeSize);
	//윈도우 사이즈가 바뀔 때 마다 호출할 함수를 등록한다

	glutTimerFunc(2000, TimerFunc, 1);
	//msecs : msecs 만큼 기다린 뒤 등록된 함수를 호출한다
	//val : 사용자 정의 값

	SetupRC();

	glutMainLoop();
}