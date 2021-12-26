#pragma once
/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����stfms.h
// �ļ����������������źŵĶ�ʱ����Ҷ�任
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/25
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/

#include <vector>
#include <tuple>
#include <iostream>
#include <complex>
#include "universal.h"
#include "fftw3.h"		// ���ã�https://blog.csdn.net/Aubrey_yt/article/details/102974019 , ����dll�ļ�Ҳ��Ҫ�ƶ�������Ŀ¼��	
#include <windows.h>
using namespace std;

/*-----------------------------------------------------------------
// ���룺��Ҫ���ж�ʱ����Ҷ�任���ź�in_array��������win���������˱任����nfft(>=����������)��֡��inc
// �������ʱ����Ҷ�任�����ʵ�����鲿��(nfft/2+1) x ֡��
// ���������������źŵĶ�ʱ��ʱ����Ҷ�任
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/26
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
vector<vector <complex<double> > >stftms(vector<double>in_array, vector<double>win, int nfft, int inc);