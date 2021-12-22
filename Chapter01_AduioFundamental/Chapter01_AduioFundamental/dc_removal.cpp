//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：dc_removal.cpp
// 文件功能描述：语音信号的直流分量消除
// 创建者：SeventeenChen
// 时间：2021/12/22
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------

#include "dc_removal.h"

/*-----------------------------------------------------------------
// 输入：音频数据（vector）
// 输出：消除直流分量后音频数据（vector）
// 功能描述：对音频数据统一消除直流偏置
// 作者：SeventeenChen
// 日期：2021/12/22
// 修改人：
// 记录：
// 日期：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::vector<double> dc_removal(vector<double> in_array)
{
	double average = 0;			// 平均数
	int n = in_array.size();	// 数组大小
	std::vector<double> out_array(n);
	for (int i = 0; i < n; i++)
	{
		average += in_array[i];
	}
	average /= n;
	for (int i = 0; i < n; i++)
	{
		out_array[i] = in_array[i] - average;
	}
	return out_array;
}