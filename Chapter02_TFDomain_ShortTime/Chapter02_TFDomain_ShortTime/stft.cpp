/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：stft.cpp
// 文件功能描述：语音信号的短时傅里叶变换
// 创建者：SeventeenChen
// 时间：2021/12/29
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#include "stft.h"

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
vector<vector <complex<double> > >stft(vector<double>in_array, vector<double>win, int nfft, int inc)
{
	int inlen = 0, wlen = 0, frame_num = 0; // 输入信号长度, 窗函数长度，帧数初始化
	int i = 0, j = 0, k = 0;	// 初始化循环因子
	inlen = in_array.size();	// 输入信号长度
	wlen = win.size();			// 窗函数长度
	frame_num = 1 + (inlen - wlen) / inc;	// 帧数
	vector<vector<double> >frame_signal(frame_num, vector<double>(wlen));	// 初始化分帧后数组
	vector<vector <complex<double> > >d(frame_num, vector<complex<double> >((1 + nfft / 2)));	// 初始化输出数组
	frame_signal = enframe(in_array, win, inc);	// 分帧后数据
	Complex* inarr = new Complex[nfft];
	Complex* outarr = new Complex[nfft];
	for (k = 0; k < frame_num; k++)
	{
		for (i = 0; i < nfft; i++)
		{
			if (i < wlen)
			{
				inarr[i].real = frame_signal[k][i];
				inarr[i].imag = 0.0;
			}
			else
			{
				inarr[i].real = 0.0;
				inarr[i].imag = 0.0;
			}
		}
		int r = log2(nfft);
		FFT(inarr, outarr, r);
		for (j = 0; j < 1 + nfft / 2; j++)
		{
			d[k][j] = complex<double>(outarr[j].real, outarr[j].imag);
		}
	}

	return d;
}
