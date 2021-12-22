/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：short_time_energy.cpp
// 文件功能描述：语音信号的短时能量
// 创建者：SeventeenChen
// 时间：2021/12/21
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#include "short_time_energy.h"

/*-----------------------------------------------------------------
// 输入：语音信号in_array，窗函数win，帧移frame_shift
// 输出：每帧短时能量：帧数 x 1
// 功能描述：计算语音信号的短时能量
// 作者：SeventeenChen
// 日期：2021/12/18
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
vector<double> energy(vector<double> in_array, vector<double> win, int frame_shift)
{
	int wlen = win.size();	// 窗长
	int frame_num = (in_array.size() - wlen + frame_shift) / frame_shift;	// 帧数
	vector<vector<double> >frame_signal(frame_num, vector<double>(wlen));	// 分帧后数据
	frame_signal = enframe(in_array, win, frame_shift);	// 分帧
	vector<double> En(frame_num);
	for (int i = 0; i < frame_num; i++)
	{
		for (int j = 0; j < wlen; j++)
		{
			En[i] += frame_signal[i][j] * frame_signal[i][j];
		}
	}

	return En;
}