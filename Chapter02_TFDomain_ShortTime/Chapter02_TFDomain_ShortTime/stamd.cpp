/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：stamd.cpp
// 文件功能描述：语音信号的短时平均幅度差
// 创建者：SeventeenChen
// 时间：2021/12/24
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#include "stamd.h"

/*-----------------------------------------------------------------
// 输入：一帧信号（一维数组）
// 输出：信号的短时平均幅度差，维度与信号维度相等
// 功能描述：计算信号的短时平均幅度差
// 作者：SeventeenChen
// 日期：2021/12/24
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
vector<double>amdf(vector<double> in_array)
{
	int wlen = 0;	// 初始化窗长
	int i = 0, j = 0;	// 初始化循环因子
	wlen = in_array.size();
	vector<double> amd(wlen);
	for (i = 0; i < wlen; i++)
	{
		for (j = 0; j < wlen - i; j++)
		{
			amd[i] += std::abs(in_array[j+i] - in_array[j]);
		}
	}
	int max = amd[0];	// 初始化数组最大值
	for (int i = 1; i < wlen; i++)
	{
		if (amd[i] > max)
		{
			max = amd[i];
		}
	}
	for (int i = 1; i < wlen; i++)	
	{
		amd[i] /= (max + EPS);		// 最大值归一化
	}
	return amd;
}