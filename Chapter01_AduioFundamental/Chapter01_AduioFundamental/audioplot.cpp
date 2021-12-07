#include "audioplot.h"

void audioplot(std::vector<double> in_dataArray)
{
	glClearColor(0.8, 0.8, 0.8, 0.8);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2);		//设置线段宽度
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);

	int i = 0;
	float xstart = -1.0;
	float ystart = 0.0;
	float xend = 0.0;
	float yend = 0.0;
	float temp = 0.0;

	for (i; i < in_dataArray.size(); i++)
	{
		xstart = in_dataArray[0] + 0.00003;
		ystart = temp;
		xend = xstart + 0.00003;

		yend = in_dataArray[i];
		
		glVertex2f(xstart, ystart);
		glVertex2f(xend, yend);

		temp = yend;    //终点作为下一次的起点
	}

	glEnd();

}