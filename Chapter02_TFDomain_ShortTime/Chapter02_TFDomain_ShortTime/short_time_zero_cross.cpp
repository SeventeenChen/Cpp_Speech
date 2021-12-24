/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����short_time_zero_cross.cpp
// �ļ����������������źŵĶ�ʱƽ��������
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/22
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/
#include "short_time_zero_cross.h"

/*-----------------------------------------------------------------
// ���룺�����ź�in_array��������win��֡��frame_shift
// �����ÿ֡��ʱ�����ʣ�֡�� x 1
// �������������������źŵĶ�ʱ������
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/18
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
std::vector<double>zero_cross(vector<double> in_array, vector<double> win, int frame_shift)
{
	int i = 0, j = 0;
	int n = in_array.size();
	int wlen = win.size();	// ����
	int frame_num = (in_array.size() - wlen + frame_shift) / frame_shift;	// ֡��
	vector<double> zcr(frame_num);
	vector<double> dc_remove_array(n);	// ��ʼ��ȥֱ������
	dc_remove_array = dc_removal(in_array);		// ȥֱ��
	vector<vector<double> >frame_signal(frame_num, vector<double>(wlen));	// ��ʼ����֡������
	frame_signal = enframe(dc_remove_array, win, frame_shift);	// ��֡
	for (i = 0; i < frame_num; i++)
	{
		for (j = 0; j < wlen - 1; j++)
		{
			if (frame_signal[i][j] * frame_signal[i][j + 1] < 0)
			{
				zcr[i] += 1;		// ͳ��ÿ֡�������
			}
		}
	}
	for (i = 0; i < frame_num; i++)
	{
		zcr[i] /= wlen;			// ����ƽ��������
	}
	return zcr;
}
