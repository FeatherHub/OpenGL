#include "glut.h"
#include "glutFunc.h"
#include <math.h>

void main()
{
	//���� �ɼ�
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	//������ ������ ����
	glutInitWindowSize(512, 512);
	//������ ��ġ ����
	glutInitWindowPosition(0, 0);

	//������ ����
	glutCreateWindow("Atom");

	//�ݹ� ���
	glutDisplayFunc(gl::RenderScene);
	glutTimerFunc(33, gl::OnTimeTick, 0);
	glutReshapeFunc(gl::OnChangeSize);
	glutSpecialFunc(gl::OnKeyPressed);

	gl::Init();

	//���� ����
	glutMainLoop();
}