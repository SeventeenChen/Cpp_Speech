/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：stpsd.cpp
// 文件功能描述：语音信号的短时功率谱密度
// 创建者：SeventeenChen
// 时间：2022/01/06
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#include "stpsd.h"

/*-----------------------------------------------------------------
// 输入：语音信号in_array，窗函数win，傅里叶变换点数nfft，帧移inc
// 输出：短时功率谱密度
// 功能描述：短时功率谱密度的周期图法：短时傅里叶变换后求每帧的功率除以每帧点数
// 作者：SeventeenChen
// 日期：2021/01/06
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
vector<vector <double> > periodogramPSE(vector<double>in_array, vector<double>win, int nfft, int inc)
{
	int wlen = win.size();	// 窗长
	int frame_num = (in_array.size() - wlen + inc) / inc;	// 帧数
	vector<vector <complex<double> > >d(frame_num, vector<complex<double> >((1 + nfft / 2)));	// 初始化stft数组
	vector<vector <double> >psd(frame_num, vector<double>((1 + nfft / 2)));	// 初始化psd数组
	d = stft(in_array, win, nfft, inc);		// stft数组：帧数 x 窗长（复数）
	int i = 0, j = 0;	// 初始化循环因子
	for (i = 0; i < frame_num; i++)
	{
		for (j = 0; j < wlen; j++)
		{
			psd[i][j] = abs(d[i][j]) * abs(d[i][j]) / wlen;
		}
	}
	
	return psd;
}