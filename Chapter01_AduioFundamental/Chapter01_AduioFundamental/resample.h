/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����resample.h
// �ļ����������������źŵ��ز���
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/14
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/
#pragma once

#include <vector>
#include <numeric>
#include <iostream>
#include "spline.h"
using namespace std;
using namespace SplineSpace;

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
std::vector<double> resample(vector<double> in_array, int target_fs, int source_fs);