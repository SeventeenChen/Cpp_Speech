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
// �����汾��VS2015
//----------------------------------------------------------------*/
#pragma once

#include <vector>
#include <iostream>
using namespace std;

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
std::vector<double> xcorr(vector<double>in_array_1, vector<double>in_array_2);