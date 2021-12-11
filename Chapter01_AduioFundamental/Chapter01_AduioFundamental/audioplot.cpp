//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����audioplot.cpp
// �ļ����������������źŲ��εĻ���
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/08
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------
#include "audioplot.h"

/*-----------------------------------------------------------------
// ���룺��Ƶ���ݣ�vector����ͼ����⣨string��
// �����
// ��������������openGL������Ƶ����
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/08
// �޸��ˣ�SeventeenChen
// ��¼�����title���
// ���ڣ�2021/12/10
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
int GLFWPlot(std::vector<double> in_dataArray, const char *title)
{	
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/*your draw*/
		audioplot(in_dataArray);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;

}

/*-----------------------------------------------------------------
// ���룺��Ƶ����
// �����
// ��������������openGL������Ƶ����
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/08
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
void audioplot(std::vector<double> in_dataArray)
{
	glClearColor(0.8, 0.8, 0.8, 0.8);	// ���ڵ�ɫ
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2);		//�����߶ο��
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);	// �߶���ɫ

	int i = 0;
	float xstart = -1.0;
	float ystart = 0.0;
	float xend = 0.0;
	float yend = 0.0;
	float temp = 0.0;

	int wav_length = in_dataArray.size();
	float x_stepsize;
	x_stepsize = 2.0/wav_length;	// �������ݳ��ȼ��㲽����ʹ�û�������ˮƽ������-1~1��
	for (i; i < wav_length; i++)
	{
		xstart = xstart + x_stepsize;
		ystart = temp;
		xend = xstart + x_stepsize;

		yend = in_dataArray[i];
		
		glVertex2f(xstart, ystart);	// �������
		glVertex2f(xend, yend);		// �����յ�

		temp = yend;    //�յ���Ϊ��һ�ε����
	}

	glEnd();
}

