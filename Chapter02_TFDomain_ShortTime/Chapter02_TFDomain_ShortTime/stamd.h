/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����stamd.h
// �ļ����������������źŵĶ�ʱƽ�����Ȳ�
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/24
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/
#pragma once

#pragma once
#include <vector>
#include <cmath>
#include <limits>
#include <type_traits>
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef EPS
#define EPS std::numeric_limits<double>::epsilon()
#endif

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
vector<double>amdf(vector<double> in_array);