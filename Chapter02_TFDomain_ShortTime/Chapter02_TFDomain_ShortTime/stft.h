/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：stft.h
// 文件功能描述：语音信号的短时傅里叶变换
// 创建者：SeventeenChen
// 时间：2021/12/29
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#pragma once

#include <vector>
#include <ccomplex>
#include <iostream>
#include "FFT.h"
#include "universal.h"

using namespace std;

vector<vector <complex<double> > >stft(vector<double>in_array, vector<double>win, int nfft, int inc);
