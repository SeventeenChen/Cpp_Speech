/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����resample.cpp
// �ļ����������������źŵ��ز���
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/11
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/

#include "resample.h"

/*-----------------------------------------------------------------
// ���룺���ز����źţ�һά���� vector����Ŀ������ʣ�ԭʼ������
// ������ز������źţ�һά���� vector��
// ����������һά�źŵ��ز���
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/11
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �汾��
-----------------------------------------------------------------*/
std::vector<double> resample(vector<double> in_array, int target_fs, int source_fs)
{
	int source_len, target_len;
	double duration;	// ����ʱ����ʼ�����룩
	double resample_stepsize = (double) source_fs / target_fs;	// �ز��������Ա�������
	double leftBound = 0, rightBound = 0;	//�߽絼��

	source_len = in_array.size();		// ��֪���г���
	std::vector<double> source_x(source_len);	// ��֪�����Ա�����ʼ��
	std::iota(source_x.begin(), source_x.end(), 0);	// ��������
	// vector ---> array
	double *x0 = new double[source_len];	// ��֪�����Ա��������ʼ��
	if (!source_x.empty())
	{
		memcpy(x0, &source_x[0], source_len * sizeof(double));	// ��ֵ
	}
	double *y0 = new double[source_len];	// ��֪��������������ʼ��
	if (!in_array.empty())
	{
		memcpy(y0, &in_array[0], source_len * sizeof(double));
	}
	Spline sp(x0, y0, source_len, GivenSecondOrder, leftBound, rightBound);
	duration = double(source_len) / source_fs;
	target_len = floor(duration * target_fs);	// �ز��������г���
	std::vector<double> target_x(target_len);	// ��ʼ���ز����������Ա���
	std::vector<double> target_y(target_len);	// ��ʼ���ز����������Ա���
	std::iota(target_x.begin(), target_x.end(), 0);	// ��������
	double *x = new double[target_len];	// �ز����������Ա��������ʼ��
	double *y = new double[target_len];	// �ز�������������������ʼ��
	if (!target_x.empty())
	{
		memcpy(x, &target_x[0], target_len * sizeof(double));	// �ز��������Ա�������
	}
	for (int i = 0; i < target_len; i++)
	{
		x[i] *= resample_stepsize;		// ʵ���ز����Ա�������
		if (x[i] > x0[source_len - 1])
		{
			x[i] = x0[source_len - 1];
		}
	}
	if (!target_y.empty())
	{
		memcpy(y, &target_y[0], target_len * sizeof(double));
	}

	sp.MultiPointInterp(x, target_len, y);			//��ֵ���

	vector<double> target_vec (y, y + target_len);

	return target_vec;
}

