/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����short_time_zero_cross.h
// �ļ����������������źŵĶ�ʱƽ��������
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/22
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/
#pragma once
#include <vector>
#include <iostream>
#include "universal.h"
using namespace std;

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
std::vector<double>zero_cross(vector<double> in_array, vector<double> win, int frame_shift);
