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
// #include "audioplot.h"

int main()
{
	string filepath = "bluesky3.wav";
	int fs = 16000;
	bool disp_flag = true;
	std::tuple<vector <double>, int> in_data;
	std::vector<double> in_array;

	// ע����Ŀ�Ҽ�-����-ϵͳ-��ϵͳ-����̨
	in_data = audioread(filepath, fs, disp_flag);	// �����źŵĶ�ȡ

	in_array = std::get<0>(in_data);	// ��Ƶ����
	fs = std::get<1>(in_data);			// ����Ƶ��

	cout << "fs = " << fs << endl;

	// audioplot(in_array);

	return 0;
}

