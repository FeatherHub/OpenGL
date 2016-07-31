#include <glut.h>

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//실제 clear 작업 수행

	glColor3f(0.1f, 0.4f, 0.6f);
	//드로잉할 색상을 지정한다

	glRectf(0.0f, 0.0f, 40.0f, 40.0f);
	//x1, y1부터 x2, y2까지 사각형을 그린다

	glFlush();
	//Queue에 채워진 명령어들을 수행
	//Rendering pipeline 을 사용하는 OpenGL 명령어들은 종종 Queue에 저장
	//OpenGL에게 더 이상 명령 받지 말고 지금까지 요청을 처리하도록 지시
}

void SetupRC()
{
	glClearColor(0.3f, 0.6f, 0.3f, 1.0f);
	//생성된 window를 clear할 색상 설정 - clear 작업 수행은 아직 안 함
	//OpenGL 구현에서 float로 정의
	//0.0~1.0 사이의 값으로 정의

	//마지막 component = alpha component
	//blending, translucence 표현에 사용
}

void WinSizeChanged(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	//윈도우 내의 일정영역을 실제 스크린 좌표로 시정하여 사용한다
	//OpenGL이 실제로 그림을 그리는데 사용하는 영역
	//분할 설정 가능(multi-viewport)

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-100.0f, 100.0f, -100.0f * h / w, 100.0f *h / w, 1.0f, -1.0f);	
		//left right bottom top near far
	else //w > h
		glOrtho(-100.0f * w / h, 100.0f*w / h, -100.0f, 100.0f, 1.0f, -1.0f);
		//직교 투영
		//2차원 좌표계에서 깊이 성분을 추가하여 3차원으로 확장한다
		//3차원 Canvas

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//GLUT_SINGLE : Single buffered 
	//모든 드로잉 명령들을 화면에 나타난 윈도우 상에서 수행

	//GLUT_RGB : RGBA color mode 
	//1 component : 8 bit

	glutCreateWindow("Practice 01");
	//Create window using glut API

	glutDisplayFunc(RenderScene);
	//Display callback function
	//윈도우를 그릴 때마다 GLUT는 등록된 함수를 호출한다

	glutReshapeFunc(WinSizeChanged);
	//윈도우 사이즈가 바뀔 때마다 호출할 함수를 등록한다

	SetupRC();
	//개인이 만든 함수 즉 예약 함수 아님
	//Rendering 전에 수행될 OpenGL 초기화 작업을 한다

	glutMainLoop();
	//Include 한 GLUT framework를 호출
	//메시지, 키보드 입력 등과 같은 운영체제에 관련된 모든 사항을
	//프로그램이 종료될 때까지 처리한다
}