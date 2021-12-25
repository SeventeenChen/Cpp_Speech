/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����stfms.cpp
// �ļ����������������źŵĶ�ʱ����Ҷ�任
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/25
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/

#include "stftms.h"

/*-----------------------------------------------------------------
// ���룺��Ҫ���ж�ʱ����Ҷ�任���ź�in_array��������win���������˱任����nfft(>=����������)��֡��inc
// �������ʱ����Ҷ�任���飺(nfft/2+1) x ֡��
// ���������������źŵĶ�ʱ��ʱ����Ҷ�任
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/25
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
vector<vector<double> >stftms(vector<double>in_array, vector<double>win, int nfft, int inc)
{
	int inlen = 0, wlen = 0, frame_num = 0; // �����źų���, ���������ȣ�֡����ʼ��
	int i = 0, j = 0;	// ��ʼ��ѭ������
	inlen = in_array.size();	// �����źų���
	wlen = win.size();			// ����������
	frame_num = 1 + (inlen-wlen)/inc;	// ֡��
	vector<vector<double> >frame_signal(frame_num, vector<double>(wlen));	// ��ʼ����֡������
	vector<vector<double> >d(frame_num, vector<double>((1 + nfft / 2)));	// ��ʼ���������
	frame_signal = enframe(in_array, win, inc);	// ��֡������
	vector<double> one_frame(wlen);
	for (i = 0; i < frame_num; i++)
	{
		
	}
}