#include "glut.h"
#include "glutFunc.h"
#include <math.h>

void main()
{
	//랜더 옵션
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	//윈도우 사이즈 설정
	glutInitWindowSize(512, 512);
	//윈도우 위치 설정
	glutInitWindowPosition(0, 0);

	//윈도우 생성
	glutCreateWindow("Atom");

	//콜백 등록
	glutDisplayFunc(gl::RenderScene);
	glutTimerFunc(33, gl::OnTimeTick, 0);
	glutReshapeFunc(gl::OnChangeSize);
	glutSpecialFunc(gl::OnKeyPressed);

	gl::Init();

	//메인 루프
	glutMainLoop();
}