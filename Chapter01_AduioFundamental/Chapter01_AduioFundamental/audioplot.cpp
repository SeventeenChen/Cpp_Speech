//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：audioplot.cpp
// 文件功能描述：语音信号波形的绘制
// 创建者：SeventeenChen
// 时间：2021/12/08
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------
#include "audioplot.h"

/*-----------------------------------------------------------------
// 输入：音频数据（vector），图像标题（string）
// 输出：
// 功能描述：利用openGL绘制音频波形
// 作者：SeventeenChen
// 日期：2021/12/08
// 修改人：SeventeenChen
// 记录：添加title标记
// 日期：2021/12/10
// 修改人：
// 记录：
// 版本：
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
// 输入：音频数据
// 输出：
// 功能描述：利用openGL绘制音频波形
// 作者：SeventeenChen
// 日期：2021/12/08
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void audioplot(std::vector<double> in_dataArray)
{
	glClearColor(0.8, 0.8, 0.8, 0.8);	// 窗口底色
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2);		//设置线段宽度
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);	// 线段颜色

	int i = 0;
	float xstart = -1.0;
	float ystart = 0.0;
	float xend = 0.0;
	float yend = 0.0;
	float temp = 0.0;

	int wav_length = in_dataArray.size();
	float x_stepsize;
	x_stepsize = 2.0/wav_length;	// 根据数据长度计算步长，使得绘制数据水平铺满（-1~1）
	for (i; i < wav_length; i++)
	{
		xstart = xstart + x_stepsize;
		ystart = temp;
		xend = xstart + x_stepsize;

		yend = in_dataArray[i];
		
		glVertex2f(xstart, ystart);	// 折线起点
		glVertex2f(xend, yend);		// 折现终点

		temp = yend;    //终点作为下一次的起点
	}

	glEnd();
}

