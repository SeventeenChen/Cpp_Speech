//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：main.cpp
// 文件功能描述：语音信号基本操作测试主函数
// 创建者：SeventeenChen
// 时间：2021/12/06
// 修改人：SeventeenChen
// 时间：2021/12/06
// 修改说明：实现语音信号的读取
// 软件版本：VS2015
//----------------------------------------------------------------
#include "audioread.h"
#include "audioplot.h"
#include "enframe.h"

int main()
{
	string filepath = "bluesky3.wav";
	int fs = 16000;
	bool disp_flag = false;
	std::tuple<vector <double>, int> in_data;
	std::vector<double> in_array;

	// 注：项目右键-属性-链接器-系统-子系统-控制台
	in_data = audioread(filepath, fs, disp_flag);	// 语音信号的读取

	in_array = std::get<0>(in_data);	// 音频数据
	fs = std::get<1>(in_data);			// 采样频率

	// cout << "fs = " << fs << endl;
	// 注：项目右键-属性-配置：Debug-C/C++-代码生成-运行库：多线程调试DLL（/MDd）
	// openGL配置：https://blog.csdn.net/lady_killer9/article/details/88987990
	// GLFWPlot(in_array);

	// 窗函数
	std::vector<double> rect_window;
	std::vector<double> hann_window;
	std::vector<double> hamm_window;
	int win_len = 10;
	int frame_shift = 80;
	rect_window = window(win_len, "rect");
	hann_window = window(win_len, "hanning");
	hamm_window = window(win_len, "hamming");

	cout << "rectangle window fuction: " << endl;
	for (int i = 0; i < win_len; i++)
	{
		cout << rect_window[i] << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "hanning window fuction: " << endl;
	for (int i = 0; i < win_len; i++)
	{
		cout << hann_window[i] << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "hamming window fuction: " << endl;
	for (int i = 0; i < win_len; i++)
	{
		cout << hamm_window[i] << endl;
	}
	return 0;
}

