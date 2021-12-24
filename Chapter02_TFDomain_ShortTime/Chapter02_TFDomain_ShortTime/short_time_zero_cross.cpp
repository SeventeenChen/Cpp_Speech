/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：short_time_zero_cross.cpp
// 文件功能描述：语音信号的短时平均过零率
// 创建者：SeventeenChen
// 时间：2021/12/22
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#include "short_time_zero_cross.h"

/*-----------------------------------------------------------------
// 输入：语音信号in_array，窗函数win，帧移frame_shift
// 输出：每帧短时过零率：帧数 x 1
// 功能描述：计算语音信号的短时过零率
// 作者：SeventeenChen
// 日期：2021/12/18
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::vector<double>zero_cross(vector<double> in_array, vector<double> win, int frame_shift)
{
	int i = 0, j = 0;
	int n = in_array.size();
	int wlen = win.size();	// 窗长
	int frame_num = (in_array.size() - wlen + frame_shift) / frame_shift;	// 帧数
	vector<double> zcr(frame_num);
	vector<double> dc_remove_array(n);	// 初始化去直流数组
	dc_remove_array = dc_removal(in_array);		// 去直流
	vector<vector<double> >frame_signal(frame_num, vector<double>(wlen));	// 初始化分帧后数组
	frame_signal = enframe(dc_remove_array, win, frame_shift);	// 分帧
	for (i = 0; i < frame_num; i++)
	{
		for (j = 0; j < wlen - 1; j++)
		{
			if (frame_signal[i][j] * frame_signal[i][j + 1] < 0)
			{
				zcr[i] += 1;		// 统计每帧过零点数
			}
		}
	}
	for (i = 0; i < frame_num; i++)
	{
		zcr[i] /= wlen;			// 计算平均过零率
	}
	return zcr;
}
