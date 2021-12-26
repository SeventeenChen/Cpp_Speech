#pragma once
/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：stfms.h
// 文件功能描述：语音信号的短时傅里叶变换
// 创建者：SeventeenChen
// 时间：2021/12/25
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#include <vector>
#include <tuple>
#include <iostream>
#include <complex>
#include "universal.h"
#include "fftw3.h"		// 配置：https://blog.csdn.net/Aubrey_yt/article/details/102974019 , 三个dll文件也需要移动到代码目录下	
#include <windows.h>
using namespace std;

/*-----------------------------------------------------------------
// 输入：需要进行短时傅里叶变换的信号in_array，窗函数win，弗里有人变换窗长nfft(>=窗函数长度)，帧移inc
// 输出：短时傅里叶变换数组的实部和虚部：(nfft/2+1) x 帧数
// 功能描述：语音信号的短时短时傅里叶变换
// 作者：SeventeenChen
// 日期：2021/12/26
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
vector<vector <complex<double> > >stftms(vector<double>in_array, vector<double>win, int nfft, int inc);