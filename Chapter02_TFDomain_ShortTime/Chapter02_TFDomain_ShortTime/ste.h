/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����short_time_energy.h
// �ļ����������������źŵĶ�ʱ����
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/21
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/
#pragma once
#include <vector>
#include <iostream>
#include "universal.h"
// #include "../../Chapter01_AduioFundamental/Chapter01_AduioFundamental/enframe.h"
using namespace std;

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
vector<double> energy(vector<double> in_array, vector<double> win, int frame_shift);