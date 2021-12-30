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

/*-----------------------------------------------------------------
// 输入：语音信号in_array，窗函数win，傅里叶变换点数nfft，帧移inc
// 输出：短时傅里叶变换 帧数 x （1 + nfft/2）
// 功能描述：语音信号的短时傅里叶变换
// 作者：SeventeenChen
// 日期：2021/12/30
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
vector<vector <complex<double> > >stft(vector<double>in_array, vector<double>win, int nfft, int inc);
