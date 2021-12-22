//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����dc_removal.cpp
// �ļ����������������źŵ�ֱ����������
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/22
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------

#include "dc_removal.h"

/*-----------------------------------------------------------------
// ���룺��Ƶ���ݣ�vector��
// ���������ֱ����������Ƶ���ݣ�vector��
// ��������������Ƶ����ͳһ����ֱ��ƫ��
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/22
// �޸��ˣ�
// ��¼��
// ���ڣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
std::vector<double> dc_removal(vector<double> in_array)
{
	double average = 0;			// ƽ����
	int n = in_array.size();	// �����С
	std::vector<double> out_array(n);
	for (int i = 0; i < n; i++)
	{
		average += in_array[i];
	}
	average /= n;
	for (int i = 0; i < n; i++)
	{
		out_array[i] = in_array[i] - average;
	}
	return out_array;
}