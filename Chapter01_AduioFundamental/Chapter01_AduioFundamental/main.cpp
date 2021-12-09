//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����main.cpp
// �ļ����������������źŻ�����������������
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/06
// �޸��ˣ�SeventeenChen
// ʱ�䣺2021/12/06
// �޸�˵����ʵ�������źŵĶ�ȡ
// ����汾��VS2015
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

	// ע����Ŀ�Ҽ�-����-������-ϵͳ-��ϵͳ-����̨
	in_data = audioread(filepath, fs, disp_flag);	// �����źŵĶ�ȡ

	in_array = std::get<0>(in_data);	// ��Ƶ����
	fs = std::get<1>(in_data);			// ����Ƶ��

	// cout << "fs = " << fs << endl;
	// ע����Ŀ�Ҽ�-����-���ã�Debug-C/C++-��������-���п⣺���̵߳���DLL��/MDd��
	// openGL���ã�https://blog.csdn.net/lady_killer9/article/details/88987990
	// GLFWPlot(in_array);

	// ������
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

