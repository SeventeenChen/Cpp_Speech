/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：xcorr.cpp
// 文件功能描述：语音信号的互相关
// 创建者：SeventeenChen
// 时间：2021/12/23
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#include "xcorr.h"

/*-----------------------------------------------------------------
// 输入：两个长度大于1的一维数组
// 输出：信号的互相关（size: 2 *M - 1），M为输入信号中数组维度最大值
// 功能描述：计算信号的互相关
// 作者：SeventeenChen
// 日期：2021/12/23
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::vector<double> xcorr(vector<double>in_array_1, vector<double>in_array_2)
{
	int n1 = 0, n2 = 0, M = 0;
	n1 = in_array_1.size();	// 第一个数组的维度
	n2 = in_array_2.size();	// 第二个数组的维度
	int i = 0, j = 0;	// 循环计数因子初始化
	if (n1 >= n2)	// 寻找输入数组维度最大值
	{
		M = n1;
	}
	else
	{
		M = n2;
	}
	vector<double> temp_arr1(M), temp_arr2(M);	// 初始化补零后数组
	copy(in_array_1.begin(), in_array_1.end(), temp_arr1.begin());
	copy(in_array_2.begin(), in_array_2.end(), temp_arr2.begin());
	vector<double> corr(2 * M - 1);		// 初始化互相关数组
	vector<double> corr_shift(2 * M - 1);		// 初始化互相关数组
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M - i; j++)
		{
			corr[i] += temp_arr1[j] * temp_arr2[j + i];	
		}
		corr[i] /= corr[0];		// 最大值归一化
		corr[2 * M - 2 -i] = corr[i];
	}
	
	for (i = 0; i < M; i++)			// 最大值移到中间，对称
	{
		corr_shift[i] = corr[M - 1 - i];
		corr_shift[2 * M - 2 - i] = corr_shift[i];
	}
	return corr_shift;
}