#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#ifndef _pi_
#define _pi_  3.1415926535898
#endif


/*-----------------------------------------------------------------
// ���룺�����ź�in_array��������win��֡��frame_shift
// �������֡�����飬֡�� x ֡��
// ������������֡
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/09
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
std::vector<vector<double> > enframe(vector<double> in_array, vector<double> win, int frame_shift);

/*-----------------------------------------------------------------
// ���룺������int���������ͣ�����"default"/����"hamming"/����"hanning"
// �������������vector��
// ������������������ֵ
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/09
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
std::vector<double> window(int window_length, string window_type);