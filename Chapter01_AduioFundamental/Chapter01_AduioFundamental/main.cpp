//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����main.cpp
// �ļ����������������źŻ�����������������
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/06
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
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
	// GLFWPlot(in_array, "waveform");

	// ������
	std::vector<double> rect_window;
	std::vector<double> hann_window;
	std::vector<double> hamm_window;
	int win_len = 200;	// set 10 for test
	int frame_shift = 80;
	rect_window = window(win_len, "rect");
	hann_window = window(win_len, "hanning");
	hamm_window = window(win_len, "hamming");

	///*cout << "rectangle window fuction: " << endl;
	//for (int i = 0; i < win_len; i++)
	//{
	//	cout << rect_window[i] << endl;
	//}
	//cout << "----------------------------------" << endl;
	//cout << "hanning window fuction: " << endl;
	//for (int i = 0; i < win_len; i++)
	//{
	//	cout << hann_window[i] << endl;
	//}
	//cout << "----------------------------------" << endl;
	//cout << "hamming window fuction: " << endl;
	//for (int i = 0; i < win_len; i++)
	//{
	//	cout << hamm_window[i] << endl;
	//}*/

	// �Ӵ���֡
	int frame_num = (in_array.size() - win_len + frame_shift) / frame_shift;
	vector<vector<double> >frame_signal(frame_num, vector<double>(win_len));
	vector<double> one_frame_signal(win_len);
	frame_signal = enframe(in_array, hann_window, frame_shift);	// ��֡

	int frame_index = 0;
	cout << "whcih frame do you want to visualize?" << endl;
	cin >> frame_index;

	for (int i = 0; i < win_len; i++)
	{
		one_frame_signal[i] = frame_signal[frame_index - 1][i];
	}

	string str = {};
	str = "The\40" + std::to_string(frame_index) + "th frame waveform";
	const char *title = str.c_str();
	GLFWPlot(one_frame_signal, title);


	return 0;
}

