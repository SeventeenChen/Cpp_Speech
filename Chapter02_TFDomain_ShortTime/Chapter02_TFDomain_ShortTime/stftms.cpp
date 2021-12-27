/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：stfms.cpp
// 文件功能描述：语音信号的短时傅里叶变换
// 创建者：SeventeenChen
// 时间：2021/12/25
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#include "stftms.h"

/*-----------------------------------------------------------------
// 输入：需要进行短时傅里叶变换的信号in_array，窗函数win，弗里有人变换窗长nfft(>=窗函数长度)，帧移inc
// 输出：短时傅里叶变换数组的实部和虚部：(nfft/2+1) x 帧数
// 功能描述：语音信号的短时短时傅里叶变换
// 作者：SeventeenChen
// 日期：2021/12/25
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
vector<vector <complex<double> > >stftms(vector<double>in_array, vector<double>win, int nfft, int inc)
{
	int inlen = 0, wlen = 0, frame_num = 0; // 输入信号长度, 窗函数长度，帧数初始化
	int i = 0, j = 0, k = 0;	// 初始化循环因子
	inlen = in_array.size();	// 输入信号长度
	wlen = win.size();			// 窗函数长度
	frame_num = 1 + (inlen-wlen)/inc;	// 帧数
	vector<vector<double> >frame_signal(frame_num, vector<double>(wlen));	// 初始化分帧后数组
	vector<vector <complex<double> > >d(frame_num, vector<complex<double> >((1 + nfft / 2)));	// 初始化输出数组
	frame_signal = enframe(in_array, win, inc);	// 分帧后数据
	fftw_complex *in, *out;
	fftw_plan p;
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nfft);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nfft);
	for (k = 0; k < frame_num; k++)
	{
		for (i = 0; i < nfft; i++)
		{
			if (i < wlen)
			{
				in[i][0] = frame_signal[k][i];
				in[i][1] = 0.0;
			}
			else
			{
				in[i][0] = 0.0;
				in[i][1] = 0.0;
			}
		}
		p = fftw_plan_dft_1d(nfft, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
		fftw_execute(p); // repeat as needed
		for (j = 0; j < 1 + nfft / 2; j++)
		{
			d[k][j] = complex<double>(out[j][0], out[j][1]);
		}
	}
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);

	return d;
}

