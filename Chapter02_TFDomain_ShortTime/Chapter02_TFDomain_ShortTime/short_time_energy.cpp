/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����short_time_energy.cpp
// �ļ����������������źŵĶ�ʱ����
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/21
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/
#include "short_time_energy.h"

/*-----------------------------------------------------------------
// ���룺�����ź�in_array��������win��֡��frame_shift
// �����ÿ֡��ʱ������֡�� x 1
// �������������������źŵĶ�ʱ����
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/18
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
vector<double> energy(vector<double> in_array, vector<double> win, int frame_shift)
{
	int wlen = win.size();	// ����
	int frame_num = (in_array.size() - wlen + frame_shift) / frame_shift;	// ֡��
	vector<vector<double> >frame_signal(frame_num, vector<double>(wlen));	// ��֡������
	frame_signal = enframe(in_array, win, frame_shift);	// ��֡
	vector<double> En(frame_num);
	for (int i = 0; i < frame_num; i++)
	{
		for (int j = 0; j < wlen; j++)
		{
			En[i] += frame_signal[i][j] * frame_signal[i][j];
		}
	}

	return En;
}