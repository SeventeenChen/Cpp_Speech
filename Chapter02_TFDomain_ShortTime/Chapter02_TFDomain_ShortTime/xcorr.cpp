/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����xcorr.cpp
// �ļ����������������źŵĻ����
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/23
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/

#include "xcorr.h"

/*-----------------------------------------------------------------
// ���룺�������ȴ���1��һά����
// ������źŵĻ���أ�size: 2 *M - 1����MΪ�����ź�������ά�����ֵ
// ���������������źŵĻ����
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/23
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
std::vector<double> xcorr(vector<double>in_array_1, vector<double>in_array_2)
{
	int n1 = 0, n2 = 0, M = 0;
	n1 = in_array_1.size();	// ��һ�������ά��
	n2 = in_array_2.size();	// �ڶ��������ά��
	int i = 0, j = 0;	// ѭ���������ӳ�ʼ��
	if (n1 >= n2)	// Ѱ����������ά�����ֵ
	{
		M = n1;
	}
	else
	{
		M = n2;
	}
	vector<double> temp_arr1(M), temp_arr2(M);	// ��ʼ�����������
	copy(in_array_1.begin(), in_array_1.end(), temp_arr1.begin());
	copy(in_array_2.begin(), in_array_2.end(), temp_arr2.begin());
	vector<double> corr(2 * M - 1);		// ��ʼ�����������
	vector<double> corr_shift(2 * M - 1);		// ��ʼ�����������
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M - i; j++)
		{
			corr[i] += temp_arr1[j] * temp_arr2[j + i];	
		}
		corr[i] /= corr[0];		// ���ֵ��һ��
		corr[2 * M - 2 -i] = corr[i];
	}
	
	for (i = 0; i < M; i++)			// ���ֵ�Ƶ��м䣬�Գ�
	{
		corr_shift[i] = corr[M - 1 - i];
		corr_shift[2 * M - 2 - i] = corr_shift[i];
	}
	return corr_shift;
}