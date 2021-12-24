/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����stamd.cpp
// �ļ����������������źŵĶ�ʱƽ�����Ȳ�
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/24
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// �����汾��VS2015
//----------------------------------------------------------------*/

#include "stamd.h"

/*-----------------------------------------------------------------
// ���룺һ֡�źţ�һά���飩
// ������źŵĶ�ʱƽ�����Ȳά�����ź�ά�����
// ���������������źŵĶ�ʱƽ�����Ȳ�
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/24
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
vector<double>amdf(vector<double> in_array)
{
	int wlen = 0;	// ��ʼ������
	int i = 0, j = 0;	// ��ʼ��ѭ������
	wlen = in_array.size();
	vector<double> amd(wlen);
	for (i = 0; i < wlen; i++)
	{
		for (j = 0; j < wlen - i; j++)
		{
			amd[i] += std::abs(in_array[j+i] - in_array[j]);
		}
	}
	int max = amd[0];	// ��ʼ���������ֵ
	for (int i = 1; i < wlen; i++)
	{
		if (amd[i] > max)
		{
			max = amd[i];
		}
	}
	for (int i = 1; i < wlen; i++)	
	{
		amd[i] /= (max + EPS);		// ���ֵ��һ��
	}
	return amd;
}