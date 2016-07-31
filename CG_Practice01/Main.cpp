#include <glut.h>

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//���� clear �۾� ����

	glColor3f(0.1f, 0.4f, 0.6f);
	//������� ������ �����Ѵ�

	glRectf(0.0f, 0.0f, 40.0f, 40.0f);
	//x1, y1���� x2, y2���� �簢���� �׸���

	glFlush();
	//Queue�� ä���� ��ɾ���� ����
	//Rendering pipeline �� ����ϴ� OpenGL ��ɾ���� ���� Queue�� ����
	//OpenGL���� �� �̻� ��� ���� ���� ���ݱ��� ��û�� ó���ϵ��� ����
}

void SetupRC()
{
	glClearColor(0.3f, 0.6f, 0.3f, 1.0f);
	//������ window�� clear�� ���� ���� - clear �۾� ������ ���� �� ��
	//OpenGL �������� float�� ����
	//0.0~1.0 ������ ������ ����

	//������ component = alpha component
	//blending, translucence ǥ���� ���
}

void WinSizeChanged(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	//������ ���� ���������� ���� ��ũ�� ��ǥ�� �����Ͽ� ����Ѵ�
	//OpenGL�� ������ �׸��� �׸��µ� ����ϴ� ����
	//���� ���� ����(multi-viewport)

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-100.0f, 100.0f, -100.0f * h / w, 100.0f *h / w, 1.0f, -1.0f);	
		//left right bottom top near far
	else //w > h
		glOrtho(-100.0f * w / h, 100.0f*w / h, -100.0f, 100.0f, 1.0f, -1.0f);
		//���� ����
		//2���� ��ǥ�迡�� ���� ������ �߰��Ͽ� 3�������� Ȯ���Ѵ�
		//3���� Canvas

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//GLUT_SINGLE : Single buffered 
	//��� ����� ��ɵ��� ȭ�鿡 ��Ÿ�� ������ �󿡼� ����

	//GLUT_RGB : RGBA color mode 
	//1 component : 8 bit

	glutCreateWindow("Practice 01");
	//Create window using glut API

	glutDisplayFunc(RenderScene);
	//Display callback function
	//�����츦 �׸� ������ GLUT�� ��ϵ� �Լ��� ȣ���Ѵ�

	glutReshapeFunc(WinSizeChanged);
	//������ ����� �ٲ� ������ ȣ���� �Լ��� ����Ѵ�

	SetupRC();
	//������ ���� �Լ� �� ���� �Լ� �ƴ�
	//Rendering ���� ����� OpenGL �ʱ�ȭ �۾��� �Ѵ�

	glutMainLoop();
	//Include �� GLUT framework�� ȣ��
	//�޽���, Ű���� �Է� ��� ���� �ü���� ���õ� ��� ������
	//���α׷��� ����� ������ ó���Ѵ�
}