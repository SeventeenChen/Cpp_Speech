#pragma once
#include <vector>
#include <iostream>
#include "../../Chapter01_AduioFundamental/Chapter01_AduioFundamental/enframe.h"
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